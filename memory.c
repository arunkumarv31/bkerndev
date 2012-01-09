
void *memset ( void *dest, char val, unsigned int count )
{
	char *temp = ( char * ) dest;
	for ( ; count != 0; count-- )
	{
		*temp++ = val;
	}
	return dest;
}
