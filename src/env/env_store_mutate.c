/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_store_mutate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:09:55 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:09:55 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static void	env_append_new(char ***env, char *entry)
{
	char	**new_env;
	int		n;
	int		idx;

	n = env_len(*env);
	new_env = malloc(sizeof(char *) * (n + 2));
	idx = 0;
	while (idx < n)
	{
		new_env[idx] = (*env)[idx];
		idx++;
	}
	new_env[n] = entry;
	new_env[n + 1] = NULL;
	free(*env);
	*env = new_env;
}

int	env_set(char ***env, const char *key, const char *val)
{
	int		idx;
	char	*entry;
	char	*tmp;

	tmp = ft_strjoin((char *)key, "=");
	entry = ft_strjoin(tmp, (char *)val);
	free(tmp);
	idx = env_index(*env, key);
	if (idx >= 0)
	{
		free((*env)[idx]);
		(*env)[idx] = entry;
		return (0);
	}
	env_append_new(env, entry);
	return (0);
}

int	env_unset(char ***env, const char *key)
{
	int		idx;
	int		i;
	int		j;
	char	**new_env;

	idx = env_index(*env, key);
	if (idx < 0)
		return (-1);
	new_env = malloc(sizeof(char *) * env_len(*env));
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i != idx)
			new_env[j++] = (*env)[i];
		else
			free((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}
