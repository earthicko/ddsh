/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:47:10 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:47:12 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTERS_H
# define TESTERS_H
# include "t_token.h"
# include "t_node.h"
# define MSG_DEBUG "DEBUG: "

void	node_print_content(t_node *root);
void	node_print(t_node *root, int depth);

void	print_tokens(t_token *p_token, int n_tokens);

#endif
