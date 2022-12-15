/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:55 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/12 16:37:26 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(char **envp)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (envp[++i])
		count++;
	return (count);
}

int	get_index(char *var_name)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_list.env[i])
	{
		tmp = ft_strjoin(var_name, "=");
		if (ft_strncmp(g_list.env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
		free(tmp);
	}
	return (i);
}

void	printenv(void)
{
	int	i;

	i = 0;
	while (g_list.env[i++])
	{
		ft_putstr_fd("\033[0;32m", 1);
		ft_putstr_fd(g_list.env[i], 1);
		ft_putstr_fd("\033[0;39m", 1);
		if (g_list.env[i])
			ft_putstr_fd("\n", 1);
	}
}
