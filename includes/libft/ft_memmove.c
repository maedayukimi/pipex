/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:24:02 by mawako            #+#    #+#             */
/*   Updated: 2024/09/08 17:56:05 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	if (dest > src)
	{
		while (n--)
			*(d + n) = *((unsigned char *)src + n);
	}
	else
	{
		while (n--)
		{
			*d = *((unsigned char *)src);
			d++;
			src++;
		}
	}
	return (dest);
}
