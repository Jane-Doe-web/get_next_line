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
#include <stdlib.h>

char	*ft_strchr(char *container)
{
	int	i;

	i = 0;
	while (container[i])
	{
		if (container[i] == '\n')
			return (&container[i]);
		i++;
	}
	return (NULL);
}

char	*extracting_line (char *container)
{
	char	*line;
	int	i;

	i = 0;
	while (container[i] != '\n')
		i++;
	line = ft_substr(container, 0, i);
	return (line);
}

char	*update_container (char *container)
{
	char	*new_container;
	int	i;
	int	j;

	while (container[i] != '\n')
		i++;
	while (container[j] != '\0')
		j++;
	new_container = ft_substr(container, i++, j - i);
	return (new_container);
}

char	*get_next_line(int fd)
{	
	static int	bytes_read;
	char	*line;
	char	*buffer;
	static char	*container;

	line = NULL;	
	if (fd < 0 || read (fd, NULL, 0) != 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char)); //allocate memory to the initial buffer
	if (!buffer)   //malloc protection
		return (NULL);
	container = ft_strdup("");
	while (1)  //infinitely looping
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE); //read from fd to the buffer and count the bytes read
		if (bytes_read <= 0) //checking if reading was unsuccessful
			return (free (buffer), NULL);
		container = ft_strjoin (container, buffer); //copy the initial buffer to a bigger buffer
		if (ft_strchr(container)) //looking for \n
		{
			line = extracting_line (container);
			container = update_container(container);
			break;
		}
	}	
	return (line);
}

int	main()
{
	char *str;
	int	fd = open ("file.txt", O_RDONLY);
	if (fd == -1) 
	{
		printf("Failed to open the file");
		return (1);
	}
	str = get_next_line (fd);
	while (str)
	{
		printf ("%s", get_next_line(fd));
		str = get_next_line(fd);		
	}
	close (fd);
}