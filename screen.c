

unsigned int x_pos = 0, y_pos = 0;
unsigned int attribute = 0x0F;
unsigned short *videoram = (unsigned short *)0xB8000;


void printletter ( unsigned char charecter, unsigned int x_pos, unsigned int y_pos );
void printline ( char *ptr );


void printline ( char *ptr )
{
	while ( *ptr != '\0' )
	{
		printletter (*ptr++, x_pos++, y_pos );
	}
	x_pos = 0;
	y_pos++;
}


void printletter ( unsigned char character, unsigned int x_pos, unsigned int y_pos )
{
	unsigned int index = ( y_pos * 80 ) + x_pos;
	unsigned short *where = videoram + index;
	*where = character | (attribute << 8);
}
