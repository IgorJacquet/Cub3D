/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:04:20 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/22 15:14:53 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		isset(char s1, const char *set)
{
	unsigned int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i] != '\0')
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char			*start;
	char			*end;
	char			*rep;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	start = (char *)s1;
	if (!s1 || !set)
		return (NULL);
	end = (char *)s1 + ft_strlen((char *)s1);
	while (isset(*start, set) == 1)
		start++;
	if (end > start)
		end--;
	while (isset(*end, set) == 1)
		end--;
	len = end - start + 1;
	if (!(rep = (char *)malloc(sizeof(*start) * (len + 1))))
		return (NULL);
	while (len--)
		rep[i++] = *start++;
	rep[i] = '\0';
	return (rep);
}
