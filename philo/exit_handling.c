/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:52:47 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/20 23:31:50 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	write(fd, s, i);
}

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

void	error(t_academy *acad)
{
	ft_putstr_fd("Error\n", 2);
	free_struct(acad);
	exit(0);
}
