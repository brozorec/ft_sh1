/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/23 20:20:23 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

int			get_cmd(char *line, char ***cmd)
{
	*cmd = ft_strsplit(line, ' ');
	if (!ft_strcmp(**cmd, "cd") || !ft_strcmp(**cmd, "setenv") ||
		!ft_strcmp(**cmd, "unsetenv") || !ft_strcmp(**cmd, "exit") ||
		!ft_strcmp(**cmd, "env"))
		return (1);
	return (0);
}

void		sig_handler(int sig)
{
	if (sig == SIGQUIT)
		exit(0);
	signal(sig, SIG_IGN);
	signal(sig, SIG_DFL);
	// ft_putnbr(sig);
}

int			main(void)
{
	extern char **environ;
	char		**env;
	char		*line;
	char		**cmd;
	char		**paths;
	char		*my_path;
	pid_t		child;
	int			status;

	signal(SIGINT, sig_handler);
	// signal(SIGQUIT, sig_handler);
	env = 0;
	env = set_my_env(environ, 0, 0, 0);
	paths = get_paths(env);
	while (1)
	{
		cmd = 0;
		ft_putstr("@>");
		get_next_line(0, &line);
		if (ft_strlen(line) == 0)
			continue;
		if (get_cmd(line, &cmd) == 1)
		{
			opt_builtin(cmd, &env);
			continue;
		}
		if ((my_path = lookup_paths(paths, cmd[0])) == 0)
			write(2, "error main\n", 12);
		else if ((child = fork()) == 0)
			execve(my_path, cmd, env);
		waitpid(child, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			sig_handler(WTERMSIG(status));
	}
	return (0);
}
