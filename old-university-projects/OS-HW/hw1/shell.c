#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include "tokenizer.h"

/* Convenience macro to silence compiler warnings about unused function parameters. */
#define unused __attribute__((unused))

/* Whether the shell is connected to an actual terminal or not. */
bool shell_is_interactive;

/* File descriptor for the shell input */
int shell_terminal;

/* Terminal mode settings for the shell */
struct termios shell_tmodes;

/* Process group id for the shell */
pid_t shell_pgid;

int cmd_exit(struct tokens *tokens);
int cmd_pwd(struct tokens *tokens);
int cmd_cd(struct tokens *tokens);
int cmd_help(struct tokens *tokens);

/* Built-in command functions take token array (see parse.h) and return int */
typedef int cmd_fun_t(struct tokens *tokens);

/* Built-in command struct and lookup table */
typedef struct fun_desc {
  cmd_fun_t *fun;
  char *cmd;
  char *doc;
} fun_desc_t;

fun_desc_t cmd_table[] = {
  {cmd_help, "?", "show this help menu"},
  {cmd_pwd, "pwd", "prints the working directory"},
  {cmd_cd, "cd", "changes the directory"},
  {cmd_exit, "exit", "exit the command shell"},
};

/* Prints a helpful description for the given command */
int cmd_help(unused struct tokens *tokens) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    printf("%s - %s\n", cmd_table[i].cmd, cmd_table[i].doc);
  return 1;
}

int cmd_pwd(unused struct tokens *tokens) {
  printf("%s\n", getcwd(0, 0));
  return 1;
}

int cmd_cd(unused struct tokens *tokens) {
  if (tokens_get_length(tokens) == 1) {
    chdir(getenv("HOME"));
  } else {
    chdir(tokens_get_token(tokens, 1));
  }

  return 1;
}

/* Exits this shell */
int cmd_exit(unused struct tokens *tokens) {
  exit(0);
}

/* Looks up the built-in command, if it exists. */
int lookup(char cmd[]) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    if (cmd && (strcmp(cmd_table[i].cmd, cmd) == 0))
      return i;
  return -1;
}

/* Intialization procedures for this shell */
void init_shell() {
  /* Our shell is connected to standard input. */
  shell_terminal = STDIN_FILENO;

  /* Check if we are running interactively */
  shell_is_interactive = isatty(shell_terminal);

  if (shell_is_interactive) {
    /* If the shell is not currently in the foreground, we must pause the shell until it becomes a
     * foreground process. We use SIGTTIN to pause the shell. When the shell gets moved to the
     * foreground, we'll receive a SIGCONT. */
    while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
      kill(-shell_pgid, SIGTTIN);

    /* Saves the shell's process id */
    shell_pgid = getpid();

    /* Take control of the terminal */
    tcsetpgrp(shell_terminal, shell_pgid);

    /* Save the current termios to a variable, so it can be restored later. */
    tcgetattr(shell_terminal, &shell_tmodes);
  }
}

int main(unused int argc, unused char *argv[]) {
  init_shell();

  static char line[4096];
  int line_num = 0;

  /* Please only print shell prompts when standard input is not a tty */
  if (shell_is_interactive)
    fprintf(stdout, "%d: ", line_num);

  while (fgets(line, 4096, stdin)) {
    /* Split our line into words. */
    struct tokens *tokens = tokenize(line);

    /* Find which built-in function to run. */
    int fundex = lookup(tokens_get_token(tokens, 0));

    if (fundex >= 0) {
      cmd_table[fundex].fun(tokens);
    } else {
      pid_t pid;
      
      if ((pid = fork()) == -1)
        perror("fork error");
      else if (pid == 0) {
        char *arguments[99] = {tokens_get_token(tokens, 0)};
        
        for (unsigned int i = 1; i < tokens_get_length(tokens); i++) {
          arguments[i] = tokens_get_token(tokens, i);
        }

        arguments[tokens_get_length(tokens)] = NULL;

        /*
        if (strchr(tokens_get_token(tokens, 0), '/') != NULL) {
          execv(tokens_get_token(tokens, 0), arguments);
        } else {
          FILE *filePointer;
          char whichOutput[256];
          char *command = "which ";
          strcat(command, tokens_get_token(tokens, 0));

          filePointer = popen(command, "r");

          while (fgets(whichOutput, sizeof(whichOutput), filePointer) != NULL) {
            strcpy(arguments[0], whichOutput);
            execv(tokens_get_token(tokens, 0), arguments);
          }

          pclose(filePointer);
        }
        */

        if (access(tokens_get_token(tokens, 0), F_OK) != -1 && access(tokens_get_token(tokens, 0), X_OK) != -1) {
          execv(tokens_get_token(tokens, 0), arguments);
        } else {
          char *path = getenv("PATH");
          char *part;

          while ((part = strsep(&path, ":"))) {
            char program[1024];

            strcpy(program, part);
            strcat(program, "/");
            strcat(program, tokens_get_token(tokens, 0));

            if (access(program, F_OK) != -1 && access(program, X_OK) != -1) {
              strcpy(arguments[0], program);
              execv(program, arguments);
            }
          }
        }
      
        _exit(0);
      }
    }

    if (shell_is_interactive)
      /* Please only print shell prompts when standard input is not a tty */
      fprintf(stdout, "%d: ", ++line_num);

    /* Clean up memory */
    tokens_destroy(tokens);
  }

  return 0;
}
