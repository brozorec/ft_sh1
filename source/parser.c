/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:52:07 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/22 16:52:09 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

char		*trim_quot_marks(char *str)
{
	char		*new;
	int			i;
	int			j;

	new = 0;
	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '"')
		{
			++i;
			continue;
		}
		new[j++] = str[i++];
	}
	free(str);
	if ((i - j) % 2 != 0)
	{
		err_msg("Unmatched \".\n");
		return (0);
	}
	return (new);
}

int
	check_if_home(char **cmd, char **env, t_res **res)
{
	char				*copy;

	if ((*cmd)[0] == '~')
	{
		if ((*cmd)[1] != 0 && (*cmd)[1] != '/')
		{
			err_msg("Unknown user: ");
			err_msg(&(*cmd)[1]);
			err_msg(".\n");
			return (-1);
		}
		copy = ft_strdup(*cmd);
		ft_strdel(cmd);
		*cmd = take_env_var("HOME=", ft_strchr(copy, '~') + 1, env);
		if (*cmd == 0)
			*cmd = ft_strjoin((*res)->home, ft_strchr(copy, '~') + 1);
		free(copy);
	}
	return (1);
}

int
	get_cmd(char *line, char ***cmd, char **env, t_res **res)
{
	int					i;

	i = 1;
	*cmd = ft_str2split(line, ' ', '\t');
	if (**cmd == 0)
		return (-1);
	while ((*cmd)[i])
	{
		if (ft_strchr((*cmd)[i], '"'))
		{
			if (((*cmd)[i] = trim_quot_marks((*cmd)[i])) == 0)
				return (-1);
		}
		else if (check_if_home(&(*cmd)[i], env, res) == -1)
			return (-1);
		++i;
	}
	free(line);
	return (0);
}
