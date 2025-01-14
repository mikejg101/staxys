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

#include <cstdlib>
#include <string>
#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include "staxys/utils/daemon_utils.h"

void mainTask() {
    while (true) {
        sleep(10);
    }
}

// TODO: This shouldn't be here
bool checkUserExists(const std::string &userName) {
    struct passwd *pw = getpwnam(userName.c_str());
    return pw != nullptr;
}

int main(int argc, char *argv[]) {

    if (!checkUserExists("staxys")) {
        std::cerr
                << "User 'staxys' does not exist. Please create the user or configure the application to use an existing user."
                << std::endl;
        return EXIT_FAILURE;
    }

    const std::string pidFile = "/var/run/staxys.pid";

    if (argc == 2) {
        std::string command = argv[1];
        if (command == "start") {
            std::cout << "Starting the application..." << std::endl;
            if (staxys::utils::DaemonUtils::start(pidFile)) {
                std::cout << "Application started successfully." << std::endl;
                mainTask();
            } else {
                std::cerr << "Failed to start the application." << std::endl;
                return EXIT_FAILURE;
            }
        } else if (command == "stop") {
            std::cout << "Stopping the application..." << std::endl;
            if (!staxys::utils::DaemonUtils::stop(pidFile)) {
                std::cerr << "Failed to stop the application." << std::endl;
                return EXIT_FAILURE;
            }
        } else {
            std::cerr << "Unknown command. Use 'start' or 'stop'." << std::endl;
        }
    } else {
        std::cerr << "Usage: staxys [start|stop]" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

