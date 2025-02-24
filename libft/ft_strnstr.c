/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <mawako@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:38:29 by mawako            #+#    #+#             */
/*   Updated: 2024/09/11 09:59:54 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s;

	s = (char *)str;
	if (*to_find == 0)
		return (s);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (to_find[j] && (i + j) < len && str[i + j] == to_find[j])
			j++;
		if (i + j <= len && to_find[j] == 0)
			return (s + i);
		i++;
	}
	return (0);
}
