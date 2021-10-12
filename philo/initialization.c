/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 22:58:41 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/13 00:13:13 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_academy *acad, int n)
{
	acad->philos[n - 1].id = 0;
	acad->philos[n - 1].id = malloc(sizeof(pthread_t));
	acad->philos[n - 1].n = n;
	acad->philos[n - 1].acad = acad;
	acad->philos[n - 1].speak = acad->speak;
	acad->philos[n - 1].mu_stop = acad->mu_stop;
	acad->philos[n - 1].mu_meal = acad->mu_meal;
	acad->philos[n - 1].lst_meal = 0;
	acad->philos[n - 1].meals = 0;
	acad->philos[n - 1].f_right = &(acad->forks[n - 1]);
	if (n != 1)
		acad->philos[n - 1].f_left = &(acad->forks[n - 2]);
	else
		acad->philos[n - 1].f_left = &(acad->forks[acad->nb - 1]);
}

void	create_philosophers(t_academy *acad)
{
	int	n;

	n = acad->nb;
	acad->philos = malloc(sizeof(t_philo) * n);
	while (n)
	{
		init_philo(acad, n);
		n--;
	}
	n = 0;
	acad->time_0 = diff_time(0);
	while (n < acad->nb)
	{
		if (pthread_create(acad->philos[n].id, NULL,
				&philo_life, (void *)&(acad->philos[n])))
			error(acad);
		n++;
	}
}

void	create_forks(t_academy *acad)
{
	int	n;

	n = acad->nb;
	acad->forks = malloc(sizeof(pthread_mutex_t) * n);
	acad->speak = malloc(sizeof(pthread_mutex_t));
	acad->mu_stop = malloc(sizeof(pthread_mutex_t));
	acad->mu_meal = malloc(sizeof(pthread_mutex_t));
	while (n)
	{
		if (pthread_mutex_init(&(acad->forks[n - 1]), NULL))
			error(acad);
		n--;
	}
	if (pthread_mutex_init(acad->speak, NULL))
		error(acad);
	if (pthread_mutex_init(acad->mu_stop, NULL))
		error(acad);
	if (pthread_mutex_init(acad->mu_meal, NULL))
		error(acad);
}

void	initialization(t_academy *acad)
{
	acad->forks = NULL;
	acad->speak = NULL;
	acad->mu_stop = NULL;
	acad->mu_meal = NULL;
	acad->philos = NULL;
}
