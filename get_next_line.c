/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteudle <esteudle@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:22:59 by esteudle          #+#    #+#             */
/*   Updated: 2024/12/02 17:23:03 by esteudle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strchr(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (&buffer[i]);
		i++;
	}
	return (NULL);
}

char	*extracting_line (char *buffer)
{
	char	*line;
	int	j;
	int	i;

	i = 0;
	j = 0;
	line = ft_calloc((BUFFER_SIZE - &buffer) + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (buffer[i])
	{
		line[i + j] = buffer[j];
		j++;
	}
	return (&line[i]);
}

char	*get_next_line(int fd)
{	
	static int	bytes_read;
	char	*line;
	char	buffer[BUFFER_SIZE * ((BUFFER_SIZE > 0) - (BUFFER_SIZE <= 0))];
	int	i;
	char	*ptr;

	line = NULL;	
	if (fd < 0 || read (fd, NULL, 0) != 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{	
		return (NULL);
		free (buffer);
	}
	while (1)
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{	
			return (NULL);
			free (buffer);
		}
		if (ft_strchr(&buffer))
		{
			ptr = ft_strchr(&buffer);
			line = extracting_line (&ptr);
			&buffer[BUFFER_SIZE] + 1;
			break;
		}
	}	
	return (line);
}

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
}