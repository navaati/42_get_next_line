/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillot- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 17:53:23 by lgillot-          #+#    #+#             */
/*   Updated: 2015/05/14 22:06:04 by lgillot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include <libft.h>

#include "get_next_line.h"

static ssize_t	append_buf_grow(t_append_buf *abuf)
{
	size_t	new_allocated;
	char	*new_buf;

	new_allocated = abuf->buf ? abuf->allocated * 2 : BUFF_SIZE;
	if ((new_buf = (char *)malloc(new_allocated)) == NULL)
		return (-1);
	if (abuf->buf)
	{
		ft_memcpy(new_buf, abuf->buf, abuf->size);
		free(abuf->buf);
	}
	abuf->buf = new_buf;
	abuf->allocated = new_allocated;
	return (new_allocated);
}

static int		append_buf_fill(t_append_buf *abuf, int const fd)
{
	ssize_t	read_bytes;

	if (abuf->allocated - abuf->size < BUFF_SIZE)
	{
		if (append_buf_grow(abuf) < 0)
			return (-1);
	}
	read_bytes = read(fd, abuf->buf + abuf->size, BUFF_SIZE);
	if (read_bytes <= 0)
		return (read_bytes);
	abuf->size += read_bytes;
	return (1);
}

static char		*append_buf_pop_head(t_append_buf *abuf, size_t head_size)
{
	char	*new_buf;
	size_t	new_size;
	char	*head;

	if ((new_buf = malloc(abuf->allocated)) == NULL)
		return (NULL);
	new_size = abuf->size - head_size;
	if (new_size)
		ft_memcpy(new_buf, abuf->buf + head_size, new_size);
	head = abuf->buf;
	abuf->size = new_size;
	abuf->buf = new_buf;
	return (head);
}

int				get_next_line(int const fd, char **line)
{
	static t_append_buf	abuf = NULL_ABUF;
	t_bool				eol_found;
	size_t				processed_bytes;
	int					ret;

	if (!line)
		return (-1);
	eol_found = FALSE;
	processed_bytes = 0;
	ret = 1;
	while (!eol_found)
	{
		if (processed_bytes == abuf.size)
			if ((ret = append_buf_fill(&abuf, fd)) <= 0)
				break ;
		if (abuf.buf[processed_bytes] == '\n')
		{
			eol_found = TRUE;
			abuf.buf[processed_bytes] = '\0';
		}
		processed_bytes++;
	}
	*line = append_buf_pop_head(&abuf, processed_bytes);
	return (ret);
}
