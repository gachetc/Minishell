# Minishell

A simplified shell implementation written in C, inspired by bash. This is a 42 school project.

## Features

- Interactive prompt with user, shell level and color display
- Command execution with absolute/relative paths and `$PATH` resolution
- Pipes (`|`) to chain commands
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Built-in commands:
  - `echo` (with `-n` option)
  - `cd` (with relative/absolute path, `~`, `..`)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Requirements

- macOS or Linux
- `gcc`
- `make`
- `readline` library (installed via Homebrew on macOS)

## Build

```bash
make        # compile the project
make clean  # remove object files
make fclean # remove object files and executable
make re     # full recompile
```

## Usage

```bash
./minishell
```

## Project structure

```
.
├── Makefile
├── includes/
│   └── minishell.h
├── src/
│   ├── Main/           # Entry point
│   ├── Builtin/        # Built-in commands (cd, echo, env, exit, export, pwd, unset)
│   ├── Lexer/          # Tokenization of input
│   ├── Parse/          # Command parsing, redirections, heredoc
│   ├── Envvar/         # Environment variable expansion
│   ├── Execute/        # Command execution, pipes, redirections
│   ├── Signals/        # Signal handling
│   ├── Get_input/      # Readline input and validation
│   ├── Cleanup/        # Memory management and freeing
│   ├── Lib_utils/      # Utility functions
│   └── init/           # Shell initialization
└── Libft/              # Custom C library (libft, ft_printf, get_next_line)
```

## Authors

42 school project.
