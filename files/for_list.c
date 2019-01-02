/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:03:30 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:21:36 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	del_list(t_data *data, int q, int i)
{
	t_sector *sector;
	t_sector *tmp;

	if (i == 0)
	{
		sector = &data->sectors[q];
		tmp = &data->sectors[q];
	}
	else
	{
		sector = &data->tmp[q];
		tmp = &data->tmp[q];
	}
	while (sector->next != NULL)
	{
		if (sector->next->next == NULL)
		{
			free(sector->next);
			sector->next = NULL;
			sector = tmp;
		}
		else
			sector = sector->next;
	}
	sector->next = NULL;
}

int		len_list(t_sector *sectors)
{
	t_sector	*sect;
	int			res;

	res = 0;
	sect = sectors;
	while (sect->next != NULL)
	{
		res++;
		sect = sect->next;
	}
	return (res);
}
