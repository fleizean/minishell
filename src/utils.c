/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:04:01 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/08 23:26:13 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cwd_buf(void)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	return (buf);
}

char	*create_prompt(void)
{
	t_temp_var	a;

	a.tmp = get_cwd_buf();
	a.tmp1 = ft_strdup(CYAN);
	a.tmp2 = ft_strdup(WHITE);
	a.tmp3 = ft_strjoin(a.tmp1, a.tmp);
	a.tmp4 = ft_strjoin(a.tmp3, a.tmp2);
	a.tmp5 = ft_strjoin(a.tmp4, " $ ");
	free(a.tmp3);
	free(a.tmp);
	free(a.tmp4);
	free(a.tmp1);
	free(a.tmp2);
	return (a.tmp5);
}

void	ft_lst_free(t_list **stackA)
{
	t_list	*temp;

	temp = NULL;
	while (*stackA)
	{
		temp = (*stackA)->next;
		free(*stackA);
		*stackA = NULL;
		if (temp == NULL)
			break ;
		*stackA = temp;
	}
	free(stackA);
}

int	count(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

char	*sub_redir(char **str, int i)
{
	char	*temp;
	int		m;
	int		k;
	int		j;

	j = 0;
	k = -1;
	temp = (char *)malloc(sizeof(char) * 100);
	while (++k < i)
	{
		m = 0;
		while (str[k][m])
			temp[j++] = str[k][m++];
		temp[j] = ' ';
		j++;
	}
	temp[j - 1] = '\0';
	return (temp);
}
