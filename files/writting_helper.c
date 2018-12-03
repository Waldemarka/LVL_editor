/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writting_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:46:35 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/03 17:46:37 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


int		find_wall(t_data *data, vector dot_1, vector dot_2, int check)
{
	t_sector *sector;
	int q;

	q = -1;
	while (++q != data->current_sector)
	{
		sector = &data->sectors[q];
		while (sector->next != NULL && q != check)
		{
			if (((int)dot_1.x == sector->x0 && (int)dot_1.y == sector->y0 &&
				(int)dot_2.x == sector->next->x0 && (int)dot_2.y == sector->next->y0)
				|| ((int)dot_2.x == sector->x0 && (int)dot_2.y == sector->y0 &&
				(int)dot_1.x == sector->next->x0 && (int)dot_1.y == sector->next->y0))
				return (q);
			if (sector->next->next == NULL)
				if (((int)dot_1.x == sector->x0 && (int)dot_1.y == sector->y0 &&
				(int)dot_2.x == data->sectors[q].x0 && (int)dot_2.y == data->sectors[q].y0)
				|| ((int)dot_2.x == sector->x0 && (int)dot_2.y == sector->y0 &&
				(int)dot_1.x == data->sectors[q].x0 && (int)dot_1.y == data->sectors[q].y0))
					return (q);
			sector = sector->next;
		}
	}
	return (-1);
}

void	writte_walls(t_data *data, FILE *fp, int q, size_t count)
{
	t_sector *sector;
	vector dot_1;
	vector dot_2;
	char *wall;

	sector = &data->sectors[q];
	while (sector->next != NULL)
	{
		dot_1.x = (double)sector->x0;
		dot_1.y = (double)sector->y0;
		if (sector->next->next == NULL)
		{
			sector->next->x0 = data->sectors[q].x0;
			sector->next->y0 = data->sectors[q].y0;
		}
		dot_2.x = (double)sector->next->x0;
		dot_2.y = (double)sector->next->y0;
		wall = ft_itoa(find_wall(data, dot_1, dot_2, q));
		count = fwrite(wall, ft_strlen(wall), 1, fp);
		count = fwrite(" ", 1, 1, fp);
		sector = sector->next;
	}
}

void	wri_sect(t_data *data, FILE *fp)
{
	int q;
	size_t count;
	char const *str = "sector  ";
	int y = 0;
	t_sector *sector;

	q = -1;
	while (++q != data->current_sector + 1)
	{
		sector = &data->sectors[q];
		if (sector->next != NULL)
			count = fwrite(str, ft_strlen(str), 1, fp);
		if (sector->next == NULL)
			break;
		fwrite("0 20     ", 8, 1, fp);
		while (sector->next != NULL)
		{
			count = fwrite(ft_itoa(y), ft_strlen(ft_itoa(y)), 1, fp);
			count = fwrite(" ", 1, 1, fp);
			sector = sector->next;
			y++;
		}
		count = fwrite("          ", 10, 1, fp);
		writte_walls(data, fp, q, count);
		count = fwrite(" \n", 1, 2, fp);
	}
}