#include "syscall.h"
#include "user.h"

// #include "proc.h"
// #include "types.h"
// #include "defs.h"
// #include "param.h"
// #include "memlayout.h"
// #include "mmu.h"
// #include "x86.h"
// #include "spinlock.h"

// #include "stat.h"
// #include "fs.h"
// #include "fcntl.h"
// #include "traps.h"


void cpu_bound(){
    int j=0, k=0;
    for(j=0; j<100; j++){
        while(k<1000000){
            k++;
        }
    }
}

void s_cpu(){
    int j=0, k=0;
    for(j=0; j<100; j++){
        while(k<1000000){
            k++;
        }
        yield();
    }
}

void io_bound(){
    //simulate 100 IO calls
    int j=0;
    for(j=0; j<100; j++){
        sleep(1);
    }
}


void sanity(int n){
    int stop = 3*n;
    int i = 0;

    for(i=0; i<stop; i++){
        //fork

        //wait - wait2

        if(p->pid % 3 == 0){ //CPU-Bound process
            cpu_bound();
            
        }

        else if(p->pid % 3 == 1){ //S-CPU process
            s_cpu();
        }

        else if(p->pid % 3 == 2){ //IO-Bound process
            io_bound();
        }
    }

    //para cada processo terminado
    if(p->pid % 3 == 0){ //CPU-Bound process
        cprintf("%d, CPU-Bound\n", p->pid);
        cprintf("%d, %d, %d\n\n", p->retime, p->rutime, p->stime);
    }

    else if(p->pid % 3 == 1){ //S-CPU process
        cprintf("%d, S-Bound\n", p->pid);
        cprintf("%d, %d, %d\n\n", p->retime, p->rutime, p->stime);
    }

    else if(p->pid % 3 == 2){ //IO-Bound process
        cprintf("%d, IO-Bound\n", p->pid);
        cprintf("%d, %d, %d\n\n", p->retime, p->rutime, p->stime);
    }

}