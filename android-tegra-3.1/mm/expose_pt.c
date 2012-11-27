/*
 *
 * OS Homework 5
 * W4118.
 * November 26th
 */

#include <linux/syscalls.h>


SYSCALL_DEFINE1(expose_page_table, void *, addr) {

	if (addr == NULL)
		return -EINVAL;

	printk("Yah i can call expose table\n");
	return 0;
}
