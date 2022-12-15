/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:37:55 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 18:45:09 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pwd_res(void)
{
	char	buff[2048];
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (g_list.env[++i])
	{
		if (ft_strncmp(g_list.env[i], "OLDPWD=", 7) == 0)
		{
			while (g_list.env[++j])
				if (ft_strncmp(g_list.env[j], "PWD=", 4) == 0)
					break ;
			free(g_list.env[i]);
			tmp = ft_substr(g_list.env[j], 4, ft_strlen(g_list.env[j]) - 4);
			g_list.env[i] = ft_strjoin("OLDPWD=", tmp);
			free(tmp);
			break ;
		}
	}
	getcwd(buff, sizeof(buff));
	free(g_list.env[j]);
	g_list.env[j] = ft_strjoin("PWD=", buff);
}

void	mini_cd(char *tmp)
{
	char	*sub;
	int		len;

	len = ft_strlen(tmp);
	sub = ft_substr(tmp, 3, len - 3);
	if (sub[0] == '\0' || sub[0] == '~')
	{
		if (sub)
			free(sub);
		sub = ft_strdup(getenv("HOME"));
	}
	if (chdir(sub))
		ft_putstrendl_fd("cd: no such file or directory", 1);
	pwd_res();
	free(sub);
}
