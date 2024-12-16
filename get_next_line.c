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
	while (container[i] != '\n' && container[i] != '\0')
		i++;
	if (container[i] == '\n')
		i++;
	line = ft_substr(container, 0, i);
	return (line);
}

char	*update_container (char *container)
{
	char	*new_container;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (container[i] != '\n' && container[i] != '\0')
		i++;
	if (container[i] == '\0')
	{
		free(container);
		return (NULL);
	}
	i++; //skip '\n'
	while (container[i + j] != '\0')
        j++;
    new_container = ft_substr(container, i, j);
    free(container); // free old container as it's no longer needed
    return (new_container);
}

char	*get_next_line(int fd)
{	
	int	bytes_read;
	char	*line;
	char	*buffer;
	static char	*container;

	line = NULL;	
	if (fd < 0 || read (fd, NULL, 0) != 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!container)
		container = ft_strdup("");
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char)); //allocate memory to the initial buffer
	if (!buffer)   //malloc protection
		return (NULL);
	while (1)  //infinitely looping
	{
		if (ft_strchr(container)) // checking if container already has \n and no need to read
		{
			line = extracting_line (container);
			container = update_container(container);
			break;
		}
		bytes_read = read (fd, buffer, BUFFER_SIZE); //read from fd to the buffer and count the bytes read
		if (bytes_read <= 0) //checking if reading was unsuccessful or EOF
		{
			free(buffer);
			if (container)
			{
				line = extracting_line(container);
				free(container);
			}
			return(line);
		}
		container = ft_strjoin (container, buffer); //copy the initial buffer to a bigger buffer
		if (ft_strchr(container)) //looking for \n
		{
			line = extracting_line (container);
			container = update_container(container);
			break;
		}		
	}
	free(buffer);	
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
		printf("%s", str);  // Print the current line
		str = get_next_line(fd);  // Get the next line		
	}
	// printf ("%s", get_next_line(fd));
	// printf ("%s", get_next_line(fd));
	// printf ("%s", get_next_line(fd));
	close (fd);
}