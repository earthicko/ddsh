/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:30 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

int	heredoc_init(void);
int	heredoc_read(char *delimeter);
int	heredoc_get_filename(int doc_id, char **buf);
int	heredoc_get_next_filename(char **buf);
int	heredoc_clear(void);

#endif
