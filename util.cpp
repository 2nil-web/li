
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

#include "util.h"

bool try_stoi(std::string s, size_t &n, size_t defn)
{
  bool ret = false;

  if (s.empty())
    n = defn;
  else
  {
    std::size_t pos{};
    try
    {
      const int i{std::stoi(s, &pos)};
      n = (size_t)i;
      ret = true;
    }
    catch (std::invalid_argument const &ex)
    {
      std::cerr << "invalid argument: " << ex.what() << ", setting to default value: " << defn << std::endl;
      n = defn;
    }
    catch (std::out_of_range const &ex)
    {
      std::cerr << "out of range: " << ex.what() << ", setting to default value: " << defn << std::endl;
      n = defn;
    }
  }

  return ret;
}

std::string ltrim(std::string &s, const std::string ws)
{
  s.erase(0, s.find_first_not_of(ws));
  return s;
}

std::string rtrim(std::string &s, const std::string ws)
{
  s.erase(s.find_last_not_of(ws) + 1);
  return s;
}

std::string trim(std::string &s, const std::string ws)
{
  s.erase(0, s.find_first_not_of(ws));
  s.erase(s.find_last_not_of(ws) + 1);
  return s;
}

void split_1st(std::string &r1, std::string &r2, std::string s, char c)
{
  size_t pos = s.find_first_of(c);
  if (pos == std::string::npos)
  {
    r1 = s;
    r2 = {};
  }
  else
  {
    r1 = s.substr(0, pos);
    trim(r1);
    r2 = s.substr(pos + 1);
    trim(r2);
  }
}

// Get env var val if exists else empty string
std::string envvar_get(const std::string var)
{
  char *pVal = nullptr;
  std::string val = {};

#ifdef _WIN32
  DWORD vl = GetEnvironmentVariable(var.c_str(), NULL, 0);
  if (vl > 0)
  {
    pVal = new char[vl + 1];
    GetEnvironmentVariable(var.c_str(), pVal, vl);
    if (pVal != nullptr)
    {
      val = pVal;
      delete[] pVal;
    }
  }
#else
  pVal = getenv(var.c_str());
  if (pVal != nullptr)
    val = pVal;
#endif

  return val;
}

// Set env var
// Return true if OK else false
bool envvar_set(const std::string var, const std::string val)
{
#ifdef _WIN32
  return SetEnvironmentVariable(var.c_str(), val.c_str()) != 0;
#else
  return setenv((char *)var.c_str(), (char *)val.c_str(), 1) == 0;
#endif
}
