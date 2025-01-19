/*
 * Copyright 2025 Michael Goodwin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "staxys/config/loader.h"
#include "staxys/config/validator.h"
#include "staxys/core/engine.h"
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace program_options = boost::program_options;

int main(int argc, char *argv[]) {
  try {
    program_options::options_description desc("Usage: staxys [options...] <command>");

    desc.add_options()("help,h", "display help information")("version,v", "print version string")(
        "check,c", "check the configuration file")("daemon,d", "run as a daemon");

    program_options::positional_options_description p;
    p.add("command", 1);

    program_options::options_description all_options;
    all_options.add(desc).add_options()("command", program_options::value<std::string>(),
                                        "command to execute (start|stop|restart)");

    program_options::variables_map variables_map;
    store(
        program_options::command_line_parser(argc, argv).options(all_options).positional(p).run(),
        variables_map);
    notify(variables_map);

    if (variables_map.contains("help")) {
      std::cout << desc << "\n";
      return EXIT_SUCCESS;
    }

    if (variables_map.contains("version")) {
      std::cout << "staxys version 0.1.0" << "\n";
      return EXIT_SUCCESS;
    }

    // TODO: Allow the configuration file to be specified as a command line argument
    auto config = staxys::config::Loader::load_engine_config("/etc/staxys/staxys.cfg");

    if (variables_map.contains("check")) {
      std::cout << "Checking the configuration file..." << "\n";
      if (staxys::config::Validator::validate_engine_config(config)) {
        std::cout << "Configuration file is valid." << "\n";
        return EXIT_SUCCESS;
      }

      std::cerr << "Configuration file is invalid." << "\n";
      return EXIT_FAILURE;
    }

    if (!variables_map.contains("command")) {
      std::cerr << "Command is required. Use --help for usage information." << "\n";
      return EXIT_FAILURE;
    }

    std::string command = variables_map["command"].as<std::string>();
    std::cout << "Command: " << command << std::endl;

    staxys::core::Engine engine(config);

    if (command == "start") {
      return engine.start_application(variables_map.contains("daemon"));
    }
    if (command == "stop") {
      return engine.stop_application();
    }

    if (command == "restart") {
      return engine.restart_application();
    }

    std::cerr << "Unknown command: " << command << "\n";
    return EXIT_FAILURE;

  } catch (program_options::error &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
}
