/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:11:09 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 14:10:07 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dble_quote_incheck(char *s, int *i)
{
	(*i)++;
	while (*(s + *i) != '\"' && *(s + *i))
	{
		if (*(s + *i) == '$' && *(s + *i + 1) != '\"')
			finder_dollar_env(s, i);
		else if (*(s + *i) != '\"')
			ft_putchar_fd(*(s + *i), 1);
		(*i)++;
	}
}

void	echo_withn(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			dble_quote_incheck(s, &i);
		else if (s[i] == '\'')
			sngle_quote_incheck(s, &i);
		else if (s[i] == '$' && s[i + 1] == '?')
		{
			ft_putnbr_fd(g_list.exit_status, 1);
			i++;
		}
		else if (s[i] == '$' && ft_isalnum(s[i + 1]))
			finder_dollar_env(s, &i);
		else
			ft_putchar_fd(s[i], 1);
		i++;
	}
}

void	echo_withoutn(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			dble_quote_incheck(s, &i);
		else if (s[i] == '\'')
			sngle_quote_incheck(s, &i);
		else if (s[i] == '$' && s[i + 1] == '?')
		{
			ft_putnbr_fd(g_list.exit_status, 1);
			i++;
		}	
		else if (s[i] == '$' && ft_isalnum(s[i + 1]))
			finder_dollar_env(s, &i);
		else
			ft_putchar_fd(s[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}
