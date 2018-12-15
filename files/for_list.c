/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:03:30 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/11 16:48:29 by vomelchu         ###   ########.fr       */
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

/*void	list_copy(t_sector *new, t_sector *old)
  {
  while (old->next != NULL)
  {
//new->x0 = old->x0;
ft_swap(&new->x0, &old->x0);
ft_swap(&new->y0, &old->y0);
ft_swap(&new->floor, &old->floor);
ft_swap(&new->ceil, &old->ceil);
//new->y0 = old->y0;
if (!(new->next = (t_sector *)malloc(sizeof(t_sector))))
ft_error("Bad malloc in list_copy");
new = new->next;
old = old->next;
}
new->next = NULL;
}*/

/*void	list_copy(t_data *data, int i)
{
	t_sector *new;
	t_sector old;
	int q;

	q = -1;
	while (++q < data->current_sector)
	{
		if (i == 0)
		{
			new = &data->tmp[q];
			old = data->sectors[q];
		}
		else
		{
			new = &data->sectors[q];
			old =  data->tmp[q];	
		}
		while (old.next != NULL)
		{
			new->x0 = old.x0;
			new->y0 = old.y0;
			new->floor = old.floor;
			new->ceil = old.ceil;
			if (!(new->next = (t_sector *)malloc(sizeof(t_sector))))
				ft_error("Bad malloc in list_copy");
			new = new->next;
			old = *old.next;
		}
		new->next = NULL;
	}
}

void	free_list(t_data *data, int i)
{
	t_sector **sector;
	t_sector *tmp;
	int q;

	q = -1;
	if (i == 0)
		sector = &data->sectors;
	else
		sector = &data->tmp;
	while (++q < data->current_sector)
	{
		while (sector[q]->next != NULL)
		{
			tmp = sector[q];
			free(sector[q]);
			sector[q] = tmp;
			sector[q] = sector[q]->next;
		}
	}
}*/

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

/*void	list_malloc(t_sector **list, int q)
{
	if (!(list[q] = (t_sector *)malloc(sizeof(t_sector))))
		ft_error("Bad realloc");
}

void	list_realloc(t_data *data)
{
	int q;

	q = -1;
	list_malloc(&data->tmp, data->current_sector - 1);
	while (++q != data->current_sector)
		list_copy(data, 0);
	q = -1;
	while (++q < data->current_sector)
		del_list(data, q, 0);
	list_malloc(&data->sectors, data->current_sector);
	q = -1;
	while (++q != data->current_sector - 1)
		list_copy(data, 1);
	q = -1;
	printf("%d\n", data->current_sector);
	while (++q < data->current_sector - 1)
		del_list(data, q, 1);
}
*/

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
