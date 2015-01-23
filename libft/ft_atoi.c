/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:34:59 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/12 15:08:48 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*start(char *str)
{
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if ((*str != 45 && *str != 43 && *str < 48) || *str > 57)
		return (0);
	if (*str == 45 || *str == 43)
	{
		str++;
		if (*str == '\0' || *str < 48 || *str > 57)
			return (0);
		else
			str--;
	}
	return (str);
}

int				ft_atoi(const char *str)
{
	int		sign;
	int		k;
	char	*copy;

	k = 0;
	sign = 1;
	copy = start((char *)str);
	if (!copy)
		return (0);
	if (*copy == 45)
	{
		copy++;
		sign = -1;
	}
	if (*copy == 43)
		copy++;
	while (copy && *copy > 47 && *copy < 58)
	{
		k = k * 10 + *copy - '0';
		copy++;
	}
	return (k * sign);
}
