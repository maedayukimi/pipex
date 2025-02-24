/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:36:00 by mawako            #+#    #+#             */
/*   Updated: 2024/08/24 12:54:46 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	ch;

	src = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*src == ch)
			return (src);
		src++;
	}
	return (NULL);
}
