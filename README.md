# SOShell

**SOShell** is a simple shell (command interpreter) implemented in C. Its purpose is to simulate the basic behavior of a terminal, supporting several built-in commands and additional functionalities, such as file manipulation, mathematical operations, and threading.

## Main Features

- **Customizable Prompt**: The default prompt is `"SOSHELL: Enter a command : prompt>"`, and it can be changed via `PS1=<new_prompt>`.
- **Built-in Commands**:
  - `sair`: Exits the shell.
  - `42`: Displays the famous reference to "The Hitchhiker's Guide to the Galaxy".
  - `obterinfo`: Shows the shell version.
  - `quemsoueu`: Displays current user information (`id`).
  - `cd <directory>`: Changes the current directory.
  - `socp <source> <destination>`: Copies files.
  - `socpthread <source> <destination>`: Copies files using threads.
  - `calc <num1> <op> <num2>`: Simple calculator.
  - `bits <num1> <op> <num2>`: Bitwise operations.
  - `isjpeg <file>`: Checks if a file is a JPEG.
  - `displayBitsOps <num1> <num2>`: Displays bitwise operations between two numbers.
  - `isValid <fd>`: Checks if a file descriptor is valid.
  - `openfile <file>` / `closefd <fd>` / `read <file> <size>`: File operations.
  - `fileinfo`: Displays information about the current file.
  - `aviso <message> <time>`: Displays a warning message after a specified time.
  - `infoCopias`: Shows information about copies made with `socpthread`.
  - `Maior <num1> <num2>`: Displays the larger number.
  - `setx <value>` / `removerl <value>` / `sols <value>`: Additional commands for variable and list manipulation.
  - `history`: Displays command history.
- **External Command Execution**: Unrecognized commands are executed via `exec()`.

## Technologies

- Language: **C**
- Libraries: `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, `fcntl.h`, `pthread.h`, and others.

## Build and Run

1. **Clone the repository**:
   ```bash
   git clone https://github.com/FoodEat12104/soshell.git
   cd soshell

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

