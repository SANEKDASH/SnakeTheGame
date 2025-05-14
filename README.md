# SnakeTheGame

This is a classic game "Snake" written on C++ language.

> [!NOTE]
> Works atleast on Ubuntu Linux 22.04


## Instalation
- https:
```bash
  git clone https://github.com/SANEKDASH/SnakeTheGame.git
```
- ssh:
```bash
  git clone git@github.com:SANEKDASH/SnakeTheGame.git
```

To run the snake with the SFML graphics you need to install SFML library:
```bash
  sudo apt-get install libsfml-dev
```
Then go to the project directory:
```bash
  cd SnakeTheGame
```
And run the build command:
```bash
  make
```

Now you have `snake` executable.

> [!WARNING]
> Boot the `snake` executable only from the project directory.

## Boot options
| Flag | Description              | Argument          |
|------|--------------------------|-------------------|
| `-b <number>` | Regulates amount of bots | amount of bots    |
| `-g`          | Boot with the SFML view  |     -             |
| `-t`          | Boot with terminal view  | -                |
| `-p "udlr"`   | Adds the second player   |  'u' - keyboard char for moving up <br> 'd' - keyboard char for moving up down <br> 'l' - keyboard char for moving up left <br>'r' - keyboard char for moving up right |



