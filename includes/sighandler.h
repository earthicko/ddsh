/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:47:08 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:47:14 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLER_H
# define SIGHANDLER_H

int	signal_set_state_default(void);
int	signal_set_state_interactive(void);
int	signal_set_state_heredoc(void);
int	signal_set_state_executing(void);

#endif
