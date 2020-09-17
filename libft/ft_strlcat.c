/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:39:21 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/24 13:06:28 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	while (src[j] != '\0')
		j++;
	if (i == size)
		return (i + j);
	k = i + j;
	j = 0;
	while ((src[j] != '\0') && ((i + j) < (size - 1)))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (k);
}
