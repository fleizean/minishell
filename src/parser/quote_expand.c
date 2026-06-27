/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:34 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:35 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

char	*int_to_str(int n)
{
	char			buf[12];
	int				i;
	int				neg;
	unsigned int	un;

	i = 11;
	buf[i] = '\0';
	neg = (n < 0);
	if (neg)
		un = -(unsigned int)n;
	else
		un = (unsigned int)n;
	if (un == 0)
		buf[--i] = '0';
	while (un)
	{
		buf[--i] = (un % 10) + '0';
		un /= 10;
	}
	if (neg)
		buf[--i] = '-';
	return (ft_strdup(buf + i));
}

char	*append_str(char *res, char *addition)
{
	char	*joined;

	joined = ft_strjoin(res, addition);
	free(res);
	free(addition);
	return (joined);
}

char	*expand_dollar(const char *raw, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
	if (raw[*i] == '?')
	{
		(*i)++;
		return (int_to_str(shell->exit_status));
	}
	start = *i;
	while (raw[*i] && ft_isalnum(raw[*i]))
		(*i)++;
	if (start == *i)
		return (ft_strdup("$"));
	name = ft_substr((char *)raw, start, *i - start);
	val = env_get(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

int	is_dollar_expansion(const char *raw, int i, char in_quote)
{
	return (raw[i] == '$' && in_quote != '\''
		&& (ft_isalnum(raw[i + 1]) || raw[i + 1] == '?'));
}
