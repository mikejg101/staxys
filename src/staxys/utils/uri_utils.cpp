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

#include "staxys/utils/uri_utils.h"
#include "staxys/utils/string_utils.h"
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>

bool staxys::utils::UriUtils::parse(const std::string &uri, staxys::utils::UriUtils::UriComponents &components) {
  if (uri.empty()) {
    return false;
  }

  std::string uri_temp = uri;
  if (!staxys::utils::StringUtils::contains(uri_temp, "://")) {
    uri_temp = "http://" + uri_temp;
  }

  std::smatch match;
  std::regex uri_regex(R"(^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)");

  if (!std::regex_match(uri_temp, match, uri_regex)) {
    return false;
  }

  components.scheme = match[2].str();
  components.host = match[4].str();

  if (staxys::utils::StringUtils::contains(components.host, ":")) {
    auto pos = components.host.find(':');
    components.port = components.host.substr(pos + 1);
    components.host = components.host.substr(0, pos);
  } else {
    components.port = "";
  }

  components.path = match[5].str().empty() ? "/" : match[5].str();

  if (!match[7].str().empty()) {
    parse_query(match[7].str(), components.query);
  }

  // match fragment
  if (!match[9].str().empty()) {
    components.fragment = match[9].str();
  }

  return true;
}

std::string staxys::utils::UriUtils::encode(const std::string &component) {
  std::ostringstream encoded;
  for (unsigned char c : component) {
    if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      encoded << c;
    } else {
      encoded << "%" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
  }
  return encoded.str();
}

std::string staxys::utils::UriUtils::decode(const std::string &component) {
  std::ostringstream decoded;
  for (size_t i = 0; i < component.size(); i++) {
    if (component[i] == '%') {
      int value;
      std::istringstream hex(component.substr(i + 1, 2));
      hex >> std::hex >> value;
      decoded << static_cast<char>(value);
      i += 2;
    } else {
      decoded << component[i];
    }
  }
  return decoded.str();
}

std::string staxys::utils::UriUtils::resolve(const std::string &base, const std::string &relative) {
  staxys::utils::UriUtils::UriComponents components;
  auto is_valid = staxys::utils::UriUtils::parse(base, components);
  if (!is_valid) {
    return "";
  }

  std::string port = (components.port.empty()) ? "" : ":" + components.port;

  if (relative.empty()) {
    return base;
  }

  // If the relative URI is absolute, return it as is
  if (relative.find("://") != std::string::npos) {
    return relative;
  }

  // If the relative URI is a path, resolve it against the base URI
  if (relative[0] == '/') {
    return components.scheme + "://" + components.host + port + relative;
  }

  // If the relative URI is a query or a fragment, resolve it against the base URI
  if (relative[0] == '?' || relative[0] == '#') {
    return components.scheme + "://" + components.host + port + components.path + relative;
  }

  std::string relative_url = relative;

  while (relative_url.find("../") == 0) {
    auto pos = components.path.rfind('/');
    if (pos != std::string::npos) {
      components.path = components.path.substr(0, pos);
    }
    relative_url = relative_url.substr(3);
    std::cout << "Path: " << components.path << std::endl;
    std::cout << "Relative Url: " << relative_url << std::endl;
  }

  return components.scheme + "://" + components.host + port + components.path + "/" + relative_url;
}

bool staxys::utils::UriUtils::validate(const std::string &uri) {
  if (uri.empty()) {
    return false;
  }

  std::string uri_temp = uri;
  if (!staxys::utils::StringUtils::contains(uri_temp, "://")) {
    uri_temp = "http://" + uri_temp;
  }

  std::smatch match;
  std::regex uri_regex(R"(^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)");

  return std::regex_match(uri_temp, match, uri_regex);
}

std::string staxys::utils::UriUtils::get_path(const std::string &uri) {
  staxys::utils::UriUtils::UriComponents components;
  staxys::utils::UriUtils::parse(uri, components);
  return components.path;
}

std::map<std::string, std::string> staxys::utils::UriUtils::get_query(const std::string &uri) {
  staxys::utils::UriUtils::UriComponents components;
  staxys::utils::UriUtils::parse(uri, components);
  return components.query;
}

std::string staxys::utils::UriUtils::join(const std::string &base, const std::string &relative) {
  return std::string();
}

bool staxys::utils::UriUtils::parse_query(const std::string &queryString,
                                          std::map<std::string, std::string> &queryParams) {
  auto query = queryString[0] == '?' ? queryString.substr(1) : queryString;
  std::istringstream query_stream(query);
  std::string param;
  while (std::getline(query_stream, param, '&')) {
    auto pos = param.find('=');
    if (pos != std::string::npos) {
      auto key = param.substr(0, pos);
      auto value = param.substr(pos + 1);
      queryParams[key] = value;
    }
  }
  return true;
}