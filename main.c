/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/26 19:40:51 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void		err_msg(char *err)
{
	int			i;

	i = 0;
	while (err[i])
	{
		write(2, &err[i], 1);
		++i;
	}
}

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
	if (sig <= 31)
		return ;
	// if (sig == SIGQUIT)
	// {
	// 	ft_putstr("caught SIGQUIT");
	// 	return ;
	// }
	// if (sig == SIGHUP)
	// {
	// 	ft_putstr("caught SIGHUP");
	// 	kill(0, SIGQUIT);
	// 	return ;
	// }
	// if (sig == SIGINT)
	// {
	// 	ft_putstr("caught SIGINT");
	// 	return ;
	// }
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

int			proceed(char ***env, char ***cmd, char **my_path, char **paths)
{
	char		*line;

	ft_putstr("@>");
	if (get_next_line(0, &line) == 0)
	{
		ft_putstr("\n");
		return(1);
	}
	if (ft_strlen(line) == 0)
		return(1);
	if (get_cmd(line, cmd) == 1)
	{
		opt_builtin(*cmd, env);
		return(1);
	}
	if ((*my_path = lookup_paths(paths, (*cmd)[0])) == 0)
	{
		*my_path = ft_strdup((*cmd)[0]);
		return(0);
	}
	return (0);
}

int			main(void)
{
	extern char **environ;
	char		**env;
	char		**cmd;
	char		**paths;
	char		*my_path;
	pid_t		child;
	int			status;

	signals();
	signal(SIGINT, SIG_DFL);
	env = 0;
	cmd = 0;
	env = set_my_env(environ, 0, 0, 0);
	paths = get_paths("PATH=", env);
	while (1)
	{
		if (proceed(&env, &cmd, &my_path, paths) == 1)
			continue;
		if ((child = fork()) == 0)
		{
			printf("%s\n", my_path);
			if (execve(my_path, cmd, env) == -1)
				write(2, "error main\n", 12);
		}
		waitpid(child, &status, WUNTRACED);
		// if (WIFSIGNALED(status))
		// 	sig_handler(WTERMSIG(status));
	}
	return (0);
}
