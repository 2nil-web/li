
#include <algorithm>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "options.h"
#include "util.h"

// The main function
int main(int argc, char **argv, char **)
{
  options myopt;
  myopt.set(argc, argv,
            {
                option_info(
                    'i', "interp", [&myopt](s_opt_params &) -> void { myopt.parse(std::cin); }, "Enter interpreter mode.", no_arg, option),
                option_info(
                    'e', "println", [](s_opt_params &p) -> void { std::cout << trim(p.val, "\"") << std::endl; }, "Echo the provided paramete(r)s and add a carriage return.", optional, interp),
                option_info(
                    'w', "print", [](s_opt_params &p) -> void { std::cout << trim(p.val, "\""); }, "Echo the provided paramete(r)s without adding a carriage return.", optional, interp),
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
