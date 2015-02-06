/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/06 18:18:29 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

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

void		execute_command(char *my_path, char **cmd, char **env)
{
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

int			proceed(char ***env, char ***cmd, char **my_path, char ***saved)
{
	char		*line;
	int			i;

	if (get_next_line(0, &line) == 0)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	if (ft_strlen(line) == 0 || (i = get_cmd(line, cmd)) == -1)
		return (1);
	if (i == 1)
	{
		opt_builtin(*cmd, env, saved);
		return (1);
	}
	if ((*cmd)[0][0] == '/' || (*cmd)[0][0] == '.')
		*my_path = ft_strdup((*cmd)[0]);
	else if ((*my_path = lookup_paths("PATH=", (*cmd)[0], *env)) == 0
		&& (*my_path = lookup_paths("PATH=", (*cmd)[0], *saved)) == 0)
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
	char		**saved;

	signals();
	env = 0;
	cmd = 0;
	saved = get_reserve_paths();
	env = set_my_env(environ, 0, 0, 0);
	while (1)
	{
		ft_putstr("@>");
		if (proceed(&env, &cmd, &my_path, &saved) == 1)
			continue;
		execute_command(my_path, cmd, env);
	}
	return (0);
}
