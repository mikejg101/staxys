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

#include <map>
#include <string>

namespace staxys::network {

class Uri {
public:
  explicit Uri(std::string url);
  ~Uri() = default;
  const bool is_valid_uri() const { return m_is_valid; }
  const std::string &query_parameter(const std::string &key) const { return m_query.at(key); }
  const std::string &port() const { return m_port; }
  const std::string &scheme() const { return m_scheme; }
  const std::string &host() const { return m_host; }
  const std::string &path() const { return m_path; }
  const std::map<std::string, std::string> &query() const { return m_query; }
  const int query_size() const { return m_query.size(); }
  const std::string &raw() const { return m_raw; }
  const std::string &fragment() const { return m_fragment; }

private:
  std::string m_raw;
  std::string m_port;
  std::string m_scheme;
  std::string m_host;
  std::string m_path;
  std::string m_fragment;
  std::map<std::string, std::string> m_query;
  bool m_is_valid;
};

} // namespace staxys::network

#endif // STAXYS_URI_H
