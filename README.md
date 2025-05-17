# 🚀 Creation of a Custom Shell: `HSH`

Welcome to our custom shell project!

In this project, our goal was to write a simple UNIX command interpreter. We worked as a team to develop a simplified version of a shell, handling the different usual commands, some built-in commands and a few special features.

## 📋 Project Overview

This custom shell interprets the command typed by the user. `HSH` can handle the basic usual commands such as `ls`, `pwd`, `rm` and many others, as well as buit-in ones like `cd`, `exit`, `help` and `history`. It relies on the value of the PATH environment variable in order to find a command without the need to specify its absolute path.

## 🛠 Features

`HSH` supports the main following features:

- Accessing usual commands and handling arguments (`ls`, `pwd`, `rm`, etc.).
- Printing, adding and removing environment variables (`env`, `setenv`, `unsetenv`).
- Changing the current working directory (`cd`).
- Exiting the shell with a status code (`exit`).
- Printing the help for a built-in command (`help`).
- Handling a history of commands (`history`).
- Using variable expansion (`$`) and comments (`#`).

## 🔗 Exit Status

`HSH` can stop with a custom exit status if specified, or with the exit status of the previous command otherwise. The exit status (0) means nothing went wrong. If a problem occurs while using the shell, one of the following cases might have happened:
- If a general error occurs, the shell will stop with the exit status (1). This means something went wrong with a system call or with memory allocation.
- If an argument error occurs, the shell will update the exit status to (2). This means a required argument for the command is missing or invalid.
- If a history error occurs, the shell will update the exit status to (3). This means the history of commands couldn't be loaded or exported.
- If a specified command does not exist or if it is not found, the shell will stop with the exit status (127).

## 🔧 Technologies Used

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/GCC-343741?style=for-the-badge&logo=gnu&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![Vim](https://img.shields.io/badge/Vim-019733?style=for-the-badge&logo=vim&logoColor=white)
![Linux Badge](https://img.shields.io/badge/Linux-333333?style=for-the-badge&logo=linux&logoColor=white)

## 📂 Project Structure

The project contains several files, which are the following:

| Files | Description  |
| :---- | :----------- |
| [`builtin.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/builtin.c) | The  file  containing functions related to built-in commands. |
| [`commands.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/commands.c) | The file containing functions related to the command execution.  |
| [`environment.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/environment.c) | The  file  containing functions related to environment variables. |
| [`hsh.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/hsh.c) | The file containing the main function of the program. |
| [`main.h`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/main.h) | The header file containing structures and functions prototypes. |
| [`paths.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/paths.c) | The file containing functions related to the path search. |
| [`program.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/program.c) | The file containing functions related to starting and stopping the program. |

## ⚙️  Compilation and Restrictions

**The code should be compiled this way:**

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

💡 What does it do?

This command is used to strictly compile all C files in our project.
It helps ensure the code is:

✅ Clean and free from common bugs

✅ Following C89 coding standards

✅ Compiled with any warning treated as an error

**The restrictions are as follows**:

- No more than **5 functions** per file
- No use of global variables

Authorized functions and macros:

 - all functions from string.h
 - `access`
 - `chdir`
 - `close`
 - `closedir`
 - `execve`
 - `exit`
 - `_exit`
 - `fflush`
 - `fork`
 - `free`
 - `getcwd`
 - `getline`
 - `getpid`
 - `isatty`
 - `kill`
 - `malloc`
 - `open`
 - `opendir`
 - `perror`
 - `printf`
 - `fprintf`
 - `vfprintf`
 - `sprintf`
 - `putchar`
 - `read`
 - `readdir`
 - `signal`
 - `stat`
 - `lstat`
 - `fstat`
 - `strtok`
 - `wait`
 - `waitpid`
 - `wait3`
 - `wait4`
 - `write`

## 🧩 Use in Code

Let's take a look at what `HSH` actually does when used with a few basic commands and some built-in ones:

```
root@b6579b5f94d3:/home/ubuntu/holbertonschool-simple_shell$ ./hsh
hsh$ ls
AUTHORS  builtin.c  commands.c  environment.c  hsh  hsh.c  main.h  man_1_simple_shell  paths.c  program.c  README.md
hsh$ pwd
/home/ubuntu/holbertonschool-simple_shell
hsh$ mkdir test
hsh$ setenv DIRECTORY test
hsh$ cd $DIRECTORY
hsh$ pwd
/home/ubuntu/holbertonschool-simple_shell/test
hsh$ exit
root@b6579b5f94d3:/home/ubuntu/holbertonschool-simple_shell$
```

## 💾 Use of Memory

The code uses dynamic allocation of the memory, and is free of any memory-related issue. To ensure this, a tool such as `Valgrind` can be used on the executable file, after compilation:

```
root@b6579b5f94d3:/home/ubuntu/holbertonschool-simple_shell$ valgrind ./hsh
==52238== Memcheck, a memory error detector
==52238== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==52238== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==52238== Command: ./hsh
==52238== 
hsh$ cd ..
hsh$ pwd
/home/ubuntu
hsh$ setenv COMMAND history
hsh$ $COMMAND
[0] ls
[1] pwd
[2] mkdir test
[3] setenv DIRECTORY test
[4] cd $DIRECTORY
[5] pwd
[6] exit
[7] cd ..
[8] pwd
[9] setenv COMMAND history
[10] $COMMAND
hsh$ exit
==52238== 
==52238== HEAP SUMMARY:
==52238==     in use at exit: 0 bytes in 0 blocks
==52238==   total heap usage: 267 allocs, 267 frees, 27,223 bytes allocated
==52238== 
==52238== All heap blocks were freed -- no leaks are possible
==52238== 
==52238== For lists of detected and suppressed errors, rerun with: -s
==52238== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
root@b6579b5f94d3:/home/ubuntu/holbertonschool-simple_shell$
```

## 📂 Flowchart of the Project

![Drawio](https://github.com/user-attachments/assets/48e47a62-ffac-4103-b308-82dfd3fe3ef6)

## 🧑‍🤝‍🧑 Authors

This project was carried out by:

- [Gwendal Minguy-Pèlerin](https://github.com/gwendalminguy)
- [Dorine Lemée](https:/https://github.com/dougd0ug)
