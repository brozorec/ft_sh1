/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/23 17:37:48 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

void		examine_status(int status, pid_t child)
{
	if (WIFEXITED(status))
		ft_putstr("@>");
	else if (WIFSTOPPED(status))
		kill(child, 9);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) != 2 && WTERMSIG(status) != 3 &&
			WTERMSIG(status) != 18 && WTERMSIG(status) != 10 &&
			WTERMSIG(status) != 11)
			ft_putstr("@>");
		if (WTERMSIG(status) == 10)
		{
			err_msg("Bus error\n");
			ft_putstr("@>");
		}
		if (WTERMSIG(status) == 11)
		{
			err_msg("Segmentation fault\n");
			ft_putstr("@>");
		}
	}
}

void		execute_command(char *my_path, char **cmd, char **env)
{
	pid_t		child;
	int			status;

	if ((child = fork()) == 0)
	{
		if (execve(my_path, cmd, env) == -1)
		{
			err_msg(my_path);
			err_msg(": Command not found.\n");
			exit(127);
		}
	}
	waitpid(child, &status, WUNTRACED);
	examine_status(status, child);
}

int			proceed(char ***env, char ***cmd, char **my_path, t_res **res)
{
	char		*line;
	int			i;

	if (get_next_line(0, &line) == 0)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	if (ft_strlen(line) == 0 || (i = get_cmd(line, cmd, *env, res)) == -1)
		return (1);
	if (i == 1)
	{
		opt_builtin(*cmd, env, res);
		return (1);
	}
	if ((*cmd)[0][0] == '/' || (*cmd)[0][0] == '.')
		*my_path = ft_strdup((*cmd)[0]);
	else if ((*my_path = lookup_paths("PATH=", (*cmd)[0], *env)) == 0
		&& (*my_path = lookup_paths("PATH=", (*cmd)[0], (*res)->paths)) == 0)
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
	t_res		*res;

	signals();
	env = 0;
	res = get_reserved(environ);
	env = set_my_env(environ, 0, 0, 0);
	ft_putstr("@>");
	while (1)
	{
		cmd = 0;
		my_path = 0;
		if (proceed(&env, &cmd, &my_path, &res) == 1)
		{
			ft_putstr("@>");
			ft_strdel(cmd);
			free(my_path);
			continue;
		}
		execute_command(my_path, cmd, env);
	}
	return (0);
}
