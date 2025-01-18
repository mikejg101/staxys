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

#include <map>
#include <string>

namespace staxys::utils {

class UriUtils {
public:
  struct UriComponents {
    std::string scheme;
    std::string host;
    std::string port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
  };

  static bool parse(const std::string &, UriComponents &);

  static std::string encode(const std::string &);

  static std::string decode(const std::string &);

  static std::string resolve(const std::string &, const std::string &);

  static bool validate(const std::string &);

  static std::string get_path(const std::string &);

  static std::map<std::string, std::string> get_query(const std::string &);

  static std::string join(const std::string &, const std::string &);

private:
  static bool parse_query(const std::string &, std::map<std::string, std::string> &);
};

} // namespace staxys::utils

#endif // STAXYS_URI_UTILS_H
