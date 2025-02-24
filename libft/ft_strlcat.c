/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:48:17 by mawako            #+#    #+#             */
/*   Updated: 2024/09/08 16:24:10 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	char	*copy;

	copy = dst;
	while (*dst)
		dst++;
	while (0 < len && *src)
	{
		*dst = *src;
		dst++;
		src++;
		len--;
	}
	*dst = 0;
	return (copy);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	max;
	size_t	d_len;
	size_t	s_len;

	if (size == 0 && !dst)
		return (ft_strlen(src));
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (size <= d_len)
		return (size + s_len);
	max = size - d_len - 1;
	ft_strncat(dst, src, max);
	return (s_len + d_len);
}
