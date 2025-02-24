/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:30:29 by mawako            #+#    #+#             */
/*   Updated: 2024/09/08 16:34:24 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*mem;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		mem = (char *)malloc(1);
		if (mem)
			mem[0] = '\0';
		return (mem);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	mem = (char *)malloc((len + 1) * sizeof(char));
	if (!mem)
		return (NULL);
	while (i < len)
		mem[i++] = s[start++];
	mem[i] = '\0';
	return (mem);
}
