/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:05:41 by dahkang           #+#    #+#             */
/*   Updated: 2022/11/12 23:24:11 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(t_line *line)
{
	if (line->str)
		free(line->str);
	line->str = 0;
	line->len = 0;
	return (0);
}

static char	*line_join(t_line *line, char *buf)
{
	if (!(line->len))
	{
		if (line->str)
			free(line->str);
		line->str = 0;
		line->len = gnl_strlen(buf);
		return (gnl_strdup(buf));
	}
	else
		return (gnl_strjoin(line, buf));
	return (0);
}

static char	*get_nl_line(t_line *line)
{
	char	*ret;
	char	*left;
	size_t	cut_off;

	cut_off = gnl_get_idx(line->str, '\n');
	ret = gnl_substr(line, 0, cut_off + 1);
	if (!ret)
		return (ft_free(line));
	left = gnl_substr(line, cut_off + 1, line->len);
	if (!left)
	{
		free(ret);
		ret = 0;
		return (ft_free(line));
	}
	free(line->str);
	line->len = gnl_strlen(left);
	if (left[0] == 0)
	{
		free(left);
		line->str = 0;
	}
	else
		line->str = left;
	return (ret);
}

static char	*get_eof_line(t_line *line)
{
	char	*ret;

	if (gnl_get_idx(line->str, '\n') != -1)
		return (get_nl_line(line));
	if (line->len)
	{
		ret = gnl_strdup(line->str);
		if (!ret)
			return (ft_free(line));
		free(line->str);
		line->str = 0;
		line->len = 0;
		return (ret);
	}
	else
		return (ft_free(line));
}

char	*get_next_line(int fd)
{
	static t_line	line[OPEN_FD_MAX];
	char			buf[BUFFER_SIZE + 1];
	ssize_t			byte;

	if (fd < 0 || fd > OPEN_FD_MAX || BUFFER_SIZE <= 0)
		return (0);
	if (gnl_get_idx(line[fd].str, '\n') != -1)
		return (get_nl_line(&line[fd]));
	byte = read(fd, buf, BUFFER_SIZE);
	while (byte)
	{
		if (byte < 0)
			return (ft_free(&line[fd]));
		buf[byte] = 0;
		line[fd].str = line_join(&line[fd], buf);
		if (!(line[fd].str))
			return (ft_free(&line[fd]));
		if (gnl_get_idx(buf, '\n') != -1)
			return (get_nl_line(&line[fd]));
		byte = read(fd, buf, BUFFER_SIZE);
	}
	return (get_eof_line(&line[fd]));
}
