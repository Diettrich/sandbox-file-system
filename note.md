# Notes

### 21/01/2020

#### Z.Anouar:

new notes: (OBSOLETE)

- I initially started with the implementation of the `mkdir` command, which in hindsight, was not the optimal choice.
  It
  would have been more appropriate to begin with the `ls` and/or `cd` commands.
- The `mkdir` command required a significant number of utility functions.
- The code was not modular, and a solution to this issue was needed.

### 23/01/2020

#### Z.Anouar:

new notes: (OBSOLETE)

- Added ls and cd along with their dependencies.
- So far, cd and ls are working well, please report any bugs!
- The other functions are not working.
- The code is still not modular.

### 27/01/2024 (after the new version)

#### Z.Anouar:

In the past, the project was disorganized and lacked modularity, leading to functionality issues. However, I have since
overhauled the project, enhancing its modularity and improving its overall performance. The commands ls, cd, mkdir, pwd,
and exit have been re-implemented successfully. Additionally, several modules have been introduced:

- `commands`: This module defines the structure and functionalities of various shell commands. It includes the Command
  structure, which represents a command, and functions to execute each command such as ls, cd, mkdir, pwd, and exit.
- `commands_helper`: This module assists in the parsing and execution of commands. It includes functions to parse a
  command string into a Command structure, determine the type of command, and extract command arguments.
- `file_node`: This module is responsible for the representation and manipulation of files and directories in the
  emulated
  file system. It includes the FileNode structure, which represents a file or a directory, and functions to create,
  append, and retrieve FileNode instances.
- `file_path_utils`: This module provides utilities for handling file paths. It includes functions to retrieve a
  FileNode
  from a given path and to generate a path from a FileNode.
- `path`: This module is responsible for the representation and manipulation of paths. It includes the Path structure,
  which represents a path, and functions to create and destroy Path instances.
- `shell`: This module is the core of the file system emulator. It includes the Shell structure, which represents the
  state of the shell, and functions to initialize the shell, execute commands, and run the shell loop.
- `utils`: This module provides general utility functions used across the project. It includes functions to split a
  string
  into tokens and join tokens into a string.

