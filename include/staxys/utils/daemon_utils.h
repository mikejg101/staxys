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

#ifndef STAXYS_DAEMON_UTILS_H
#define STAXYS_DAEMON_UTILS_H

#include <string>

namespace staxys::utils {
    class DaemonUtils {
    public:

        /// Starts the daemon process.
        /// \details Starts the daemon process by checking if it is already running and
        ///          then daemonizing the process.
        /// \param pidFile The path to the PID file.
        /// \return true if the process was successfully started, false otherwise.
        static bool start(const std::string &pidFile);

        /// Stops the daemon process.
        /// \details Stops the daemon process by reading the PID from the specified PID
        ///          file and sending a SIGTERM signal.
        /// \param pidFile The path to the PID file.
        /// \return true if the process was successfully stopped, false otherwise.
        static bool stop(const std::string &pidFile);

    private:
        /// Daemonize the current process.
        /// \details This function forks the current process, creates a new session,
        ///          and detaches the process from the terminal. It also redirects standard
        ///          input, output, and error to /dev/null to detach the process from the
        ///          terminal.
        /// \return true if the daemonization process was successful, false otherwise.
        static bool daemonize();

        /// Writes the process ID to the specified PID file.
        /// \details This function opens the specified PID file and writes the process ID
        ///          of the current process to it. If the file cannot be opened, it prints
        ///          an error message and returns false.
        /// \param pidFile The path to the PID file.
        /// \return true if the process ID was successfully written to the PID file, false otherwise.
        static bool writePidFile(const std::string &pidFile);

        /// Safely forks the current process.
        /// \details This function forks the current process and checks for errors. If the
        ///          fork fails, it prints an error message and returns -1.
        /// \return The process ID of the child process if the fork was successful, -1 otherwise.
        static pid_t safeFork();
    };

}

#endif //STAXYS_DAEMON_UTILS_H
