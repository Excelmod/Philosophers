/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:03:13 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/09 21:08:09 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fills(long n, char **s)
{
	if(n / 10)
	{
		ft_fills(n / 10, s);
	}
	**s = '0' + (n % 10);
	(*s)++;
}

void	ft_itoa_philo(char *s, long time, int n, char *msg)
{
	int i;

	i = 0;
	ft_fills(time, &s);
	*(s++) = ' ';
	ft_fills((long)n, &s);
	*(s++) = ' ';
	while(msg[i])
	{
		s[i] = msg[i];
		i++;		
	}
	s[i++] = '\n';
	s[i] = 0;
}