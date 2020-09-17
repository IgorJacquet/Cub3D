/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:35:07 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/15 18:30:26 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	ptr = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			ptr = (char *)haystack + i;
			j = 0;
			while (haystack[i + j] == needle[j] && (i + j) < len)
			{
				if (needle[j + 1] == '\0')
					return (ptr);
				j++;
			}
		}
		i++;
	}
	return (0);
}
