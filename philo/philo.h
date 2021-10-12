/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:36:14 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/12 23:26:37 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

struct  s_academy;

typedef struct s_philo
{
    int                 n;
    pthread_t           *id;
    pthread_mutex_t     *f_right;
    pthread_mutex_t     *f_left;
    pthread_mutex_t     *speak;
    pthread_mutex_t     *mu_meal;
    pthread_mutex_t     *mu_stop;
    long                lst_meal;
    long                meals;
    struct s_academy    *acad;

}               t_philo;

typedef struct s_academy
{
    t_philo *philos;
    pthread_mutex_t  *forks;
    pthread_mutex_t  *speak;
    pthread_mutex_t  *mu_stop;
    pthread_mutex_t  *mu_meal;
    long    nb;
    long    to_sleep;
    long    to_eat;
    long    to_die;
    long    times_eat;
    int     stop;
    long    time_0;

}               t_academy;

void    *philo_life(void *arg);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void    create_forks(t_academy *acad);
void    create_philosophers(t_academy *acad);
long    diff_time(long time);
void	arguments_handling(t_academy *acad, char **av, int ac);
void	error(t_academy *acad);
void    timer(t_academy *acad);
void    initialization(t_academy* acad);
int     ft_usleep(long time, t_philo *philo);
void	ft_itoa_philo(char *s, long time, int n, char *msg);

#endif