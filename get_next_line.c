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

char	*tackle_next_line(char **next_line, int fd)
{
	char	*buffer;
	int	bytes_read;
	char	*line;
	char	*temp;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(*next_line) && bytes_read > 0)
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);  // if read fails
		if (bytes_read == 0)
			break;
		temp = ft_strjoin(*next_line, buffer);
		free(*next_line);
		*next_line = temp;
	}
	if (bytes_read == 0 && **next_line == '\0')
		return(free(buffer), NULL); // If no more lines, return NULL
	line = extract_line(*next_line);
	*next_line = update_next_line(*next_line);
	return (free(buffer), line);
}

char	*extract_line(char *next_line)
{
	char	*line;
	int	i;

	i = 0;
	while (next_line[i] != '\n' && next_line[i] != '\0')
		i++;
	if (next_line[i] == '\n')
		i++;
	line = ft_substr(next_line, 0, i); 
	return (line);
}

char	*update_next_line (char *next_line)
{
	char	*temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (next_line[i] != '\n' && next_line[i] != '\0')
		i++;
	if (next_line[i] == '\0')
		return(free(next_line), NULL);
	i++; //skip '\n'
	while (next_line[i + j] != '\0')
		j++;
	temp = ft_substr(next_line, i, j);
	free(next_line); 
	return (temp);
}

char	*ft_strchr(char *container)
{
	int	i;

	i = 0;
	while (container[i])
	{
		if (container[i] == '\n' )
			return (&container[i]);
		i++;
	}
	return (NULL);
}

char	*get_next_line (int fd)
{
	static char	*next_line;
	char	*line;

	line = NULL;	
	if (fd < 0 || read (fd, NULL, 0) != 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!next_line)
		next_line = ft_strdup(""); 
	line = tackle_next_line (&next_line, fd);
	if (line == NULL && next_line) 
	{
		free(next_line);
		next_line = NULL;  // Optionally set it to NULL to avoid dangling pointer
	}
	return (line);
}