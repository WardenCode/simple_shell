[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

# hsh - Simple Shell

A simple UNIX command interpreter written as part of the low-level programming and algorithm track at Holberton School.


## Description

hsh is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.


## Available commands

| Commands | Description |
|--|--|
| `ls` | ls (from list), allows you to list the contents of a directory or file. |
| `pwd` | Pwd (from print working directory) is a convenient command that prints our path or location when executed, so we avoid getting lost if we are working with multiple directories and folders. |
| `touch` | touch creates an empty file, if the file exists it updates the modification time. |
| `rm` | rm (from remove) is the command needed to delete a file or directory. |
| `mkdir` | mkdir (from make directory) creates a new directory taking into account the current location. |
| `cp` | cp (from copy) copies a source file or directory to a target fileor directory. |
| `rmdir` | rmdir (from ReMove DIRectory) This command is used to delete empty directories or subdirectories. |
| `cd` | cd (from change directory) you will need this command to access a path other than the one you are in. basically it is for navigating from directory to directory. |
| `exit` | exits the current shell. 0 status value indicates successful execution, another value represents unsuccessful execution. |
| `cat` | cat (from concatenate), is a wonderful utility that allows us to visualize the content of a text file in the standard output, without the need of an editor. |

## Installation

Clone this repository:
```bash
git clone https://github.com/WardenCode/simple_shell.git

```
Enter to the directory:
```bash
cd simple_shell
```

Compile the .c files:
```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

Execute the program:
```bash
./hsh
```
    
## Code Style
On this project was used the [Betty code style](https://github.com/alx-tools/Betty) for the C programming language.
## Interactive and non-interactive mode

**hsh** can be invoked both interactively and non-interactively. If **hsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:
```bash
$ echo "echo 'hello'" | ./hsh
'hello'
$
```

If **hsh** is invoked with standard input connected to a terminal (determined by [isatty](https://linux.die.net/man/3/isatty)(3)), an *interactive* shell is opened. When executing interactively, **hsh** displays the prompt `$ ` when it is ready to read a command.

Example:
```bash
$./hsh
$
```

Alternatively, if command line arguments are supplied upon invocation, **hsh** treats the first argument as a file from which to read commands. The supplied file should contain one command per line. **hsh** runs each of the commands contained in the file in order before exiting.

Example:
```bash
$ cat test
echo 'hello'
$ ./hsh test
'hello'
$
```

## Environment

Upon invocation, **hsh** receives and copies the environment of the parent process in which it was executed. This environment is an array of *name-value* strings describing variables in the format *NAME=VALUE*. A few key environmental variables are:

### HOME
The home directory of the current user and the default directory argument for the **cd** builtin command.

```bash
$ echo "echo $HOME" | ./hsh
/home/vagrant
```

### PWD
The current working directory as set by the **cd** command.

```bash
$ echo "echo $PWD" | ./hsh
/home/vagrant/holberton/simple_shell
```

### OLDPWD
The previous working directory as set by the **cd** command.

```bash
$ echo "echo $OLDPWD" | ./hsh
/home/vagrant/holberton/printf
```

### PATH
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

```bash
$ echo "echo $PATH" | ./hsh
/home/linuxbrew/.linuxbrew/bin:/home/linuxbrew/.linuxbrew/sbin:/home/vagrant/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```

## Usage/Examples

### Exit Status

**hsh** returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

### Signals

While running in interactive mode, **hsh** ignores the keyboard input `Ctrl+c`. Alternatively, an input of end-of-file (`Ctrl+d`) will exit the program.

User hits `Ctrl+d` in the third line.
```bash
$ ./hsh
$ ^C
$ ^C
$
```

### Variable Replacement

**hsh** interprets the `$` character for variable replacement.

#### $ENV_VARIABLE
`ENV_VARIABLE` is substituted with its value.

Example:
```bash
$ echo "echo $PWD" | ./hsh
/home/vagrant/git/holberton/simple_shell
```

#### $?
`?` is substitued with the return value of the last program executed.

Example:
```bash
$ echo "echo $?" | ./hsh
0
```


### Built-in Commands

#### exit
  * Usage: `exit [STATUS]`
  * Exits the shell.
  * The `STATUS` argument is the integer used to exit the shell.
  * If no argument is given, the command is interpreted as `exit 0`.

Example:
```bash
$ ./hsh
$ exit
```

#### env
  * Usage: `env`
  * Prints the current environment.

Example:
```bash
$ ./hsh
$ env
SHELL=/bin/bash
```

## Authors

* Diego Linares <[WardenCode](https://github.com/wardencode)>
* Frank Quispe <[QuispeFrank](https://github.com/QuispeFrank)>

This project was written as part of the curriculum for Holberton School. Holberton School is a campus-based full-stack software engineering program that prepares students for careers in the tech industry using project-based peer learning. For more information, visit [this link](https://www.holbertonschool.com/).

<p align="center">
  <img src="https://www.holbertonschool.com.mx/wp-content/uploads/Holberton.png" alt="Holberton School logo">
</p>


## License

[MIT](https://choosealicense.com/licenses/mit/)
