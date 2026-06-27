/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_store_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:00:00 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:00:00 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**env_sorted_copy(char **env)
{
	char	**copy;
	int		n;
	int		i;
	int		j;

	n = env_len(env);
	copy = env_copy(env);
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
				swap(&copy[j], &copy[j + 1]);
			j++;
		}
		i++;
	}
	return (copy);
}
