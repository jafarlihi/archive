#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>

#include "IRC.hpp"

namespace IRC {
Client::Client(
    const std::shared_ptr<boost::asio::io_context> &ctx_, Settings settings_,
    std::shared_ptr<boost::fibers::buffered_channel<std::string>> channel_,
    std::shared_ptr<boost::fibers::buffered_channel<std::string>> send_channel_)
    : ctx{ctx_}, settings{std::move(settings_)}, socket{*ctx_},
      channel{std::move(channel_)}, send_channel{std::move(send_channel_)} {
  connect();
}

void Client::join(std::string_view channel_) {
  std::stringstream msg;
  msg << "JOIN " << channel_;
  send_line(msg.str());
}

void Client::say(std::string_view receiver, std::string_view message) {
  std::stringstream msg;
  msg << "PRIVMSG " << receiver << " :" << message;
  send_line(msg.str());
}

void Client::send_line(std::string data) {
  data += "\r\n";
  to_write.push_back(std::move(data));
  if (to_write.size() == 1) {
    send_raw();
  }
}

void Client::connect() {
  socket.close();
  boost::asio::ip::tcp::resolver resolver(*ctx);
  auto handler = [this](auto &&...params) {
    on_hostname_resolved(std::forward<decltype(params)>(params)...);
  };

  resolver.async_resolve(settings.host, std::to_string(settings.port), handler);
}

void Client::identify() {
  std::stringstream msg;
  msg << "USER " << settings.nick
      << " "
         "foo bar :"
      << settings.nick;
  send_line(msg.str());
  msg.str("");
  msg << "NICK " << settings.nick;
  send_line(msg.str());
}

void Client::on_hostname_resolved(
    boost::system::error_code const &error,
    const boost::asio::ip::tcp::resolver::results_type &results) {
  if (error) {
    connect();
    return;
  }
  if (results.empty()) {
    std::stringstream msg;
    msg << "Failed to resolve '" << settings.host << "'";
    throw std::runtime_error(msg.str());
  }
  auto handler = [this](auto const &error_) { on_connected(error_); };
  socket.async_connect(*results, handler);
}

void Client::on_connected(boost::system::error_code const &error) {
  if (error) {
    connect();
    return;
  }
  identify();
  await_new_line();
  auto send_thread = std::thread([this] {
    std::string str;
    while (boost::fibers::channel_op_status::success ==
           this->send_channel->pop(str)) {
      this->send_line(str);
    }
  });
  send_thread.detach();
}

// NOLINTNEXTLINE(misc-no-recursion)
void Client::await_new_line() {
  auto handler =
      // NOLINTNEXTLINE(misc-no-recursion)
      [this](auto const &error, std::size_t /*size*/) {
        if (error) {
          connect();
          return;
        }
        std::istream istream{&in_buf};
        std::string line;
        std::getline(istream, line);
        on_new_line(line);
        await_new_line();
      };
  boost::asio::async_read_until(socket, in_buf, "\r\n", handler);
}

void Client::on_new_line(std::string const &line) { this->channel->push(line); }

void Client::send_raw() {
  if (to_write.empty()) {
    return;
  }

  socket.async_send(
      boost::asio::buffer(to_write.front().data(), to_write.front().size()),
      [this](auto &&...params) { handle_write(params...); });
}

void Client::handle_write(boost::system::error_code const &error,
                          std::size_t bytes_read) {
  if (error) {
    std::cerr << "Error: " << error << std::endl;
    return;
  }
  const long to_erase =
      static_cast<long>(std::min(bytes_read, to_write.front().size()));
  auto &buf = to_write.front();
  buf.erase(buf.begin(), buf.begin() + to_erase);
  if (buf.empty()) {
    to_write.erase(to_write.begin());
  }
  if (!to_write.empty()) {
    send_raw();
  }
}
} // namespace IRC
