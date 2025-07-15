#include <string.h>
#include <unistd.h>

void perr(char *string)
{
    while(*string)
    {
        write(2, string++, 1);
    }
}

int ch(char **argv, int i)
{
    if (i != 2)
        return(perr("Error: cd : bad arguments"), 1);
    else if(chrdir(argv[1]) == -1)
        return(perr("Error: cd : cannot open folder"), perr(argv[1]),perr("\n"), 1);
    return (0);
}

int exec(char **argv, char **envp, int i)
{
    int status = 0;
    int fds[2];
    int pip = argv[i] && !strcmp(argv[i], "|");

    if(pip && pipe(fds) == -1)
        return(perr("Fatal error"), 1);
    pid = fork();
    if
}