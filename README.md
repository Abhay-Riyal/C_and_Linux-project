# C_and_Linux-project
This project can only run in a linux distribution as multiple linux specific functions and scripts are used.

# Problem Statement:
~ store information in a away that even after the program terminates , we can still access the information.
~ make the input of password safe.
~ search the username and only allow signup if the username doesn't exist already.
~ user is only allowed to delete an account if they know the password associated with it.

# Solution:
~ This problem is solved with the help of files , so rather than storing information in the program(RAM) we put it inside files(hard disk) so it doesn't get deleted after termination of the program.
~ This problem is solved by using getch() function , as it takes input by keypress and doesnt show the output on the terminal as it disables echo.
~ This problem is solved by using grep command .
~ This problem is solved by writing and reading information in a certain way , so that a particular username is associated with a specific password and you get access to that username only if you know the passsword associated with it. 
