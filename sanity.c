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
    int retime;
    int rutime;
    int stime;
    int old_retime = 0;
    int old_rutime = 0;
    int old_stime = 0;
    int total_cpu_bound_retime = 0;
    int total_cpu_bound_rutime = 0;
    int total_cpu_bound_stime = 0;
    int total_s_cpu_retime = 0;
    int total_s_cpu_rutime = 0;
    int total_s_cpu_stime = 0;
    int total_io_bound_retime = 0;
    int total_io_bound_rutime = 0;
    int total_io_bound_stime = 0;
    int cpu_bound_count = 0;
    int s_cpu_count = 0;
    int io_bound_count = 0;
    for (i = 0; i < stop; i++)
    {
        int fpid = fork();
        if (fpid == 0)
        {
            int cpid = getpid();
            if (cpid % 3 == 0)
            {
                cpu_bound();
            }
            else if (cpid % 3 == 1)
            {
                s_cpu();
            }
            else if (cpid % 3 == 2)
            {
                io_bound();
            }
            exit();
        }
        else if (fpid > 0)
        {
            wait2(&retime, &rutime, &stime);
            printf(stdout, "PID: %d\n", fpid);
            printf(stdout, "retime: %d\n", retime - old_retime);
            printf(stdout, "rutime: %d\n", rutime - old_rutime);
            printf(stdout, "stime: %d\n", stime - old_stime);
            if (fpid % 3 == 0)
            {
                printf(stdout, "Tipo: CPU-Bound\n");
                cpu_bound_count++;
                total_cpu_bound_retime += retime - old_retime;
                total_cpu_bound_rutime += rutime - old_rutime;
                total_cpu_bound_stime += stime - old_stime;
            }
            else if (fpid % 3 == 1)
            {
                printf(stdout, "Tipo: S-CPU\n");
                s_cpu_count++;
                total_s_cpu_retime += retime - old_retime;
                total_s_cpu_rutime += rutime - old_rutime;
                total_s_cpu_stime += stime - old_stime;
            }
            else if (fpid % 3 == 2)
            {
                printf(stdout, "Tipo: IO-Bound\n");
                io_bound_count++;
                total_io_bound_retime += retime - old_retime;
                total_io_bound_rutime += rutime - old_rutime;
                total_io_bound_stime += stime - old_stime;
            }
            printf(stdout, "\n");
            old_retime = retime;
            old_rutime = rutime;
            old_stime = stime;
        }
    }

    printf(stdout, "Total de processos cpu_bound: %d\n", cpu_bound_count);
    printf(stdout, "retime medio: %d\n", total_cpu_bound_retime / cpu_bound_count);
    printf(stdout, "rutime medio: %d\n", total_cpu_bound_rutime / cpu_bound_count);
    printf(stdout, "stime medio: %d\n\n", total_cpu_bound_stime / cpu_bound_count);

    printf(stdout, "Total de processos s_cpu: %d\n", s_cpu_count);
    printf(stdout, "retime medio: %d\n", total_s_cpu_retime / s_cpu_count);
    printf(stdout, "rutime medio: %d\n", total_s_cpu_rutime / s_cpu_count);
    printf(stdout, "stime medio: %d\n\n", total_s_cpu_stime / s_cpu_count);

    printf(stdout, "Total de processos io_bound: %d\n", io_bound_count);
    printf(stdout, "retime medio: %d\n", total_io_bound_retime / io_bound_count);
    printf(stdout, "rutime medio: %d\n", total_io_bound_rutime / io_bound_count);
    printf(stdout, "stime medio: %d\n\n", total_io_bound_stime / io_bound_count);
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    sanity(n);
    exit();
}
