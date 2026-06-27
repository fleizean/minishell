/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:28:37 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:28:37 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "minishell.h"

/* internal helpers shared between split implementation files */
int				has_quote(const char *raw);
char			*strip_quotes(const char *raw);
t_cmd			*new_cmd(void);
void			append_argv(t_cmd *cmd, char *word);
t_redir_type	redir_type_of(t_tok_type type);
char			*append_str(char *res, char *addition);
char			*expand_dollar(const char *raw, int *i, t_shell *shell);
int				is_dollar_expansion(const char *raw, int i, char in_quote);
t_token			*new_token(t_tok_type type, char *text);
void			append_token(t_token **head, t_token **tail, t_token *tok);
int				read_word_end(const char *line, int start, int *error);
int				run_multi(t_cmd *cmds, t_shell *shell);
int				count_cmds(t_cmd *cmds);
void			close_all_pipes(int *fds, int n);
void			run_child(t_cmd *cmd, t_shell *shell, t_pipe_ctx ctx);
int				*create_pipes(int n);
char			*build_path(int counter);
int				read_heredoc_line(int fd, t_redir *redir, t_shell *shell,
					int *stop);
int				env_len(char **env);
int				env_index(char **env, const char *key);
char			*resolve_direct(const char *cmd, int *errcode);
char			*search_dirs(char **dirs, const char *cmd, int *errcode);

#endif
