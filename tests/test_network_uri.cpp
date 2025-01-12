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

#include <gtest/gtest.h>
#include "staxys/network/uri.h"

TEST(UriTest, Parse) {
    std::string uri = "https://www.example.com:8080/path/to/resource?query=param";
    staxys::network::Uri u(uri);
    ASSERT_EQ("https", u.getScheme());
    ASSERT_EQ("www.example.com", u.getHost());
    ASSERT_EQ(8080, u.getPort());
    ASSERT_EQ("/path/to/resource", u.getPath());
    ASSERT_EQ(1, u.getQuerySize());
    ASSERT_EQ("param", u.getQueryParameter("query"));
}