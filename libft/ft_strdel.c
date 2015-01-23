/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 13:12:16 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/15 16:29:58 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel(char **as)
{
	int	i;

	i = 0;
	if (as && *as)
	{
		while (as[i])
		{
			free(as[i]);
			i++;
		}
		as = 0;
	}
}
