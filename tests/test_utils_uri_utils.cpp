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
#include <staxys/utils/uri_utils.h>

TEST(UriUtilsTest, Parse) {
    std::string uri = "https://www.example.com:8080/path/to/resource?query=param";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("https", scheme);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ(8080, port);
    ASSERT_EQ("/path/to/resource", path);
    ASSERT_EQ(1, query.size());
    ASSERT_EQ("param", query["query"]);
}

TEST(UriUtilsTest, ParseWithoutScheme) {
    std::string uri = "www.example.com:8080/path/to/resource?query=param";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("http", scheme);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ(8080, port);
    ASSERT_EQ("/path/to/resource", path);
    ASSERT_EQ(1, query.size());
    ASSERT_EQ("param", query["query"]);
    ASSERT_EQ(0, fragment.size());
}

TEST(UriUtilsTest, ParseWithoutQueryParams) {
    std::string uri = "www.example.com:8080/path/to/resource";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("http", scheme);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ(8080, port);
    ASSERT_EQ("/path/to/resource", path);
    ASSERT_EQ(0, query.size());
    ASSERT_EQ(0, fragment.size());
}

TEST(UriUtilsTest, ParseRootWithPort) {
    std::string uri = "www.example.com:8080";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("http", scheme);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ(8080, port);
    ASSERT_EQ("/", path);
    ASSERT_EQ(0, query.size());
    ASSERT_EQ(0, fragment.size());
}

TEST(UriUtilsTest, ParseRoot) {
    std::string uri = "www.example.com";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("http", scheme);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ(80, port);
    ASSERT_EQ("/", path);
    ASSERT_EQ(0, query.size());
    ASSERT_EQ(0, fragment.size());
}

TEST(UriUtilsTest, ParseLocalHost) {
    std::string uri = "localhost";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("http", scheme);
    ASSERT_EQ("localhost", host);
    ASSERT_EQ(80, port);
    ASSERT_EQ("/", path);
    ASSERT_EQ(0, query.size());
    ASSERT_EQ(0, fragment.size());
}

TEST(UriUtilsTest, ParseIp) {
    std::string uri = "192.68.1.1";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("http", scheme);
    ASSERT_EQ("192.68.1.1", host);
    ASSERT_EQ(80, port);
    ASSERT_EQ("/", path);
    ASSERT_EQ(0, query.size());
    ASSERT_EQ(0, fragment.size());
}

TEST(UriUtilsTest, ParseWithFragment) {
    std::string uri = "https://www.example.com:8080/path/to/resource?query=param#fragment";
    std::string scheme;
    std::string host;
    int port;
    std::string path;
    std::map<std::string, std::string> query;
    std::string fragment;
    ASSERT_TRUE(staxys::utils::UriUtils::parse(uri, scheme, host, port, path, query, fragment));
    ASSERT_EQ("https", scheme);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ(8080, port);
    ASSERT_EQ("/path/to/resource", path);
    ASSERT_EQ(1, query.size());
    ASSERT_EQ("param", query["query"]);
    ASSERT_EQ("fragment", fragment);
}

TEST(UriUtilsTest, Encode) {
    EXPECT_EQ(staxys::utils::UriUtils::encode("hello world"), "hello%20world");
    EXPECT_EQ(staxys::utils::UriUtils::encode("C++ programming"), "C%2B%2B%20programming");
    EXPECT_EQ(staxys::utils::UriUtils::encode("URI encoding"), "URI%20encoding");
    EXPECT_EQ(staxys::utils::UriUtils::encode("special characters: !@#$%^&*()"),
              "special%20characters%3A%20%21%40%23%24%25%5E%26%2A%28%29");
    EXPECT_EQ(staxys::utils::UriUtils::encode("spaces and tabs"), "spaces%20and%20tabs");
    EXPECT_EQ(staxys::utils::UriUtils::encode("new\nline"), "new%0Aline");
    EXPECT_EQ(staxys::utils::UriUtils::encode("carriage\rreturn"), "carriage%0Dreturn");
    EXPECT_EQ(staxys::utils::UriUtils::encode("slash/"), "slash%2F");
    EXPECT_EQ(staxys::utils::UriUtils::encode("backslash\\"), "backslash%5C");
    EXPECT_EQ(staxys::utils::UriUtils::encode("quote\""), "quote%22");
    EXPECT_EQ(staxys::utils::UriUtils::encode("single'quote"), "single%27quote");
    EXPECT_EQ(staxys::utils::UriUtils::encode("question?"), "question%3F");
    EXPECT_EQ(staxys::utils::UriUtils::encode("hash#"), "hash%23");
    EXPECT_EQ(staxys::utils::UriUtils::encode("percent%"), "percent%25");
    EXPECT_EQ(staxys::utils::UriUtils::encode("ampersand&"), "ampersand%26");
    EXPECT_EQ(staxys::utils::UriUtils::encode("asterisk*"), "asterisk%2A");
    EXPECT_EQ(staxys::utils::UriUtils::encode("plus+"), "plus%2B");
    EXPECT_EQ(staxys::utils::UriUtils::encode("comma,"), "comma%2C");
    EXPECT_EQ(staxys::utils::UriUtils::encode("semicolon;"), "semicolon%3B");
    EXPECT_EQ(staxys::utils::UriUtils::encode("colon:"), "colon%3A");
}

TEST(UriUtilsTest, Decode) {
    EXPECT_EQ(staxys::utils::UriUtils::decode("hello%20world"), "hello world");
    EXPECT_EQ(staxys::utils::UriUtils::decode("C%2B%2B%20programming"), "C++ programming");
    EXPECT_EQ(staxys::utils::UriUtils::decode("URI%20encoding"), "URI encoding");
    EXPECT_EQ(staxys::utils::UriUtils::decode("special%20characters%3A%20%21%40%23%24%25%5E%26%2A%28%29"),
              "special characters: !@#$%^&*()");
    EXPECT_EQ(staxys::utils::UriUtils::decode("spaces%20and%20tabs"), "spaces and tabs");
    EXPECT_EQ(staxys::utils::UriUtils::decode("new%0Aline"), "new\nline");
    EXPECT_EQ(staxys::utils::UriUtils::decode("carriage%0Dreturn"), "carriage\rreturn");
    EXPECT_EQ(staxys::utils::UriUtils::decode("slash%2F"), "slash/");
    EXPECT_EQ(staxys::utils::UriUtils::decode("backslash%5C"), "backslash\\");
    EXPECT_EQ(staxys::utils::UriUtils::decode("quote%22"), "quote\"");
    EXPECT_EQ(staxys::utils::UriUtils::decode("single%27quote"), "single'quote");
    EXPECT_EQ(staxys::utils::UriUtils::decode("question%3F"), "question?");
    EXPECT_EQ(staxys::utils::UriUtils::decode("hash%23"), "hash#");
    EXPECT_EQ(staxys::utils::UriUtils::decode("percent%25"), "percent%");
    EXPECT_EQ(staxys::utils::UriUtils::decode("ampersand%26"), "ampersand&");
    EXPECT_EQ(staxys::utils::UriUtils::decode("asterisk%2A"), "asterisk*");
    EXPECT_EQ(staxys::utils::UriUtils::decode("plus%2B"), "plus+");
    EXPECT_EQ(staxys::utils::UriUtils::decode("comma%2C"), "comma,");
    EXPECT_EQ(staxys::utils::UriUtils::decode("semicolon%3B"), "semicolon;");
    EXPECT_EQ(staxys::utils::UriUtils::decode("colon%3A"), "colon:");
}

TEST(UriUtilsTest, Resolve) {
    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "https://www.example.com/path/to/resource",
            "/another/resource"),
              "https://www.example.com/another/resource");

    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "https://www.example.com/path/to/resource",
            "../another/resource"),
              "https://www.example.com/path/to/another/resource");

    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "https://www.example.com/path/to/resource",
            "../../another/resource"),
              "https://www.example.com/path/another/resource");

    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "https://www.example.com/path/to/resource",
            "/another/resource?query=param"),
              "https://www.example.com/another/resource?query=param");

    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "https://www.example.com/path/to/resource",
            "/another/resource#section"),
              "https://www.example.com/another/resource#section");

    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "https://www.example.com/path/to/resource",
            "?query=param"),
              "https://www.example.com/path/to/resource?query=param");

    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "https://www.example.com/path/to/resource",
            "#section"),
              "https://www.example.com/path/to/resource#section");

    EXPECT_EQ(staxys::utils::UriUtils::resolve(
            "www.example.com/path/to/resource",
            "/another/resource"),
              "http://www.example.com/another/resource");
}

//TEST(UriUtilsTest, Validate) {
//    std::string uri = "https://www.example.com/path/to/resource?query=param";
//    ASSERT_TRUE(staxys::utils::UriUtils::validate(uri));
//}
//
//TEST(UriUtilsTest, ValidateInvalid) {
//    std::string uri = "https://www.example.com/path/to/resource?query=param";
//    uri[0] = 'h';
//    ASSERT_FALSE(staxys::utils::UriUtils::validate(uri));
//}
//
//TEST(UriUtilsTest, GetPath) {
//    std::string uri = "https://www.example.com/path/to/resource?query=param";
//    std::string expected = "/path/to/resource";
//    ASSERT_EQ(expected, staxys::utils::UriUtils::getPath(uri));
//}
//
//TEST(UriUtilsTest, GetQuery) {
//    std::string uri = "https://www.example.com/path/to/resource?query=param";
//    std::map<std::string, std::string> expected = {{"query", "param"}};
//    ASSERT_EQ(expected, staxys::utils::UriUtils::getQuery(uri));
//}
//
//TEST(UriUtilsTest, Join) {
//    std::string base = "https://www.example.com/path/to/resource";
//    std::string relative = "/another/resource";
//    std::string expected = "https://www.example.com/another/resource";
//    ASSERT_EQ(expected, staxys::utils::UriUtils::join(base, relative));
//}