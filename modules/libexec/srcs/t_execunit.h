/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_execunit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXECUNIT_H
# define T_EXECUNIT_H

enum	e_redirtype
{
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_IN_HERE,
	REDIR_OUT_APPEND,
};

typedef struct s_redir
{
	int		type;
	char	*content;
}	t_redir;

typedef struct s_execunit
{
	char	**argv;
	t_redir	*redir_arr;
	int		n_redir;
	int		n_word;
}	t_execunit;	

void	units_destroy(t_execunit *units, int n_units);
int		_free_unit_member(t_execunit *unit);
int		_free_single_unit(t_execunit *unit);
int		_free_all_unit(t_execunit *units, int n_units);

#endif
