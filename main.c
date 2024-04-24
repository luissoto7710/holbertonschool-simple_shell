#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *prompt = "$ ";
    int last_status = 0;

    while (printf("%s", prompt), (read = getline(&line, &len, stdin)) != -1) {
        last_status = execute_command(line);
    }

    free(line);
    return last_status;
}

