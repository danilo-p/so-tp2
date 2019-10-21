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
    int retime, rutime, stime, old_retime = 0, old_rutime = 0, old_stime = 0;
    for (i = 0; i < stop; i++)
    {
        int fpid = fork();
        if (fpid == 0)
        {
            int cpid = getpid();
            printf(stdout, "PID: %d\n", cpid);
            if (cpid % 3 == 0)
            {
                printf(stdout, "Tipo: CPU-Bound\n");
                cpu_bound();
            }
            else if (cpid % 3 == 1)
            {
                printf(stdout, "Tipo: S-CPU\n");
                s_cpu();
            }
            else if (cpid % 3 == 2)
            {
                printf(stdout, "Tipo: IO-Bound\n");
                io_bound();
            }
            exit();
        }
        else if (fpid > 0)
        {
            wait2(&retime, &rutime, &stime);
            printf(stdout, "retime: %d\n", retime - old_retime);
            printf(stdout, "rutime: %d\n", rutime - old_rutime);
            printf(stdout, "stime: %d\n", stime - old_stime);
            printf(stdout, "\n");
            old_retime = retime;
            old_rutime = rutime;
            old_stime = stime;
        }
    }
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    sanity(n);
    exit();
}
