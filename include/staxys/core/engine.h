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

#ifndef STAXYS_ENGINE_H
#define STAXYS_ENGINE_H

#include "staxys/config/engine_config.h"
#include <csignal>
#include <memory>

namespace staxys::core {

class Engine {
public:
  explicit Engine(std::shared_ptr<const staxys::config::EngineConfig> &config) : m_config(config) {}
  ~Engine() = default;
  int start_application(bool asDaemon);
  int stop_application();
  int restart_application();
  static void signal_handler(int signal, siginfo_t *info, void *context);

private:
  int main_task();
  bool m_is_running = false;
  bool m_is_daemon = false;
  std::shared_ptr<const staxys::config::EngineConfig> m_config;
};

struct EngineSignalData {
  Engine *engine;
};

} // namespace staxys::core

#endif // STAXYS_ENGINE_H
