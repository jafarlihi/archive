#include "Application.hpp"

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer.h>
#include <boost/asio.hpp>
#include <boost/fiber/buffered_channel.hpp>
#include <imgui.h>

#include "Core/DPIHandler.hpp"
#include "Core/Debug/Instrumentor.hpp"
#include "Core/IRC.hpp"
#include "Core/Resources.hpp"
#include "Core/imgui_stdlib.hpp"
#include "Settings/Project.hpp"

namespace App {
class ClientUIState {
public:
  ClientUIState(
      bool show_panel_,
      std::shared_ptr<boost::fibers::buffered_channel<std::string>> channel_,
      std::shared_ptr<boost::fibers::buffered_channel<std::string>> send_channel_)
      : show_panel(show_panel_), channel(std::move(channel_)), send_channel(std::move(send_channel_)) {}
  bool show_panel;
  std::string input;
  std::shared_ptr<boost::fibers::buffered_channel<std::string>> channel;
  std::shared_ptr<boost::fibers::buffered_channel<std::string>> send_channel;
  std::string buffer;
};

class UIState {
public:
  std::string connect_input;
  std::vector<std::pair<IRC::Client *, ClientUIState>> clients;
};

Application::Application(const std::string &title) {
  APP_PROFILE_FUNCTION();

  const unsigned int init_flags{SDL_INIT_VIDEO | SDL_INIT_TIMER |
                                SDL_INIT_GAMECONTROLLER};
  if (SDL_Init(init_flags) != 0) {
    APP_ERROR("Error: %s\n", SDL_GetError());
    m_exit_status = ExitStatus::FAILURE;
  }

  m_window = std::make_unique<Window>(Window::Settings{title});
}

Application::~Application() {
  APP_PROFILE_FUNCTION();
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_Quit();
}

void connect_to_server(UIState &state, const std::string &address) {
  auto io = std::make_shared<boost::asio::io_context>();
  const IRC::Settings settings{address, 6667, "newIrcClientTest"};
  auto channel =
      std::make_shared<boost::fibers::buffered_channel<std::string>>(256);
  auto send_channel =
      std::make_shared<boost::fibers::buffered_channel<std::string>>(32);
  auto *irc = new IRC::Client(io, settings, channel, send_channel);
  state.clients.emplace_back(irc, ClientUIState(true, channel, send_channel));
  auto *client = &state.clients.back();

  std::thread buffer_thread([channel, client] {
    std::string str;
    while (boost::fibers::channel_op_status::success == channel->pop(str)) {
      client->second.buffer.append("\n" + str);
    }
  });
  std::thread io_thread([io] { io->run(); });
  buffer_thread.detach();
  io_thread.detach();
}

ExitStatus App::Application::run() {
  APP_PROFILE_FUNCTION();

  if (m_exit_status == ExitStatus::FAILURE) {
    return m_exit_status;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io{ImGui::GetIO()};

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard |
                    ImGuiConfigFlags_DockingEnable |
                    ImGuiConfigFlags_ViewportsEnable;

  const std::string user_config_path{
      SDL_GetPrefPath(COMPANY_NAMESPACE.c_str(), APP_NAME.c_str())};
  APP_DEBUG("User config path: {}", user_config_path);

  // Absolute imgui.ini path to preserve settings independent of app location.
  static const std::string imgui_ini_filename{user_config_path + "imgui.ini"};
  io.IniFilename = imgui_ini_filename.c_str();

  // ImGUI font
  const float font_scaling_factor{DPIHandler::get_scale()};
  const float font_size{18.0F * font_scaling_factor};
  const std::string font_path{
      Resources::font_path("Manrope.ttf").generic_string()};

  io.Fonts->AddFontFromFileTTF(font_path.c_str(), font_size);
  io.FontDefault = io.Fonts->AddFontFromFileTTF(font_path.c_str(), font_size);
  DPIHandler::set_global_font_scaling(&io);

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(m_window->get_native_window(),
                                    m_window->get_native_renderer());
  ImGui_ImplSDLRenderer_Init(m_window->get_native_renderer());

  UIState state = UIState();

  m_running = true;
  while (m_running) {
    APP_PROFILE_SCOPE("MainLoop");

    SDL_Event event{};
    while (SDL_PollEvent(&event) == 1) {
      APP_PROFILE_SCOPE("EventPolling");

      ImGui_ImplSDL2_ProcessEvent(&event);

      if (event.type == SDL_QUIT) {
        stop();
      }

      if (event.type == SDL_WINDOWEVENT &&
          event.window.windowID ==
              SDL_GetWindowID(m_window->get_native_window())) {
        on_event(event.window);
      }
    }

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (!m_minimized) {
      ImGui::DockSpaceOverViewport();

      if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
          if (ImGui::MenuItem("Exit", "Cmd+Q")) {
            stop();
          }
          ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
          ImGui::MenuItem("Some Panel", nullptr, &m_show_some_panel);
          ImGui::MenuItem("Debug Panel", nullptr, &m_show_debug_panel);
          for (auto &client : state.clients) {
            ImGui::MenuItem(client.first->get_settings().host.c_str(), nullptr,
                            &client.second.show_panel);
          }
          ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
      }

      for (auto &client : state.clients) {
        if (client.second.show_panel) {
          ImGui::Begin(client.first->get_settings().host.c_str(),
                       &client.second.show_panel);
          ImGui::TextWrapped("%s", client.second.buffer.c_str());
          ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
          if (ImGui::InputText("##", &client.second.input,
                               ImGuiInputTextFlags_EnterReturnsTrue)) {
            client.second.send_channel->push(client.second.input);
            client.second.input = "";
          }
          if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0F);
          }
          ImGui::End();
        }
      }

      // Whatever GUI to implement here ...
      if (m_show_some_panel) {
        ImGui::Begin("Some panel", &m_show_some_panel);
        ImGui::InputText("Address", &state.connect_input);
        if (ImGui::Button("Connect")) {
          connect_to_server(state, state.connect_input);
        }
        ImGui::End();
      }

      // Debug panel
      if (m_show_debug_panel) {
        ImGui::Begin("Debug panel", &m_show_debug_panel);
        ImGui::Text("User config path: %s", user_config_path.c_str());
        ImGui::Separator();
        ImGui::Text("Font path: %s", font_path.c_str());
        ImGui::Text("Font size: %f", font_size);
        ImGui::Text("Global font scaling %f", io.FontGlobalScale);
        ImGui::Text("UI scaling factor: %f", font_scaling_factor);
        ImGui::End();
      }
    }

    // Rendering
    ImGui::Render();

    SDL_SetRenderDrawColor(m_window->get_native_renderer(), 100, 100, 100, 255);
    SDL_RenderClear(m_window->get_native_renderer());
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(m_window->get_native_renderer());
  }

  return m_exit_status;
}

void App::Application::stop() { m_running = false; }

void Application::on_event(const SDL_WindowEvent &event) {
  switch (event.event) {
  case SDL_WINDOWEVENT_CLOSE:
    return on_close();
  case SDL_WINDOWEVENT_MINIMIZED:
    return on_minimize();
  case SDL_WINDOWEVENT_SHOWN:
    return on_shown();
  }
}

void Application::on_minimize() { m_minimized = true; }

void Application::on_shown() { m_minimized = false; }

void Application::on_close() { stop(); }
} // namespace App
