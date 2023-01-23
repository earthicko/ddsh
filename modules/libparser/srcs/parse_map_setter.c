/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:53 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_token.h"
#include "t_node.h"

void	_map_setter_cmd_word(int *token_map)
{
	ft_bzero(token_map, sizeof(int) * N_TOKENTYPE);
	token_map[TOKENTYPE_WORD] = TRUE;
}

void	_map_setter_io_op_file(int *token_map)
{
	ft_bzero(token_map, sizeof(int) * N_TOKENTYPE);
	token_map[TOKENTYPE_REDIR_IN] = TRUE;
	token_map[TOKENTYPE_REDIR_OUT] = TRUE;
	token_map[TOKENTYPE_REDIR_OUT_APPEND] = TRUE;
}

void	_map_setter_filename(int *token_map)
{
	ft_bzero(token_map, sizeof(int) * N_TOKENTYPE);
	token_map[TOKENTYPE_WORD] = TRUE;
}

void	_map_setter_io_op_here(int *token_map)
{
	ft_bzero(token_map, sizeof(int) * N_TOKENTYPE);
	token_map[TOKENTYPE_REDIR_IN_HERE] = TRUE;
}

void	_map_setter_here_end(int *token_map)
{
	ft_bzero(token_map, sizeof(int) * N_TOKENTYPE);
	token_map[TOKENTYPE_WORD] = TRUE;
}
