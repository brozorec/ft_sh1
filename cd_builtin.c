/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:29:46 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/27 19:18:38 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

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

char 			*take_home_or_oldpwd(char *var, char *addr, char **env)
{
	char 			*path;
	int				cmp;
	int				i;

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

int				cd_options(char *cmd)
{
	int				i;
	int				opt;

	i = 1;
	opt = 0;
	while (cmd[i])
	{
		if (cmd[i] != 'L' && cmd[i] != 'P')
		{
			cd_options_err(cmd[i]);
			return (-1);
		}
		else if (cmd[i] == 'L' && opt == 0)
			opt = 1;
		else if (cmd[i] == 'P' && opt == 0)
			opt = 2;
		++i;
	}
	return (opt);
}

char 			*ft_readlink(char *link_path)
{
	char 			*path;
	// char 			buf[30];
	// int				ret;
	int				fd;
	// int				i;

	path = 0;
	if ((fd = open(link_path, O_SYMLINK)) == -1)
		return (0);
	// ft_putnbr(fd);
	// ft_putstr(link_path);
	// if ((i = get_next_line(fd, &path)) == -1)
	// {
	// 	ft_putnbr(i);
	// 	return (0);
	// }
	// free(link_path);
	// ret = read(fd, buf, 50);
	// buf[30] = '\0';
	// printf("%d\n", errno);
	// ft_putnbr(ret);
	// ft_putstr(buf);
	// ret = readlink(link_path, buf, 30);
	// buf[ret] = '\0';
	printf("%s\n", path);
	close(fd);
	return (path);

}

char 			*examine(int opt, char *cmd, char *cwd, char **env)
{
	char 			*path;
	struct stat 	buf;

	path = 0;
	if (opt == 0)
	{
		if ((path = take_home_or_oldpwd("OLDPWD=", 0, env)) == 0)
		{
			err_msg(": No such file or directory.\n");
			return (0);
		}
		return (path);
	}
	if (cmd[0] == '~')
		path = take_home_or_oldpwd("HOME=", &cmd[1], env);
	else if (cmd[0] != '/')
		path = ft_str3join(cwd, "/", cmd);
	else
		path = ft_strdup(cmd);
	if (opt == 1)
	{
		lstat(path, &buf);
		if (S_ISLNK(buf.st_mode))
		{
			printf("%s\n", path);
		}
	}
	return (path);
}

char			*set_path(char **cmd, char *cwd, char ***env)
{
	int				opt;
	char 			*path;

	path = 0;
	if (cmd[1] == 0)
		path = take_home_or_oldpwd("HOME=", 0, *env);
	else if (cmd[1][0] == '-')
	{
		opt = cd_options(cmd[1]);
		path = examine(opt, cmd[2], cwd, *env);
	}
	else
		path = examine(1, cmd[1], cwd, *env);
	return (path);
}

void			cd_builtin(char **cmd, char ***env)
{
	char 		*path;
	char		old_dir[4096];
	char		new_dir[4096];

	getcwd(old_dir, 4096);
	path = set_path(cmd, old_dir, env);
	if (chdir(path) == -1)
	{
		if (chdir(second_try(cmd[1], *env)) == -1) // da
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
