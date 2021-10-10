/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/10 15:02:58 by ljulien          ###   ########.fr       */
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

    start = diff_time(0);
    while (diff_time(start) < time)
    {
        if (philo->acad->stop == 0)
            usleep(200);
        else
            return (1);
    }
    return (0);
}

void     philo_speak(t_philo* philo, char *msg)
{
    long time_0;
    /*char  *str1;
    char  *str2;
    char  *str;*/


    time_0 = philo->acad->time_0;
    if (philo->acad->stop == 0)
    {
        /*str2 = ft_itoa(philo->n);
        str1 = ft_itoa(diff_time(time_0));
        time_0 = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(msg) + 2;
        str = malloc(sizeof(char *) * (time_0));
        str[0] = 0;
        strlcat(str, str1, time_0);
        strlcat(str, str2, time_0);
        strlcat(str, msg, time_0);
        strlcat(str, "\n", time_0);
        pthread_mutex_lock(&(philo->speak));
        ft_putstr_fd(str, 1);
        usleep(150);
        pthread_mutex_unlock(&(philo->speak));
        free(str1);
        free(str2);
        free(str);*/
        pthread_mutex_lock(&(philo->speak));
        if (philo->acad->stop == 0)
            printf("%ld %d %s\n", diff_time(time_0), philo->n, msg);
        pthread_mutex_unlock(&(philo->speak));
    }
}

void    *philo_life(void *arg)
{
    t_philo *philo;

    philo = arg;
    philo->meals = 0;
    while (1)
    {
        if (philo->n % 2)
        {
            pthread_mutex_lock(philo->f_right);
            philo_speak(philo, "has taken a fork");
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
        philo->lst_meal = diff_time(philo->acad->time_0); 
        ft_usleep(philo->acad->to_eat, philo);
        pthread_mutex_unlock(philo->f_left);
        pthread_mutex_unlock(philo->f_right);
        (philo->meals)++;
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

    while(1)
    {
        n = 0;
        cnt = 0;
        usleep(50);
        while (n < acad->nb)
        {
            if (acad->times_eat != -1 && acad->philos[n].meals >= acad->times_eat)
            {
                cnt++;
            }      
            else if ((diff_time(acad->time_0) - acad->philos[n].lst_meal) > acad->to_die)
            {
                acad->stop = 1;
                pthread_mutex_lock(&(acad->speak));
                usleep(200);
                printf("%ld %d died\n",diff_time(acad->time_0), n + 1);
                pthread_mutex_unlock(&(acad->speak));
                return;
            }     
            n++;
        }
        if  (cnt == acad->nb)
        {
            acad->stop = 1;
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
    academy->stop = 0;
    create_forks(academy);
    create_philophers(academy);
    //destroy_academy(academy);
    
    timer(academy);
    int i;

    i = 0;
    while(i < academy->nb)
    {
        pthread_join(*(academy->philos[i].id), NULL);
        printf("FIN du philo %d et il a mange %ld fois\n", i + 1, academy->philos[i].meals);
        pthread_mutex_destroy(academy->philos[i].f_right);
        i++;
    }
    pthread_mutex_destroy(&(academy->speak));
    free(academy->forks);
    free(academy->philos);
    free(academy);
    return(0);   
}
