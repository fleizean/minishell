/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:50 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/12 16:37:09 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_dups(t_pipe_var variables, int countpipe)
{
	if (variables.j != 0)
		if (dup2(variables.fd[(variables.j - 1) * 2], 0) < 0)
			exit(1);
	if (variables.temp->next)
		if (dup2(variables.fd[variables.j * 2 + 1], 1) < 0)
			exit(1);
	variables.i = -1;
	while (++variables.i < 2 * countpipe)
		close(variables.fd[variables.i]);
	variables.cmd = ft_split(variables.temp->data, ' ');
	variables.path = find_path(variables.cmd[0]);
	if (execve(variables.path, variables.cmd, g_list.env) < 0)
	{
		g_list.exit_status = 127;
		ft_free_str(variables.cmd);
		exit(1);
	}
	free(variables.path);
	ft_free_str(variables.cmd);
	kill(variables.pid, SIGKILL);
}

static void	split_piped(t_pipe_var variables, int countpipe, t_list **mini)
{
	variables.j = 0;
	variables.temp = (*mini);
	while (variables.temp)
	{
		variables.pid = fork();
		run_signals(2);
		if (variables.pid == 0)
			ft_dups(variables, countpipe);
		variables.temp = variables.temp->next;
		variables.j++;
	}
}

void	execpiped(t_list **mini, int countpipe)
{
	t_pipe_var	variables;

	variables.i = -1;
	variables.fd = malloc(countpipe * 2);
	while (++variables.i < countpipe)
	{
		if (pipe(variables.fd + variables.i * 2) < 0)
			exit(1);
	}
	split_piped(variables, countpipe, mini);
	variables.i = -1;
	while (++variables.i < 2 * countpipe)
		close(variables.fd[variables.i]);
	countpipe++;
	while (countpipe--)
		waitpid(0, &g_list.exit_status, WUNTRACED);
	if (WIFEXITED(g_list.exit_status))
		g_list.exit_status = WEXITSTATUS(g_list.exit_status);
	else
		g_list.exit_status = 0;
	if (variables.fd[0] != '\0')
		free(variables.fd);
}
