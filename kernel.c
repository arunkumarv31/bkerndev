#include <system.h>
#include <screen.h>
#include <gdt.h>
#include <idt.h>
#include <irq.h>


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

unsigned int *page_directory;
unsigned int *first_page_table;

void paging_codes ( void )
{
	page_directory = ( unsigned int *) 0x9C000;
	first_page_table = page_directory + 0x1000;

	int i = 0;
	for(i = 0; i < 1024; i++)
	{
		//attribute: supervisor level, read/write, not present.
    		page_directory[i] = 0 | 2; 
	}
	unsigned int address = 0; 
 
	for(i = 0; i < 1024; i++)
	{
    		first_page_table[i] = address | 3; 
    		address = address + 4096; 
	}
	page_directory[0] = first_page_table; 
	page_directory[0] |= 3;
	printline ( "before paging" );	
	//moves page directory into CR3 and finally enable paging in CR0
	asm volatile("mov %0, %%cr3":: "b"(page_directory));
	//reads cr0, switches the "paging enable" bit, and writes it back.
	unsigned int cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "b"(cr0));
	printline ( "paging enabled" );	
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
		paging_codes ();
		gdt_install ();
		idt_install ();
		isrs_install ();
		irq_install ();
		__asm__ __volatile__ ("sti");
		timer_install (2);
		keyboard_install ();
		for(;;);
	}
}


