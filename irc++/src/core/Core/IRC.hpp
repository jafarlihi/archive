#pragma once

#include <deque>
#include <functional>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/fiber/all.hpp>
#include <boost/lexical_cast.hpp>

namespace IRC {
struct Settings {
  std::string host;
  int port;
  std::string nick;
};

class Client {
public:
  using message_handler =
      std::function<void(std::string_view, std::string_view, std::string_view)>;

  Client(const std::shared_ptr<boost::asio::io_context> &ctx, Settings settings,
         std::shared_ptr<boost::fibers::buffered_channel<std::string>> channel,
         std::shared_ptr<boost::fibers::buffered_channel<std::string>> send_channel);

  void join(std::string_view channel_);
  void say(std::string_view receiver, std::string_view message);
  void send_line(std::string data);
  auto const &get_settings() const { return settings; }

private:
  void connect();
  void identify();
  void on_hostname_resolved(
      boost::system::error_code const &error,
      const boost::asio::ip::tcp::resolver::results_type &results);
  void on_connected(boost::system::error_code const &error);
  void await_new_line();
  void on_new_line(std::string const &line);
  void send_raw();
  void handle_write(boost::system::error_code const &error,
                    std::size_t bytes_read);

  std::shared_ptr<boost::asio::io_context> ctx;
  Settings settings;
  boost::asio::ip::tcp::socket socket;
  boost::asio::streambuf in_buf;
  std::unordered_map<std::string, std::vector<message_handler>> handlers;
  std::vector<std::function<void()>> on_connect_handlers;
  std::deque<std::string> to_write;
  std::shared_ptr<boost::fibers::buffered_channel<std::string>> channel;
  std::shared_ptr<boost::fibers::buffered_channel<std::string>> send_channel;
};
} // namespace IRC
