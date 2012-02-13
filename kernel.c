#include <system.h>
#include <isrs.h>
#include <screen.h>

struct regs 
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};


extern void gdt_flush ( void );

void gdt_install ( void );
void gdt_set_gate ( int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran );
void idt_set_gate ( unsigned char num, unsigned long base, unsigned short sel, unsigned char flags );
void idt_load ( void );
void idt_install ( void );
void isrs_install ( void ) ;
void fault_handler ( struct regs *r );
void irq_handler ( struct regs *r );

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



struct gdt_entry gdt[3];
struct gdt_ptr gp;



void gdt_set_gate ( int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran )
{
	gdt[num].base_low = base & 0xFFFF;
	gdt[num].base_middle = ( base >> 16 ) & 0xFF;
    	gdt[num].base_high = (base >> 24) & 0xFF;

    	gdt[num].limit_low = (limit & 0xFFFF);
    	gdt[num].granularity = ((limit >> 16) & 0x0F);

    	gdt[num].granularity |= (gran & 0xF0);
    	gdt[num].access = access;
}



void gdt_install ( void )
{
	gp.limit = ( sizeof ( struct gdt_entry ) * 3 ) - 1;
	gp.base = (unsigned int) &gdt;

	gdt_set_gate ( 0, 0, 0, 0, 0 ); //NULL descriptor
	gdt_set_gate ( 1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //Data segment

	gdt_flush();
	printline ("Installed GDT");
}

struct idt_entry
{
	unsigned short base_lo;
	unsigned short sel;
	unsigned char always0;
	unsigned char flags;
	unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate ( unsigned char num, unsigned long base, unsigned short sel, unsigned char flags )
{
	idt[num].base_lo = base & 0xFFFF;
	idt[num].base_hi = ( base >> 16 ) & 0xFFFF;
	
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}


void idt_install ( void ) 
{
	idtp.limit = ( sizeof ( struct idt_entry) * 256 );
	idtp.base = (unsigned int ) &idt;

	memset ( &idt, 0, sizeof ( struct idt_entry ) * 256 );
	idt_load ();
	printline ( "Installed IDT" );
}


void isrs_install ( void ) 
{
	idt_set_gate ( 0, ( unsigned ) isr0, 0x08, 0x8E );
	idt_set_gate ( 1, ( unsigned ) isr1, 0x08, 0x8E );
	idt_set_gate ( 2, ( unsigned ) isr2, 0x08, 0x8E );
	idt_set_gate ( 3, ( unsigned ) isr3, 0x08, 0x8E );
	idt_set_gate ( 4, ( unsigned ) isr4, 0x08, 0x8E );
	idt_set_gate ( 5, ( unsigned ) isr5, 0x08, 0x8E );
	idt_set_gate ( 6, ( unsigned ) isr6, 0x08, 0x8E );
	idt_set_gate ( 7, ( unsigned ) isr7, 0x08, 0x8E );
	idt_set_gate ( 8, ( unsigned ) isr8, 0x08, 0x8E );
	idt_set_gate ( 9, ( unsigned ) isr9, 0x08, 0x8E );
	idt_set_gate ( 10, ( unsigned ) isr10, 0x08, 0x8E );
	idt_set_gate ( 11, ( unsigned ) isr11, 0x08, 0x8E );
	idt_set_gate ( 12, ( unsigned ) isr12, 0x08, 0x8E );
	idt_set_gate ( 13, ( unsigned ) isr13, 0x08, 0x8E );
	idt_set_gate ( 14, ( unsigned ) isr14, 0x08, 0x8E );
	idt_set_gate ( 15, ( unsigned ) isr15, 0x08, 0x8E );
	idt_set_gate ( 16, ( unsigned ) isr16, 0x08, 0x8E );
	idt_set_gate ( 17, ( unsigned ) isr17, 0x08, 0x8E );
	idt_set_gate ( 18, ( unsigned ) isr18, 0x08, 0x8E );
	idt_set_gate ( 19, ( unsigned ) isr19, 0x08, 0x8E );
	idt_set_gate ( 20, ( unsigned ) isr20, 0x08, 0x8E );
	idt_set_gate ( 21, ( unsigned ) isr21, 0x08, 0x8E );
	idt_set_gate ( 22, ( unsigned ) isr22, 0x08, 0x8E );
	idt_set_gate ( 23, ( unsigned ) isr23, 0x08, 0x8E );
	idt_set_gate ( 24, ( unsigned ) isr24, 0x08, 0x8E );
	idt_set_gate ( 25, ( unsigned ) isr25, 0x08, 0x8E );
	idt_set_gate ( 26, ( unsigned ) isr26, 0x08, 0x8E );
	idt_set_gate ( 27, ( unsigned ) isr27, 0x08, 0x8E );
	idt_set_gate ( 28, ( unsigned ) isr28, 0x08, 0x8E );
	idt_set_gate ( 29, ( unsigned ) isr29, 0x08, 0x8E );
	idt_set_gate ( 30, ( unsigned ) isr30, 0x08, 0x8E );
	idt_set_gate ( 31, ( unsigned ) isr31, 0x08, 0x8E );
	printline("Installed ISRs");
}


void fault_handler ( struct regs *r )
{
	if ( r->int_no < 32 )
	{
		printline ( exception_messages[r->int_no] );
		printline ( "Exception, System halted" );
	}
}


void irq_handler ( struct regs *r )
{

}

void kmain ( void* mbd, unsigned int magic )
{
        if ( magic != 0x2BADB002 )
        {
		/* there is something wrong */
        } 
	else 
	{
		clearscreen();
		printline ("akv's - code is running");
		gdt_install ();
		idt_install ();
		isrs_install ();
        }

}
