/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/20 18:26:45 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int ac, char **av)
{
    t_academy *academy;

    if (ac > 6 || ac < 5)
        return(0);
    academy = malloc(sizeof(t_academy));
    argument_handling(academy, av, ac);
    create_philophers(academy);
    create_forks(academy);
    initialization(academy);
    start_feast(academy);
    destroy_academy(academy);
    return(0);   
}
