/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:37:26 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/10 16:38:13 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int ch)
{
	int	diff;

	diff = 'a' - 'A';
	if ('A' <= ch && ch <= 'Z')
		return (ch + diff);
	else
		return (ch);
}