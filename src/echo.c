/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:59 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 14:10:32 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_handle(char *s, t_utils utils)
{
	utils.quote_flag = 1;
	if (check_quotes(s, utils) == -1)
	{
		g_list.exit_status = 127;
		printf(RED"minishell: syntax error with open quotes\n");
	}
	else
	{
		if (utils.n_flag == 1)
			echo_withn(s);
		else if (utils.n_flag == -1)
			echo_withoutn(s);
	}
}

static char	*split_echo_one(char *str, int last, int start)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i - 1] == ' ' && (str[i] == '-' && str[i + 1] == 'n')
			&& str[i + 2] == ' ')
		{
			i += 3;
			while (str[i] < 33)
				i++;
			start = i;
		}
		i++;
	}
	tmp = ft_echo_substr(str, start, last + 1);
	return (tmp);
}

static char	*split_echo_two(char *str, int last, int start)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] > 32)
			;
		else
		{
			i++;
			while (str[i] < 33)
				i++;
			start = i;
			break ;
		}
		i++;
	}
	tmp = ft_echo_substr(str, start, last + 1);
	return (tmp);
}

static char	*ft_split_echo(char *str, t_utils utils)
{
	int		last;
	int		start;
	int		len;
	char	*tmp;

	last = 0;
	start = 0;
	len = ft_strlen(str) - 1;
	while (len)
	{
		if (str[len] > 32 && str[len] <= 127)
		{
			last = len;
			break ;
		}
		len--;
	}
	if (utils.n_flag == 1)
		tmp = split_echo_one(str, last, start);
	else
		tmp = split_echo_two(str, last, start);
	return (tmp);
}

void	echo_canalizer(char	*str)
{
	t_utils	utils;
	char	*tmp;

	tmp = NULL;
	utils.n_flag = n_check(str);
	if (!isonlyecho(str))
		;
	else
	{
		tmp = ft_split_echo(str, utils);
		echo_handle(tmp, utils);
		free(tmp);
	}
}
