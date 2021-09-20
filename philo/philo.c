/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/21 00:17:00 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_life(void *arg)
{
    int n;
    t_philo *philo;
    struct timeval tv;

    philo = arg;
    n = 1;
    while (n <= 1000)
    {
        pthread_mutex_lock(&(philo->speak));
        gettimeofday(&tv,NULL);
        printf("time =%ld le philo numero %d fait son %d-eme tour\n",tv.tv_usec, philo->n, n);
        pthread_mutex_unlock(&(philo->speak));
        n++;
    }
    return(NULL);
}

void    create_philophers(t_academy *acad)
{
    int     n;

    n = acad->nb;
    acad->philos = malloc(sizeof(t_philo) * n);
    while (n)
    {
        acad->philos[n - 1].id = malloc(sizeof(pthread_t));
        acad->philos[n - 1].n = n;
        acad->philos[n - 1].speak = acad->speak;
        if(n == acad->nb)
            acad->philos[n - 1].p_right = &(acad->philos[0]);
        else
            acad->philos[n - 1].p_right = &(acad->philos[n]);
        acad->philos[n - 1].f_right = &(acad->forks[n - 1]);
        if(n == 1)
        {
            acad->philos[n - 1].p_left = &(acad->philos[n - 2]);
            acad->philos[n - 1].f_left = &(acad->forks[n - 2]);
        }
        else
        {
            acad->philos[n - 1].p_left = &(acad->philos[acad->nb - 1]);
            acad->philos[n - 1].f_left = &(acad->forks[acad->nb - 1]);
        } 
        n--;
    }
    n = 0;
    while (n < acad->nb)
    {
        if(pthread_create(acad->philos[n].id, NULL, &philo_life, (void *)&(acad->philos[n])))
        {
            error(acad);
        }
        n++;
    }
}

void    create_forks(t_academy *acad)
{
  int     n;

    n = acad->nb;
    acad->forks = malloc(sizeof(pthread_mutex_t) * n);
    while (n)
    {
        if (pthread_mutex_init(&(acad->forks[n - 1]), NULL))
        {
            error(acad);
        }
        n--;
    }
     if (pthread_mutex_init(&(acad->speak), NULL))
        {
            error(acad);
        }
}

int     main(int ac, char **av)
{
    t_academy *academy;
    int n;

    if (ac > 6 || ac < 5)
        return(0);
    academy = malloc(sizeof(t_academy));
    arguments_handling(academy, av, ac);
    create_forks(academy);
    create_philophers(academy);
    //initialization(academy);
    //destroy_academy(academy);
    n = 0;
    while (n < academy->nb)
    {
        pthread_join(*(academy->philos[n].id), NULL);
        free(academy->philos[n].id);
        n++;
    }
    free(academy->forks);
    free(academy->philos);
    free(academy);
    return(0);   
}
