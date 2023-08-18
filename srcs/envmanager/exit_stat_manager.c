/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stat_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:45 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// set new_stat to negative to retreive prev exit stat.
// set new stat to 0 <= new_stat to set exit stat.
int	exit_stat_manager(int new_stat)
{
	static int	stat;

	if (new_stat < 0)
		return (stat);
	if (0 <= new_stat)
	{
		stat = new_stat;
		return (0);
	}
	return (-1);
}
