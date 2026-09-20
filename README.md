# MiniShell

A Unix-like command shell written in C.

## Status

Work in progress.

## Planned Features

- Interactive prompt
- External command execution (fork, execvp, waitpid)
- Built-ins: cd, pwd, echo, help, exit
- Input/output redirection (<, >, >>)
- Pipes (cmd1 | cmd2 | ...)
- Background processes (&)
- Environment variable expansion ($VAR)
- Signal handling (Ctrl+C)

## Build and Run

    make
    ./minishell

## License

MIT. See the LICENSE file.