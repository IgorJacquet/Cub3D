/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:59:08 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/24 13:08:54 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t length)
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	b = 0;
	if (!dest || !src)
		return (0);
	while (src[a] != '\0')
		++a;
	if (length == 0)
		return (a);
	while (src[b] != '\0' && b < (length - 1))
	{
		dest[b] = src[b];
		++b;
	}
	dest[b] = '\0';
	return (a);
}
