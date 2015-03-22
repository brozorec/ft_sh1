/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 19:50:44 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/22 16:07:19 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

void		print_env(char **env)
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

void		env_builtin(char **cmd, char **env)
{
	int			fd;
	char		*line;
	char		*path;

	if ((fd = open("/etc/paths", O_RDONLY)) == -1)
		fd = open("./source/builtins/path", O_RDONLY);
	while (fd != -1 && get_next_line(fd, &line) != 0)
	{
		if ((path = dir_content(line, "env")) != 0)
			break ;
	}
	close(fd);
	if (fork() == 0)
	{
		if (execve(path, cmd, env) == -1)
		{
			if (cmd[2] == 0)
				ft_putendl(cmd[1]);
			else
				ft_putendl(cmd[2]);
			exit(0);
		}
	}
	wait(0);
}

void		free_env_cmd_res(char ***cmd, char ***env, t_res **res)
{
	ft_str3del(*env);
	ft_str3del(*cmd);
	ft_str3del((*res)->paths);
	free((*res)->home);
	free((*res));
}

void		exit_builtin(char **cmd, char ***env, t_res *res)
{
	int			status;
	int			i;

	i = 0;
	if (cmd[1] == 0)
	{
		free_env_cmd_res(&cmd, env, &res);
		exit(0);
	}
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1][i++]) == 0)
		{
			exit_err(i);
			return ;
		}
	}
	if (cmd[2] != 0)
	{
		err_msg("exit: Expression Syntax.\n");
		return ;
	}
	status = ft_atoi(cmd[1]);
	free_env_cmd_res(&cmd, env, &res);
	exit(status);
}
