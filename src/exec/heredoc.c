/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:44 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:45 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static char	*uint_to_str(unsigned int n)
{
	char	buf[12];
	int		i;

	i = 11;
	buf[i] = '\0';
	if (n == 0)
		buf[--i] = '0';
	while (n)
	{
		buf[--i] = (n % 10) + '0';
		n /= 10;
	}
	return (ft_strdup(buf + i));
}

char	*build_path(int counter)
{
	char	*num1;
	char	*num2;
	char	*tmp1;
	char	*tmp2;
	char	*path;

	num1 = uint_to_str((unsigned int)getpid());
	num2 = uint_to_str((unsigned int)counter);
	tmp1 = ft_strjoin("/tmp/mshd_", num1);
	tmp2 = ft_strjoin(tmp1, "_");
	path = ft_strjoin(tmp2, num2);
	free(num1);
	free(num2);
	free(tmp1);
	free(tmp2);
	return (path);
}

static void	warn_eof(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited by "
		"end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}

static int	handle_eof(t_redir *redir, int *stop)
{
	if (g_signal == SIGINT)
		return (-1);
	warn_eof(redir->target);
	*stop = 1;
	return (0);
}

int	read_heredoc_line(int fd, t_redir *redir, t_shell *shell, int *stop)
{
	char	*line;
	char	*to_write;

	line = readline("> ");
	if (!line)
		return (handle_eof(redir, stop));
	if (ft_strcmp(line, redir->target) == 0)
	{
		free(line);
		*stop = 1;
		return (0);
	}
	if (redir->literal)
		to_write = ft_strdup(line);
	else
		to_write = expand_heredoc_line(line, shell);
	ft_putstrendl_fd(to_write, fd);
	free(to_write);
	free(line);
	return (0);
}
