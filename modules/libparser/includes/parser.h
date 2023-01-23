/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:26 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:30 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "t_node.h"
# include "t_token.h"

t_node	*parse_tokens(t_token *tokenarr, int n_tokens);

#endif
