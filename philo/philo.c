/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/22 01:20:33 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    diff_time(long time)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - time);
}

void    *philo_life(void *arg)
{
    t_philo *philo;
    long    time_0;

    int     n;

    philo = arg;
    n = 0;
    time_0 = philo->acad->time_0;
    while (philo->acad->times_eat == -1 || philo->acad->times_eat > n)
    {
        if (philo->n % 2)
        {
            pthread_mutex_lock(philo->f_right);
            pthread_mutex_lock(&(philo->speak));
            printf("%ld %d has taken a fork\n",diff_time(time_0), philo->n);
            pthread_mutex_unlock(&(philo->speak));
            pthread_mutex_lock(philo->f_left);
        }
        else
        {
            pthread_mutex_lock(philo->f_left);
            pthread_mutex_lock(&(philo->speak));
            printf("%ld %d has taken a fork\n",diff_time(time_0), philo->n);
            pthread_mutex_unlock(&(philo->speak));
            pthread_mutex_lock(philo->f_right);
        }
        pthread_mutex_lock(&(philo->speak));
        printf("%ld %d has taken a fork\n",diff_time(time_0), philo->n);
        pthread_mutex_unlock(&(philo->speak));
        pthread_mutex_lock(&(philo->speak));
        printf("%ld %d is eating\n",diff_time(time_0), philo->n);
        philo->lst_meal = diff_time(philo->acad->time_0); 
        pthread_mutex_unlock(&(philo->speak));
        usleep(philo->acad->to_eat * 1000);
        pthread_mutex_unlock(philo->f_left);
        pthread_mutex_unlock(philo->f_right);
        pthread_mutex_lock(&(philo->speak));
        printf("%ld %d is sleeping\n",diff_time(time_0), philo->n);
        pthread_mutex_unlock(&(philo->speak));
        usleep(philo->acad->to_sleep * 1000);
        pthread_mutex_lock(&(philo->speak));
        printf("%ld %d is thinking\n",diff_time(time_0), philo->n);
        pthread_mutex_unlock(&(philo->speak));
        n++;
    }
    return(NULL);
}

void    *timer_thread(void *arg)
{
    int n;
    t_academy *acad;

    acad = arg;
    while(1)
    {
        n = 0;
        while (n < acad->nb)
        {
            if ((diff_time(acad->time_0) - acad->philos[n].lst_meal) > acad->to_die)
            {
                pthread_mutex_lock(&(acad->speak));
                printf("%ld %d died %ld\n",diff_time(acad->time_0), n + 1, acad->to_die);
                return(0);
            }            
            n++;
        }
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
        acad->philos[n - 1].acad = acad;
        acad->philos[n - 1].speak = acad->speak;
        acad->philos[n - 1].lst_meal = 0;
        if(n == acad->nb)
            acad->philos[n - 1].p_right = &(acad->philos[0]);
        else
            acad->philos[n - 1].p_right = &(acad->philos[n]);
        acad->philos[n - 1].f_right = &(acad->forks[n - 1]);
        if(n != 1)
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
    acad->timer = malloc(sizeof(pthread_t));
    acad->time_0 = diff_time(0);
    if (pthread_create(acad->timer, NULL, &timer_thread, (void *)acad))
        error(acad);
    while (n < acad->nb)
    {
        if(pthread_create(acad->philos[n].id, NULL, &philo_life, (void *)&(acad->philos[n])))
            error(acad);
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

    if (ac > 6 || ac < 5)
        return(0);
    academy = malloc(sizeof(t_academy));
    arguments_handling(academy, av, ac);
    academy->death = 0;
    create_forks(academy);

    create_philophers(academy);
    //initialization(academy);
    //destroy_academy(academy);
    
    pthread_join(*(academy->timer), NULL);
    printf("FIN\n");
    //free(academy->forks);
    //free(academy->philos);
    //free(academy);
    return(0);   
}
