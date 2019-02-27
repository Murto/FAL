#include <fstream>
#include <iostream>
#include <string>


int main(int argc, char** argv) {

  // Exit if the wrong number of arguments is given
  if (argc != 2) {
    const std::string USAGE = "Usage: fal automaton";
    std::cout << USAGE << '\n';
    return 1;
  }

  // Set the file path
  const std::string automaton_path = argv[0];

  // Open file
  std::fstream automaton_file{automaton_path};

  // Exit if the given file does not exist
  if (!automaton_file) {
    const std::string INVALID_PATH = "Invalid path";
    std::cout << INVALID_PATH << '\n';
    return 1;
  }

  return 0;

}
