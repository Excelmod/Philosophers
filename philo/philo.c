/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/12 22:35:36 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    diff_time(long time)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - time);
}

int    ft_usleep(long time, t_philo *philo)
{
    long    start;
    int     stop;

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

void     philo_speak(t_philo* philo, char *msg)
{
    long    time_0;
    char    str[100];
    int     stop;


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

//int     philo();

void    *philo_life(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (1)
    {
        if (philo->n % 2)
        {
            usleep(500);
            pthread_mutex_lock(philo->f_right);
            philo_speak(philo, "has taken a fork");
            if (philo->acad->nb == 1)
            {
                pthread_mutex_unlock(philo->f_right);
                return(NULL);
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
        pthread_mutex_unlock(philo->f_left);
        pthread_mutex_unlock(philo->f_right);
        pthread_mutex_lock(philo->mu_meal);
        (philo->meals)++;
        pthread_mutex_unlock(philo->mu_meal);
        if (philo->acad->times_eat == philo->meals)
        return(0);
        philo_speak(philo, "is sleeping");
        if(ft_usleep(philo->acad->to_sleep, philo))
            return(0);
        philo_speak(philo, "is thinking");
    }
    return(NULL);
}

void    timer(t_academy *acad)
{
    int         n;
    int         cnt;
    int         r;
    int         r1;

    while(1)
    {
        n = 0;
        cnt = 0;
        usleep(50);
        while (n < acad->nb)
        {
            pthread_mutex_lock(acad->mu_meal);
            r = acad->philos[n].meals;
            r1 = acad->philos[n].lst_meal;
            pthread_mutex_unlock(acad->mu_meal);
            if (acad->times_eat != -1 && r >= acad->times_eat)
            {
                cnt++;
            }      
            else if ((diff_time(acad->time_0) - r1) > acad->to_die)
            {
                pthread_mutex_lock(acad->mu_stop);
                acad->stop = 1;
                pthread_mutex_unlock(acad->mu_stop);
                pthread_mutex_lock(acad->speak);
                usleep(200);
                printf("%ld %d died\n",diff_time(acad->time_0), n + 1);
                pthread_mutex_unlock(acad->speak);
                return;
            }     
            n++;
        }
        if  (cnt == acad->nb)
        {
            pthread_mutex_lock(acad->mu_stop);
            acad->stop = 1;
            pthread_mutex_unlock(acad->mu_stop);
            return;
        }
    }
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
        acad->philos[n - 1].mu_stop = acad->mu_stop;
        acad->philos[n - 1].mu_meal = acad->mu_meal;
        acad->philos[n - 1].lst_meal = 0;
        acad->philos[n - 1].meals = 0;
        acad->philos[n - 1].f_right = &(acad->forks[n - 1]);
        if(n != 1)
            acad->philos[n - 1].f_left = &(acad->forks[n - 2]);
        else
            acad->philos[n - 1].f_left = &(acad->forks[acad->nb - 1]);
        n--;
    }
    n = 0;
    acad->time_0 = diff_time(0);
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

void destroy_academy(t_academy *academy)
{
    int i;

    i = 0;
    while(i < academy->nb)
    {
        pthread_join(*(academy->philos[i].id), NULL);
        i++;
    }
    i = 0;
    while(i < academy->nb)
    {
        pthread_mutex_destroy(academy->philos[i].f_right);
        i++;
    }
    pthread_mutex_destroy(academy->speak);
    pthread_mutex_destroy(academy->mu_stop);
    pthread_mutex_destroy(academy->mu_meal);
    free(academy->forks);
    free(academy->philos);
    free(academy);
}

int     main(int ac, char **av)
{
    t_academy *academy;

    if (ac > 6 || ac < 5)
        return(0);
    academy = malloc(sizeof(t_academy));
    arguments_handling(academy, av, ac);
    academy->stop = 0;
    create_forks(academy);
    create_philophers(academy);
    timer(academy);
    destroy_academy(academy);
    return(0);   
}
