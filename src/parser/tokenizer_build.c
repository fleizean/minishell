/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:19 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:20 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static t_token	*read_operator(const char *p, int *consumed)
{
	if (*p == '|')
	{
		*consumed = 1;
		return (new_token(TOK_PIPE, ft_strdup("|")));
	}
	if (*p == '<' && p[1] == '<')
	{
		*consumed = 2;
		return (new_token(TOK_HEREDOC, ft_strdup("<<")));
	}
	if (*p == '<')
	{
		*consumed = 1;
		return (new_token(TOK_REDIR_IN, ft_strdup("<")));
	}
	if (*p == '>' && p[1] == '>')
	{
		*consumed = 2;
		return (new_token(TOK_REDIR_APPEND, ft_strdup(">>")));
	}
	*consumed = 1;
	return (new_token(TOK_REDIR_OUT, ft_strdup(">")));
}

static int	lex_step(const char *line, int i, t_lex_state *st, int *error)
{
	t_token	*tok;
	int		consumed;
	int		end;

	if (line[i] == ' ' || line[i] == '\t')
		return (i + 1);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		tok = read_operator(line + i, &consumed);
		append_token(&st->head, &st->tail, tok);
		return (i + consumed);
	}
	end = read_word_end(line, i, error);
	if (*error)
		return (-1);
	tok = new_token(TOK_WORD, ft_substr((char *)line, i, end - i));
	append_token(&st->head, &st->tail, tok);
	return (end);
}

t_token	*tokenize(const char *line, int *syntax_error)
{
	t_lex_state	st;
	int			i;

	st.head = NULL;
	st.tail = NULL;
	*syntax_error = 0;
	i = 0;
	while (line[i])
	{
		i = lex_step(line, i, &st, syntax_error);
		if (i < 0)
		{
			free_tokens(st.head);
			return (NULL);
		}
	}
	return (st.head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->text);
		free(tokens);
		tokens = next;
	}
}
