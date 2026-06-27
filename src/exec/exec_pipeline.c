/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:52 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:53 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

int	count_cmds(t_cmd *cmds)
{
	int	n;

	n = 0;
	while (cmds)
	{
		n++;
		cmds = cmds->next;
	}
	return (n);
}

void	close_all_pipes(int *fds, int n)
{
	int	i;

	i = 0;
	while (i < 2 * (n - 1))
	{
		close(fds[i]);
		i++;
	}
}

void	run_child(t_cmd *cmd, t_shell *shell, t_pipe_ctx ctx)
{
	setup_child_signals();
	if (ctx.idx > 0)
		dup2(ctx.fds[(ctx.idx - 1) * 2], 0);
	if (ctx.idx < ctx.n - 1)
		dup2(ctx.fds[ctx.idx * 2 + 1], 1);
	close_all_pipes(ctx.fds, ctx.n);
	if (apply_redirs(cmd, shell) < 0)
		exit(shell->exit_status);
	if (!cmd->argv[0])
		exit(0);
	if (is_builtin_name(cmd->argv[0]))
		exit(exec_builtin(cmd, shell));
	exec_external(cmd, shell);
}

int	*create_pipes(int n)
{
	int	*fds;
	int	i;

	fds = malloc(sizeof(int) * 2 * (n - 1));
	i = 0;
	while (i < n - 1)
	{
		if (pipe(fds + i * 2) < 0)
			return (NULL);
		i++;
	}
	return (fds);
}
