# Minesweeper Game
This Minesweeper game project is developed in C as part of my college project. Minesweeper is a classic puzzle game where the objective is to clear a grid of hidden mines without detonating any of them.

## Features
- Classic Minesweeper gameplay with different difficulty levels.
- Command-line interface for easy interaction.
- Safe and user-friendly interface.
- Support for marking potential mine locations with flags.

## Prerequisites
Before you begin, ensure you have met the following requirements:

- A C compiler (e.g., GCC) installed on your system.
- Basic familiarity with the command line.
- (Optional) An ANSI color-supporting terminal for enhanced user experience.

## Installation
Clone this repository to your local machine using:
- git clone https://https://github.com/priyanshum143/Minesweeper

## How to Play  
- The game grid consists of cells, some of which contain hidden mines.
- Your goal is to clear all non-mine cells without triggering any mines.
- Use the row and column number to navigate the grid.
- If you suspect a cell contains a mine, you can flag it by entering "99 99" instead of row and col and then enter the location of cell containing a mine.
- If you think you have flagged a wrong cell then enter "99 99" instead of row and column and then enter the location of cell from which you want to remove flag
    and then enter 1.
- The game ends when you either clear all safe cells or trigger a mine.
