#include "get_next_line.h"
#include <stdio.h>

int	main()
{
	char *str;
	char *temp;
	int	fd = open ("file.txt", O_RDONLY);
	if (fd == -1) 
	{
		printf("Failed to open the file");
		return (1);
	}
	str = get_next_line (fd);
	while (str)
	{
		printf("%s", str);  // Print the current line
		temp = get_next_line(fd);  // Get the next line
		free(str);
		str = temp;
	}
	close (fd);

}