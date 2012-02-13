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
		for(;;);
	}
}

