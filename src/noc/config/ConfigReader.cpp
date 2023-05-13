#include "ConfigReader.hpp"

ConfigReader::ConfigReader(const string &filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::invalid_argument("Configuration file not found.");
    }
    std::string line, section;
    while (std::getline(file, line)) {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        if (line.empty() || line[0] == '#') {
            continue; // skip comments and empty lines
        }
        if (line[0] == '[' && line[line.length() - 1] == ']') {
            section = line.substr(1, line.length() - 2); // extract section name
        } else {
            std::istringstream iss(line);
            std::string key, value;
            std::getline(iss, key, '=');
            std::getline(iss, value);
            key.erase(0, key.find_first_not_of(' '));
            key.erase(key.find_last_not_of(' ') + 1);
            value.erase(0, value.find_first_not_of(' '));
            value.erase(value.find_last_not_of(' ') + 1);
            data_[section + "." + key] = value; // store key-value pair with section name
        }
    }
    file.close();
}

int ConfigReader::GetInteger(const string &section, const string &key) const {
    try {
        return std::stoi(data_.at(section + "." + key));
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Requested key-value pair not found in configuration file.");
    }
}

double ConfigReader::GetDouble(const string &section, const string &key) const {
    try {
        return std::stod(data_.at(section + "." + key));
    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Requested key-value pair not found in configuration file.");
    }
}

std::string ConfigReader::GetString(const string &section, const string &key) const {
    try {
        return data_.at(section + "." + key);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Requested key-value pair not found in configuration file.");
    }
}
