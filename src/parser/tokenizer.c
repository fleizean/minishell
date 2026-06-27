/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:11 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:12 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

t_token	*new_token(t_tok_type type, char *text)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->text = text;
	tok->next = NULL;
	return (tok);
}

void	append_token(t_token **head, t_token **tail, t_token *tok)
{
	if (!*head)
		*head = tok;
	else
		(*tail)->next = tok;
	*tail = tok;
}

static int	skip_quoted_span(const char *line, int i, int *error)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
	{
		*error = 1;
		return (i);
	}
	return (i + 1);
}

int	read_word_end(const char *line, int start, int *error)
{
	int	i;

	i = start;
	while (line[i] && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '|' && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = skip_quoted_span(line, i, error);
			if (*error)
				return (i);
		}
		else
			i++;
	}
	return (i);
}
