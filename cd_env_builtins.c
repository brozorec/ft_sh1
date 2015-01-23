/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:29:46 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/23 15:32:29 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void		env_builtin(char **env)
{
	int			i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putstr("\n");
		++i;
	}
}

void		cd_builtin(char **cmd, char ***env)
{
	int			i;
	char		cwdbuf[4096];

	i = 0;
	if (chdir(cmd[1]) == -1)
	{
		write(2 ,"error cd\n", 9);
		return ;
	}
	getcwd(cwdbuf, 4096);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], "PWD=", 4) == 0)
		{
			free((*env)[i]);
			(*env)[i] = 0;
			(*env)[i] = ft_strjoin("PWD=", cwdbuf);
			return ;
		}
		++i;
	}
}
