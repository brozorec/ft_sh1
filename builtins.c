/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/22 20:39:07 by bbarakov         ###   ########.fr       */
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

void		opt_builtin(char **cmd, char ***env)
{
    if (!ft_strcmp(cmd[0], "cd"))
		cd_builtin(cmd, env);
	else if (!ft_strcmp(cmd[0], "exit"))
		exit(0);
	else if (!ft_strcmp(cmd[0], "env"))
		env_builtin(*env);
	else if (!ft_strcmp(cmd[0], "setenv"))
		setenv_builtin(cmd, env);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		unsetenv_builtin(cmd, env);
}
