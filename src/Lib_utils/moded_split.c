#include "minishell.h"

static int	find_delimiter(const char *input_str, char delimiter)
{
	int		i;

	i = 0;
	while (input_str[i] != '\0')
	{
		if (input_str[i] == delimiter)
			return (i);
		i++;
	}
	return (-1);
}

static void	free_allocated(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
}

static void	store_first_word(const char *input_str, char **result, \
	int *current_word, int first_delimiter)
{
	if (first_delimiter == 0)
	{
		result[*current_word] = ft_substr("", 0, 0);
		if (!result[*current_word])
		{
			free_allocated(result, *current_word);
			error_exit("ft_split_first > ft_substr malloc error");
		}
	}
	else
	{
		result[*current_word] = ft_substr(input_str, 0, first_delimiter);
		if (!result[*current_word])
		{
			free_allocated(result, *current_word);
			error_exit("ft_split_first > ft_substr malloc error");
		}
	}
	(*current_word)++;
}

char	**ft_split_first(const char *input_str, const char delimiter)
{
	char	**result;
	int		length;
	int		first_delimiter;
	int		word_count;
	int		current_word;

	current_word = 0;
	word_count = 1;
	first_delimiter = find_delimiter(input_str, delimiter);
	if (first_delimiter >= 0)
		word_count = 2;
	result = (char **) malloc_and_check_alloc((word_count + 1) * sizeof(char *) \
	, "ft_split_first malloc error");
	if (word_count == 2)
		store_first_word(input_str, result, &current_word, first_delimiter);
	if (first_delimiter >= 0 && input_str[first_delimiter] == delimiter)
		first_delimiter++;
	if (first_delimiter < 0)
		first_delimiter = 0;
	length = ft_strlen(input_str + first_delimiter);
	result[current_word] = ft_substr(input_str, first_delimiter, length);
	if (!result[current_word])
		return (free_allocated(result, current_word), NULL);
	result[current_word + 1] = NULL;
	return (result);
}
