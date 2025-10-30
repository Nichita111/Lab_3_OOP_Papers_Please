#include "../include/file_reader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

FileReader::FileReader(const std::string& path) : path_(path) {}

bool FileReader::read() {
    std::ifstream in(path_);
    std::ostringstream ss;
    ss << in.rdbuf();
    contents_ = ss.str();
    return true;
}

void FileReader::printRaw() const {
    std::cout << "---- Raw file contents (" << path_ << ") ----\n";
    std::cout << contents_ << "\n";
    std::cout << "---- end raw ----\n";
}

bool FileReader::parseJson() {
    j_ = json::parse(contents_);
    parsed_ = true;
    return true;
}

void FileReader::printTopLevelElements() const {
    std::cout << "---- Top-level JSON elements ----\n";
    for (auto it = j_.begin(); it != j_.end(); ++it) {
        std::cout << "Member '" << it.key() << "':\n" << it.value().dump(4) << "\n\n";
    }
    std::cout << "---- end top-level ----\n";
}

void FileReader::printArrayElements(const std::string& key) const {
    if (!j_.is_object()) {
        std::cout << "Top-level JSON is not an object; cannot lookup key '" << key << "'.\n";
        return;
    }

    const auto& arr = j_.at(key);
    if (!arr.is_array()) {
        std::cout << "Value at key '" << key << "' is not an array.\n";
        return;
    }

    std::cout << "---- Elements inside array '" << key << "' ----\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "Element [" << i << "]:\n" << arr[i].dump(4) << "\n\n";
    }
    std::cout << "---- end array elements ----\n";
}
