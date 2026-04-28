/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:31:06 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:50:02 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	tab = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!tab)
		return (free_memory(&tab));
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	unsigned int	i;

	if (!s || !c)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*tab;
	int		i;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen_gnl(s1);
	i = 0;
	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (free_memory(&tab));
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

void	*ft_calloc_gnl(size_t size)
{
	void			*ptr;
	unsigned char	*p;
	size_t			i;

	i = 0;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	while (i < size)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
