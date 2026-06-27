/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:10:20 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:10:20 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

int	has_quote(const char *raw)
{
	int	i;

	i = 0;
	while (raw[i])
	{
		if (raw[i] == '\'' || raw[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static int	scan_unquoted_run(const char *raw, int i, char in_quote)
{
	while (raw[i] && raw[i] != in_quote
		&& !(!in_quote && (raw[i] == '\'' || raw[i] == '\"')))
		i++;
	return (i);
}

static int	toggle_quote(const char *raw, int i, char *in_quote)
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

char	*strip_quotes(const char *raw)
{
	char	*res;
	int		i;
	int		start;
	char	in_quote;
	int		next;

	res = ft_strdup("");
	i = 0;
	in_quote = 0;
	while (raw[i])
	{
		next = toggle_quote(raw, i, &in_quote);
		if (next >= 0)
		{
			i = next;
			continue ;
		}
		start = i;
		i = scan_unquoted_run(raw, i, in_quote);
		res = append_str(res, ft_substr((char *)raw, start, i - start));
	}
	return (res);
}
