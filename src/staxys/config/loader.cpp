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

#include "staxys/config/loader.h"

#include "staxys/utils/string_utils.h"
#include <fstream>
#include <iostream>
#include <regex>

namespace staxys::config {

std::shared_ptr<const EngineConfig> Loader::load_engine_config(const std::string &server_config_path) {
  auto engine_config = std::make_shared<EngineConfig>();
  std::ifstream file(server_config_path);
  if (!file.is_open()) {
    std::cout << "Failed to open file: " << server_config_path << std::endl;
    return engine_config;
  }

  try {
    std::regex re("^error_(\\d+)_page$");
    std::string line;
    while (std::getline(file, line)) {
      if (line.empty()) {
        continue;
      }

      // TODO: We only really need to trim start. We could also not trim at
      //       all and just check for '#' at the start of the line.
      if (utils::StringUtils::trim(line)[0] == '#') {
        continue;
      }

      auto delimiter = line.find('=');
      if (delimiter == std::string::npos) {
        continue;
      }

      auto key = utils::StringUtils::trim(line.substr(0, delimiter));
      auto value = utils::StringUtils::trim(line.substr(delimiter + 1));

      if (value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.size() - 2);
      }

      if (key == "user") {
        engine_config->user(value);
      } else if (key == "pid_file") {
        engine_config->pid_file(value);
      } else if (key == "ports") {
        std::vector<std::string> listen_ports;
        auto start = 0U;
        auto end = value.find(';');
        while (end != std::string::npos) {
          listen_ports.push_back(value.substr(start, end - start));
          start = end + 1;
          end = value.find(';', start);
        }
        listen_ports.push_back(value.substr(start, end));
        engine_config->listen_ports(listen_ports);
      } else if (key == "server_static_root") {
        engine_config->server_static_root(value);
      } else if (key == "listen_ports") {
        std::vector<std::string> listen_ports;
        auto start = 0U;
        auto end = value.find(';');
        while (end != std::string::npos) {
          listen_ports.push_back(value.substr(start, end - start));
          start = end + 1;
          end = value.find(';', start);
        }
        listen_ports.push_back(value.substr(start, end));
        engine_config->listen_ports(listen_ports);
      } else if (key == "default_index") {
        engine_config->default_index(value);
      } else if (key == "default_error_page") {
        engine_config->default_error_page(value);
      } else if (std::regex_match(key, re)) {
        std::smatch match;
        std::regex_search(key, match, re);
        engine_config->add_error_page(std::stoi(match[1]), value);
      } else if (key == "error_404_page") {
        engine_config->access_log(value);
      } else if (key == "access_log") {
        engine_config->access_log(value);
      } else if (key == "error_log") {
        engine_config->error_log(value);
      } else if (key == "log_level") {
        engine_config->log_level(value);
      } else if (key == "ssl_enabled") {
        engine_config->ssl_enabled(value == "false");
      } else if (key == "ssl_cert") {
        engine_config->ssl_cert(value);
      } else if (key == "ssl_key") {
        engine_config->ssl_key(value);
      } else if (key == "worker_processes") {
        engine_config->worker_processes(std::stoi(value));
      } else if (key == "worker_connections") {
        engine_config->worker_connections(std::stoi(value));
      } else if (key == "http2_enabled") {
        engine_config->http2_enabled(value == "false");
      } else if (key == "client_max_body_size") {
        engine_config->client_max_body_size(value);
      } else if (key == "client_body_timeout") {
        // TODO: parse shorthand time values
      } else if (key == "send_timeout") {
        engine_config->send_timeout(std::stoi(value));
      } else if (key == "keep_alive_timeout") {
        engine_config->keep_alive_timeout(std::stoi(value));
      } else if (key == "allowed_ips") {
        // TODO: handle allowed ip's
      } else if (key == "denied_ips") {
        // TODO: handle denied ip's
      } else if (key == "enable_basic_auth") {
        engine_config->enable_basic_auth(value == "false");
      } else if (key == "cache_enabled") {
        engine_config->cache_enabled(value == "false");
      } else if (key == "cache_path") {
        engine_config->cache_path(value);
      } else if (key == "cache_duration") {
        engine_config->cache_duration(std::stoi(value));
      } else if (key == "health_check_enabled") {
        engine_config->health_check_enabled(value == "false");
      } else if (key == "health_check_url") {
        engine_config->health_check_url(value);
      } else {
        // TODO: We may not want to log this in production environments
        std::cout << "Unknown key: " << key << std::endl;
      }
    }

    return engine_config;
  } catch (const std::exception &e) {

    // TODO: We may not want to log this in production environments
    std::cerr << "Error parsing engine config: " << e.what() << std::endl;
    return engine_config;
  }
}

std::shared_ptr<const ServerConfig> Loader::load_server_config(const std::string &) {
  auto server_config = std::make_shared<ServerConfig>();
  // TODO: Load the server config from the file at server_config_path
  return server_config;
}

} // namespace staxys::config
