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

#ifndef STAXYS_ENGINE_CONFIG_H
#define STAXYS_ENGINE_CONFIG_H

#include <map>
#include <string>
#include <vector>

namespace staxys::config {
class EngineConfig {
public:
  EngineConfig() = default;

  ~EngineConfig() = default;

  const std::string &user() const { return m_user; };
  void user(const std::string &user) { m_user = user; }

  const std::string &pid_file() const { return m_pid_file; };
  void pid_file(const std::string &pid_file) { m_pid_file = pid_file; };

  const std::vector<std::string> &listen_ports() const { return m_listen_ports; };
  void listen_ports(const std::vector<std::string> &listen_ports) { m_listen_ports = listen_ports; };

  const std::string &server_static_root() const { return m_server_static_root; };
  void server_static_root(const std::string &server_static_root) { m_server_static_root = server_static_root; };

  const std::string &default_index() const { return m_default_index; };
  void default_index(const std::string &default_index) { m_default_index = default_index; };

  const std::string &default_error_page() const { return m_default_error_page; };
  void default_error_page(const std::string &default_error_page) { m_default_error_page = default_error_page; };

  const std::map<int, std::string> &error_pages() const { return m_error_pages; };
  void add_error_page(int code, const std::string &page) { m_error_pages[code] = page; };

  const std::string &access_log() const { return m_access_log; };
  void access_log(const std::string &access_log) { m_access_log = access_log; };

  const std::string &error_log() const { return m_error_log; };
  void error_log(const std::string &error_log) { m_error_log = error_log; };

  const std::string &log_level() const { return m_log_level; };
  void log_level(const std::string &log_level) { m_log_level = log_level; };

  const bool ssl_enabled() const { return m_ssl_enabled; };
  void ssl_enabled(const bool ssl_enabled) { m_ssl_enabled = ssl_enabled; };

  const std::string &ssl_cert() const { return m_ssl_cert; };
  void ssl_cert(const std::string &ssl_cert) { m_ssl_cert = ssl_cert; };

  const std::string &ssl_key() const { return m_ssl_key; };
  void ssl_key(const std::string &ssl_key) { m_ssl_key = ssl_key; };

  const int worker_processes() const { return m_worker_processes; };
  void worker_processes(const int worker_processes) { m_worker_processes = worker_processes; };

  const int worker_connections() const { return m_worker_connections; };
  void worker_connections(const int worker_connections) { m_worker_connections = worker_connections; };

  const bool http2_enabled() const { return m_http2_enabled; };
  void http2_enabled(const bool http2_enabled) { m_http2_enabled = http2_enabled; };

  const std::string &client_max_body_size() const { return m_client_max_body_size; };
  void client_max_body_size(const std::string &client_max_body_size) { m_client_max_body_size = client_max_body_size; };

  const int client_body_timeout() const { return m_client_body_timeout; };
  void client_body_timeout(const int client_body_timeout) { m_client_body_timeout = client_body_timeout; };

  const int send_timeout() const { return m_send_timeout; };
  void send_timeout(const int send_timeout) { m_send_timeout = send_timeout; };

  const int keep_alive_timeout() const { return m_keep_alive_timeout; };
  void keep_alive_timeout(const int keep_alive_timeout) { m_keep_alive_timeout = keep_alive_timeout; };

  const std::vector<std::string> &allowed_ip() const { return m_allowed_ip; };
  void allowed_ip(const std::vector<std::string> &allowed_ip) { m_allowed_ip = allowed_ip; };

  const std::vector<std::string> &denied_ip() const { return m_denied_ip; };
  void denied_ip(const std::vector<std::string> &denied_ip) { m_denied_ip = denied_ip; };

  const bool enable_basic_auth() const { return m_enable_basic_auth; };
  void enable_basic_auth(const bool enable_basic_auth) { m_enable_basic_auth = enable_basic_auth; };

  const bool cache_enabled() const { return m_cache_enabled; };
  void cache_enabled(const bool cache_enabled) { m_cache_enabled = cache_enabled; };

  const std::string &cache_path() const { return m_cache_path; };
  void cache_path(const std::string &cache_path) { m_cache_path = cache_path; };

  const int cache_duration() const { return m_cache_duration; };
  void cache_duration(const int cache_duration) { m_cache_duration = cache_duration; };

  const bool health_check_enabled() const { return m_health_check_enabled; };
  void health_check_enabled(const bool health_check_enabled) { m_health_check_enabled = health_check_enabled; };

  const std::string &health_check_url() const { return m_health_check_url; };
  void health_check_url(const std::string &health_check_url) { m_health_check_url = health_check_url; };

private:
  std::string m_user;
  std::string m_pid_file;
  std::string m_server_static_root;
  std::vector<std::string> m_listen_ports;
  std::string m_default_index;
  std::string m_default_error_page;
  std::map<int, std::string> m_error_pages;
  std::string m_access_log;
  std::string m_error_log;
  std::string m_log_level;
  bool m_ssl_enabled;
  std::string m_ssl_cert;
  std::string m_ssl_key;
  int m_worker_processes;
  int m_worker_connections;
  bool m_http2_enabled;
  std::string m_client_max_body_size;
  int m_client_body_timeout;
  int m_send_timeout;
  int m_keep_alive_timeout;
  std::vector<std::string> m_allowed_ip;
  std::vector<std::string> m_denied_ip;
  bool m_enable_basic_auth;
  bool m_cache_enabled;
  std::string m_cache_path;
  int m_cache_duration;
  bool m_health_check_enabled;
  std::string m_health_check_url;
};
} // namespace staxys::config

#endif // STAXYS_ENGINE_CONFIG_H
