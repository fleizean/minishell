/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_single.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:10:05 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:10:06 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static int	run_external_single(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		setup_child_signals();
		if (apply_redirs(cmd, shell) < 0)
			exit(shell->exit_status);
		exec_external(cmd, shell);
	}
	while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		;
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (shell->exit_status);
}

static int	run_builtin_single(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;

	saved_in = -1;
	saved_out = -1;
	if (cmd->redirs)
	{
		saved_in = dup(0);
		saved_out = dup(1);
	}
	if (apply_redirs(cmd, shell) == 0)
	{
		if (cmd->argv[0])
			exec_builtin(cmd, shell);
		else
			shell->exit_status = 0;
	}
	if (saved_in >= 0)
	{
		dup2(saved_in, 0);
		dup2(saved_out, 1);
		close(saved_in);
		close(saved_out);
	}
	return (shell->exit_status);
}

static int	run_single_command(t_cmd *cmd, t_shell *shell)
{
	if (cmd->argv[0] && !is_builtin_name(cmd->argv[0]))
		return (run_external_single(cmd, shell));
	return (run_builtin_single(cmd, shell));
}

int	run_pipeline(t_cmd *cmds, t_shell *shell)
{
	if (!cmds->next)
		return (run_single_command(cmds, shell));
	return (run_multi(cmds, shell));
}
