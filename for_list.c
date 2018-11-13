/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:03:30 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/07 18:03:31 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	list_copy(t_sector *new, t_sector *old)
{
	while (old->next != NULL)
	{
		new->x0 = old->x0;
		new->y0 = old->y0;
		if (!(new->next = (t_sector *)malloc(sizeof(t_sector))))
			ft_error("Bad malloc in list_copy");
		new = new->next;
		old = old->next;
	}
	new->next = NULL;
}

void	list_malloc(t_sector **list, int size)
{
	if (!(*list = (t_sector *)malloc(sizeof(t_sector) * size)))
		ft_error("Bad realloc");
}

void	free_list(t_sector *list)
{
	t_sector *tmp;

	while (list->next != NULL)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
	free(list);
}

void	list_realloc(t_data *data)
{
	int q;

	q = -1;
	list_malloc(&data->tmp, data->for_realloc - 1);
	while (++q != data->for_realloc - 1)
		list_copy(&data->tmp[q], &data->sectors[q]);
	free_list(data->sectors); // leaks
	list_malloc(&data->sectors, data->for_realloc);
	q = -1;
	while (++q != data->for_realloc - 1)
		list_copy(&data->sectors[q], &data->tmp[q]);
	free_list(data->tmp); //leaks
}





