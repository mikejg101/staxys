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

#ifndef STAXYS_LOADER_H
#define STAXYS_LOADER_H

#include "staxys/config/engine_config.h"
#include "staxys/config/server_config.h"
#include <memory>
#include <string>

namespace staxys::config {
class Loader final {
public:
  static std::shared_ptr<const EngineConfig> load_engine_config(const std::string &);
  static std::shared_ptr<const ServerConfig> load_server_config(const std::string &);
  Loader() = delete;
  ~Loader() = delete;
};
} // namespace staxys::config

#endif // STAXYS_LOADER_H
