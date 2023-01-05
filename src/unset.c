/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:04:19 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/05 19:20:28 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_exist(char *str)
{
	int	i;

	i = 0;
	while (g_list.env[i])
	{
		if (ft_strcmp(g_list.env[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	unset(int var_pos)
{
	int		i;
	int		count;
	int		j;
	char	**new_env;

	j = 0;
	i = -1;
	count = env_len(g_list.env);
	if (env_exist(g_list.env[var_pos]) == 1)
	{
		new_env = (char **)malloc(sizeof(char *) * (count));
		while (g_list.env[++i])
		{
			if (var_pos != i)
				new_env[j++] = g_list.env[i];
		}
		free(g_list.env[var_pos]);
		free(g_list.env);
		new_env[i + 1] = NULL;
		g_list.env = new_env;
	}
}

void	unset_handle(char *str)
{
	int		i;
	int		j;
	char	**s;
	char	*sub;
	char	**tmp;

	tmp = ft_split(str, ' ');
	sub = ft_substr(str, 6, ft_strlen(str) - 6);
	s = ft_split(sub, ' ');
	i = -1;
	if(tmp[0] != NULL && tmp[1] == NULL)
		return;
	while (s[++i])
	{
		j = get_index(s[i]);
		if (g_list.env[j])
			unset(j);
	}
	if (sub[0] != '\0')
		free(sub);
	if (s[0][0] != '\0')
		ft_free_str(s);
}
