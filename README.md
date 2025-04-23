# 🚀 Creation of a Custom `SHELL`

Welcome to our custom `SHELL` project!

In this project, our goal was to write a simple UNIX command interpreter. We worked as a team to develop a simplified version of a shell, handling different commands and built-in commands.

## 📋 Project Overview

This custom `SHELL` interprets the command inputs by the user. It can handle the basic commands such as `ls`, `pwd`, `touch`, `rm` and `man` as examples, as well as buit-in ones like `cd`, `env`, `exit` and `help`.

## 🛠 Features

This custom `SHELL` supports the principals following features:

- Displaying files of a directory (`ls`).
- Displaying path of the current directory (`pwd`).
- Create a new file (`touch`).
- Remove a file (`rm`).
- Print the manuel of a command (`man`).
- Change the directory (`cd`).
- Print the current environnement (`env`).
- Exit the `SHELL` (`exit`).
- Print the help page of a built-in command (`help`).

## 🔧 Technologies Used

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/GCC-343741?style=for-the-badge&logo=gnu&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![Vim](https://img.shields.io/badge/Vim-019733?style=for-the-badge&logo=vim&logoColor=white)
![Linux Badge](https://img.shields.io/badge/Linux-333333?style=for-the-badge&logo=linux&logoColor=white)

## 📂 Project Structure

The project contains several files, which are the following:

| Files | Description  |
| :-------- | :------- |
| [`main.h`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/main.h) | The header file containing structures and functions prototypes. |
| [`paths.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/paths.c) | The file containing functions related to the path search. |
| [`commands.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/commands.c) | The file containing functions related to the command execution.  |
| [`environment.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/environment.c) | The  file  containing functions related to environment variables. |
| [`builtin.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/builtin.c) | The  file  containing functions related to built-in commands. |
| [`hsh.c`](https://github.com/gwendalminguy/holbertonschool-simple_shell/blob/main/hsh.c) | The file containing the main function of the program. |

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
 - `stat` (__xstat)
 - `lstat` (__lxstat)
 - `fstat` (__fxstat)
 - `strtok`
 - `wait`
 - `waitpid`
 - `wait3`
 - `wait4`
 - `write`

## 🧩 Use in Code

Let's take a look at what our `SHELL` actually does when we test our code with a `touch`, a `ls` and an `rm`:

```

hsh$ touch test
hsh$ ls
AUTHORS  README.md  builtin.c  commands.c  environment.c  hsh  hsh.c  main.h  man_1_simple_shell  paths.c  test
hsh$ rm test
hsh$ ls
AUTHORS  README.md  builtin.c  commands.c  environment.c  hsh  hsh.c  main.h  man_1_simple_shell  paths.c
hsh$ pwd
/home/dougdoug/holbertonschool-simple_shell

```

Let's take a look at what our `SHELL` actually does when we test our code with a `cd` and an `exit`:

```

dougdoug@dorinette:~/holbertonschool-simple_shell$ ./hsh
hsh$ ls
AUTHORS  README.md  builtin.c  commands.c  environment.c  hsh  hsh.c  main.h  man_1_simple_shell  paths.c
hsh$ cd ..
hsh$ ls
Betty                                    holbertonschool-printf        holbertonschool-simple_shell-1
holbertonschool-binary_trees             holbertonschool-shell         holbertonschool-sorting_algorithms
holbertonschool-low_level_programming-3  holbertonschool-simple_shell  snap
hsh$ cd holbertonschool-simple_shell
hsh$ ls
AUTHORS  README.md  builtin.c  commands.c  environment.c  hsh  hsh.c  main.h  man_1_simple_shell  paths.c
hsh$ exit
dougdoug@dorinette:~/holbertonschool-simple_shell$

```

Let's take a look at what our `SHELL` actually does when we test our code with a `unsetenv` and an `env`:

```
hsh$ unsetenv LS_COLOR
hsh$ unsetenv PATH
hsh$ env
SHELL=/bin/bash
COLORTERM=truecolor
WSL2_GUI_APPS_ENABLED=1
TERM_PROGRAM_VERSION=1.99.2
WSL_DISTRO_NAME=Ubuntu-24.04
NAME=dorinette
PWD=/home/dougdoug/holbertonschool-simple_shell
LOGNAME=dougdoug
VSCODE_GIT_ASKPASS_NODE=/home/dougdoug/.vscode-server/bin/4949701c880d4bdb949e3c0e6b400288da7f474b/node
HOME=/home/dougdoug
LANG=C.UTF-8
WSL_INTEROP=/run/WSL/1324_interop
WAYLAND_DISPLAY=wayland-0
GIT_ASKPASS=/home/dougdoug/.vscode-server/bin/4949701c880d4bdb949e3c0e6b400288da7f474b/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
LESSCLOSE=/usr/bin/lesspipe %s %s
TERM=xterm-256color
LESSOPEN=| /usr/bin/lesspipe %s
USER=dougdoug
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-7aaa4a50df.sock
DISPLAY=:0
SHLVL=1
XDG_RUNTIME_DIR=/run/user/1000/
WSLENV=VSCODE_WSL_EXT_LOCATION/up:VSCODE_SERVER_TAR/up
VSCODE_GIT_ASKPASS_MAIN=/home/dougdoug/.vscode-server/bin/4949701c880d4bdb949e3c0e6b400288da7f474b/extensions/git/dist/askpass-main.js
XDG_DATA_DIRS=/usr/local/share:/usr/share:/var/lib/snapd/desktop
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
HOSTTYPE=x86_64
PULSE_SERVER=unix:/mnt/wslg/PulseServer
TERM_PROGRAM=vscode
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-df8becd6-2ae6-41ff-ac9e-492a32994422.sock
_=./hsh

```



## 💾 Use of Memory

The code does not contain any dynamic allocation of the memory.
However, to ensure the code is free of any memory-related issue, a tool such as `Valgrind` can be used on the executable file, after compilation:

```
valgrind ./hsh 
==92313== Memcheck, a memory error detector
==92313== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==92313== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==92313== Command: ./hsh
==92313== 
hsh$ ls
AUTHORS  README.md  builtin.c  commands.c  environment.c  hsh  hsh.c  main.h  man_1_simple_shell  paths.c
hsh$ cd
hsh$ pwd
/home/dougdoug
hsh$ cd -
hsh$ ==92313== 
==92313== HEAP SUMMARY:
==92313==     in use at exit: 0 bytes in 0 blocks
==92313==   total heap usage: 315 allocs, 315 frees, 30,781 bytes allocated
==92313== 
==92313== All heap blocks were freed -- no leaks are possible
==92313== 
==92313== For lists of detected and suppressed errors, rerun with: -s
==92313== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## 🧑‍🤝‍🧑 Authors

This project was carried out by: 

- [Gwendal Minguy-Pèlerin](https://github.com/gwendalminguy)
- [Dorine Lemée](https:/https://github.com/dougd0ug)
