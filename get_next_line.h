/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillot- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 18:54:37 by lgillot-          #+#    #+#             */
/*   Updated: 2015/05/10 21:35:56 by lgillot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8

typedef struct	s_append_buf
{
	size_t	allocated;
	size_t	size;
	char	*buf;
}				t_append_buf;

# define NULL_ABUF { .allocated = 0, .size = 0, .buf = NULL }

int				get_next_line(int const fd, char **line);

#endif
