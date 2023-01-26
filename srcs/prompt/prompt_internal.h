/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:43:41 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:43:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_INTERNAL_H
# include "t_token.h"
# include "t_node.h"
# define PROMPT_INTERNAL_H
# define CODE_CONTINUE 1

int		prompt_clear(void);
int		prompt_getstr(char **buf);
int		prompt_gettokens(char *str, t_toks *toks);
int		prompt_getparsetree(t_toks *toks, t_node **buf);
int		prompt_execute(t_node *parse_tree);
void	prompt_print_banner(void);
char	*prompt_get_prompt_prefix(void);

#endif
