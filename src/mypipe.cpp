#include "mypipe.h"
#include <unistd.h>
#include <sys/types.h>
#include <array>
#include <string>
#include <iostream>

// Constructor: Creates a unidirectional pipe using pipe().
// pipe() initializes two file descriptors: fd[0] for reading, fd[1] for writing.
mypipe::mypipe()
{
	pipe(fd.data());
	if (pipe(fd.data()))
	{
		std::cout << "Error in laying pipe";
	}
}

// Destructor: Closes both ends of the pipe to release resources
mypipe::~mypipe()
{
	close(fd[0]);
	close(fd[1]);
}

// redirect(): Redirects standard output (STDOUT) to the pipe's write end.
// This allows capturing output that would normally go to the console.
void mypipe::redirect()
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

// read(): Reads data from the pipe's read end and returns it as a std::string.
// Typically used to capture the output that was redirected into the pipe.
std::string mypipe::read()
{
	std::string result;
	std::array<char, 256> buf;
	ssize_t bytes;
	while ((bytes = ::read(fd[0], buf.data(), buf.size())) > 0)
	{
		result.append(buf.data(), bytes);
	}
	return result;
}