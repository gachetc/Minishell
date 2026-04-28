/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:59:13 by cgachet           #+#    #+#             */
/*   Updated: 2024/08/14 00:49:56 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_stash(int fd, char *stash, char *buffer);
char	*get_new_stash(char	*stash);
char	*grab_line(char *stash, char *line);

char	*free_memory(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	char		*buffer;

	line = NULL;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (free_memory(&buffer));
	if (read(fd, 0, 0) < 0)
	{
		free_memory(&stash[fd]);
		return (free_memory(&buffer));
	}
	stash[fd] = fill_stash(fd, stash[fd], buffer);
	if (!stash[fd])
		return (free_memory(&stash[fd]));
	line = grab_line(stash[fd], line);
	if (!line || line[0] == '\0')
	{
		free_memory(&stash[fd]);
		return (free_memory(&line));
	}
	stash[fd] = get_new_stash(stash[fd]);
	return (line);
}

char	*fill_stash(int fd, char *stash, char *buffer)
{
	ssize_t	readed_bytes;
	char	*temp;

	readed_bytes = 1;
	if (!stash)
		stash = ft_strdup_gnl("");
	while (readed_bytes > 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes == -1)
			return (free_memory(&buffer));
		if (readed_bytes == 0)
			break ;
		buffer[readed_bytes] = '\0';
		temp = stash;
		stash = ft_strjoin_gnl(temp, buffer);
		free_memory(&temp);
		if (!stash)
			return (free_memory(&stash));
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	free_memory(&buffer);
	return (stash);
}

char	*get_new_stash(char	*stash)
{
	int		index_stash;
	int		index_new_stash;
	char	*new_stash;

	index_stash = 0;
	index_new_stash = 0;
	if (!stash)
		return (NULL);
	while (stash[index_stash] != '\n' && stash[index_stash])
		index_stash++;
	if (stash[index_stash] == '\n')
		index_stash++;
	new_stash = ft_calloc_gnl((ft_strlen_gnl(stash) - index_stash + 1) \
	* sizeof(char));
	if (!new_stash)
		return (free_memory(&new_stash));
	while (stash[index_stash + index_new_stash])
	{
		new_stash[index_new_stash] = stash[index_stash + index_new_stash];
		index_new_stash++;
	}
	free_memory(&stash);
	new_stash[index_new_stash] = 0;
	return (new_stash);
}

char	*grab_line(char *stash, char *line)
{
	int	index_stash;
	int	index_line;

	index_stash = 0;
	index_line = 0;
	if (!stash)
		return (NULL);
	while (stash[index_stash] != '\n' && stash[index_stash] != '\0')
		index_stash++;
	if (stash[index_stash] == '\n')
		index_stash++;
	line = ft_calloc_gnl((index_stash + 1) * sizeof(char));
	if (!line)
		return (free_memory(&line));
	while (index_line < index_stash)
	{
		line[index_line] = stash[index_line];
		index_line++;
	}
	line[index_line] = 0;
	return (line);
}
