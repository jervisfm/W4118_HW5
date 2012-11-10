#ifndef _OBSCURED_H_
#define _OBSCURED_H_

/**
 * Hides a message somewhere in memory.
 */
void store_super_double_secret_msg(void);

/**
 * Decodes a message hidden in memory.
 * @addr - Address of the page the message is stored in.
 * returns 0 on success, -1 on failure.
 *
 * Note: Function will catch and handle SIGSEGV
 */
int super_double_secret_msg_decoder(void *addr);

#endif
