/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:22 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:22 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static int	is_operator(t_token *tok)
{
	return (tok && tok->type != TOK_WORD);
}

static void	syntax_error(t_shell *shell, const char *near)
{
	ft_putstr_fd((char *)"minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)near, 2);
	ft_putstr_fd((char *)"'\n", 2);
	shell->exit_status = 2;
}

static int	check_operator_token(t_token *cur, t_shell *shell)
{
	if (!cur->next)
	{
		syntax_error(shell, "newline");
		return (1);
	}
	if (is_operator(cur->next))
	{
		syntax_error(shell, cur->next->text);
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*cur;

	if (!tokens)
		return (0);
	if (tokens->type == TOK_PIPE)
	{
		syntax_error(shell, "|");
		return (1);
	}
	cur = tokens;
	while (cur)
	{
		if (is_operator(cur) && check_operator_token(cur, shell))
			return (1);
		cur = cur->next;
	}
	return (0);
}
