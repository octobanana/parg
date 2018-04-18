#include "parg.hh"

#include <string>
#include <iostream>

int main()
{
  // create the parg object
  // no arguments to constructor because we are going to parse args from a std::string
  OB::Parg pg;

  // pg.set(<long,short>, <default_value>, <value_description>, <description>);
  pg.set("file,f", "config.cfg", "string", "the file to read from");
  pg.set("num,n", "8", "int", "an integer value");

  // parse from a std::string instead of from argc/argv
  std::string arg_str {"-f 'filename.txt' --num=64"};
  int status {pg.parse(arg_str)};

  // if status > 0, no arguments were found
  // if status = 0, parsing was successful
  // if status < 0, an error occurred while parsing

  if (status < 0)
  {
    // handle parsing error
    std::cout << pg.help() << "\n";
    std::cout << "Error: " << pg.error() << "\n";
    return 1;
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
