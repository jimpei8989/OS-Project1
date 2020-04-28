#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage void sys_my_printk(char *s){
    printk(s);
    return;
}
