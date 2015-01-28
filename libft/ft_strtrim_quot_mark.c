/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_quot_mark.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 17:35:20 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/15 17:07:43 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_quot_mark(char const *s)
{
	char	*new;
	int		i;
	int		j;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == '"')
		i++;
	if (s[i] == '\0')
	{
		new = ft_strnew(1);
		return (new);
	}
	j = ft_strlen(s) - 1;
	while (s[j] == '"')
		j--;
	j = j - i + 1;
	new = ft_strnew(j);
	if (new == 0)
		return (0);
	ft_memcpy(new, &s[i], j);
	return (new);
}
