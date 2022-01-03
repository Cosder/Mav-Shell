# Mav-Shell
Shell program, Mav shell (msh), similar to  bourne shell (bash), c-shell (csh), or korn shell (ksh). It will accept commands, fork a child  process and execute those commands. The shell, like csh or bash, will run and accept  commands until the user exits the shell. 

# Functionality
1) Program will print out a prompt of msh> when it is ready to 
accept input. It must read a line of input and, if the command given is a supported shell 
command, it shall execute the command and display the output of the command.

2) If the command is not supported prints the invalid 
command followed by “: Command not found.”. If the command option is an invalid option then prints
the command followed by “: invalid option --” and the option that was invalid as 
well as a prompt to try —help. After each command completes, program prints the msh> 
prompt and accept another line of input. 

3) Shell will exit with status zero if the command is “quit” or “exit”. 

4) Mav shell shall supports up to 10 command line 
parameters in addition to the command.  
Supports and executes any command entered. Any 
command in /bin, /usr/bin/, /usr/local/bin/ and the current working directory.
Shell searches in the following PATH order:  
1. Current working directory,  
2. /usr/local/bin 
3. /usr/bin 
4. /bin  
Parameters may also be combined. For example, ps may be executed as: ps –aef or ps 
–a –e -f  

5) Shell shall supports the cd command to change directories.

6) Shell supports the showpids command to list the PIDs of 
the last 15 processes spawned by your shell. If there have been less than 15 processes 
spawned then it shall print only those process PIDs  

7) Shell supports the history command which will list the last 
15 commands entered by the user. Typing !n, where n is a number between 1 and 15 will 
result in your shell re-running the nth command.  If the nth command does not exist then 
your shell will state “Command not in history.”.  The output shall be a list of 
numbers 1 through n and their commands, each on a separate line, single spaced. If nth command is 
also !k (k being some number) command does not execute. If there are less than 15 commands in the history 
only lists the commands the user has 
entered up to that point.


