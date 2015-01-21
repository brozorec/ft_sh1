/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:51:32 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/21 19:21:53 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "get_next_line.h"
# include <stdio.h> // don't forget it
# include <errno.h> // don't forget it

char		*lookup_paths(char **tab_paths, char *name);
char		**get_paths(char **env);
void		opt_builtin(char **cmd, char ***environ);

#endif
