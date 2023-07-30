# Game-Store

This repository contains the source code for a simple Game Store Management System.

The system provides a console-based interface for a game store. It allows for adding new games, buying games, printing information about games, saving game information to a file, and loading game information from a file.

File Structure:

- 'main.c': Contains the main function and the control loop for the application.

Getting Started

Prerequisites:

- C Compiler

Building:

1. Clone the repository:
'git clone https://github.com/pyrylss/Game-Store.git'
2. Navigate into the cloned repository:
'cd Game-Store'
3. Compile the 'main.c' file:
'gcc main.c -o main'
4. Run the compiled file:
'./main'

Features:

- Add a Game: Adds a new game to the database by providing the game name and its price.
- Buy a Game: Buys N units of a game from the database. Increases the total sales of the game.
- Print Game Information: Prints all the game information in the database in descending order based on their total sales.
- Save Game Information: Saves all the game information to a file specified by the user.
- Load Game Information: Loads game information from a file specified by the user.

How to Use:

1. Add a Game: 'A <game_name> <price>'
2. Buy a Game: 'B <game_name> <number_of_units>'
3. Print Game Information: 'L'
4. Save Game Information: 'W <filename>'
5. Load Game Information: 'O <filename>'
6. Exit the Program: 'Q'
