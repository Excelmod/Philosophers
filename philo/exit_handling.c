/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:52:47 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/18 18:17:30 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	del_int(void *content)
{
	free((int *)content);
	content = NULL;
}

void	del_str(void *content)
{
	free((char *)content);
	content = NULL;
}

void	free_struct(t_academy *acad)
{
	free(psh_swp->str);
	free(psh_swp->kept);
	ft_lstclear(&(psh_swp->cmd_head), del_int);
	ft_lstclear(&(psh_swp->head_a), del_int);
	ft_lstclear(&(psh_swp->head_b), del_int);
	free(psh_swp);
	psh_swp = NULL;
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
