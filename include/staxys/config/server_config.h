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

#ifndef STAXYS_SERVER_CONFIG_H
#define STAXYS_SERVER_CONFIG_H

#include <map>
#include <string>
#include <vector>

namespace staxys::config {
class ServerConfig {
public:
  ServerConfig() = default;
  ~ServerConfig() = default;

  const std::string &server_name() const { return m_server_name; };
  void server_name(const std::string &server_name) { m_server_name = server_name; }

  const std::string &root() const { return m_root; };
  void root(const std::string &root) { m_root = root; }

  const std::string &index() const { return m_index; };
  void index(const std::string &index) { m_index = index; }

  const bool ssl_enabled() const { return m_ssl_enabled; };
  void ssl_enabled(const bool ssl_enabled) { m_ssl_enabled = ssl_enabled; }

  const std::string &ssl_cert() const { return m_ssl_cert; };
  void ssl_cert(const std::string &ssl_cert) { m_ssl_cert = ssl_cert; }

  const std::string &ssl_key() const { return m_ssl_key; };
  void ssl_key(const std::string &ssl_key) { m_ssl_key = ssl_key; }

  const std::string &proxy_pass() const { return m_proxy_pass; };
  void proxy_pass(const std::string &proxy_pass) { m_proxy_pass = proxy_pass; }

  const std::string &default_error_page() const { return m_default_error_page; };
  void default_error_page(const std::string &default_error_page) { m_default_error_page = default_error_page; }

  const std::map<int, std::string> &error_pages() const { return m_error_pages; };
  void error_pages(const std::map<int, std::string> &error_pages) { m_error_pages = error_pages; }

  const std::vector<std::string> &allowed_ip() const { return m_allowed_ip; };
  void allowed_ip(const std::vector<std::string> &allowed_ip) { m_allowed_ip = allowed_ip; }

  const std::vector<std::string> &denied_ip() const { return m_denied_ip; };
  void denied_ip(const std::vector<std::string> &denied_ip) { m_denied_ip = denied_ip; }

  const bool cache_enabled() const { return m_cache_enabled; };
  void cache_enabled(const bool cache_enabled) { m_cache_enabled = cache_enabled; }

  const int cache_duration() const { return m_cache_duration; };
  void cache_duration(const int cache_duration) { m_cache_duration = cache_duration; }

  const std::string &access_log() const { return m_access_log; };
  void access_log(const std::string &access_log) { m_access_log = access_log; }

  const std::string &error_log() const { return m_error_log; };
  void error_log(const std::string &error_log) { m_error_log = error_log; }

  const std::string &log_level() const { return m_log_level; };
  void log_level(const std::string &log_level) { m_log_level = log_level; }

  const std::string &client_max_body_size() const { return m_client_max_body_size; };
  void client_max_body_size(const std::string &client_max_body_size) { m_client_max_body_size = client_max_body_size; }

  const int client_body_timeout() const { return m_client_body_timeout; };
  void client_body_timeout(const int client_body_timeout) { m_client_body_timeout = client_body_timeout; }

  const int send_timeout() const { return m_send_timeout; };
  void send_timeout(const int send_timeout) { m_send_timeout = send_timeout; }

  const bool health_check_enabled() const { return m_health_check_enabled; };
  void health_check_enabled(const bool health_check_enabled) { m_health_check_enabled = health_check_enabled; }

  const std::string &health_check_url() const { return m_health_check_url; };
  void health_check_url(const std::string &health_check_url) { m_health_check_url = health_check_url; }

private:
  std::string m_server_name;
  std::string m_root;
  std::string m_index;
  bool m_ssl_enabled;
  std::string m_ssl_cert;
  std::string m_ssl_key;
  std::string m_proxy_pass;
  std::string m_default_error_page;
  std::map<int, std::string> m_error_pages;
  std::vector<std::string> m_allowed_ip;
  std::vector<std::string> m_denied_ip;
  bool m_cache_enabled;
  int m_cache_duration;
  std::string m_access_log;
  std::string m_error_log;
  std::string m_log_level;
  std::string m_client_max_body_size;
  int m_client_body_timeout;
  int m_send_timeout;
  bool m_health_check_enabled;
  std::string m_health_check_url;
};

} // namespace staxys::config

#endif // STAXYS_SERVER_CONFIG_H
