/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:52:47 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/20 23:28:29 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	atoi_check(t_academy *acad, const char *str)
{
	int			i;
	long long	nb;
	int			flag;

	i = 0;
	nb = 0;
	flag = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i++] - '0';
		flag = 1;
		if (nb > 9223372036854775807)
			error(acad);
	}
	if (str[i] != '\0' || flag == 0)
		error(acad);
	return ((long)(nb));
}

void	arguments_handling(t_academy *acad, char **av, int ac)
{
	acad->nb = atoi_check(acad, av[1]);
	acad->to_die = atoi_check(acad, av[2]);
	acad->to_eat = atoi_check(acad, av[3]);
	acad->to_sleep = atoi_check(acad, av[4]);
	if (ac == 6)
	{
		acad->times_eat = atoi_check(acad, av[5]);
	}
	else
		acad->times_eat = -1;
}