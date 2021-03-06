# SimpleShell
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)
[![Licence](https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge)](./LICENSE)

## Description
In this program, we create our own shell that runs on top of the regular command-line interpreter for Linux. My shell reads lines of user input, then parses it and executes the commands by forking/creating new processes. First we parse the input using a buffer which should not exceed than 512 bytes and then separate the input buffer into substrings. We store the commands in an array of character pointers, and compare all with strcmp(). Then we Execute system commands and libraries by forking a child and calling execvp. For executing a system command, a new child is created and then by using the execvp, the command is executed, and wait until it is finished. The shell waits for its child process to complete, and then prints the child PID and the return result from the child process. If the shell encounters EOF while reading a line of input, it exits gracefully without reporting an error. If the user enters the exit command, the shell terminates and returns to the regular shell.

# Please refer to WriteUp for more information.
