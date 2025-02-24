/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:57:23 by mawako            #+#    #+#             */
/*   Updated: 2024/09/08 16:43:35 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	slen;
	char	*mem;
	char	*copy;

	i = 0;
	slen = ft_strlen(s) + 1;
	mem = (char *)malloc(slen * sizeof(char));
	if (!mem || !s)
		return (NULL);
	copy = mem;
	while (i < slen - 1)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (mem);
}
