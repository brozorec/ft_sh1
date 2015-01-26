/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:29:46 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/26 19:49:55 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

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

char 			*second_try(char *name, char **env)
{
	char 			**tab_paths;
	char 			*path;
	char 			*new_path;
	char 			*truncated;
	int				i;

	if ((tab_paths = get_paths("CDPATH=", env)) == 0)
		return (0);
	if ((path = lookup_paths(tab_paths, name)) != 0)
	{
		ft_strdel(tab_paths);
		return (path);
	}
	truncated = ft_strdup(ft_strchr(name, '/'));
	i = ft_strlen(name) - ft_strlen(truncated);
	ft_bzero(&name[i], ft_strlen(truncated));
	if ((path = lookup_paths(tab_paths, name)) != 0)
	{
		new_path = ft_strjoin(path, truncated);
		free(truncated);
		ft_strdel(tab_paths);
		return (new_path);
	}
	return (0);
}

void			change_or_add_env_var(char *var, char *value, char ***env)
{
	int			i;
	int			cmp;

	i = 0;
	cmp = ft_strlen(var);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, cmp) == 0)
		{
			free((*env)[i]);
			(*env)[i] = 0;
			(*env)[i] = ft_strjoin(var, value);
			return ;
		}
		++i;
	}
	*env = set_my_env(*env, ft_strjoin(var, value), 0, 1);
}

char 			*take_home_or_oldpwd(char *var, char *addr, char **env)
{
	char 		*path;
	int			cmp;
	int			i;

	i = 0;
	cmp = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, cmp) == 0)
		{
			if (addr)
				path = ft_strjoin(&env[i][cmp], addr);
			else
				path = ft_strdup(&env[i][cmp]);
			return (path);
		}
		++i;
	}
	return (0);
}

void		cd_builtin(char **cmd, char ***env)
{
	char 		*path;
	char		old_dir[4096];
	char		new_dir[4096];

	getcwd(old_dir, 4096);
	if (cmd[1] == 0)
		path = take_home_or_oldpwd("HOME=", 0, *env);
	else if (cmd[1][0] == '~')
		path = take_home_or_oldpwd("HOME=", &cmd[1][1], *env);
	else if (cmd[1][0] == '-' && cmd[1][1] == 0)
	{
		if ((path = take_home_or_oldpwd("OLDPWD=", &cmd[1][1], *env)) == 0)
		{
			err_msg(": No such file or directory.\n");
			return ;
		}
	}
	else
		path = ft_strdup(cmd[1]);
	if (chdir(path) == -1)
	{
		if (chdir(second_try(path, *env)) == -1)
		{
			cd_errors(path, old_dir);
			free(path);
			return ;
		}
	}
	getcwd(new_dir, 4096);
	change_or_add_env_var("PWD=", new_dir, env);
	change_or_add_env_var("OLDPWD=", old_dir, env);
	free(path);
}
