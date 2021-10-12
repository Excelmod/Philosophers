/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 22:49:25 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/13 00:07:14 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_speak(t_philo *philo, char *msg)
{
	long	time_0;
	char	str[100];
	int		stop;

	pthread_mutex_lock(philo->mu_stop);
	stop = philo->acad->stop == 0;
	pthread_mutex_unlock(philo->mu_stop);
	time_0 = philo->acad->time_0;
	if (stop)
	{
		ft_itoa_philo(str, diff_time(time_0), philo->n, msg);
		pthread_mutex_lock(philo->speak);
		if (stop)
		{
			ft_putstr_fd(str, 2);
		}
		pthread_mutex_unlock(philo->speak);
	}
}

int	philo_loop(t_philo *philo)
{
	if (philo->n % 2)
	{
		usleep(500);
		pthread_mutex_lock(philo->f_right);
		philo_speak(philo, "has taken a fork");
		if (philo->acad->nb == 1)
		{
			pthread_mutex_unlock(philo->f_right);
			return (1);
		}
		pthread_mutex_lock(philo->f_left);
	}
	else
	{
		pthread_mutex_lock(philo->f_left);
		philo_speak(philo, "has taken a fork");
		pthread_mutex_lock(philo->f_right);
	}
	philo_speak(philo, "has taken a fork");
	philo_speak(philo, "is eating");
	pthread_mutex_lock(philo->mu_meal);
	philo->lst_meal = diff_time(philo->acad->time_0);
	pthread_mutex_unlock(philo->mu_meal);
	ft_usleep(philo->acad->to_eat, philo);
	return (0);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo_loop(philo))
			return (NULL);
		pthread_mutex_unlock(philo->f_left);
		pthread_mutex_unlock(philo->f_right);
		pthread_mutex_lock(philo->mu_meal);
		(philo->meals)++;
		pthread_mutex_unlock(philo->mu_meal);
		if (philo->acad->times_eat == philo->meals)
			return (0);
		philo_speak(philo, "is sleeping");
		if (ft_usleep(philo->acad->to_sleep, philo))
			return (0);
		philo_speak(philo, "is thinking");
	}
	return (NULL);
}
