/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:59:17 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/22 15:08:03 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count(long long n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	char			*str;
	unsigned int	i;
	long long		temp;

	temp = n;
	i = count(temp);
	if (!(str = malloc(sizeof(str[i]) * i + 1)))
		return (0);
	if (temp < 0)
	{
		str[0] = '-';
		temp *= -1;
	}
	str[i] = '\0';
	if (temp == 0)
		str[0] = '0';
	while (temp > 0)
	{
		str[--i] = temp % 10 + '0';
		temp = temp / 10;
	}
	return (str);
}
