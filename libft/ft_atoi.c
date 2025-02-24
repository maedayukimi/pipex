/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawako <mawako@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:24:12 by mawako            #+#    #+#             */
/*   Updated: 2024/09/11 09:59:43 by mawako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_max(int s)
{
	if (s == 1)
		return ((int)LONG_MAX);
	if (s == -1)
		return ((int)LONG_MIN);
	return (0);
}

int	ft_long(long num, int c)
{
	if (num == 0)
		return (0);
	if ((LONG_MAX - c) / 10 < num && c > 0)
		return (1);
	if ((LONG_MIN - c) / 10 > num && c < 0)
		return (1);
	return (0);
}

int	ft_atoi(const char *n)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while ((*n >= 9 && *n <= 13) || *n == 32)
		n++;
	if (*n == '+' || *n == '-')
	{
		if (*n == '-')
			sign *= -1;
		n++;
	}
	while (*n >= '0' && *n <= '9')
	{
		if (ft_long(res, ((*n - '0')) * sign))
			return (ft_max(sign));
		res = res * 10 + sign * (*n - 48);
		n++;
	}
	return ((int)res);
}
