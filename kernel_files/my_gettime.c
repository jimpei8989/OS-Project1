#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/timer.h>

asmlinkage void sys_my_gettime(struct timespec *ts){
    getnstimeofday(&ts);
    return;
}
