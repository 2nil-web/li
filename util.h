
#ifndef UTIL_H
#define UTIL_H

bool try_stoi(std::string s, size_t &n, size_t defn = 0);
std::string rtrim(std::string &s, const std::string ws = " \t\n\r\f\v");
std::string ltrim(std::string &s, const std::string ws = " \t\n\r\f\v");
std::string trim(std::string &s, const std::string ws = " \t\n\r\f\v");

void split_1st(std::string &, std::string &, std::string, char c = ' ');

std::string envvar_get(const std::string var);
bool envvar_set(const std::string var, const std::string val);

#endif /* UTIL_H */
