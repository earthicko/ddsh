/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_execunit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:51 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:52 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXECUNIT_H
# define T_EXECUNIT_H

# include "libft_def.h"
# include "t_node.h"

enum	e_redirtype
{
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_IN_HERE,
	REDIR_OUT_APPEND,
};

typedef struct s_exec_redir
{
	int		type;
	char	*content;
}	t_exec_redir;

typedef struct s_exec_arg
{
	char	*content;
}	t_exec_arg;

typedef struct s_exec_simplecom
{
	t_list	*redirs;
	t_list	*args;
}	t_exec_simplecom;

typedef struct s_exec_pipeseq
{
	t_list	*simplecoms;
}	t_exec_pipeseq;

t_exec_redir		*exec_redir_create(t_node *root);
t_exec_redir		*exec_redir_destroy(t_exec_redir *exec);
t_exec_arg			*exec_arg_create(t_node *root);
t_exec_arg			*exec_arg_destroy(t_exec_arg *exec);
t_exec_simplecom	*exec_simplecom_create(t_node *root);
t_exec_simplecom	*exec_simplecom_destroy(t_exec_simplecom *exec);
t_exec_pipeseq		*exec_pipeseq_create(t_node *root);
t_exec_pipeseq		*exec_pipeseq_destroy(t_exec_pipeseq *exec);

int					exec_simplecom_getargv(t_exec_simplecom *exec, char ***buf);

t_exec_simplecom	*get_nth_simplecom(t_exec_pipeseq *exec, int n);
t_exec_redir		*get_nth_redir(t_exec_simplecom *exec, int n);
t_exec_arg			*get_nth_arg(t_exec_simplecom *exec, int n);

int					exec_lstadd(t_list **lst, void *exec);
void				*get_nth_exec(t_list *lst, int n);

#endif
