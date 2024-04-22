#include "library.h"

int main(void)
{
    char cmd[128];
    int status;

    while (1)
    {
        printf("$ ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n");
                break;
            }
            else
            {
                perror("fgets");
                continue;
            }
        }


        cmd[strcspn(cmd, "\n")] = '\0';

        if (strcmp(cmd, "exit") == 0)
        {
            break;
        }
        else
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
              
                if (execlp(cmd, cmd, NULL) == -1)
                {
                    perror("execlp");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
               
                if (waitpid(pid, &status, 0) == -1)
                {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return 0;
}

