#pragma once

#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

class FileReader {
public:
    explicit FileReader(const std::string& path) : path_(path) {}

    // Read the file contents into memory
    bool read() {
        std::ifstream in(path_);
        if (!in) return false;
        std::ostringstream ss;
        ss << in.rdbuf();
        contents_ = ss.str();
        return true;
    }

    // Parse the read contents as JSON
    bool parseJson() {
        try {
            j_ = json::parse(contents_);
            parsed_ = true;
            return true;
        } catch (...) {
            parsed_ = false;
            return false;
        }
    }

    // Access parsed JSON
    const json& getJson() const { return j_; }

private:
    std::string path_;
    std::string contents_;
    json j_;
    bool parsed_ = false;
};
