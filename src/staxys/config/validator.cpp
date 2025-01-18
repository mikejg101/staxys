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

#include "staxys/config/validator.h"
#include <iostream>

namespace staxys::config {

    bool Validator::validate_engine_config(const std::shared_ptr<const EngineConfig> &config) {
        if (config->listen_ports().empty()) {
            std::cerr << "No ports have been defined for Staxys to listen on." << std::endl;
            return false;
        }
        return true;
    }

    bool Validator::validate_server_config(const std::shared_ptr<const ServerConfig> &config) {
        // TODO: Actual validation
        return true;
    }

} // namespace staxys::config
