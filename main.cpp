
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
               option_info('i', "interp", [&myopt](s_opt_params &p) -> void { myopt.parse(std::cin); }, "Enter interpreter mode."),
               option_info('e', "echo", [](s_opt_params &p) -> void { std::cout << p.val; }, "Echo the provided paramete(r)s."),
             }
           );

  myopt.parse();

  // If no remaining argument then interpretation mode
  if (myopt.args.empty()) myopt.parse(std::cin);
  // else run all the provided file
  else for (auto arg : myopt.args)
    myopt.parse(arg);

  return 0;
}
