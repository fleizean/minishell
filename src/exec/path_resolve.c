/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:14:16 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:14:17 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

char	*resolve_direct(const char *cmd, int *errcode)
{
	if (access(cmd, F_OK) != 0)
	{
		*errcode = 127;
		return (NULL);
	}
	if (is_directory(cmd) || access(cmd, X_OK) != 0)
	{
		*errcode = 126;
		return (NULL);
	}
	return (ft_strdup((char *)cmd));
}

static char	*check_candidate(char *dir, const char *cmd, int *errcode)
{
	char	*joined;
	char	*candidate;

	joined = ft_strjoin(dir, "/");
	candidate = ft_strjoin(joined, (char *)cmd);
	free(joined);
	if (access(candidate, F_OK) != 0 || is_directory(candidate))
	{
		free(candidate);
		return (NULL);
	}
	if (access(candidate, X_OK) == 0)
		return (candidate);
	*errcode = 126;
	free(candidate);
	return (NULL);
}

char	*search_dirs(char **dirs, const char *cmd, int *errcode)
{
	int		i;
	char	*result;

	i = 0;
	while (dirs[i] && !*errcode)
	{
		result = check_candidate(dirs[i], cmd, errcode);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}
