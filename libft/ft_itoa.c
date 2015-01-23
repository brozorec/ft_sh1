/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:39:12 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/14 11:59:37 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*get_lenght(int n, int *len, int sign)
{
	char	*str;

	*len = 0;
	if (sign == -1 || n == 0)
		(*len)++;
	while (n > 0)
	{
		(*len)++;
		n /= 10;
	}
	str = ft_strnew(*len);
	if (str == 0)
		return (0);
	if (sign == -1)
		str[0] = '-';
	return (str);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	str = get_lenght(n, &len, sign);
	if (str == 0)
		return (0);
	len--;
	while (len >= 0 && str[len] != '-')
	{
		str[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}
