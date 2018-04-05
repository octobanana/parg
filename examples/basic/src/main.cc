#include "parg.hh"

#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  // create the parg object
  OB::Parg pg {argc, argv};

  // set the program name and version
  pg.name("app").version("0.1.0 (00.00.0000)");

  // set a brief description of the program
  pg.description("an example of parg");

  // set the usage info
  pg.usage("[-v|-h]");

  // set the author
  pg.author("octobanana");

  // add help and version flags
  // default value for flags is false
  // flags and options must have both a long and short name
  // pg.set(<long,short>, <description>);
  pg.set("help,h", "print the help output");
  pg.set("version,v", "print the program version");

  // add file option
  // pg.set(<long,short>, <default_value>, <value_description>, <description>);
  pg.set("file,f", "config.cfg", "string", "the file to read from");

  // add num option
  pg.set("num,n", "8", "int", "an integer value");

  // parse the arguments
  // if status > 0, no arguments were found
  // if status = 0, parsing was successful
  // if status < 0, an error occurred while parsing
  int status {pg.parse()};

  if (status < 0)
  {
    // handle parsing error
    std::cout << pg.help() << "\n";
    std::cout << "Error: " << pg.error() << "\n";
    return 1;
  }

  // flags and options are accessed with their long name
  if (pg.get<bool>("help"))
  {
    // handle -h and --help
    std::cout << pg.help();
    return 0;
  }

  if (pg.get<bool>("version"))
  {
    // handle -v and --version
    std::cout << pg.name() << " v" << pg.version() << "\n";
    return 0;
  }

  // check to see if the file option was found
  // if it wasn't found, the default parameter given will be returned with pg.get("file");
  if (pg.find("file"))
  {
    std::string file {pg.get("file")};
    std::cout << "file: " << file << "\n";
  }
  else
  {
    std::cout << "using default file: " << pg.get("file") << "\n";
  }

  // print out the num value
  int num {pg.get<int>("num")};
  std::cout << "num: " << num << "\n";

  return 0;
}
