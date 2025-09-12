#pragma once

#include <cstddef>
#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;
    bool operator()(const std::string_view str1, const std::string_view str2) {
        return str1 < str2;
    }
    bool operator()(const std::string& str1, const std::string& str2) {
        return str1 < str2;
    }
    bool operator()(const std::string_view str1, const std::string str2) {
        return str1 < str2;
    }
    bool operator()(const std::string& str1, const std::string_view& str2) {
        return str1 < str2;
    }
};

struct TransparentStringEqual {
    using is_transparent = void;
    bool operator()(const std::string_view str1, const std::string_view str2) {
        return str1 == str2;
    }
    bool operator()(const std::string& str1, const std::string& str2) {
        return str1 == str2;
    }
    bool operator()(const std::string_view str1, const std::string& str2) {
        return str1 == str2;
    }
    bool operator()(const std::string& str1, const std::string_view str2) {
        return str1 == str2;
    }
};

struct TransparentStringHash {
    using is_transparent = void;
    size_t operator()(const std::string_view str) {
        return std::hash<std::string_view>{}(str);
    }

    size_t operator()(const std::string& str) {
        return std::hash<std::string>{}(str);
    }
};

}  // namespace bookdb
