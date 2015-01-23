/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:35:06 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/10 18:52:19 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n)
{
	long long		copy;
	long long		div;
	char			a;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	copy = n;
	div = 1;
	while (copy >= 10)
	{
		div *= 10;
		copy /= 10;
	}
	while (div > 0)
	{
		a = '0' + n / div;
		write(1, &a, 1);
		n %= div;
		div /= 10;
	}
}
