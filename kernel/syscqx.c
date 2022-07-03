#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(hello)

{
    printk("SUCCESS: syscalls work.\n");
    return 0;
}

