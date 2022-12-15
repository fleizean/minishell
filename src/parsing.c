/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:06 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/12 17:15:37 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_executable(char *cmd_path)
{
	if (access(cmd_path, 0) == 0)
		return (1);
	return (0);
}

static int	find_path2(char *cmdline)
{
	t_temp_var	a;
	struct stat	s;

	if (cmdline == NULL)
		return (0);
	if (is_executable(cmdline) == 1)
		return (1);
	a.tmp = find_value("PATH", g_list.env);
	a.tmp_2ar = ft_split(a.tmp, ':');
	a.i = -1;
	while (a.tmp_2ar [++a.i])
	{
		a.tmp = ft_strjoin("/", cmdline);
		a.tmp2 = ft_strjoin(a.tmp_2ar [a.i], a.tmp);
		free(a.tmp);
		if (stat(a.tmp2, &s) == 0)
		{
			free(a.tmp2);
			ft_free_str(a.tmp_2ar);
			return (1);
		}
		free(a.tmp2);
	}
	ft_free_str(a.tmp_2ar);
	return (0);
}

int	process_string(char *str)
{
	char	**commands;

	if (!str[0])
		return (0);
	commands = ft_split(str, ' ');
	if (find_path2(commands[0]))
	{
		g_list.exit_status = 0;
		execsimple(commands);
	}
	else
	{
		g_list.exit_status = 127;
		printf(RED"This command not executed command!\n");
	}
	ft_free_str(commands);
	return (0);
}
