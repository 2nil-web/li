
#include <algorithm>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "options.h"
#include "util.h"

std::map<std::string, std::string> sym_table;

bool setvar(std::string expr)
{
  trim(expr, "\"");
  std::string var, val;
  split_1st(var, val, expr, '=');

  if (var.empty() || val.empty())
    return false;

  trim(val, "\"");
  sym_table[var] = val;
  return true;
}

bool unsetvar(std::string var)
{
  trim(var, "\"");
  if (var.empty())
    return false;
  sym_table.erase(var);
  return true;
}

std::string expand(std::string expr)
{
  trim(expr, "\"");
  std::string res = {};

  for (size_t i = 0; i < expr.size(); i++)
  {
    if (expr[i] == '$')
    {
      if (!res.empty() && res.back() == '$')
        continue;

      std::string var = {};
      for (;;)
      {
        i++;
        if (!isalpha(expr[i]) || isspace(expr[i]) || i >= expr.size())
        {
          if (!var.empty())
            res += sym_table[var];
          res += expr[i];
          break;
        }

        var += expr[i];
      }
    }
    else
    {
      res += expr[i];
    }
  }

  return res;
}

// The main function
int main(int argc, char **argv, char **)
{
  options myopt;
  myopt.set(argc, argv,
            {
                option_info(
                    'i', "interp", [&myopt](s_opt_params &) -> void { myopt.parse(std::cin); }, "Enter interpreter mode.", no_arg, option),
                option_info(
                    's', "set", [](s_opt_params &p) -> void { setvar(p.val); }, "Set a value to a variable in the form 'set var=val'.", required, interp),
                option_info(
                    'u', "unset", [](s_opt_params &p) -> void { unsetvar(p.val); }, "Unset a variable in the form 'unset var'.", required, interp),
                option_info(
                    'e', "println", [](s_opt_params &p) -> void { std::cout << expand(p.val) << std::endl; }, "Echo the provided parameter(s) and add a carriage return. Variable names must start with '$' and are expanded to their value", optional, interp),
                option_info(
                    'w', "print", [](s_opt_params &p) -> void { std::cout << expand(p.val) << std::flush; }, "Same as 'println' without adding a carriage return.", optional, interp),
                option_info(
                    'x', "exit", [](s_opt_params &) -> void { exit(0); }, "Exit from interpreted mode.", no_arg, interp),
                option_info(
                    'q', "quit", [](s_opt_params &) -> void { exit(0); }, "Alias for exit.", no_arg, interp),
            });

  myopt.parse();

  // If no remaining argument then interpretation mode
  if (myopt.args.empty())
    myopt.parse(std::cin);
  // else run all the provided file(s)
  else
    for (auto arg : myopt.args)
      myopt.parse(arg);

  return 0;
}
