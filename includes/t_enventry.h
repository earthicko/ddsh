/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_enventry.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENVENTRY_H
# define T_ENVENTRY_H

typedef struct s_enventry
{
	char	*name;
	char	*val;
	int		exp;
}	t_enventry;

#endif
