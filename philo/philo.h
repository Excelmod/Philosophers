/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:36:14 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/22 01:02:49 by ljulien          ###   ########.fr       */
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
    struct s_philo             *p_right;
    struct s_philo             *p_left;
    pthread_mutex_t     *f_right;
    pthread_mutex_t     *f_left;
    pthread_mutex_t     speak;
    long                lst_meal;
    struct s_academy    *acad;

}               t_philo;

typedef struct s_academy
{
    t_philo *philos;
    pthread_mutex_t  *forks;
    pthread_mutex_t  speak;
    pthread_t   *timer;
    long    nb;
    long    to_sleep;
    long    to_eat;
    long    to_die;
    long    times_eat;
    int                 death;
    long    time_0;

}               t_academy;

void	arguments_handling(t_academy *acad, char **av, int ac);
void	error(t_academy *acad);
void	ft_putnbr_fd(int n, int fd);

#endif