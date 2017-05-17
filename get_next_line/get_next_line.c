/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:06:56 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/10 18:09:52 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*mem_realloc(char *s, int i)
{
	char	*ret;

	if ((ret = (char *)ft_memalloc(i * 2 + 1)) == NULL)
		return (NULL);
	ret = (char *)ft_memcpy(ret, s, i);
	free(s);
	return (ret);
}

static char		*read_file(const int fd)
{
	char	*buff;
	char	*file;
	int		i;
	int		byte;
	int		realloc_cntrl;

	i = 0;
	if ((buff = (char *)ft_memalloc(BUFF_SIZE + 1)) == NULL ||
			(file = (char *)ft_memalloc(BUFF_SIZE + 1)) == NULL)
		return (NULL);
	realloc_cntrl = BUFF_SIZE;
	while ((byte = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (i + byte >= realloc_cntrl)
		{
			file = mem_realloc(file, realloc_cntrl);
			realloc_cntrl *= 2;
			if (file == NULL)
				return (NULL);
		}
		ft_memcpy(file + i, buff, byte);
		i += byte;
	}
	return ((byte < 0) ? (NULL) : (file));
}

static t_get	*list_control(t_get **start, const int fd)
{
	t_get	*tmp;
	t_get	*ret;

	tmp = *start;
	if (tmp && tmp->fd == fd)
		return (tmp);
	while (tmp && (tmp = tmp->next) != *start)
		if (tmp->fd == fd)
			return (tmp);
	if ((ret = (t_get *)malloc(sizeof(t_get))) == NULL)
		return (NULL);
	ret->string = NULL;
	ret->fd = fd;
	if (*start)
	{
		ret->next = *start;
		tmp = *start;
		while (tmp->next != *start)
			tmp = tmp->next;
		tmp->next = ret;
	}
	else
		ret->next = ret;
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static t_get	*ptr;
	int				i;

	if ((ptr = list_control(&ptr, fd)) == NULL || BUFF_SIZE <= 0 || fd < 0)
		return (READ_ERROR);
	if (ptr->string == NULL)
	{
		ptr->i = 0;
		ptr->len = 0;
		if ((ptr->string = read_file(fd)) == NULL)
			return (READ_ERROR);
		ptr->len = ft_strlen(ptr->string);
		i = -1;
		while (ptr->string[++i])
			if (ptr->string[i] == '\n')
				ptr->string[i] = '\0';
	}
	*line = ft_strdup(ptr->string + ptr->i);
	if (ptr->i >= ptr->len)
	{
//		free(ptr->string);
		return (READ_COMPLETE);
	}
	ptr->i += 1 + ft_strlen(ptr->string + ptr->i);
	return (READ_SUCCESS);
}
