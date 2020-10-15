/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:13:14 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/15 12:14:00 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	endl_checker(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '\n')
			return (1);
	return (0);
}

static int	ft_reader(char (*line)[BUFFER_SIZE + 1], char *buf, int fd)
{
	int	len;
	int	i;

	i = 0;
	len = read(fd, buf, BUFFER_SIZE);
	if (len <= 0)
		return (len);
	while (i < len)
	{
		(*line)[i] = buf[i];
		i++;
	}
	(*line)[i] = '\0';
	return (1);
}

static int	line_filler(char **line, char (*rest)[BUFFER_SIZE + 1])
{
	int	a;
	int	rest_size;

	a = 0;
	rest_size = 0;
	while ((*rest)[rest_size] && (*rest)[rest_size] != '\n')
		rest_size++;
	if (!(*line = ft_memcat(*line, *rest, ft_strlen(*line), rest_size)))
		return (0);
	rest_size++;
	while ((*rest)[rest_size])
	{
		(*rest)[a] = (*rest)[rest_size];
		a++;
		rest_size++;
	}
	while ((*rest)[a])
	{
		(*rest)[a] = '\0';
		a++;
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	rest[OPEN_MAX][BUFFER_SIZE + 1];
	char		buf[BUFFER_SIZE + 1];
	int			r;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	while (!endl_checker(rest[fd]))
	{
		if (!line_filler(line, &rest[fd]))
			return (-1);
		r = ft_reader(&rest[fd], buf, fd);
		if (r < 0)
			return (ft_freeturn(line, -1));
		else if (r == 0)
			return (r);
	}
	if (!line_filler(line, &rest[fd]))
		return (-1);
	return (1);
}
