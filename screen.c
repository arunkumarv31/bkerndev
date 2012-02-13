

static unsigned int x_pos = 0, y_pos = 0;
static unsigned int attribute = 0x0F;
static unsigned short *videoram = (unsigned short *)0xB8000;


void printletter ( unsigned char charecter, unsigned int x_pos, unsigned int y_pos );
void printline ( char *ptr );
void clearscreen ( void );
void printchar (  unsigned char character );

void printline ( char *ptr )
{
	while ( *ptr != '\0' )
	{
		printletter (*ptr++, x_pos++, y_pos );
	}
	x_pos = 0;
	y_pos++;
}


void printchar (  unsigned char character )
{
	unsigned int index = ( y_pos * 80 ) + x_pos;
        unsigned short *where = videoram + index;
        *where = character | (attribute << 8);
	x_pos++;
}

void printletter ( unsigned char character, unsigned int x_pos, unsigned int y_pos )
{
	unsigned int index = ( y_pos * 80 ) + x_pos;
	unsigned short *where = videoram + index;
	*where = character | (attribute << 8);
}

void clearscreen ( void )
{
	unsigned char i = 0, j = 0;	
	for ( i = 0; i < 25; i++ )
	{
		for ( j = 0; j < 80; j++ )
		{
			printletter ( ' ', j, i );
		}
	}
	x_pos = 0; y_pos = 0;
}
