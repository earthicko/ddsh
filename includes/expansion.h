/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:47:09 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:47:15 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "t_token.h"
# include "strutils.h"

int			do_shell_expansion(char **buf);
int			do_shell_expansion_word_split(char *str, t_pchararr **buf);
int			do_heredoc_expansion(char **buf);
int			expand_tokens(t_toks *toks);

#endif
