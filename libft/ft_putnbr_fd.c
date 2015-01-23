/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:32:39 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/08 17:08:41 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		copy;
	int		div;
	char	a;

	if (n < 0)
	{
		write(fd, "-", 1);
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
		write(fd, &a, 1);
		n %= div;
		div /= 10;
	}
}
