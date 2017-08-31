Operating Systems Assignment 1
===============================

## Usage :

<executable> <source> <destination> <symlink name>

## Eg input:

`./a.out input.txt output.txt symlink.txt`

## Eg output:

File Reversed
Symlink Created : YES
Symlink Verified : YES
Directory Created
File Created : YES
Task 2.3.1 (Directory Permissions) : rwx --- ---
Task 2.3.2 (File Permissions) : rw- --- ---
Task 2.3.2 (Symlink Permissions) : rwx rwx rwx
Task 2.4 DONE


## Eg tree structure of current folder:

.
├── a.out
├── Assignment
│   └── output.txt
├── input.txt
├── main.c
├── README.md
└── symlink.txt -> Assignment/output.txt


## Task 1 : Reverse the file

Given a file, you need to reverse the contents of that file and invert the case of each English
character in the file and store the result in a new file within a new directory named
“Assignment”. The file and directory thus created, can only be read/written by the
user who created it.


## Task 2:

### Task 2.1:

Create a symlink to the above created file in “Assignment/.."”(Directory where the original file is present).

### Task 2.2:

#### Task 2.2.1:

Verify the creation of the symlink.

#### Task 2.2.2:

Verify the creation of the new file and new directory created in the above part of question.

### Task 2.3:

Check permissions for the three files mentioned in the above point.

### Task 2.4:

Check if the file created is reversed and case-inverted version of the input file.

