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

void s_cpu()
{
    int j = 0, k = 0;
    for (j = 0; j < 100; j++)
    {
        while (k < 1000000)
        {
            k++;
        }
        yield();
    }
}

void io_bound()
{
    //simulate 100 IO calls
    int j = 0;
    for (j = 0; j < 100; j++)
    {
        sleep(1);
    }
}

void sanity(int n)
{
    int stop = 3 * n;
    int i = 0;

    for (i = 0; i < stop; i++)
    {
        int retime, rutime, stime;
        int pid = fork();
        if (pid == 0)
        { // Processo pai
            wait2(&retime, &rutime, &stime);
            printf(stdout, "retime: %d\n", retime);
            printf(stdout, "rutime: %d\n", rutime);
            printf(stdout, "stime: %d\n", stime);
            printf(stdout, "\n");
        }
        else if (pid > 0)
        { // Processo filho
            printf(stdout, "PID: %d\n", pid);
            if (pid % 3 == 0)
            { //CPU-Bound process
                printf(stdout, "Tipo: CPU-Bound\n");
                cpu_bound();
            }
            else if (pid % 3 == 1)
            { //S-CPU process
                printf(stdout, "Tipo: S-CPU\n");
                s_cpu();
            }
            else if (pid % 3 == 2)
            { //IO-Bound process
                printf(stdout, "Tipo: IO-Bound\n");
                io_bound();
            }
            exit();
        }
    }
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    sanity(n);
    exit();
}
