/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:43:00 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/12 23:43:44 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_chrjoin(char *s, char c)
{
	int		j;
	int		i;
	char	*st;

	i = ft_strlen(s);
	st = (char *)malloc(sizeof(char) * (i + 2));
	j = 0;
	while (s[j])
	{
		st[j] = s[j];
		j++;
	}
	st[i] = c;
	st[i + 1] = '\0';
	return (st);
}

char	*ft_get_env(char *var_name)
{
	t_temp_var	a;
	char		*s;

	a.flag = 0;
	a.k = 0;
	a.i = -1;
	a.j = 0;
	while (g_list.env[++a.i])
	{
		a.tmp = ft_strjoin(var_name, "=");
		a.t = ft_strlen(a.tmp);
		a.l = ft_strlen(g_list.env[a.i]) - a.t;
		if (ft_strncmp(g_list.env[a.i], a.tmp, a.t) == 0)
		{
			a.flag = 1;
			s = ft_substr(g_list.env[a.i], a.t, a.l);
		}
		free(a.tmp);
		if (a.flag == 1)
			break ;
	}
	if (a.flag == 0)
		return (ft_strdup(""));
	return (s);
}

static void	ft_dlr_cnv_utils(t_temp_var *a, char *s)
{
	a->i++;
	a->j = 0;
	while (s[a->j] && ft_isalnum(s[a->j]))
		a->j++;
	a->tmp3 = malloc(sizeof(char) * (a->j + 1));
	a->j = 0;
	while (s[a->i] && ft_isalnum(s[a->i]))
	{	
		a->tmp3[a->j] = s[a->i];
		a->i++;
		a->j++;
	}
	a->tmp3[a->j] = '\0';
	a->tmp2 = ft_get_env(a->tmp3);
	free(a->tmp3);
	a->tmp1 = ft_strjoin(a->tmp, a->tmp2);
	free(a->tmp2);
	free(a->tmp);
	a->tmp = ft_strdup(a->tmp1);
	free(a->tmp1);
}

char	*ft_dlr_cnv(char *s)
{
	t_temp_var	a;

	a.tmp = ft_strdup("");
	a.i = 0;
	while (s[a.i])
	{
		if (s[a.i] == '$' && ft_isalnum(s[a.i + 1]))
		{
			ft_dlr_cnv_utils(&a, s);
			if (a.i >= ft_strlen(s))
				break ;
		}
		else
		{
			a.tmp1 = ft_chrjoin(a.tmp, s[a.i++]);
			free(a.tmp);
			a.tmp = ft_strdup(a.tmp1);
			free(a.tmp1);
		}	
	}
	return (a.tmp);
}
