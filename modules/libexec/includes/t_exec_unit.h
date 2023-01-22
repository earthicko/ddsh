/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_unit.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  T_EXEC_UNIT_H
# define T_EXEC_UNIT_H

enum	e_redirtype
{
	REDIR_NONE = 0,
	REDIR_IN,
	REDIR_OUT,
	REDIR_IN_HERE,
	REDIR_OUT_APPEND,
};

typedef struct s_redir
{
	int		type;
	char	*content;
}	t_redir;

typedef struct s_exec_unit
{
	char	**argv;
	t_redir	*redir_arr;
	int		n_redir;
	int		n_word;
}	t_exec_unit;	

typedef struct s_unit_arr
{
	t_exec_unit	*arr;
	int			n_unit;
}	t_unit_arr;

#endif
