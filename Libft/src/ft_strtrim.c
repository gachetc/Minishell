/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:41:14 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:54:20 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, char const *set);
static void	get_trim_positions(char const *s1, \
		char const *set, int *start, int *end);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	get_trim_positions(s1, set, &start, &end);
	if (start > end)
		return (ft_strdup(""));
	result = (char *)malloc(end - start + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[start], end - start + 2);
	return (result);
}

static int	char_in_set(char c, char const *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

static void	get_trim_positions(char const *s1, \
		char const *set, int *start, int *end)
{
	*start = 0;
	while (s1[*start] && char_in_set(s1[*start], set))
		(*start)++;
	*end = ft_strlen(s1) - 1;
	while (*end >= 0 && char_in_set(s1[*end], set))
		(*end)--;
}
