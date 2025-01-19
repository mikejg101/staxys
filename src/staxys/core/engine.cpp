/*
 * Copyright 2025 Michael Goodwin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "staxys/core/engine.h"
#include "staxys/utils/daemon_utils.h"
#include <iostream>
#include <signal.h>
#include <unistd.h>

namespace staxys::core {

EngineSignalData *g_signal_data = nullptr;

int Engine::start_application(const bool asDaemon) {
  std::cout << "Starting the application..." << std::endl;

  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = signal_handler;
  sigemptyset(&sa.sa_mask);

  EngineSignalData signal_data{this};
  g_signal_data = &signal_data;

  sigaction(SIGTERM, &sa, nullptr);
  sigaction(SIGINT, &sa, nullptr);
  sigaction(SIGHUP, &sa, nullptr);

  if (!asDaemon) {
    m_is_running = true;
    return main_task();
  }

  std::cout << "Running as a daemon..." << std::endl;
  if (!utils::DaemonUtils::validate_daemon_configuration(m_config->user(), m_config->pid_file())) {
    return EXIT_FAILURE;
  }

  if (utils::DaemonUtils::start(m_config->pid_file())) {
    std::cout << "Application started successfully." << std::endl;
    m_is_running = true;
    return main_task();
  }

  std::cerr << "Failed to start the application." << std::endl;
  return EXIT_FAILURE;
}

int Engine::stop_application() {
  std::cout << "Stopping the application..." << std::endl;

  if (utils::DaemonUtils::stop(m_config->pid_file())) {
    std::cout << "Application stopped successfully." << std::endl;
    m_is_running = false;
    return EXIT_SUCCESS;
  }

  std::cerr << "Failed to stop the application." << std::endl;
  return EXIT_FAILURE;
}

int Engine::restart_application() {
  std::cout << "Restarting the application..." << std::endl;
  if (stop_application() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  return start_application(false);
}

int Engine::main_task() {
  std::cout << "Running the main task..." << std::endl;
  while (m_is_running) {
    sleep(1);
  }
  std::cout << "Main task is stopping." << std::endl;
  return EXIT_SUCCESS;
}

void Engine::signal_handler(int signal, siginfo_t *info, void *context) {
  EngineSignalData *data = g_signal_data;
  Engine &engine = *data->engine;

  switch (signal) {
  case SIGTERM:
  case SIGINT:
    std::cout << "Received termination signal. Stopping application..." << std::endl;
    engine.stop_application();
    break;
  case SIGHUP:
    std::cout << "Received SIGHUP signal. Restarting application..." << std::endl;
    engine.restart_application();
    break;
  default:
    std::cerr << "Unhandled signal " << signal << std::endl;
    break;
  }
}

} // namespace staxys::core