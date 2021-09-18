/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:52:47 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/18 18:36:01 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	atoi_check(t_academy *acad, const char *str)
{
	int			i;
	long long	nb;
	int			flag;

	i = 0;
	nb = 0;
	flag = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i++] - '0';
		flag = 1;
		if (nb > 9223372036854775807))
			error(acad);
	}
	if (str[i] != '\0' || flag == 0)
		error(acad);
	return ((long)(nb));
}