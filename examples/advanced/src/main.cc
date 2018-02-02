#include "parg.hh"

#include <iostream>
#include <string>

int program_options(OB::Parg& pg);

int program_options(OB::Parg& pg)
{
  // set info
  pg.name("app").version("0.1.0 (00.00.0000)");
  pg.description("a command line app");
  pg.usage("[flags] [options] [--] [arguments]");
  pg.usage("[-v|--version]");
  pg.usage("[-h|--help]");
  pg.info("Exit Codes", {"0 -> normal", "1 -> error"});
  pg.info("Examples", {"app -v", "app -h", "app -help", "app --version"});
  pg.author("name <email>");

  // set options
  pg.set("help,h", "print the help output");
  pg.set("version,v", "print the program version");
  pg.set("flag_a,a", "a boolean flag with default value of false");
  pg.set("option,o", "20", "int", "an option with a default value of '20'");
  pg.set("option_required,r", "", "string", "a required option");

  // uncomment to collect positional arguments
  // pg.set_pos();

  // uncomment to collect piped input
  // pg.set_stdin();

  int status {pg.parse()};
  // uncomment if at least one argument is expected
  // if (status > 0 && pg.get_stdin().empty())
  // {
  //   std::cout << pg.print_help() << "\n";
  //   std::cout << "Error: " << "expected arguments" << "\n";
  //   return -1;
  // }
  if (status < 0)
  {
    // handle parsing error
    std::cout << pg.print_help() << "\n";
    std::cout << "Error: " << pg.error() << "\n";
    return -1;
  }
  if (pg.get<bool>("help"))
  {
    // handle -h and --help
    std::cout << pg.print_help();
    return 1;
  }
  if (pg.get<bool>("version"))
  {
    // handle -v and --version
    std::cout << pg.print_version();
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  OB::Parg pg {argc, argv};
  int pstatus {program_options(pg)};
  if (pstatus > 0)
  {
    // exit success
    return 0;
  }
  else if (pstatus < 0)
  {
    // exit error
    return 1;
  }

  // get flag
  bool flag_a {pg.get<bool>("flag_a")};
  std::cout << "flag_a: " << std::boolalpha << flag_a << "\n";

  // get int option
  int option {pg.get<int>("option")};
  std::cout << "option: " << option << '\n';

  // check for required string option
  if (pg.find("option_required"))
  {
    std::string option_required {pg.get("option_required")};
    std::cout << "option_required: " << option_required << "\n";
  }
  else
  {
    std::cout << pg.print_help() << "\n";
    std::cout << "Error: " << "'option_required' is required" << "\n";
    return -1;
  }

  return 0;
}
