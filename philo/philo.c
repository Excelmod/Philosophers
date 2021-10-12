/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/13 00:05:03 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_academy(t_academy *academy)
{
	int	i;

	i = 0;
	while (academy->philos && i < academy->nb)
	{
		pthread_mutex_destroy(academy->philos[i].f_right);
		free(academy->philos[i].id);
		i++;
	}
	pthread_mutex_destroy(academy->speak);
	pthread_mutex_destroy(academy->mu_stop);
	pthread_mutex_destroy(academy->mu_meal);
	free(academy->speak);
	free(academy->mu_stop);
	free(academy->mu_meal);
	free(academy->forks);
	free(academy->philos);
	free(academy);
}

int	main(int ac, char **av)
{
	t_academy	*academy;
	int			i;

	if (ac > 6 || ac < 5)
		return (0);
	academy = malloc(sizeof(t_academy));
	arguments_handling(academy, av, ac);
	academy->stop = 0;
	create_forks(academy);
	create_philosophers(academy);
	timer(academy);
	i = 0;
	while (i < academy->nb)
	{
		pthread_join(*(academy->philos[i].id), NULL);
		i++;
	}
	destroy_academy(academy);
	return (0);
}
