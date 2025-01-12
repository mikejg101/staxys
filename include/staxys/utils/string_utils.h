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

#ifndef STAXYS_STRING_UTILS_H
#define STAXYS_STRING_UTILS_H

#include <string>
#include <vector>

namespace staxys::utils {
    class StringUtils {
    public:
        static std::string trim(const std::string &str);

        static std::vector<std::string> split(const std::string &str, char delimiter);

        static std::string toLower(const std::string &str);

        static std::string toUpper(const std::string &str);

        static std::string replace(const std::string &str, const std::string &from, const std::string &to);

        static bool contains(const std::string &str, const std::string &substring);

        static bool startsWith(const std::string &str, const std::string &prefix);

        static bool endsWith(const std::string &str, const std::string &suffix);
    };
}

#endif //STAXYS_STRING_UTILS_H
