/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgachet <cgachet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:01:41 by cgachet           #+#    #+#             */
/*   Updated: 2024/07/29 22:01:41 by cgachet          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# ifndef MAX_FD
#  define MAX_FD 10240
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*free_memory(char **ptr);
char	*fill_stash(int fd, char *stash, char *buffer);
char	*grab_line(char *stash, char *line);
char	*get_new_stash(char *stash);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*ft_strdup_gnl(const char *s1);
size_t	ft_strlen_gnl(const char *s);
void	*ft_calloc_gnl(size_t size);
#endif
