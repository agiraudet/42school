/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:14:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/11 11:13:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUSH_H
# define MUSH_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"
# include <signal.h>

# define BUILTIN_LIST "cd pwd echo exit env unset export"

enum	e_type
{
	SIMPLE,
	DOUBLE
};

enum	e_dir
{
	IN,
	OUT
};

enum	e_err
{
	BASIC,
	NOCMD,
	LIMIT,
	STRNO,
	HANDLE,
	TOKEN,
	EXPORT,
	NB_ARG,
	EXIT_ARG,
	AMB_REDIR
};

typedef struct s_envar
{
	char	*name;
	char	*value;
}				t_envar;

typedef struct s_redir
{
	enum e_type	type;
	enum e_dir	dir;
	int			fd;
	int			wip_fd;
	char		*word;
}				t_redir;

typedef struct s_cmd
{
	pid_t	pid;
	char	*pathname;
	char	**argv;
	char	**envp;
	t_list	*lenvp;
	t_redir	**rdrv;
	int		status;
	int		*pipe_in;
	int		*pipe_out;
	int		dft_fdin;
}				t_cmd;

typedef struct s_norm
{
	int		i;
	char	*tmp;
	char	**args;
	t_list	*arg_lst;
	t_list	*rdr_lst;
}				t_norm;

typedef struct s_parse
{
	int		i;
	char	**nope;
	int		ret;
	char	*ptr;
}				t_parse;

t_cmd	*cmd_new(const char *str, t_list *lenvp);
void	cmd_del(void *cmd_ptr);
t_redir	*redir_new(char **args, int *i);
void	redir_del(void *redir_ptr);
t_cmd	**parse_line(const char *line, t_list *lenvp);
int		exec_cmdlst(t_cmd **cmd_lst);
void	ft_skip_spaces(const char **str);
int		ft_arrlen(void **arr);
void	ft_arrdel(void **arr, void (*del)(void *));
void	**ft_arrflst(t_list	**lst, size_t type_size);
char	*ft_strndup(const char *src, size_t n);
void	ft_stdfd(int mode);
void	ft_str_substitute(char **src, char *find, char *replace);
int		ft_isdir(const char *pathname);
int		ft_issain(const char *str);
void	ft_arrsort(void **tab, int (*cmp)(void *, void *));
void	ft_arradd(void ***arr, void *new, size_t type_size);
void	pipe_dellist(int **pipe_lst);
void	env_init(t_list **lenvp, char **envp);
t_envar	*env_new(char *src);
char	**env_arrflst(t_list *lenvp);
char	*expand_env(t_list *lenvp, const char *str);
char	*env_get_value(t_list *lenvp, const char *name);
t_envar	*env_get(t_list *lenvp, const char *name);
void	env_del(void *envar_ptr);
void	env_update(t_list **lenvp, char *name, char *new_value);
int		env_updatesp(t_list **lenvp, char *str);
int		env_cmp(void *var, void *name);
char	*env_get_str(t_envar *var);
int		builtin_ft(t_cmd *cmd);
int		builtin_is(const char *cmdname);
int		ft_cd(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_pwd(void);
int		ft_unset(t_cmd *cmd);
char	*path_set(t_cmd *cmd);
void	pipe_setup_external(t_cmd *cmd);
void	pipe_setup_builtin(t_cmd *cmd);
void	pipe_close(int *pipe_fd);
int		**pipe_newlist(int n);
void	redir_setup(t_cmd *cmd);
void	print_cmdlst(t_cmd	**cmd_lst);
void	print_cmd(t_cmd *cmd);
void	debug_setpath(char **cmdname);
void	debug_close(char *msg, int fd);
void	exit_clean(t_list *lenvp);
void	exit_code_set(int code);
int		exit_code_get(void);
char	*error_name(char *name);
int		error_msg(char *msg, enum e_err mode);
char	*parse_format(t_list *lenvp, const char *src);
void	signals_set(void);
void	signals_set_bis(void);
int		exit_code_from_cmd(int builtin_status, pid_t last_pid);
char	*tilde_manage_expand(t_list *lenvp, char *str);
char	**args_split(const char *str);
int		check_rdr(char *str);
char	**ft_splitpath(char *s, char c);
void	redir_del(void *redir_ptr);
int		heredoc_check(t_cmd *cmd);
int		heredoc(const char *limiter);
void	heredoc_close(t_cmd *cmd);
int		ft_exit_check(t_cmd *cmd);
void	args_fix_redir(char **str);
void	ft_skip_quotes(const char *str, int *i);
pid_t	signal_check_in_pipe(void);
char	*ft_strrplc_one(char *src, char *find, char *replace);

#endif
