/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:03:13 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/06 22:57:45 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_lgh(long n)
{
	int		lgh;

	lgh = 1;
	if (n < 0)
		lgh++;
	while (n / 10)
	{
		n = n / 10;
		lgh++;
	}
	return (lgh);
}

void	ft_fills(long n, int lgh, char *s)
{
	int		stop;

	stop = 0;
	s[lgh--] = 0;
	if (n < 0)
	{
		s[0] = '-';
		stop = 1;
		s[lgh--] = -(n % 10) + '0';
		n /= 10;
		n *= -1;
	}
	while (lgh >= stop)
	{
		s[lgh--] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(long n)
{
	char	*s;
	int		lgh;

	lgh = ft_lgh(n);
	s = malloc((lgh + 2) * sizeof(char));
	if (s != NULL)
	{
		ft_fills(n, lgh, s);
		s[lgh + 1] = 0;
		s[lgh] = ' ';
	}
	return (s);
}
