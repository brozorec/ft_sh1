/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 17:15:13 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/23 17:53:59 by bbarakov         ###   ########.fr       */
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

char		*path_to_exec(char **cmd, char **env, t_res *res)
{
	char		*path;

	path = 0;
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		path = ft_strdup(cmd[0]);
	else if ((path = lookup_paths("PATH=", cmd[0], env)) == 0
		&& (path = lookup_paths("PATH=", cmd[0], res->paths)) == 0)
	{
		err_msg(cmd[0]);
		err_msg(": Command not found.\n");
		ft_putstr("@>");
		return (0);
	}
	return (path);
}

void		execute_command(char **cmd, char **env, t_res *res)
{
	pid_t		child;
	int			status;
	char		*path;

	if ((path = path_to_exec(cmd, env, res)) == 0)
		return ;
	if ((child = fork()) == 0)
	{
		if (execve(path, cmd, env) == -1)
		{
			err_msg(path);
			free(path);
			err_msg(": Command not found.\n");
			exit(127);
		}
	}
	waitpid(child, &status, WUNTRACED);
	examine_status(status, child);
	free(path);
}
