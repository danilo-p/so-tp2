#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int stdout = 1;

void cpu_bound()
{
    int j = 0, k = 0;
    for (j = 0; j < 100; j++)
    {
        while (k < 1000000)
        {
            k++;
        }
    }
}

void sanityp(int n)
{
    printf(stdout, "Parent started\n");
    int i = 0;
    for (i = 0; i < n; i++)
    {
        int fpid = fork();
        if (fpid == 0)
        {
            int cpid = getpid();
            int priotity = (cpid % 3) + 1;
            set_prio(priotity);
            printf(stdout, "PID %d started with priority %d.\n", cpid, priotity);
            cpu_bound();
            printf(stdout, "PID %d finished with priority %d.\n", cpid, priotity);
            exit();
        }
    }

    while (wait() > 0);

    printf(stdout, "Parent finished\n");
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    sanityp(n);
    exit();
}
