/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:46 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/12 16:36:48 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value(char *key, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
			return (envp[i] + ft_strlen(key) + 1);
	}
	return ("");
}

char	*find_path(char *cmdline)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	temp = find_value("PATH", g_list.env);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmdline);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(new_path, &s) == 0)
		{
			ft_free_str(paths);
			return (new_path);
		}
		free(new_path);
	}
	ft_free_str(paths);
	return (ft_strdup(cmdline));
}

void	execsimple(char **parse)
{
	int		pid;
	char	*path;
	int		res;

	path = find_path(parse[0]);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, parse, g_list.env) != 0)
		{
			g_list.exit_status = 127;
			printf(RED"This command not executed command!\n");
			exit(g_list.exit_status);
		}
		free(path);
		kill(getpid(), SIGTERM);
	}
	waitpid(pid, &res, 0);
	free(path);
	if (WIFEXITED(res))
		g_list.exit_status = WEXITSTATUS(res);
}
