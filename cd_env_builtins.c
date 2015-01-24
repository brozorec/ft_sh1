/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:29:46 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/24 20:02:44 by bbarakov         ###   ########.fr       */
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

void		cd_errors(char *path, char *cwdbuf)
{
	struct stat		buf;
	char			*new_path;

	if (path[0] != '/')
	{
		new_path = ft_strjoin(cwdbuf, "/");
		new_path = ft_strjoin(new_path, path);
	}
	else
		new_path = ft_strdup(path);
	if (stat(new_path, &buf) == -1)
	{
		err_msg("cd: no such file or directory: ");
		err_msg(path);
		err_msg("\n");
		return ;
	}
	if (S_ISDIR(buf.st_mode))
	{
		err_msg("cd: permission denied: ");
		err_msg(path);
		err_msg("\n");
	}
	else
	{
		err_msg("cd: not a directory: ");
		err_msg(path);
		err_msg("\n");
	}

}

void			cd_home(char **env)
{
	int			i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			chdir(&env[i][5]);
			return ;
		}
		++i;
	}
}

void		cd_builtin(char **cmd, char ***env)
{
	int			i;
	char		cwdbuf[4096];

	i = 0;
	getcwd(cwdbuf, 4096);
	if (cmd[1][0] == '~')
		cd_home(*env);
	else if (chdir(cmd[1]) == -1)
	{
		cd_errors(cmd[1], cwdbuf);
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
