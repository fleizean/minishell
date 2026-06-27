/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:00:28 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:00:28 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next_cmd;
	t_redir	*redir;
	t_redir	*next_redir;
	int		i;

	while (cmds)
	{
		next_cmd = cmds->next;
		i = 0;
		while (cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds->argv);
		redir = cmds->redirs;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->target);
			if (redir->fd >= 0)
				close(redir->fd);
			free(redir);
			redir = next_redir;
		}
		free(cmds);
		cmds = next_cmd;
	}
}
