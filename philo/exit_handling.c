/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:52:47 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/13 00:26:38 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_struct(t_academy *acad)
{
	free(acad);
	acad = NULL;
}

char	**ft_freetabs(char **t)
{
	int	i;

	i = 0;
	while (t[i] != NULL)
	{
		free(t[i]);
		t[i] = NULL;
		i++;
	}
	free(t);
	t = NULL;
	return (NULL);
}

void	error_msg(t_academy *acad, char *s)
{
	ft_putstr_fd("Error :", 2);
	ft_putendl_fd(s, 2);
	free(acad);
	exit(0);
}

void	error(t_academy *acad)
{
	ft_putstr_fd("Error\n", 2);
	free(acad);
	exit(0);
}
