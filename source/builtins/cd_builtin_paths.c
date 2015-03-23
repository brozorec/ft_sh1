/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 14:22:45 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/23 15:47:57 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

int			examine_path(t_cd **lst)
{
	struct stat		buf;
	char			cwd[4096];

	if ((*lst)->opt_p == 1)
	{
		lstat((*lst)->path, &buf);
		if (S_ISLNK(buf.st_mode))
		{
			if (chdir((*lst)->path) == -1)
			{
				cd_errors(lst);
				return (0);
			}
			getcwd(cwd, 4095);
			free((*lst)->path);
			(*lst)->path = ft_strdup(cwd);
		}
	}
	return (0);
}

char		*resolve_path_loop(char *path, char *new_path, int i, int j)
{
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] != '.' && j-- > 0)
			new_path[j--] = '\0';
		else if (path[i] == '.' && path[i + 1] == '.')
		{
			if (j > 0)
				new_path[--j] = '\0';
			while (new_path[j] != '/' && j >= 0)
				new_path[j--] = '\0';
			if (j >= 0)
				new_path[j] = '\0';
			++i;
			--j;
		}
		else
			new_path[j] = path[i];
		++j;
		++i;
	}
	return (new_path);
}

char		*resolve_path(char *path)
{
	char			*new_path;
	int				i;
	int				j;

	i = 0;
	j = 0;
	new_path = ft_strnew(ft_strlen(path));
	new_path = resolve_path_loop(path, new_path, i, j);
	ft_strdel(&path);
	return (new_path);
}

char		*construct_path(t_cd *lst)
{
	char			*path;
	int				i;

	path = 0;
	i = ft_strlen(lst->name) - 1;
	while (i > 0 && lst->name[i] == '/')
	{
		lst->name[i] = '\0';
		--i;
	}
	if (lst->name && lst->name[0] == '/')
		path = ft_strdup(lst->name);
	else
		path = ft_str3join(lst->old_dir, "/", lst->name);
	path = resolve_path(path);
	if (path[0] == '\0')
		path[0] = '/';
	return (path);
}
