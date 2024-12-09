/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esteudle <esteudle@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:23:15 by esteudle          #+#    #+#             */
/*   Updated: 2024/12/02 17:23:17 by esteudle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 28
# endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
