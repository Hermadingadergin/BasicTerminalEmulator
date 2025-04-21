#include "terminal.h"
#include "utility.h"
#include "mypipe.h"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>

// run_cmd:
// Takes a vector of C-style strings (char*), representing the command and its arguments.
// Forks a child process, redirects its standard output, and executes the command.
// Captures the output using a custom pipe (mypipe) and prints it to the terminal.
// Returns 0 on success, non-zero on failure.
int run_cmd(std::vector<char*> argv)
{
    mypipe pipe;

    pid_t pid = fork();
    if (pid == -1) {
        std::cout << "Fork error";
        return 1;
    }
    else if (pid == 0) {
        // child process
        pipe.redirect();
        execvp(argv[0], argv.data());
        std::cout << "Execvp error";
        exit(1);
    }
    else {
        // parent process
        int status;
        waitpid(pid, &status, 0);
        std::string result = pipe.read();
        std::cout << result;
        return WEXITSTATUS(status);
    }

}

// terminal_app:
// Implements a simple interactive terminal loop.
// Continuously prompts the user for input, parses it into command and arguments,
// and executes the command using run_cmd().
// Exits the loop when the user types "exit".
void terminal_app()
{
    std::string line;
    while (true) {
        std::cout << "shell> "; // command line
        std::getline(std::cin, line);
        if (line == "exit") // exit loop when user types "exit"
        {
            break;
        }

        std::vector<std::string> cmd_vector = cmd2vec(line); // turns input into vector of strings
        if (cmd_vector.empty()) // empty input
        {
            continue;
        }

        std::vector<char*> args = castArgs(cmd_vector);
        run_cmd(args); // call run_cmd
    }
}