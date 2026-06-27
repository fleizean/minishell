/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolve_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:14:14 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:14:14 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static char	*search_in_path(const char *cmd, char **env, int *errcode)
{
	char	*path_val;
	char	**dirs;
	char	*result;

	path_val = env_get(env, "PATH");
	if (!path_val)
	{
		*errcode = 127;
		return (NULL);
	}
	dirs = ft_split(path_val, ':');
	result = search_dirs(dirs, cmd, errcode);
	ft_free_str(dirs);
	if (!result && !*errcode)
		*errcode = 127;
	return (result);
}

char	*resolve_path(const char *cmd, char **env, int *errcode)
{
	*errcode = 0;
	if (!cmd || !cmd[0])
	{
		*errcode = 127;
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
		return (resolve_direct(cmd, errcode));
	return (search_in_path(cmd, env, errcode));
}
