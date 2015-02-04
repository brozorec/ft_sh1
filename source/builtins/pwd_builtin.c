/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 15:25:23 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/02 15:36:39 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

void		pwd_builtin(char **env)
{
	char		cwd[4096];
	char		*path;

	if ((path = take_env_var("PWD=", 0, env)) != 0)
	{
		ft_putstr(path);
		ft_putstr("\n");
		free(path);
	}
	else
	{
		getcwd(cwd, 4096);
		ft_putstr(cwd);
		ft_putstr("\n");
	}
}
