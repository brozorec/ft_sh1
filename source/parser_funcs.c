/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 15:19:59 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/23 15:20:00 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

char		*ft_trim_quot_marks(char *str)
{
	char		*new;
	int			i;
	int			j;

	new = 0;
	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '"')
		{
			++i;
			continue;
		}
		new[j++] = str[i++];
	}
	free(str);
	return (new);
}

int			ft_len_to_char(char *str, char ch1, char ch2)
{
	int					i;

	i = 0;
	while (str[i] && str[i] != ch1 && str[i] != ch2)
		++i;
	return (i);
}
