/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 06:37:23 by mawako            #+#    #+#             */
/*   Updated: 2025/02/20 17:34:30 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **arr, size_t used)
{
	size_t	i;

	i = 0;
	while (i < used)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static size_t	count_segments(const char *b, size_t l)
{
	size_t	i;
	size_t	count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (i < l)
	{
		if (b[i] != '\0' && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (b[i] == '\0')
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*dup_segment(const char *b, size_t start, size_t end)
{
	size_t	len;
	char	*seg;
	size_t	i;

	len = end - start;
	seg = malloc(len + 1);
	if (!seg)
		return (NULL);
	i = 0;
	while (i < len)
	{
		seg[i] = b[start + i];
		i++;
	}
	seg[i] = '\0';
	return (seg);
}

static int	fill_segments(const char *b, size_t l, char **arr, size_t segcount)
{
	size_t	i;
	size_t	idx;
	size_t	start;
	char	*seg;

	i = 0;
	idx = 0;
	while (idx < segcount)
	{
		while (i < l && b[i] == '\0')
			i++;
		if (i >= l)
			break ;
		start = i;
		while (i < l && b[i] != '\0')
			i++;
		seg = dup_segment(b, start, i);
		if (!seg)
			return (idx);
		arr[idx] = seg;
		idx++;
	}
	return (-1);
}

char	**null_split(const char *b, size_t l)
{
	size_t	segcount;
	char	**arr;
	int		ret;

	segcount = count_segments(b, l);
	arr = malloc(sizeof(char *) * (segcount + 1));
	if (!arr)
		return (NULL);
	arr[segcount] = NULL;
	ret = fill_segments(b, l, arr, segcount);
	if (ret >= 0)
	{
		free_array(arr, (size_t)ret);
		return (NULL);
	}
	return (arr);
}
