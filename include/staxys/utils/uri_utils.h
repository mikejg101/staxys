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

#ifndef STAXYS_URI_UTILS_H
#define STAXYS_URI_UTILS_H

#include <string>
#include <map>

namespace staxys::utils {

    class UriUtils {
    public:
        static bool parse(const std::string &uri, std::string &scheme, std::string &host,
                          int &port, std::string &path, std::map<std::string, std::string> &query,
                          std::string &fragment);

        static std::string encode(const std::string &component);

        static std::string decode(const std::string &component);

        static std::string resolve(const std::string &base, const std::string &relative);

        static bool validate(const std::string &uri);

        static std::string getPath(const std::string &uri);

        static std::map<std::string, std::string> getQuery(const std::string &uri);

        static std::string join(const std::string &base, const std::string &relative);

    private:
        static bool parseQuery(const std::string &queryString, std::map<std::string, std::string> &queryParams);
    };

}

#endif //STAXYS_URI_UTILS_H
