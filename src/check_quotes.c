/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:11:15 by eyagiz            #+#    #+#             */
/*   Updated: 2022/10/25 10:25:34 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_double_quote(char *str, int *i)
{
	(*i)++;
	while (*(str + *i) != '\"' && *(str + *i))
		(*i)++;
	if (*(str + *i) != '\"')
		return (-1);
	return (1);
}

static int	check_single_quote(char *str, int *i)
{
	(*i)++;
	while (*(str + *i) != '\'' && *(str + *i))
		(*i)++;
	if (*(str + *i) != '\'')
		return (-1);
	return (1);
}

int	check_quotes2(char *s)
{
	int	i;
	int	quote_flag;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			quote_flag = check_double_quote(s, &i);
		else if (s[i] == '\'')
			quote_flag = check_single_quote(s, &i);
		if (quote_flag == -1)
			break ;
		i++;
	}
	return (quote_flag);
}

int	check_quotes(char *s, t_utils utils)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			utils.quote_flag = check_double_quote(s, &i);
		else if (s[i] == '\'')
			utils.quote_flag = check_single_quote(s, &i);
		if (utils.quote_flag == -1)
			break ;
		i++;
	}
	return (utils.quote_flag);
}
