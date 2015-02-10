/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 13:03:19 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/10 19:04:43 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

void		sig_handler(int sig)
{
	if (sig != 20)
	{
		ft_putstr("\na>");
		return ;
	}
	else
		return ;
}

void		signals(void)
{
	int			i;

	i = 1;
	while (i <= 31)
	{
		signal(i, sig_handler);
		++i;
	}
}
