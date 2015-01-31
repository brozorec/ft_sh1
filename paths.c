/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:48 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/31 19:42:52 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

char		*dir_content(char *path, char *name)
{
	DIR					*dirp;
	struct dirent		*entry;
	char				*my_path;

	if ((dirp = opendir(path)) != 0)
	{
		while ((entry = readdir(dirp)) != 0)
		{
			if (ft_strcmp(entry->d_name, name) == 0)
			{
				my_path = ft_str3join(path, "/", name);
				closedir(dirp);
				return (my_path);
			}
		}
	}
	if (dirp)
		closedir(dirp);
	return (0);
}

char		*lookup_paths(char **tab_paths, char *name)
{
	int			i;
	char		*my_path;

	i = 0;
	while (tab_paths && tab_paths[i])
	{
		if ((my_path = dir_content(tab_paths[i], name)) != 0)
			return (my_path);
		i++;
	}
	return (0);
}

char		**get_paths(char *var, char **env)
{
	int			i;
	int			cmp;

	i = 0;
	cmp = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, cmp) == 0)
			return (ft_strsplit(&env[i][cmp], ':'));
		++i;
	}
	return (0);
}
