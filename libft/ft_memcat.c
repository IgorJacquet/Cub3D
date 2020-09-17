/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:51:10 by ijacquet          #+#    #+#             */
/*   Updated: 2020/02/17 17:52:14 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcat(char *line, char *rest, int line_size, int rest_size)
{
	int		i;
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (line_size + rest_size + 1))))
		return (NULL);
	i = -1;
	while (++i < line_size)
		str[i] = line[i];
	free(line);
	while (i < line_size + rest_size)
	{
		str[i] = rest[i - line_size];
		i++;
	}
	str[i] = '\0';
	return (str);
}