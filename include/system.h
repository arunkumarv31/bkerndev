#ifndef __SYSTEM_H
#define __SYSTEM_H

extern void *memset ( void *dest, char *val, unsigned int count );
extern void outportb (unsigned short _port, unsigned char _data);

extern void timer_install ( int divisior );
extern unsigned char inportb (unsigned short _port);

extern void keyboard_install();

#endif
