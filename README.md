# Parg
A header only c++ library for parsing command line arguments and generating usage/help output.  

### Features
Parg has the following features:  
* short flags/options
* long flags/options
* default values
* positional arguments
* [--] arguments
* piped stdin
* usage output
* help output
* version output
* helpful parsing error output
* clean and formatted --help output

## Install
Copy __parg.hh__ into your projects directory, or run the install script and add `#include <ob/parg.hh>` to your source file.  

The following shell commands will install the project:  
```bash
git clone <repo_name>
cd <repo_name>
./install.sh
```

## Usage
Let's write a program that will accept the flags for help and version info, a string option called file, and an integer option called num.  
```cpp
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
  // flags and options can have either a long and short name, a long name, or a short name.
  // pg.set(<long,short>, <description>);
  // pg.set(<long>, <description>); where long is more than one char
  // pg.set(<short>, <description>); where short is one char
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
  // or short if they don't have a long name
  if (pg.get<bool>("help"))
  {
    // handle -h and --help
    std::cout << pg.print_help();
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
```

Running it with the -h flag will ouput:
```
app -h
app:
  an example of parg

Usage:
  app [-v|-h]

Flags:
  -h, --help
    print the help output
  -v, --version
    print the program version

Options:
  -f, --file=<string>
    the file to read from
  -n, --num=<int>
    an integer value

Author:
  octobanana
```

## Examples
See the __examples__ directory.  

Compile and run each example with:  
```bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../
make
./app
```
