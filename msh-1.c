/*
Name: Marium Mannan
ID: 1001541605
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <stdbool.h>

#define WHITESPACE " \t\n"   //github code
#define MAX_COMMAND_SIZE 256 //github code
#define MAX_NUM_ARGUMENTS 10 //requirement 7
#define MAX_PIDS_PRINTED 15  //requirement 11
#define MAX_CMDS_PRINTED 15  //requirement 12


int main(){ 
  int i;//for for loops

  //save user input in cmd_str
  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
  
  //keeping track of all the commands
  //cmdCounter: # of commands user has input so far
  int cmdCounter = 0;
  char pastCmd[MAX_COMMAND_SIZE][MAX_CMDS_PRINTED];
  
  

  //keeps track of all the pids in an array
  //int n: # of pids spawned so far
  int n = 0;
  int pidNums[MAX_PIDS_PRINTED];


  while( 1 ) {
    //clear cmd_str for next input
    memset(cmd_str, 0, MAX_COMMAND_SIZE);
    //---------------github code------------------
    printf ("msh> ");
    //REQUIREMENT 4 + 6
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );
    //---------------github code------------------


    //REQUIREMENT 5
    //quit if 'exit' or 'quit'
    if((strncmp(cmd_str, "exit", 4) == 0) || 
    strncmp(cmd_str, "quit", 4) == 0){
      break;
    }


    //save current command in the past commands array
    strcpy(pastCmd[cmdCounter], cmd_str);
    cmdCounter++;


    //---------------github code------------------
    char *token[MAX_NUM_ARGUMENTS];
    int token_count = 0;                                 
    char *argument_ptr;                                  char *working_str  = strdup( cmd_str );                
    char *working_root = working_str;

    while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) &&
    (token_count<MAX_NUM_ARGUMENTS)){
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 ){
        token[token_count] = NULL;
      }
        token_count++;
    }
    //---------------github code--------------------

    //to keep track of the command
    //if none of the custom shell commands
    //then use the exec command
    bool valid = false;

    //REQUIREMENT 12
      //check if running past commands
      if(strncmp(token[0],"!",strlen("!")) == 0){
        //valid = true; //dont have to run exec
        //split the ! and number
        char *histNumCHAR = strtok(cmd_str, "!");
        int histNum = atoi(&histNumCHAR[0]);
        
        //run if valid command number:
        if(histNum < cmdCounter-1){
          printf("Executing command[%d]: %s", histNum, pastCmd[histNum]);
          //split and update token
          cmd_str = pastCmd[histNum];
          working_str  = strdup( cmd_str );
          token_count = 0; 
          while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) &&
          (token_count<MAX_NUM_ARGUMENTS)){
            token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
            if( strlen( token[token_count] ) == 0 ){
              token[token_count] = NULL;
            }
            token_count++;
          }
        }
        else{
          valid = true;
          printf("Cannot execute command\n");
        }
      }

      //REQUIREMENT 10
      //check if cd command
      if(strncmp(token[0],"cd",2) == 0){
        valid = true; //dont have to run exec
        chdir(token[1]);
      }

      //REQUIREMENT 11
      //check if showpids command
      if(strncmp(token[0],"showpids",8) == 0){
        valid = true; //dont have to run exec
        
        //set n to 15 if more than 15 to show first 15
        if(n > MAX_PIDS_PRINTED){
          n = MAX_PIDS_PRINTED;
        }

        //print the pids
        for(i = 0; (i < n); i++){
          printf("%d: %d\n", i, pidNums[i]);
        }
      }

      //REQUIRENT 12
      //check if history command
      if(strncmp(token[0],"history",7) == 0){
        valid = true; //dont have to run exec
        int startVal;

        //if more than 15 past commands
        //display the last 15
        if(cmdCounter > MAX_CMDS_PRINTED){
          //if n > 15 then start the loop at 
          //n-15th value to show last 15
          startVal = cmdCounter - MAX_CMDS_PRINTED; 
        }

        //if less than 15 commands display from
        //the start
        else{
          startVal = 0;
        }
        
        for(i = startVal; i < cmdCounter; i++){
          printf("%d: %s\n", i, pastCmd[i]);
        }

      }

    //REQUIREMENT 8
    //run basic shell commands
    pid_t pid = fork();
    //save the pid to be printed later and update array
    pidNums[n] = pid; n++;

    //inside child 
    if(pid == 0){

      
      if(valid != true){
        //github example of execvp
        int ret = execvp(token[0], &token[0]);
        if(ret == -1){
          //REQUIREMENT 2
          printf(": Command not found--\n");
        }
      }
      _exit(0);
    
    }

    //Parent 
    else{
      //wait till all child processes are done
      int status;
      waitpid(pid, &status, 0);
    }
    
    free( working_root );//github 

  }
  
  }
  
  


