/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:41 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/12 23:42:51 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export2(t_temp_var a)
{
	a.tmp_2ar = (char **)malloc(sizeof(char *) * a.i + 1);
	a.k = env_len(g_list.env);
	while (a.k--)
	{
		a.tmp_2ar[a.j] = ft_strdup(g_list.env[a.j]);
		free(g_list.env[a.j]);
		a.j++;
	}
	free(g_list.env);
	a.tmp_2ar[a.j] = ft_strdup(a.tmp1);
	a.tmp_2ar[++a.j] = NULL;
	g_list.env = a.tmp_2ar;
}

void	export(char *var_name, char *var_val)
{
	t_temp_var	a;

	a.i = 0;
	a.j = 0;
	a.k = 0;
	a.flag = 0;
	a.tmp = ft_strjoin(var_name, "=");
	a.tmp1 = ft_strjoin(a.tmp, var_val);
	while (g_list.env[a.i])
	{
		if (ft_strncmp(g_list.env[a.i], a.tmp, ft_strlen(a.tmp)) == 0)
		{
			a.flag = 1;
			free(g_list.env[a.i]);
			g_list.env[a.i] = ft_strdup(a.tmp1);
		}
		a.i++;
	}
	if (a.flag == 0)
		export2(a);
	free(a.tmp);
	free(a.tmp1);
}

void	export_handle2(char *str)
{
	char	**s;
	char	*st;
	char	*st1;
	char	*st2;

	s = ft_split(str, '=');
	if (s[0] && s[1])
	{	
		st = ft_strtrim(s[0], " ");
		st2 = ft_dlr_cnv(s[1]);
		st1 = ft_strtrim(st2, " ");
		export(st, st1);
		free(st);
		free(st1);
		free(st2);
	}
	ft_free_str(s);
}

void	export_handle(char *str)
{
	char	*sub;
	char	*sub2;
	int		len;

	len = ft_strlen(str);
	sub = ft_substr(str, 7, len - 7);
	sub2 = ft_strtrim(sub, " ");
	if (sub2[0] == '\0')
		printexport();
	else
		export_handle2(sub2);
	free(sub2);
	free(sub);
}
