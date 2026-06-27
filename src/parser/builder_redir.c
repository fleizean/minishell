/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:00:25 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:00:26 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static void	add_redir(t_cmd *cmd, t_redir_type type, char *target, int lit)
{
	t_redir	*redir;
	t_redir	*last;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->target = target;
	redir->literal = lit;
	redir->fd = -1;
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

static t_token	*consume_redir(t_token *tok, t_cmd *cmd, t_shell *shell)
{
	t_redir_type	type;
	t_token			*word_tok;

	type = redir_type_of(tok->type);
	word_tok = tok->next;
	if (type == REDIR_HEREDOC)
		add_redir(cmd, type, strip_quotes(word_tok->text),
			has_quote(word_tok->text));
	else
		add_redir(cmd, type, expand_word(word_tok->text, shell), 0);
	return (word_tok->next);
}

t_cmd	*build_pipeline(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*cur;
	t_token	*tok;

	head = new_cmd();
	cur = head;
	tok = tokens;
	while (tok)
	{
		if (tok->type == TOK_WORD)
		{
			append_argv(cur, expand_word(tok->text, shell));
			tok = tok->next;
		}
		else if (tok->type == TOK_PIPE)
		{
			cur->next = new_cmd();
			cur = cur->next;
			tok = tok->next;
		}
		else
			tok = consume_redir(tok, cur, shell);
	}
	return (head);
}
