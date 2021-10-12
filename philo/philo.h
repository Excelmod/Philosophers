/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:36:14 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/12 18:23:44 by ljulien          ###   ########.fr       */
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
    long                lst_meal;
    long                meals;
    struct s_academy    *acad;

}               t_philo;

typedef struct s_academy
{
    t_philo *philos;
    pthread_mutex_t  *forks;
    pthread_mutex_t  *speak;
    long    nb;
    long    to_sleep;
    long    to_eat;
    long    to_die;
    long    times_eat;
    int     stop;
    long    time_0;

}               t_academy;

char	*ft_itoa(long n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	arguments_handling(t_academy *acad, char **av, int ac);
void	error(t_academy *acad);
void	ft_putnbr_fd(int n, int fd);
void	ft_itoa_philo(char *s, long time, int n, char *msg);

#endif