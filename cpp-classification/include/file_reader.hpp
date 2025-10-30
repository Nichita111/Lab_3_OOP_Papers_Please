#pragma once

#include "nlohmann/json.hpp"
#include <string>

using json = nlohmann::json;

class FileReader {
public:
    explicit FileReader(const std::string& path);
    // Read the file contents into memory
    bool read();
    // Print raw file contents to console
    void printRaw() const;
    // Parse the read contents as JSON
    bool parseJson();
    // Print each top-level JSON element separately (array elements or object members)
    void printTopLevelElements() const;
    // If top-level is an object with an array at `key`, print each element of that array separately
    void printArrayElements(const std::string& key) const;

private:
    std::string path_;
    std::string contents_;
    json j_;
    bool parsed_ = false;
};
