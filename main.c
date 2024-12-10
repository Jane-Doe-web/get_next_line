#include "get_next_line.h"
#include <stdio.h>
int	main()
{
	int	fd = open ("file.txt", O_RDONLY);
	if (fd == -1) 
	{
		printf("Failed to open the file");
		return (1);
	}
	printf ("%s", get_next_line(fd));
	
	close (fd);
	return (0);
}