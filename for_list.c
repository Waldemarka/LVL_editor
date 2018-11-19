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

 void	list_malloc(t_sector **list, int size)
 {
 	if (!(*list = (t_sector *)malloc(sizeof(t_sector) * size)))
 		ft_error("Bad realloc");
 }

void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	list_copy(t_sector *new, t_sector *old)
{
	while (old->next != NULL)
	{
		//new->x0 = old->x0;
		ft_swap(&new->x0, &old->x0);
		ft_swap(&new->y0, &old->y0);
		//new->y0 = old->y0;
		if (!(new->next = (t_sector *)malloc(sizeof(t_sector))))
			ft_error("Bad malloc in list_copy");
		new = new->next;
		old = old->next;
	}
	new->next = NULL;
}

/*
void	free_list(t_data *data, t_sector **list)
{
	t_sector *tmp;
	int i = -1;
	while (++i < data->for_realloc - 1)
	{
		printf("------\n");
		while (list[i]->next != NULL)
		{
			tmp = list[i]->next;
			printf("%d\n", i);
			printf("%d\n", list[i]->x0);
			printf("%d\n", data->tmp[0].x0);
			free(list[i]);
			list[i] = tmp;
		}
	}
	free(list[i]);
}
*/
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
	//free_list(data, &data->sectors); // leaks
	//printf("%d\n", data->tmp[0].x0);
	list_malloc(&data->sectors, data->for_realloc);
	q = -1;
	while (++q != data->for_realloc - 1)
		list_copy(&data->sectors[q], &data->tmp[q]);
	//free_list(data, &data->tmp); //leaks
}


int		len_list(t_sector *sectors)
{
	t_sector	*sect;
	int			res;

	res = 0;
	sect = sectors; 
	while (sect->next != NULL)
	{
		//printf("%d+_+_+_+_+_\n", sect->x0);
		res++;
		sect = sect->next;
	}
	return (res);
}


