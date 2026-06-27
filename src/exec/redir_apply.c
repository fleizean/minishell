/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:27 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:27 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static void	print_open_error(char *target)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

static int	open_target(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->target, O_RDONLY));
	if (redir->type == REDIR_APPEND)
		return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

static int	apply_one(t_redir *redir, t_shell *shell)
{
	int	fd;

	if (redir->type == REDIR_HEREDOC)
	{
		if (redir->fd < 0)
			return (-1);
		dup2(redir->fd, 0);
		close(redir->fd);
		redir->fd = -1;
		return (0);
	}
	fd = open_target(redir);
	if (fd < 0)
	{
		print_open_error(redir->target);
		shell->exit_status = 1;
		return (-1);
	}
	if (redir->type == REDIR_IN)
		dup2(fd, 0);
	else
		dup2(fd, 1);
	close(fd);
	return (0);
}

int	apply_redirs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (apply_one(redir, shell) < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
