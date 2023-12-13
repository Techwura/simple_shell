# shellby - Simple Shell

A basic interpreter for UNIX commands built as a component of the low-level programming and algorithm course at ALX.

## Description

Simple UNIX command language interpreter **Shellby** reads and executes commands from standard input or a file.

### Invocation
Usage: **shellby** [filename]

Compile every `.c} file in the repository, then launch the resulting executable to activate **shellby**:

```
gcc *.c -o shellby
./shellby
```

You can call **Shellby** in an interactive or non-interactive manner. When **shellby** is used without a terminal connection and standard input, it reads and processes commands in the order that they are received.

If **shellby** is invoked with standard input connected to a terminal (determined by [isatty](https://linux.die.net/man/3/isatty)(3)), an *interactive* shell is opened. When executing interactively, **shellby** displays the prompt `$ ` when it is ready to read a command.

In the event that command line arguments are provided during execution, **shellby** handles the initial argument as a file that commands can be read from. One command per line should be present in the provided file. Before quitting, **Shellby** executes all of the commands in the file in the correct order.

### Environment
As soon as it is invoked, **shellby** takes over and replicates the parent process's environment. The variables in this environment are described by an array of *name-value* strings with the type *NAME=VALUE*. Several crucial environmental factors include:
* **HOME**
The home directory of the current user and the default directory argument for the **cd** builtin command.

* **PWD**
The current working directory as set by the **cd** command.

* **OLDPWD**
The previous working directory as set by the **cd** command.

* **PATH**
A list of directories, separated by colons, where commands are searched by the shell. The current directory can be identified by a null directory name in the path, which can be shown as either the first or last colon, or as two adjacent colons.

### Command Execution
**shellby** takes a command, tokenizes it into words, and uses {" "} as a delimiter. All words that follow are regarded as arguments to the initial word, which is regarded as the command. **Shellby** then takes the subsequent actions:
* The shell looks for the command in the list of shell builtins if its initial character isn't a dot ({.}) or a slash ({\}). The builtin is called if one with that name already exists.
* In the event that the command's initial character is neither a dot ({.}), slash ({\}), nor built-in, **shellby** looks for an executable file with that name in every directory contained in the **PATH** environmental variable.
* The shell runs the named programme in a different execution environment together with any remaining parameters if the initial character of the command is a slash ({\}) or dot ({.}) or if one of the aforementioned searches was successful.

### Exit Status
**Shellby** provides the exit status of the most recent command that was run; a non-zero result denotes failure and a zero result indicates success.

A command's return status is 126 if it cannot be executed, and 127 if it can be found but not executed.

When used incorrectly, all built-ins return one or two instead of zero (as indicated by a matching error message).

### Signals
The keyboard input `Ctrl+c} is ignored by **shellby** when it is operating in interactive mode. Alternatively, the programme can be terminated by entering end-of-file ({Ctrl+d}).

### Variable Replacement
**Shellby** interprets the `$` character for variable replacement.
* `$ENV_VARIABLE`
  * `ENV_VARIABLE` is substituted with its value.

* `$?`
  * `?` is substitued with the return value of the last program executed.

* `$$`
  * The second `$` is substitued with the current process ID.

### Comments
**Shellby** ignores all words and characters preceeded by a `#` character on a line.

### Operators
**Shellby** specially interprets the following operator characters:
* `;` - Command separator
  * Commands separated by a `;` are executed sequentially.

* `&&` - AND logical operator
  * `command1 && command2`: `command2` is executed if, and only if, `command1` returns an exit status of zero.

* `||` - OR logical operator
  * `command1 || command2`: `command2` is executed if, and only if, `command1` returns a non-zero exit status.

The operators `&&` and `||` have equal precedence, followed by `;`.

### Shellby Builtin Commands
* **cd**
  * Usage: `cd [DIRECTORY]`
  * Changes the current directory of the process to `DIRECTORY`.
  * If no argument is given, the command is interpreted as `cd $HOME`.
  * If the argument `-` is given, the command is interpreted as `cd $OLDPWD` and the pathname of the new working directory is printed to standad output.
  * If the argument, `--` is given, the command is interpreted as `cd $OLDPWD` but the pathname of the new working directory is not printed.
  * The environment variables `PWD` and `OLDPWD` are updated after a change of directory.

* **alias**
  * Usage: `alias [NAME[='VALUE'] ...]`
  * Handles aliases.
  * `alias`: Prints a list of all aliases, one per line, in the form `NAME='VALUE'`.
  * `alias NAME [NAME2 ...]`: Prints the aliases `NAME`, `NAME2`, etc. one per line, in the form `NAME='VALUE'`.
  * `alias NAME='VALUE' [...]`: Defines an alias for each `NAME` whose `VALUE` is given. If `name` is already an alias, its value is replaced with `VALUE`.

* **env**
  * Usage: `env`
  * Prints the current environment.

* **setenv**
  * Usage: `setenv [VARIABLE] [VALUE]`
  * Initializes a new environment variable, or modifies an existing one.
  * Upon failure, prints a message to `stderr`.

* **unsetenv**
  * Usage: `unsetenv [VARIABLE]`
  * Removes an environmental variable.
  * Upon failure, prints a message to `stderr`.

## Authors
* Millicent Amegavie
* Afia Serwaa Ntosour-Amponsem 

## Acknowledgements
**Shellby** emulates basic functionality of the **sh** shell. This README borrows form the Linux man pages [sh(1)](https://linux.die.net/man/1/sh) and [dash(1)](https://linux.die.net/man/1/dash).
