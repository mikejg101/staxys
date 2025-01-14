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
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <csignal>
#include <fstream>
#include <pwd.h>

pid_t staxys::utils::DaemonUtils::safeFork() {
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed." << std::endl;
        return -1;
    }
    return pid;
}

bool staxys::utils::DaemonUtils::start(const std::string &pidFile) {
    std::ifstream file(pidFile);
    if (file.is_open()) {
        std::cerr << "Staxys is already running." << std::endl;
        return false;
    }

    if (daemonize()) {
        return writePidFile(pidFile);
    }

    std::cerr << "Something went wrong starting the process." << std::endl;
    return false;
}

bool staxys::utils::DaemonUtils::stop(const std::string &pidFile) {
    std::ifstream file(pidFile);
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

    if (remove(pidFile.c_str()) != 0) {
        std::cerr << "Failed to remove PID file." << std::endl;
        return false;
    }

    return true;
}

bool staxys::utils::DaemonUtils::daemonize() {
    pid_t pid = staxys::utils::DaemonUtils::safeFork();
    if (pid < 0) {
        return false;
    }

    if (pid > 0) exit(EXIT_SUCCESS);

    if (setsid() < 0) {
        std::cerr << "Unable to create session." << std::endl;
        return false;
    }

    signal(SIGCHLD, SIG_IGN);

    pid = staxys::utils::DaemonUtils::safeFork();
    if (pid < 0) {
        return false;
    }

    if (pid > 0) exit(EXIT_SUCCESS);

    umask(0);

    if (chdir("/") < 0) {
        return false;
    }

    int null_fd = open("/dev/null", O_RDWR);
    if (null_fd == -1) {
        std::cerr << "Failed to open /dev/null" << std::endl;
        return false;
    }

    dup2(null_fd, STDIN_FILENO);
    dup2(null_fd, STDOUT_FILENO);
    dup2(null_fd, STDERR_FILENO);

    struct passwd *pw = getpwnam("staxys");
    if (pw == nullptr) {
        std::cerr << "Failed to get user 'staxys'" << std::endl;
        return false;
    }

    if (setgid(pw->pw_gid) != 0 || setuid(pw->pw_uid) != 0) {
        std::cerr << "Failed to set user/group ID" << std::endl;
        return false;
    }

    return true;
}

bool staxys::utils::DaemonUtils::writePidFile(const std::string &pidFile) {
    std::ofstream file(pidFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open PID file." << std::endl;
        return false;
    }

    file << getpid();
    file.close();
    return true;
}
