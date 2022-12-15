/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:56:14 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 18:44:58 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_islower(char *s1, char *s2, int n)
{
	int		i;
	char	**tmp;

	tmp = ft_split(s1, ' ');
	i = 0;
	if (n == 0)
		return (1);
	while (i < n && (tmp[0][i]))
	{
		if (tmp[0][i] >= 'A' && tmp[0][i] <= 'Z')
			tmp[0][i] += 32;
		i++;
	}
	if (ft_strncmp(tmp[0], s2, n) == 0)
	{
		ft_free_str(tmp);
		return (0);
	}
	ft_free_str(tmp);
	return (1);
}
