/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/05 14:35:24 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

int			get_cmd(char *line, char ***cmd)
{
	int				i;

	i = 1;
	*cmd = ft_strsplit(line, ' ');
	while ((*cmd)[i])
	{
		if (ft_strchr((*cmd)[i], '"'))
		{
			if (((*cmd)[i] = trim_quot_marks((*cmd)[i])) == 0)
				return (-1);
		}
		++i;
	}
	if (!ft_strcmp((*cmd)[0], "cd") || !ft_strcmp((*cmd)[0], "setenv") ||
		!ft_strcmp((*cmd)[0], "unsetenv") || !ft_strcmp((*cmd)[0], "exit") ||
		!ft_strcmp((*cmd)[0], "env") || !ft_strcmp((*cmd)[0], "pwd"))
		return (1);
	return (0);
}

void		sig_handler(int sig)
{
	if (sig <= 31)
	{
		return ;
	}
}

void		signals(void)
{
	int			i;

	i = 1;
	while (i <= 31 && i != 11)
	{
		signal(i, sig_handler);
		++i;
	}
}

int			proceed(char ***env, char ***cmd, char **my_path)
{
	char		*line;
	int			i;

	ft_putstr("@>");
	if (get_next_line(0, &line) == 0)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	if (ft_strlen(line) == 0 || (i = get_cmd(line, cmd)) == -1)
		return (1);
	if (i == 1)
	{
		opt_builtin(*cmd, env);
		return (1);
	}
	if ((*cmd)[0][0] == '/' || (*cmd)[0][0] == '.')
		*my_path = ft_strdup((*cmd)[0]);
	else if ((*my_path = lookup_paths("PATH=", (*cmd)[0], *env)) == 0)
	{
		err_msg((*cmd)[0]);
		err_msg(": Command not found.\n");
		return (1);
	}
	return (0);
}

int			main(void)
{
	extern char **environ;
	char		**env;
	char		**cmd;
	char		*my_path;

	signals();
	env = 0;
	cmd = 0;
	env = set_my_env(environ, 0, 0, 0);
	while (1)
	{
		if (proceed(&env, &cmd, &my_path) == 1)
			continue;
		if (fork() == 0)
		{
			if (execve(my_path, cmd, env) == -1)
			{
				err_msg(my_path);
				err_msg(": Command not found.\n");
				exit(127);
			}
		}
		wait(0);
	}
	return (0);
}
