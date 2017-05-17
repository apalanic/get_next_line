/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 18:38:00 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/10 15:59:36 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H
# include <fcntl.h>
# include "libft/libft.h"
# define BUFF_SIZE 32
# define READ_ERROR -1
# define READ_SUCCESS 1
# define READ_COMPLETE 0

typedef struct		s_get
{
	char			*string;
	int				fd;
	size_t			i;
	size_t			len;
	struct s_get	*next;
}					t_get;

int					get_next_line(const int fd, char **line);

#endif
