# Operating Systems - Lab 1: Bash Scripting

This repository contains the solution for Lab 1 of the Operating Systems course at Cairo University, Computer Engineering Department.

## Overview

The goal of this lab is to practice Linux command-line operations and Bash scripting, focusing on:

- File and directory manipulation (mkdir, touch, cp, rm)
    
- Text processing (echo, sort, uniq, tr, grep, sed)
    
- File permissions (chmod)
    
- Input/Output redirection and piping
    

## Environment

- OS: Linux (Ubuntu via WSL2 recommended)
    
- Editor: Visual Studio Code with WSL Extension
    
- Interpreter: Bash (/bin/bash)
    

## Script Requirements

The main script req_1_firstName_secondName_ID.sh implements the following automated workflow:

1. Workspace Management: Cleans up previous Lab1 directories and initializes a new environment.
    
2. File Operations: Copies source files (words.txt, numbers.txt) and generates a side-by-side merged version.
    
3. Data Analysis:
    

- Displays the top 3 entries of the merged content.
    
- Generates a sorted version in SortedMergedContent.txt.
    
- Removes duplicates on-the-fly for terminal display.
    

4. Security & Permissions: Restricts read access to the sorted results to demonstrate permission management.
    
5. Advanced Text Processing:
    

- Case conversion (Lowercase to Uppercase) with troubleshooting for file access issues.
    
- Pattern matching using Regex to find lines starting with "w" and ending with digits.
    
- Global character replacement (substituting "i" with "o").
    

6. Comparison: Displays original and modified files side-by-side for verification.
    

## How to Run

1. Ensure the script has executable permissions:  
    chmod u+x req_1_firstName_secondName_ID.sh  
      
    
2. Execute the script:  
    ./req_1_firstName_secondName_ID.sh  
    
    

ID: [Your ID]**
