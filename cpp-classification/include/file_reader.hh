#pragma once

#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using namespace std;


class FileReader {
public:
    explicit FileReader(const string& path) : path_(path) {}

    // Read the file contents into memory
    bool read() {
        ifstream in(path_);
        if (!in) return false;
        ostringstream ss;
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
    string path_;
    string contents_;
    json j_;
    bool parsed_ = false;
};
