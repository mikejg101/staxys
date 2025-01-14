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

#ifndef STAXYS_CONFIG_H
#define STAXYS_CONFIG_H

#include <string>

namespace staxys::core {
    class Config {
    public:
        Config();

        ~Config() = default;

        [[nodiscard]] std::string user() const { return m_user; };

        [[nodiscard]] std::string pidFile() const { return m_pid_file; };

    private:
        std::string m_user;
        std::string m_pid_file;
    };
}

#endif //STAXYS_CONFIG_H
