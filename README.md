# MiniShell

A Unix-like command shell written in C, built to understand processes,
system calls, file descriptors, and inter-process communication.

## Description

MiniShell is a simplified command-line shell supporting interactive
command execution, built-in commands, I/O redirection, pipes, background
execution, and signal handling.

## Goals

- Understand processes and system calls (fork, exec, wait)
- Understand file descriptors and I/O redirection
- Understand inter-process communication (pipes)

## Specifications

- Interactive prompt with command parsing
- External command execution using fork, execvp, waitpid
- Built-in commands: cd, pwd, echo, help, exit
- Input redirection (<), output redirection (>), append redirection (>>)
- Error output redirection (2>)
- Single-stage pipes (cmd1 | cmd2)
- Background execution (&) with zombie process reaping
- SIGINT (Ctrl+C) handled so the shell survives, using sigaction
- Basic double-quote parsing (e.g. echo "hello world")
- Environment variable expansion ($VAR)
- Clear error messages for invalid commands, missing files, and bad syntax

## Design

The shell follows a clear sequence for each command:

1. **Input line**
   - User types a command at the prompt.

2. **Parser**
   - Splits the line into words.
   - Handles quotes (`"hello world"`).
   - Expands environment variables (`$HOME`).

3. **Operator detection**
   - Checks for special tokens:
     - `|` → pipe
     - `<`, `>`, `>>` → redirection
     - `&` → background execution
     - `$VAR` → variable expansion

4. **Execution path**
   - **Pipe?** → `run_pipeline` (create pipe, fork twice, dup2, execvp).
   - **Builtin?** → `run_builtin` (cd, pwd, echo, help, exit). Redirect stdout if needed.
   - **External?** → `run_external` (fork, dup2 for redirection, execvp, waitpid).

5. **Signal handling**
   - `SIGINT` (Ctrl+C) caught so the shell survives.
   - Background processes reaped with `waitpid(WNOHANG)`.

6. **Loop**
   - After execution, the prompt is shown again.

## Prerequisites

- GCC
- Make
- A Linux/Unix environment (developed and tested on Ubuntu)

## Build and Run

```bash
make
./minishell
```

## Usage Examples

```text
minishell> pwd
minishell> ls -la
minishell> cd ..
minishell> echo "hello world"
minishell> echo $HOME
minishell> echo hi > out.txt
minishell> cat < out.txt
minishell> echo more >> out.txt
minishell> ls | wc -l
minishell> sleep 5 &
minishell> exit
```

## Project Structure

```
minishell/
├── src/            source files (main, parser, executor, builtins, signals)
├── include/        header files
├── Makefile        build automation
├── LICENSE         MIT license
└── README.md       this file
```

## Limitations

This project does not attempt to reimplement Bash.

- Multi-stage pipes (more than one | in a single command)
- Combining pipes and redirection in the same command
- Command history and tab completion
- Aliases and shell scripting
- Full job control (fg, bg, process groups)
- Advanced quoting and escaping rules

## License

MIT. See the LICENSE file for details.