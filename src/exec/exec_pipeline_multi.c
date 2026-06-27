/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_multi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:10:07 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:10:08 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static void	fork_children(t_cmd *cmds, t_shell *shell, int *fds, pid_t *pids)
{
	t_cmd		*cur;
	int			i;
	t_pipe_ctx	ctx;

	cur = cmds;
	i = 0;
	ctx.fds = fds;
	ctx.n = count_cmds(cmds);
	while (cur)
	{
		ctx.idx = i;
		pids[i] = fork();
		if (pids[i] == 0)
			run_child(cur, shell, ctx);
		cur = cur->next;
		i++;
	}
}

static int	wait_children(pid_t *pids, int n, t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		while (waitpid(pids[i], &status, 0) == -1 && errno == EINTR)
			;
		if (i == n - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (shell->exit_status);
}

int	run_multi(t_cmd *cmds, t_shell *shell)
{
	int		n;
	int		*fds;
	pid_t	*pids;
	int		status;

	n = count_cmds(cmds);
	fds = create_pipes(n);
	pids = malloc(sizeof(pid_t) * n);
	fork_children(cmds, shell, fds, pids);
	close_all_pipes(fds, n);
	free(fds);
	status = wait_children(pids, n, shell);
	free(pids);
	return (status);
}
