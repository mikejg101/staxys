#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-redundant-string-init"
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
#include <staxys/utils/string_utils.h>

TEST(StringUtilsTest, Trim) {
    std::string str = "  \t\n  hello world  \t\n  ";
    std::string expected = "hello world";
    ASSERT_EQ(expected, staxys::utils::StringUtils::trim(str));
}

TEST(StringUtilsTest, Split) {
    std::string str = "hello,world";
    std::vector<std::string> expected = {"hello", "world"};
    ASSERT_EQ(expected, staxys::utils::StringUtils::split(str, ','));
}

TEST(StringUtilsTest, ToLower) {
    std::string str = "Hello World";
    std::string expected = "hello world";
    ASSERT_EQ(expected, staxys::utils::StringUtils::toLower(str));
}

TEST(StringUtilsTest, ToUpper) {
    std::string str = "Hello World";
    std::string expected = "HELLO WORLD";
    ASSERT_EQ(expected, staxys::utils::StringUtils::toUpper(str));
}

TEST(StringUtilsTest, Replace) {
    std::string str = "hello world";
    std::string from = "world";
    std::string to = "everyone";
    std::string expected = "hello everyone";
    ASSERT_EQ(expected, staxys::utils::StringUtils::replace(str, from, to));
}

TEST(StringUtilsTest, Contains) {
    std::string str = "hello world";
    std::string substring = "world";
    ASSERT_TRUE(staxys::utils::StringUtils::contains(str, substring));
}

TEST(StringUtilsTest, StartsWith) {
    std::string str = "hello world";
    std::string prefix = "hello";
    ASSERT_TRUE(staxys::utils::StringUtils::startsWith(str, prefix));
}

TEST(StringUtilsTest, EndsWith) {
    std::string str = "hello world";
    std::string suffix = "world";
    ASSERT_TRUE(staxys::utils::StringUtils::endsWith(str, suffix));
}

TEST(StringUtilsTest, ContainsEmpty) {
    std::string str = "hello world";
    std::string substring = "";
    ASSERT_TRUE(staxys::utils::StringUtils::contains(str, substring));
}

TEST(StringUtilsTest, StartsWithEmpty) {
    std::string str = "hello world";
    std::string prefix = "";
    ASSERT_TRUE(staxys::utils::StringUtils::startsWith(str, prefix));
}

TEST(StringUtilsTest, EndsWithEmpty) {
    std::string str = "hello world";
    std::string suffix = "";
    ASSERT_TRUE(staxys::utils::StringUtils::endsWith(str, suffix));
}

TEST(StringUtilsTest, ContainsNotFound) {
    std::string str = "hello world";
    std::string substring = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::contains(str, substring));
}

TEST(StringUtilsTest, StartsWithNotFound) {
    std::string str = "hello world";
    std::string prefix = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::startsWith(str, prefix));
}

TEST(StringUtilsTest, EndsWithNotFound) {
    std::string str = "hello world";
    std::string suffix = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::endsWith(str, suffix));
}

TEST(StringUtilsTest, ContainsEmptyNotFound) {
    std::string str = "hello world";
    std::string substring = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::contains(str, substring));
}

TEST(StringUtilsTest, StartsWithEmptyNotFound) {
    std::string str = "hello world";
    std::string prefix = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::startsWith(str, prefix));
}

TEST(StringUtilsTest, EndsWithEmptyNotFound) {
    std::string str = "hello world";
    std::string suffix = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::endsWith(str, suffix));
}

TEST(StringUtilsTest, ContainsEmptyEmpty) {
    std::string str = "";
    std::string substring = "";
    ASSERT_TRUE(staxys::utils::StringUtils::contains(str, substring));
}

TEST(StringUtilsTest, StartsWithEmptyEmpty) {
    std::string str = "";
    std::string prefix = "";
    ASSERT_TRUE(staxys::utils::StringUtils::startsWith(str, prefix));
}

TEST(StringUtilsTest, EndsWithEmptyEmpty) {
    std::string str = "";
    std::string suffix = "";
    ASSERT_TRUE(staxys::utils::StringUtils::endsWith(str, suffix));
}

TEST(StringUtilsTest, ContainsEmptyEmptyNotFound) {
    std::string str = "";
    std::string substring = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::contains(str, substring));
}

TEST(StringUtilsTest, StartsWithEmptyEmptyNotFound) {
    std::string str = "";
    std::string prefix = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::startsWith(str, prefix));
}

TEST(StringUtilsTest, EndsWithEmptyEmptyNotFound) {
    std::string str = "";
    std::string suffix = "everyone";
    ASSERT_FALSE(staxys::utils::StringUtils::endsWith(str, suffix));
}


#pragma clang diagnostic pop