/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:06:15 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/13 00:10:30 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	diff_time(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - time);
}

int	ft_usleep(long time, t_philo *philo)
{
	long	start;
	int		stop;

	start = diff_time(0);
	stop = 0;
	while (diff_time(start) < time)
	{
		pthread_mutex_lock(philo->mu_stop);
		stop = philo->acad->stop == 0;
		pthread_mutex_unlock(philo->mu_stop);
		if (stop)
			usleep(200);
		else
			return (1);
	}
	return (0);
}

int	timer_loop(t_academy *acad, int n, int *cnt)
{
	int	r;
	int	r1;

	pthread_mutex_lock(acad->mu_meal);
	r = acad->philos[n].meals;
	r1 = acad->philos[n].lst_meal;
	pthread_mutex_unlock(acad->mu_meal);
	if (acad->times_eat != -1 && r >= acad->times_eat)
		(*cnt)++;
	else if ((diff_time(acad->time_0) - r1) > acad->to_die)
	{
		pthread_mutex_lock(acad->mu_stop);
		acad->stop = 1;
		pthread_mutex_unlock(acad->mu_stop);
		pthread_mutex_lock(acad->speak);
		usleep(200);
		printf("%ld %d died\n", diff_time(acad->time_0), n + 1);
		pthread_mutex_unlock(acad->speak);
		return (1);
	}
	return (0);
}

void	timer(t_academy *acad)
{
	int	n;
	int	cnt;

	while (1)
	{
		n = 0;
		cnt = 0;
		usleep(50);
		while (n < acad->nb)
		{
			if (timer_loop(acad, n, &cnt))
				return ;
			n++;
		}
		if (cnt == acad->nb)
		{
			pthread_mutex_lock(acad->mu_stop);
			acad->stop = 1;
			pthread_mutex_unlock(acad->mu_stop);
			return ;
		}
	}
}
