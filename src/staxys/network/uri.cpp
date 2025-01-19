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

#include "staxys/network/uri.h"
#include "staxys/utils/uri_utils.h"

staxys::network::Uri::Uri(std::string uri) : m_raw(std::move(uri)) {
  utils::UriUtils::UriComponents components;
  utils::UriUtils::parse(m_raw, components);
  m_scheme = components.scheme;
  m_host = components.host;
  m_port = components.port;
  m_path = components.path;
  m_query = components.query;
  m_fragment = components.fragment;
}