/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:00:10 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:00:10 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static int	valid_identifier(char *s)
{
	int	i;

	if (!s[0] || (s[0] >= '0' && s[0] <= '9'))
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_shell *shell)
{
	char	**sorted;
	int		i;

	sorted = env_sorted_copy(shell->env);
	i = 0;
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sorted[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_free_str(sorted);
}

static void	export_one(char *arg, t_shell *shell, int *status)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (eq)
		key = ft_substr(arg, 0, eq - arg);
	else
		key = ft_strdup(arg);
	if (!valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*status = 1;
	}
	else if (eq)
		env_set(&shell->env, key, eq + 1);
	else if (!env_has(shell->env, key))
		env_set(&shell->env, key, "");
	free(key);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		print_export(shell);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		export_one(argv[i], shell, &status);
		i++;
	}
	return (status);
}
