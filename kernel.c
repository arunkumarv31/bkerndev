#include <system.h>
#include <screen.h>
#include <gdt.h>
#include <idt.h>
#include <irq.h>
// Declare the page directory and a page table, both 4kb-aligned
unsigned long kernelpagedir[1024] __attribute__ ((aligned (4096)));
unsigned long lowpagetable[1024] __attribute__ ((aligned (4096)));

void init_paging();

// This function fills the page directory and the page table,
// then enables paging by putting the address of the page directory
// into the CR3 register and setting the 31st bit into the CR0 one
void init_paging()
{
	// Pointers to the page directory and the page table
	void *kernelpagedirPtr = 0;
	void *lowpagetablePtr = 0;
	int k = 0;
 
	kernelpagedirPtr = (char *)kernelpagedir + 0x40000000;	// Translate the page directory from
								// virtual address to physical address
	lowpagetablePtr = (char *)lowpagetable + 0x40000000;	// Same for the page table
 
	// Counts from 0 to 1023 to...
	for (k = 0; k < 1024; k++)
	{
		lowpagetable[k] = (k * 4096) | 0x3;	// ...map the first 4MB of memory into the page table...
		kernelpagedir[k] = 0;			// ...and clear the page directory entries
	}
 
	// Fills the addresses 0...4MB and 3072MB...3076MB of the page directory
	// with the same page table
 
	kernelpagedir[0] = (unsigned long)lowpagetablePtr | 0x3;
	kernelpagedir[768] = (unsigned long)lowpagetablePtr | 0x3;
 
	// Copies the address of the page directory into the CR3 register and, finally, enables paging!
 
	asm volatile (	"mov %0, %%eax\n"
			"mov %%eax, %%cr3\n"
			"mov %%cr0, %%eax\n"
			"orl $0x80000000, %%eax\n"
			"mov %%eax, %%cr0\n" :: "m" (kernelpagedirPtr));
}


extern void printletter ( unsigned char charecter, unsigned int x_pos, unsigned int y_pos );
extern void printline ( char *ptr );
extern void clearscreen ( void );
extern void gdt_install ( void );
extern void gdt_set_gate ( int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran );
extern void gdt_flush ( void );



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

>>>>>>> gdt_in_depth


struct gdt_entry gdt[3];
struct gdt_ptr gp;

struct idt_entry idt[256];
struct idt_ptr idtp;

char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};



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
		irq_install ();
		__asm__ __volatile__ ("sti");
		timer_install (2);
		keyboard_install ();
		for(;;);
	}
		init_paging();
		gdt_install();
        }

>>>>>>> gdt_in_depth
}

