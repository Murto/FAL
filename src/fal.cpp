#include "generation.hpp"
#include "Parser.hpp"
#include "Tokeniser.hpp"
#include "TokenKind.hpp"

#include <boost/program_options.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>


int main(int argc, char** argv) {
  try {
    boost::program_options::options_description desc{"Options"};
    desc.add_options()
      ("file", boost::program_options::value<std::string>()->required(), "Input file")
      ("format", boost::program_options::value<std::string>()->required(), "Output format");
    
    boost::program_options::positional_options_description pos_desc;
    pos_desc.add("file", -1);

    boost::program_options::command_line_parser parser{argc, argv};
    boost::program_options::variables_map vm;
    boost::program_options::store(parser.options(desc).positional(pos_desc).run(), vm);

    auto input_file_path = vm["file"].as<std::string>();

    // Open file
    std::fstream automaton_file{input_file_path};

    // Exit if the given file does not exist
    if (!automaton_file) {
      const std::string INVALID_PATH = "Invalid path: \"" + input_file_path + "\"";
      std::cout << INVALID_PATH << '\n';
      return 1;
    }

    automaton_file >> std::noskipws;

    try {
      auto parser = make_parser(make_tokeniser(std::istream_iterator<char>(automaton_file), std::istream_iterator<char>()));
      auto program = parser.parse();
      if (vm["format"].as<std::string>() == "dot") {
        generate_dot(program, input_file_path + ".dot");
      } else if (vm["format"].as<std::string>() == "png") {
        generate_png(program, input_file_path + ".png");
      } else if (vm["format"].as<std::string>() == "ps") {
        generate_postscript(program, input_file_path + ".ps");
      } else {
        std::cerr << "Invalid output format";
      }
    } catch (std::runtime_error e) {
      std::cout << e.what() << '\n';
      return 1;
    }
  } catch (const boost::program_options::error& e) {
    std::cerr << e.what() << '\n';
  }
}
