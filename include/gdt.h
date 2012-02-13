#ifndef __GDT_H
#define __GDT_H

extern void gdt_flush ( void );

extern void gdt_install ( void );
extern void gdt_set_gate ( int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran );

struct gdt_entry
{
        unsigned short limit_low;
        unsigned short base_low;
        unsigned char base_middle;
        unsigned char access;
        unsigned char granularity;
        unsigned char base_high;
} __attribute__((packed));



struct gdt_ptr
{
        unsigned short limit;
        unsigned int base;
} __attribute__((packed));

#endif
