/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:37 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:38 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

char	*expand_heredoc_line(const char *line, t_shell *shell)
{
	char	*res;
	int		i;
	int		start;

	res = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (is_dollar_expansion(line, i, 0))
		{
			res = append_str(res, expand_dollar(line, &i, shell));
			continue ;
		}
		start = i;
		while (line[i] && !is_dollar_expansion(line, i, 0))
			i++;
		res = append_str(res, ft_substr((char *)line, start, i - start));
	}
	return (res);
}
