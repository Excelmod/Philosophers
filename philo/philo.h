/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:36:14 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/20 18:28:23 by ljulien          ###   ########.fr       */
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

typedef struct s_academy
{
    t_philo *philos;
    t_fork  *forks;
    long    nb;
    long    to_sleep;
    long    to_eat;
    long    to_die;
    long    times_eat;

}               t_academy;

typedef struct s_philo
{
    int         n;
    pthread_t   *id;
    t_philo     *p_right;
    t_philo     *p_left;
    t_fork      *f_right;
    t_fork      *f_left;
}               t_philo;

typedef struct      s_fork
{
    int             n;
    pthread_mutex_t *id;
}                   t_fork;

void	arguments_handling(t_academy *acad, char **av, int ac);

#endif