/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 14:54:20 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/16 15:08:28 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, t_list *new)
{
	t_list		*tmp;

	if (new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			tmp = *alst;
			while ((*alst)->next)
				*alst = (*alst)->next;
			(*alst)->next = new;
			*alst = tmp;
		}
	}
}
