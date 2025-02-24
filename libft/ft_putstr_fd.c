/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:33:47 by mawako            #+#    #+#             */
/*   Updated: 2024/09/08 16:35:45 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	size_t	count;

	if (!s)
		return ;
	count = ft_strlen(s);
	i = 0;
	while (count--)
		ft_putchar_fd(s[i++], fd);
	return ;
}
