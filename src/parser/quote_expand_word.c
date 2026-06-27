/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:14:26 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:14:26 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static int	scan_word_run(const char *raw, int i, char in_quote)
{
	while (raw[i] && raw[i] != in_quote
		&& !(!in_quote && (raw[i] == '\'' || raw[i] == '\"'))
		&& !is_dollar_expansion(raw, i, in_quote))
		i++;
	return (i);
}

static int	handle_quote_toggle(const char *raw, int i, char *in_quote)
{
	if (!*in_quote && (raw[i] == '\'' || raw[i] == '\"'))
	{
		*in_quote = raw[i];
		return (i + 1);
	}
	if (*in_quote && raw[i] == *in_quote)
	{
		*in_quote = 0;
		return (i + 1);
	}
	return (-1);
}

static int	expand_step(const char *raw, int i, t_expand_ctx *ctx,
		t_shell *shell)
{
	int	next;
	int	start;

	next = handle_quote_toggle(raw, i, &ctx->in_quote);
	if (next >= 0)
		return (next);
	if (is_dollar_expansion(raw, i, ctx->in_quote))
	{
		ctx->res = append_str(ctx->res, expand_dollar(raw, &i, shell));
		return (i);
	}
	start = i;
	i = scan_word_run(raw, i, ctx->in_quote);
	ctx->res = append_str(ctx->res, ft_substr((char *)raw, start, i - start));
	return (i);
}

char	*expand_word(const char *raw, t_shell *shell)
{
	t_expand_ctx	ctx;
	int				i;

	ctx.res = ft_strdup("");
	ctx.in_quote = 0;
	i = 0;
	while (raw[i])
		i = expand_step(raw, i, &ctx, shell);
	return (ctx.res);
}
