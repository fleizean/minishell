/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:03:19 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:03:20 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static int	heredoc_loop(int fd, char *path, t_redir *redir, t_shell *shell)
{
	int	stop;

	stop = 0;
	while (!stop)
	{
		if (read_heredoc_line(fd, redir, shell, &stop) < 0)
		{
			close(fd);
			unlink(path);
			shell->exit_status = 130;
			return (-1);
		}
	}
	return (0);
}

static int	read_heredoc(t_redir *redir, t_shell *shell)
{
	static int	counter = 0;
	char		*path;
	int			fd;

	path = build_path(counter++);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	setup_heredoc_signals();
	g_signal = 0;
	if (heredoc_loop(fd, path, redir, shell) < 0)
	{
		free(path);
		setup_parent_signals();
		return (-1);
	}
	close(fd);
	setup_parent_signals();
	fd = open(path, O_RDONLY);
	unlink(path);
	free(path);
	redir->fd = fd;
	return (0);
}

int	process_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && read_heredoc(redir,
					shell) < 0)
				return (-1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
