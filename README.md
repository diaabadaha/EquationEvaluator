# Infix Equation Evaluator

## Overview
This C program, designed for the COMP2421 course, reads a series of equations from an input file and evaluates them. It processes the equations, which are presented in infix notation, determines their validity, converts valid equations into prefix notation, evaluates them, and outputs the results.

## Repository Contents
- `EquationEvaluator.c`: The core C program file that includes all the logic for parsing, validating, converting, and evaluating infix equations.
- `Project 2 Spring 2023.pdf`: Project specification document outlining the objectives, tasks, and grading criteria for the assignment.

## Features
- Infix notation parsing for an unspecified number of equations from an input file.
- Validity checking of equations to determine whether they are well-formed.
- Conversion of valid infix equations to prefix notation.
- Evaluation of prefix expressions to calculate the results.
- Outputting the results to a designated output file.

## How It Works
1. **Read Equations**: The program prompts the user for the name of the input file and reads the listed equations.
2. **Check Validity**: It verifies each equation to determine if it's valid or not, categorizing and printing the status.
3. **Convert and Evaluate**: Valid equations are converted from infix to prefix notation. The program then evaluates these expressions and prints the outcomes.
4. **Handle Invalid Equations**: Any invalid equations are printed out as specified.
5. **Output to File**: All equations, along with their validity status, converted expressions, and results, are printed to `output.txt`.
6. **Program Exit**: The user can exit the program using the provided menu option.

## Usage
Compile the program with a C compiler, such as gcc.

## Contribution
This project represents individual effort as part of the academic curriculum for COMP2421. Contributions should be limited to suggestions, discussions, and academic feedback.
