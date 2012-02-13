
void *memset ( void *dest, char val, unsigned int count )
{
	char *temp = ( char * ) dest;
	for ( ; count != 0; count-- )
	{
		*temp++ = val;
	}
	return dest;
}

void outportb ( unsigned short _port, unsigned char _data )
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
