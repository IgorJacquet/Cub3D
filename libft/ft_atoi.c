/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:19:54 by ijacquet          #+#    #+#             */
/*   Updated: 2020/02/26 13:22:30 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long	nbrs;
	int				neg;

	nbrs = 0;
	neg = 1;
	while (*str && (*str == ' ' || *str == '\f' || *str == '\t' ||
				*str == '\n' || *str == '\r' || *str == '\v'))
		str++;
	if (*str && ((*str == '-') || (*str == '+')))
	{
		if (*str == '-')
			neg = neg * -1;
		str++;
	}
	if (!(*str) || *str > '9' || *str < '0')
		return (-1);
	while (*str && *str <= '9' && *str >= '0')
	{
		nbrs = nbrs * 10 + (*str - '0');
		if (nbrs > 9223372036854775807)
			return (neg > 0 ? -1 : 0);
		str++;
	}
	return (nbrs * neg);
}
