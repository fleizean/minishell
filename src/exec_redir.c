/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:16:17 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 13:08:23 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_redir(char *s, int fd, int i)
{
	int		n_pipe;

	run_signals(2);
	n_pipe = count(s, '|');
	dup2(fd, i);
	close(fd);
	if (n_pipe)
		pipe_handle(s, n_pipe);
	else
		process_string(s);
	exit(g_list.exit_status);
}

void	execute_dir(char *s, int fd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		g_list.exit_status = 127;
		ft_putstr_fd("Failed forking child", 1);
	}
	else if (pid == 0)
		exec_redir(s, fd, i);
	waitpid(0, &g_list.exit_status, 0);
	if (WIFEXITED(g_list.exit_status))
		g_list.exit_status = WEXITSTATUS(g_list.exit_status);
	else
		g_list.exit_status = 0;
}
