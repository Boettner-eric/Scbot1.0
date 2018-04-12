# Scbot 1.0

* An algorithm for solving permutations and finding scrabble legal words from random strings of characters

### Features
* A simple lookup function to find if a string is a scrabble legal word
* An algorithm for finding all possible combinations of a string and testing each one against a dictionary.
* Simple debug file with all prior strings and time for each computation
* Clear "best" word and score computation
* Uses simple txt files for debugging, listing results and checking strings

### In Progress
* A terminal based game board and smart detection of possible placements
* Concurrency for generating and testing strings
* User input/game mode vs. the computer
* Use class structure to fix score/tmp array
* Better checks for duplicate strings (especially for words with double consonants)
* As each string has *n!*  combinations longer words take much longer to process - this might be reduced by goroutines (requiring a rewrite)or limiting size of words to be greater than some 0 < i < n
* Many bug fixes
