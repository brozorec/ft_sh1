/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/21 19:31:01 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

int			get_cmd(char *line, char ***cmd)
{
	*cmd = ft_strsplit(line, ' ');
	if (!ft_strcmp(*cmd[0], "cd") || !ft_strcmp(*cmd[0], "setenv") ||
		!ft_strcmp(*cmd[0], "unsetenv") || !ft_strcmp(*cmd[0], "exit") ||
		!ft_strcmp(*cmd[0], "env"))
		return (1);
	return (0);
}

int			main(void)
{
	char		*line;
	char		**cmd;
	extern char **environ;
	char		**tab_paths;
	char		*my_path;
	pid_t		child;

	tab_paths = get_paths(environ);
	while (1)
	{
		cmd = 0;
		ft_putstr("@>");
		get_next_line(0, &line);
		if (ft_strlen(line) == 0)
			continue;
		if (get_cmd(line, &cmd) == 1)
			opt_builtin(cmd, &environ);
		else if ((my_path = lookup_paths(tab_paths, cmd[0])) == 0)
			write(2, "error main\n", 12);
		else if ((child = fork()) == 0)
		{
			execve(my_path, cmd, environ);
		}
		wait(NULL);
	}
	return (0);
}
