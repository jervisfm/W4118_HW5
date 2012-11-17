#define _GNU_SOURCE
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <syscall.h>
#include <unistd.h>

#include "obscured.h"

#define __NR_expose_page_table 376

#define PAGE_TABLE_SIZE (4*1024*1024) /* 4mb */

/* Some helpful macros */
#define pg_num_to_idx(num) (((num / 512 * 4096) / 4) + (num % 512))
#define get_page(page_table, num) \
		page_table[pg_num_to_idx(num)]


/* Wrapper around expose_page_table() system call - do not modify! */
static unsigned int *expose_page_table()
{
	int i, fault;
	int fd = open("/dev/zero", O_RDONLY);
	unsigned int *addr = mmap(NULL, PAGE_TABLE_SIZE * 2, PROT_READ,
				 MAP_SHARED, fd, 0);
	close(fd);
	if (addr == MAP_FAILED) {
		perror("mmap failed");
		return NULL;
	}
	/* Fault now to avoid handling in kernel */
	for (i = 0; i < (PAGE_TABLE_SIZE * 2) / 4; ++i)
		fault = addr[i];
	if (syscall(__NR_expose_page_table, addr) < 0) {
		perror("expose_page_table syscall failed");
		return NULL;
	}
	return addr;
}

/* Find the super secret secret message */
int main(int argc, char **argv)
{
	/* Obtain page table mapping */
	unsigned int *page_table = expose_page_table();
	if (page_table == NULL)
		return EXIT_FAILURE;

	store_super_double_secret_msg();

	/* Identify modified pages here */

	/* Try to decode modified pages here
	 * super_double_secret_msg_decoder();
	 */

	return EXIT_SUCCESS;
}
