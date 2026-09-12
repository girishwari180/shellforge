#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Command structure
 * Stores all words entered by the user.
 */
typedef struct {
    char *args[64];
    int count;
} Command;

/*
 * parse_command()
 * Splits the input line into individual words.
 */
void parse_command(char *line, Command *cmd)
{
    cmd->count = 0;

    char *token = strtok(line, " \t");

    while (token != NULL && cmd->count < 63) {
        cmd->args[cmd->count] = token;
        cmd->count++;

        token = strtok(NULL, " \t");
    }

    cmd->args[cmd->count] = NULL;
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;

    Command cmd;

    while (1) {
        printf("shellforge$ ");
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1)
            break;

        /* Remove newline character */
        if (strlen(line) > 0 &&
            line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        /* Organize the input */
        parse_command(line, &cmd);

        /* Ignore empty input */
        if (cmd.count == 0)
            continue;

        /* Exit command */
        if (strcmp(cmd.args[0], "exit") == 0)
            break;

        printf(
            "Structure Log -> command : %s | Arguments found: %d\n",
            cmd.args[0],
            cmd.count - 1
        );
    }

    free(line);

    return 0;
}
