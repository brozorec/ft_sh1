/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/21 20:00:36 by bbarakov         ###   ########.fr       */
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
void		cd_builtin(char **cmd, char ***environ)
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
	while ((*environ)[i])
	{
		if (ft_strncmp((*environ)[i], "PWD=", 4) == 0)
		{
			// free((*environ)[i]);
			// (*environ)[i] = 0;
			(*environ)[i] = ft_strjoin("PWD=", cwdbuf);
			return ;
		}
		++i;
	}
}

void		opt_builtin(char **cmd, char ***environ)
{
    if (!ft_strcmp(cmd[0], "cd"))
		cd_builtin(cmd, environ);
	if (!ft_strcmp(cmd[0], "exit"))
		exit(0);
	if (!ft_strcmp(cmd[0], "env"))
		env_builtin(*environ);
}
