/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:26:32 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:27:02 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>

# define PROMPT_CLR "\001\033[1;36m\002"
# define RESET_CLR "\001\033[0m\002"
# define ERR_CLR "\033[0;31m"
# define RED "\033[0;31m"
# define GREEN "\033[1;32m"

/*
** kept for libft compatibility (ft_lstnew.c / ft_lstadd_back.c use t_list)
** not used by minishell's own logic anymore
*/
typedef struct s_list
{
	void	*next;
	char	*data;
}	t_list;

typedef struct s_shell
{
	char	**env;
	int		exit_status;
}	t_shell;

typedef enum e_tok_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		type;
	char			*text;
	struct s_token	*next;
}	t_token;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				literal;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe_ctx
{
	int	*fds;
	int	n;
	int	idx;
}	t_pipe_ctx;

typedef struct s_lex_state
{
	t_token	*head;
	t_token	*tail;
}	t_lex_state;

typedef struct s_expand_ctx
{
	char	in_quote;
	char	*res;
}	t_expand_ctx;

extern int		g_signal;

/* main / loop */
void	shell_loop(t_shell *shell);

/* signals */
void	setup_parent_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);

/* prompt */
char	*build_prompt(void);
void	init_shell(void);

/* tokenizer */
t_token	*tokenize(const char *line, int *syntax_error);
void	free_tokens(t_token *tokens);

/* syntax */
int		check_syntax(t_token *tokens, t_shell *shell);

/* expansion */
char	*expand_word(const char *raw, t_shell *shell);
char	*expand_heredoc_line(const char *line, t_shell *shell);

/* builder */
t_cmd	*build_pipeline(t_token *tokens, t_shell *shell);
void	free_cmds(t_cmd *cmds);

/* env store */
char	**env_copy(char **envp);
char	*env_get(char **env, const char *key);
int		env_set(char ***env, const char *key, const char *val);
int		env_unset(char ***env, const char *key);
int		env_has(char **env, const char *key);
char	**env_sorted_copy(char **env);

/* path resolve */
char	*resolve_path(const char *cmd, char **env, int *errcode);

/* heredoc */
int		process_heredocs(t_cmd *cmds, t_shell *shell);

/* redirections */
int		apply_redirs(t_cmd *cmd, t_shell *shell);

/* exec */
int		is_builtin_name(const char *name);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
void	exec_external(t_cmd *cmd, t_shell *shell);
int		run_pipeline(t_cmd *cmds, t_shell *shell);

/* builtins */
int		builtin_echo(char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_pwd(char **argv);
int		builtin_env(char **argv, t_shell *shell);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);

/* free helpers */
void	ft_free_str(char **str);

/* libft */
char	**ft_split(const char *s, char c);
void	ft_putstr(char *str);
void	ft_putnstr(char *str, int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, int start, unsigned int len);
void	ft_putchar_fd(char c, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *str);
char	*ft_strcpy(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_islower(char *s1, char *s2, int n);
int		ft_isalnum(int c);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstrendl_fd(char *s, int fd);

#endif
