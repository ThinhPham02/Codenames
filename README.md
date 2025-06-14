# CodeNames

Welcome to **CodeNames**, a thrilling console game inspired by the popular board game where two rival teams compete to identify their secret agents using clever one-word clues.

---

## Table of Contents

- [Overview](#overview)  
- [How to Play](#how-to-play)  
- [Features](#features)  
- [Setup and Running](#setup-and-running)  
- [Files](#files)  
- [Game Flow](#game-flow)  
- [License](#license)  

---

## Overview

Two spymasters know the secret identities of 25 agents represented by single-word codenames arranged on a 5x5 grid. Each team aims to contact all their agents before the opponent does, but be cautious — one codename belongs to an assassin. Guess the assassin and your team loses instantly!

---

## How to Play

- The board contains 25 codenames arranged in a 5x5 grid.
- Each codename belongs to one of:
  - Red agents
  - Blue agents
  - Bystanders (neutral)
  - Assassin (instant loss if guessed)
- Spymasters give a one-word clue plus a number indicating how many codenames relate to the clue.
- Teammates guess codenames based on the clue.
- Guessing a teammate’s agent lets you continue guessing.
- Guessing a bystander or opposing agent ends your turn.
- Guessing the assassin ends the game immediately with a loss.

---

## Features

- Randomly generated 5x5 board from a dictionary file.
- Key card indicates which codenames belong to which team, bystanders, or assassin.
- Input validation prevents clues that reveal codenames on the board.
- Turn-based gameplay for two teams.
- Display board updates with guessed codenames revealed.
- Saves the key card to `KeyCard.txt` for reference.

---

## Setup and Running

1. Ensure you have a file named `Dictionary.txt` containing a list of words (one per line) for the game to pick codenames from.
2. Compile the code with a C++ compiler, e.g.:
   ```bash
   g++ -o codenames codenames.cpp
