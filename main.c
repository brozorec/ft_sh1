/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/22 20:44:02 by bbarakov         ###   ########.fr       */
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

int			get_len(char **ptr, int flag)
{
	int		i;

	i = 0;
	while (ptr[i])
		++i;
	if (flag == 1)
		return (i + 1);
	else if (flag == -1)
		return (i - 1);
	return (i);
}

char		**set_my_env(char **environ, char *str, int cmp, int flag)
{
	int			i;
	int			j;
	int			len;
	char		**env;

	i = 0;
	j = 0;
	len = get_len(environ, flag);
	if ((env = (char **)malloc(sizeof(char *) * (len + 1))) == 0)
		return (0);
	while (environ[i])
	{
		if (flag == -1 && str && ft_strncmp(environ[i], str, cmp) == 0)
		{
			++i;
			continue;
		}
		env[j] = ft_strdup(environ[i]);
		++j;
		++i;
	}
	if (flag == 1)
	{
		env[j] = ft_strdup(str);
		free(str);
	}
	env[len + 1] = 0;
	return (env);
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
			opt_builtin(cmd, &env);
		else if ((my_path = lookup_paths(paths, cmd[0])) == 0)
			write(2, "error main\n", 12);
		else if ((child = fork()) == 0)
		{
			execve(my_path, cmd, env);
		}
		wait(NULL);
	}
	return (0);
}
