/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:57 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:58 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	env_index(char **env, const char *key)
{
	int		i;
	size_t	len;

	len = ft_strlen((char *)key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], (char *)key, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**env_copy(char **envp)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (env_len(envp) + 1));
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*env_get(char **env, const char *key)
{
	int	idx;

	idx = env_index(env, key);
	if (idx < 0)
		return (NULL);
	return (env[idx] + ft_strlen((char *)key) + 1);
}

int	env_has(char **env, const char *key)
{
	return (env_index(env, key) >= 0);
}
