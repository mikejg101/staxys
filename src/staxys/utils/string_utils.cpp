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

#include "staxys/utils/string_utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>

/**
 * Trim leading and trailing whitespace from a string. Whitespace is defined as any character for which std::isspace
 * returns true.
 * @param str The string to trim.
 * @return The trimmed string.
 */
std::string staxys::utils::StringUtils::trim(const std::string &str) {
  auto start = str.find_first_not_of(" \t\n");
  if (start == std::string::npos) {
    return "";
  }

  auto end = str.find_last_not_of(" \t\n");
  return str.substr(start, end - start + 1);
}

/**
 * Split a string into a vector of strings using a delimiter character.
 * @param str The string to split.
 * @param delimiter The character to split the string on.
 * @return A vector of strings.
 */
std::vector<std::string> staxys::utils::StringUtils::split(const std::string &str, char delimiter) {
  std::vector<std::string> result;
  std::string token;
  std::istringstream token_stream(str);
  while (std::getline(token_stream, token, delimiter)) {
    result.push_back(token);
  }
  return result;
}

/**
 * Convert a string to lowercase.
 * @param str The string to convert.
 * @return The lowercase string.
 */
std::string staxys::utils::StringUtils::to_lower(const std::string &str) {
  auto result = str;
  std::transform(result.begin(), result.end(), result.begin(), tolower);
  return result;
}

/**
 * Convert a string to uppercase.
 * @param str The string to convert.
 * @return The uppercase string.
 */
std::string staxys::utils::StringUtils::to_upper(const std::string &str) {
  auto result = str;
  std::transform(result.begin(), result.end(), result.begin(), toupper);
  return result;
}

/**
 * Replace all occurrences of a substring in a string with another substring.
 * @param str The original string.
 * @param from The substring to be replaced.
 * @param to The substring to replace with.
 * @return The modified string with all occurrences of 'from' replaced by 'to'.
 */
std::string staxys::utils::StringUtils::replace(const std::string &str, const std::string &from,
                                                const std::string &to) {
  auto result = str;
  size_t start_pos = 0;
  while ((start_pos = result.find(from, start_pos)) != std::string::npos) {
    result.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
  return result;
}

/**
 * Check if a string contains a substring.
 * @param str The string to check.
 * @param substring The substring to look for.
 * @return True if the substring is found, false otherwise.
 */
bool staxys::utils::StringUtils::contains(const std::string &str, const std::string &substring) {
  return str.find(substring) != std::string::npos;
}

/**
 * Check if a string starts with a given prefix.
 * @param str The string to check.
 * @param prefix The prefix to look for.
 * @return True if the string starts with the prefix, false otherwise.
 */
bool staxys::utils::StringUtils::starts_with(const std::string &str, const std::string &prefix) {
  return str.rfind(prefix, 0) == 0;
}

/**
 * Check if a string ends with a given suffix.
 * @param str The string to check.
 * @param suffix The suffix to look for.
 * @return True if the string ends with the suffix, false otherwise.
 */
bool staxys::utils::StringUtils::ends_with(const std::string &str, const std::string &suffix) {
  return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}