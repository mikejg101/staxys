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

#include "staxys/utils/daemon_utils.h"
#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <staxys/utils/string_utils.h>
#include <sys/stat.h>
#include <unistd.h>

pid_t staxys::utils::DaemonUtils::safe_fork() {
  pid_t pid = fork();
  if (pid < 0) {
    std::cerr << "Fork failed." << std::endl;
    return -1;
  }
  return pid;
}

bool staxys::utils::DaemonUtils::start(const std::string &pidFile) {
  if (std::filesystem::exists(pidFile)) {
    std::cerr << "Staxys is already running." << std::endl;
    return false;
  }

  // Attempt to daemonize and write the PID file
  if (daemonize() && write_pid_file(pidFile)) {
    std::cout << "Running as a daemon..." << std::endl;
    std::cout << "PID File Path: " << pidFile << std::endl;
    return true;
  } else {
    std::cerr << "Failed to start the application." << std::endl;
    return false;
  }
}

bool staxys::utils::DaemonUtils::stop(const std::string &pid_file) {
  std::ifstream file(pid_file);
  if (!file.is_open()) {
    std::cerr << "Staxys is not running." << std::endl;
    return false;
  }

  pid_t pid;
  file >> pid;
  file.close();

  if (kill(pid, SIGTERM) != 0) {
    std::cerr << "Failed to stop the process with PID " << pid << ". Error: " << strerror(errno) << std::endl;
    return false;
  }

  // Putting the result of remove into a variable to avoid a very strange
  // error where the file is removed but the function returns a non-zero value
  auto remove_result = remove(pid_file.c_str());
  if (remove_result != 0) {
    std::cerr << "Failed to remove PID file: " << pid_file << std::endl;
    std::cerr << "Error: " << strerror(errno) << " (errno: " << errno << ")" << std::endl;
    return false;
  }

  return true;
}

bool staxys::utils::DaemonUtils::daemonize() {
  std::cout << "Daemonizing the process..." << std::endl;
  pid_t pid = safe_fork();
  if (pid < 0) {
    std::cerr << "Failed to fork the process." << std::endl;
    return false;
  }
  if (pid > 0) {
    std::cout << "Forked child process with PID: " << pid << std::endl;
    exit(0);
  }

  if (setsid() < 0) {
    std::cerr << "Failed to create a new session." << std::endl;
    return false;
  }

  pid = safe_fork();
  if (pid < 0) {
    return false;
  }
  if (pid > 0) {
    exit(0);
  }

  if (chdir("/") < 0) {
    std::cerr << "Failed to change directory to /." << std::endl;
    return false;
  }

  for (int fd = sysconf(_SC_OPEN_MAX); fd >= 0; fd--) {
    close(fd);
  }

  open("/dev/null", O_RDONLY);
  open("/dev/null", O_RDWR);
  open("/dev/null", O_RDWR);

  return true;
}

bool staxys::utils::DaemonUtils::write_pid_file(const std::string &pid_file) {
  std::ofstream file(pid_file);
  if (!file.is_open()) {
    std::cerr << "Failed to open PID file for writing: " << pid_file << std::endl;
    return false;
  }

  pid_t pid = getpid();
  std::cout << "Writing PID " << pid << " to file: " << pid_file << std::endl;
  file << pid;
  if (!file.good()) {
    std::cerr << "Failed to write PID to file: " << pid_file << std::endl;
    return false;
  }

  file.close();
  std::cout << "PID file written successfully." << std::endl;
  return true;
}

bool staxys::utils::DaemonUtils::validate_daemon_configuration(const std::string &user_name,
                                                               const std::string &pid_file) {
  struct passwd *pw = getpwnam(user_name.c_str());
  if (pw == nullptr) {
    std::cerr << "User '" << user_name << "' does not exist." << std::endl;
    return false;
  }

  size_t pos = pid_file.find_last_of('/');
  auto parent_path = (pos == std::string::npos) ? "." : pid_file.substr(0, pos);
  if (access(parent_path.c_str(), W_OK) != 0) {
    std::cerr << "Cannot write to directory: " << parent_path << std::endl;
    std::cerr << "Error: " << strerror(errno) << std::endl;
    return false;
  }
  return true;
}
