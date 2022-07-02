#include <linux/printk.h>

// Cool hello-saying syscall (it is for testing)
void sys_hello()
{
	printk("Hello!");
}

