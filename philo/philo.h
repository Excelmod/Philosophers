/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:36:14 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/18 18:02:42 by ljulien          ###   ########.fr       */
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

#endif