/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:10:16 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:10:17 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *));
	cmd->argv[0] = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	append_argv(t_cmd *cmd, char *word)
{
	int		n;
	int		i;
	char	**new_argv;

	n = 0;
	while (cmd->argv[n])
		n++;
	new_argv = malloc(sizeof(char *) * (n + 2));
	i = 0;
	while (i < n)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[n] = word;
	new_argv[n + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

t_redir_type	redir_type_of(t_tok_type type)
{
	if (type == TOK_REDIR_IN)
		return (REDIR_IN);
	if (type == TOK_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOK_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}
