<h1 align="center">🐚 Minishell 👨‍💻</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge" alt="Language C">
</p>

<p align="center">
  <img src="https://carlalexander.ca/uploads/2018/09/sai-kiran-anagani-555972-unsplash.jpg" width="500" alt="Command Line Interface">
  <br>
  <em>A custom implementation of a command-line shell, built for a 42 school project.</em>
</p>

## 📖 Table of Contents
- [About The Project](#-about-the-project)
- [Features](#-features)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#-installation)
- [Usage](#-usage)
  - [Examples](#examples)
- [Authors](#-authors)

## 🤔 About The Project

This project is a custom-built command-line interpreter created as part of the curriculum at **42 School**. It emulates a subset of the functionality found in standard shells like `bash`, providing a hands-on understanding of process management, file descriptor manipulation, and command parsing in a Unix-like environment.

The goal is to create a simple yet functional shell that can run commands, manage environment variables, and handle complex command chains involving pipes and redirections.

## ✨ Features

-   **Command Execution**: Parses and executes commands from the system's `PATH`.
-   **Built-in Commands**: Includes essential built-ins for shell functionality.
    -   `echo` with the `-n` option.
    -   `cd` to change directories.
    -   `pwd` to display the current directory.
    -   `export` to manage environment variables.
    -   `exit` to terminate the shell.
-   **Pipes (`|`)**: Chains multiple commands, redirecting the output of one to the input of another.
-   **Redirections**:
    -   Input redirection: `<`
    -   Output redirection: `>`
    -   Append output redirection: `>>`
-   **Signal Handling**: Gracefully handles `Ctrl-C` (SIGINT) and `Ctrl-D` (EOF).
-   **Environment Variable Expansion**: Expands variables like `$PATH` in commands.

## 🏁 Getting Started

Follow these steps to get the project up and running on your local machine.

### Prerequisites

You'll need a C compiler (like `gcc`), `make`, and the `readline` library.

- On **Debian/Ubuntu**:
  ```sh
  sudo apt-get install build-essential libreadline-dev
  ```
- On **macOS** (with Homebrew):
  ```sh
  brew install readline
  ```

### Installation

1.  Clone the repository:
    ```sh
    git clone https://github.com/murdex5/minishell.git
    ```
2.  Navigate to the project directory:
    ```sh
    cd minishell
    ```
3.  Compile the project using `make`:
    ```sh
    make
    ```

## 🚀 Usage

Run the compiled executable from your terminal to start the shell.

```sh
./minishell
```

### Examples

Here are a few examples of commands you can run in `minishell`:

1.  **Execute a simple command:**
    ```sh
    minishell$ ls -la
    ```
2.  **Use a built-in and redirect output:**
    ```sh
    minishell$ echo "Hello Minishell!" > greeting.txt
    ```
3.  **Chain commands with a pipe:**
    ```sh
    minishell$ cat /dev/random | head -c 100 | wc -c
    ```
4.  **Manage environment variables:**
    ```sh
    minishell$ export GREETING="Welcome"
    minishell$ echo $GREETING
    ```

## ✍️ Authors

**murdex5** - [GitHub Profile](https://github.com/murdex5)

**anjofficial** - [GitHub Profile](https://github.com/anjofficial)
