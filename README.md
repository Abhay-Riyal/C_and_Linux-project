# C_and_Linux-project
This project can only run in a linux distribution as multiple linux specific functions and scripts are used.

## Problem Statement:
1. store information in a away that even after the program terminates , we can still access the information.
2. make the input of password safe.
3. search the username and only allow signup if the username doesn't exist already.
4. user is only allowed to delete an account if they know the password associated with it.

## Solution:
1. This problem is solved with the help of files , so rather than storing information in the program(RAM) we put it inside files(hard disk) so it doesn't get deleted after termination of the program.
2. This problem is solved by using getch() function , as it takes input by keypress and doesnt show the output on the terminal as it disables echo.
3. This problem is solved by using grep command .
4. This problem is solved by writing and reading information in a certain way , so that a particular username is associated with a specific password and you get access to that username only if you know the passsword associated with it. 
