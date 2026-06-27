/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:39 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:40 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

char	*build_prompt(void)
{
	char	buf[2048];
	char	*cwd;
	char	*joined;
	char	*prompt;

	if (!getcwd(buf, sizeof(buf)))
		cwd = ft_strdup("?");
	else
		cwd = ft_strdup(buf);
	joined = ft_strjoin(PROMPT_CLR, cwd);
	free(cwd);
	prompt = ft_strjoin(joined, RESET_CLR " $ ");
	free(joined);
	return (prompt);
}
