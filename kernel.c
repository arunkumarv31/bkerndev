
extern void printletter ( unsigned char charecter, unsigned int x_pos, unsigned int y_pos );
extern void printline ( char *ptr );
extern void clearscreen ( void );


void kmain ( void* mbd, unsigned int magic )
{
        if ( magic != 0x2BADB002 )
        {
		/* there is something wrong */
        } 
	else 
	{
		clearscreen();
		printline ("there is no tomorrow");
        }

}

