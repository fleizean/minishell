/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:11:03 by eyagiz            #+#    #+#             */
/*   Updated: 2022/10/19 12:23:03 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_my_env(char *var_name)
{
	int		i;
	int		j;
	int		t;
	char	*tmp;

	i = -1;
	j = 0;
	while (g_list.env[++i])
	{
		tmp = ft_strjoin(var_name, "=");
		t = ft_strlen(tmp);
		if (ft_strncmp(g_list.env[i], tmp, t) == 0)
		{
			while (g_list.env[i][j])
			{
				if (g_list.env[i][j] == '=')
				{
					while (g_list.env[i][++j])
						ft_putchar_fd(g_list.env[i][j], 1);
				}
				j++;
			}
		}
		free(tmp);
	}
}

void	finder_dollar_env(char *s, int *i)
{
	char	*tmp;
	int		j;

	tmp = malloc(sizeof(char) * 75);
	j = 0;
	(*i)++;
	while (*(s + *i) != ' ' && *(s + *i) && ft_isalnum(*(s + *i)))
	{
		tmp[j] = *(s + *i);
		(*i)++;
		j++;
	}
	(*i)--;
	get_my_env(tmp);
	free(tmp);
}

void	sngle_quote_incheck(char *s, int *i)
{
	(*i)++;
	while (*(s + *i) != '\'' && *(s + *i))
	{
		ft_putchar_fd(*(s + *i), 1);
		(*i)++;
	}
}

char	*ft_echo_substr(char *str, int start, int end)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * (end - start) + 1);
	while (start < end)
	{
		tmp[i] = str[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	n_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '-' && str[i])
		i++;
	if (str[i - 1] == ' ' && (str[i] == '-'
			&& str[i + 1] == 'n') && str[i + 2] == ' ')
		return (1);
	return (-1);
}
