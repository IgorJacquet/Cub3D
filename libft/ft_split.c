/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:08:12 by ijacquet          #+#    #+#             */
/*   Updated: 2020/03/07 13:35:23 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ptr_ptr_size(char const *s, char c)
{
	size_t i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static void			*ft_free(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	char	**rep;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(rep = (char **)malloc((sizeof(char*)) * (ptr_ptr_size(s, c) + 1))))
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i = 0;
			while (s[i] && s[i] != c)
				i++;
			if (!(rep[j++] = ft_strndup(s, i)))
				return (ft_free(rep));
			s = s + i;
		}
	}
	rep[j] = 0;
	return (rep);
}
