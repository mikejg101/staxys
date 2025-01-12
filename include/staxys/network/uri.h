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

#ifndef STAXYS_URI_H
#define STAXYS_URI_H

#include <string>
#include <map>

namespace staxys::network {

    class Uri {
    public:
        explicit Uri(std::string uri);

        ~Uri() = default;

        [[nodiscard]] bool isValidUri() const { return isValid; }

        [[nodiscard]] int getPort() const { return port; }

        [[nodiscard]] std::string getScheme() const { return scheme; }

        [[nodiscard]] std::string getHost() const { return host; }

        [[nodiscard]] std::string getPath() const { return path; }

        [[nodiscard]] std::string getQueryParameter(const std::string &key) const { return query.at(key); }

        [[nodiscard]] std::map<std::string, std::string> getQuery() const { return query; }

        [[nodiscard]] int getQuerySize() const { return query.size(); }

        [[nodiscard]] std::string getRaw() const { return raw; }

        [[nodiscard]] std::string getFragment() const { return fragment; }

    private:
        std::string raw;
        int port;
        std::string scheme;
        std::string host;
        std::string path;
        std::string fragment;
        std::map<std::string, std::string> query;
        bool isValid;
    };

}

#endif //STAXYS_URI_H
