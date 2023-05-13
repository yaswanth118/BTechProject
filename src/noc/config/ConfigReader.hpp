#include <bits/stdc++.h>

using namespace std;
class ConfigReader {
public:
    explicit ConfigReader(const std::string& filename);

    int GetInteger(const std::string& section, const std::string& key) const;

    double GetDouble(const std::string& section, const std::string& key) const;

    std::string GetString(const std::string& section, const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> data_;
};
