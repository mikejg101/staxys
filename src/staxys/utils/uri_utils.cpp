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
#include <regex>
#include <sstream>
#include <iomanip>
#include <iostream>

bool staxys::utils::UriUtils::parse(const std::string &uri, std::string &scheme, std::string &host,
                                    int &port, std::string &path, std::map<std::string, std::string> &query,
                                    std::string &fragment) {
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

    scheme = match[2].str();
    host = match[4].str();

    if (staxys::utils::StringUtils::contains(host, ":")) {
        auto pos = host.find(':');
        port = std::stoi(host.substr(pos + 1));
        host = host.substr(0, pos);
    } else {
        port = (scheme == "https") ? 443 : 80;
    }

    path = match[5].str().empty() ? "/" : match[5].str();

    if (!match[7].str().empty()) {
        parseQuery(match[7].str(), query);
    }

    // match fragment
    if (!match[9].str().empty()) {
        fragment = match[9].str();
    }

    return true;
}

std::string staxys::utils::UriUtils::encode(const std::string &component) {
    std::ostringstream encoded;
    for (unsigned char c: component) {
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
    std::string scheme;
    std::string host;
    int portNum;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    auto isValid = staxys::utils::UriUtils::parse(base, scheme, host, portNum, path, query, fragment);
    if (!isValid) {
        return "";
    }

    std::string port = (portNum == 80 || portNum == 443) ? "" : ":" + std::to_string(portNum);

    if (relative.empty()) {
        return base;
    }

    // If the relative URI is absolute, return it as is
    if (relative.find("://") != std::string::npos) {
        return relative;
    }

    // If the relative URI is a path, resolve it against the base URI
    if (relative[0] == '/') {
        return scheme + "://" + host + port + relative;
    }

    // If the relative URI is a query or a fragment, resolve it against the base URI
    if (relative[0] == '?' || relative[0] == '#') {
        return scheme + "://" + host + port + path + relative;
    }

    std::string relativeUrl = relative;

    while (relativeUrl.find("../") == 0) {
        auto pos = path.rfind('/');
        if (pos != std::string::npos) {
            path = path.substr(0, pos);
        }
        relativeUrl = relativeUrl.substr(3);
        std::cout << "path: " << path << std::endl;
        std::cout << "relativeUrl: " << relativeUrl << std::endl;
    }

    return scheme + "://" + host + port + path + "/" + relativeUrl;
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

std::string staxys::utils::UriUtils::getPath(const std::string &uri) {
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment);
    return path;
}

std::map<std::string, std::string> staxys::utils::UriUtils::getQuery(const std::string &uri) {
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment);
    return query;
}

std::string staxys::utils::UriUtils::join(const std::string &base, const std::string &relative) {
    return std::string();
}

bool staxys::utils::UriUtils::parseQuery(const std::string &queryString, std::map<std::string,
        std::string> &queryParams) {
    auto query = queryString[0] == '?' ? queryString.substr(1) : queryString;
    std::istringstream queryStream(query);
    std::string param;
    while (std::getline(queryStream, param, '&')) {
        auto pos = param.find('=');
        if (pos != std::string::npos) {
            auto key = param.substr(0, pos);
            auto value = param.substr(pos + 1);
            queryParams[key] = value;
        }
    }
    return true;
}