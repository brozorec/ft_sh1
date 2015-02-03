/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 19:50:44 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/03 20:00:28 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void		envist_init_or_free(t_env **envist)
{
	if (*envist == 0)
	{
		*envist = (t_env *)malloc(sizeof(t_env));
		(*envist)->opt_i = 0;
		(*envist)->new_cmd = 0;
		(*envist)->new_env = 0;
		(*envist)->prog_name = 0;
	}
}

int 		get_options_env(char *cmd, t_env **envist)
{
	int 		i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i] != 'i')
		{
			err_msg("env: illegal option -- ");
			err_msg(&cmd[i]);
			err_msg("\nusage: env [-i] [name=value ...] [utility [argument ...]]\n");
			return (0);
		}
		else
			(*envist)->opt_i = 1;
		++i;
	}
	return (1);
}

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

int 		create_cmd(char **cmd, t_env **envist, int pos)
{
	int 		len;
	int 		i;

	len = get_len(&cmd[pos], 0);
	i = 0;
	(*envist)->new_cmd = (char **)malloc(len + 1);
	(*envist)->prog_name = ft_strdup(cmd[pos]);
	while (cmd[pos] && ft_strchr(cmd[pos], '=') == 0)
	{
		(*envist)->new_cmd[i] = ft_strdup(cmd[pos]);
		++i;
		++pos;
	}
	(*envist)->new_cmd[i] = 0;
	return (1);
}

int 		add_var_or_create_new_env(char **cmd, char **env, t_env **envist, int pos)
{
	char 		*var;
	char		*value;

	if ((*envist)->opt_i == 0)
		(*envist)->new_env = set_my_env(env, 0, 0, 0);
	while (cmd[pos] && ft_strchr(cmd[pos], '='))
	{
		value = ft_strdup(ft_strchr(cmd[pos], '=') + 1);
		var = ft_strchr_rev(cmd[pos], '=');
		change_or_add_env_var(var, value, &(*envist)->new_env);
		++pos;
	}
	if (get_len(&cmd[pos], 0) == pos)
	{
		print_env((*envist)->new_env);
		return (-1);
	}
	return (pos);
}

int 		env_proceed(char **cmd, char **env, t_env **envist)
{
	int 		i;

	i = 1;
	if (cmd[i] == 0)
	{
		print_env(env);
		return (0);
	}
	else if (cmd[i][0] == '-')
	{
		if (get_options_env(cmd[i], envist) == 0)
			return (0);
		++i;
	}
	if ((i = add_var_or_create_new_env(cmd, env, envist, i)) == -1)
		return (0);
	create_cmd(cmd, envist, i);
	return (0);
}

void		env_builtin(char **cmd, char **env)
{
	t_env		*envist;
	char 		*my_path;

	envist = 0;
	envist_init_or_free(&envist);
	if (env_proceed(cmd, env, &envist) == 0)
		return ;
	else if ((my_path = lookup_paths("PATH=", envist->prog_name, envist->new_env)) == 0)
	{
		err_msg("env error: command not found\n");
		return ;
	}
	if (fork() == 0)
	{
		if (execve(my_path, envist->new_cmd, envist->new_env) == -1)
		{
			err_msg("env error: command not found\n");
			exit(0);
		}
	}
	wait(0);
}

// void		env_builtin(char **cmd, char **env)
// {
// 	int 		fd;
// 	char		*line;
// 	char		*path;

// 	path = 0;
// 	fd = open("/etc/paths", O_RDONLY);
// 	while (fd != -1 && get_next_line(fd, &line) != 0)
// 	{
// 		if ((path = dir_content(line, "env")) != 0)
// 			break;
// 	}
// 	if (fork() == 0)
// 	{
// 		if (execve(path, cmd, env) == -1)
// 		{
// 			ft_putstr(cmd[2]);
// 			exit(0);
// 		}
// 	}
// 	wait(0);
// }

void		exit_builtin(char **cmd)
{
	int			status;
	int			i;

	i = 0;
	if (cmd[1] == 0)
		exit(0);
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1][i]) == 0)
		{
			exit_err(i);
			return ;
		}
		++i;
	}
	if (cmd[2] != 0)
	{
		err_msg("exit: Expression Syntax.\n");
		return ;
	}
	status = ft_atoi(cmd[1]);
	exit(status);
}
