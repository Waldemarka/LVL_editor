/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:02:18 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:24:43 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	fwri(FILE *fp, char *str)
{
	fwrite(str, ft_strlen(str), 1, fp);
	fwrite("  ", 2, 1, fp);
}

void	fwri1(FILE *fp, int q)
{
	char *str;

	str = ft_itoa(q);
	fwrite(str, ft_strlen(str), 1, fp);
	fwrite("  ", 2, 1, fp);
	free(str);
}

void	sort_list(t_data *data)
{
	t_vertex *orig;
	t_vertex *tmp;

	orig = &data->vertex;
	tmp = &data->vertex;
	while (orig->next != NULL)
	{
		if ((orig->y_vert > orig->next->y_vert) && orig->next->next != NULL)
		{
			ft_swap(&orig->x_vert, &orig->next->x_vert);
			ft_swap(&orig->y_vert, &orig->next->y_vert);
			orig = tmp;
		}
		else
			orig = orig->next;
	}
}

void	write_sector(t_data *data, FILE *fp, int q)
{
	t_sector	*sector;

	while (++q != data->current_sector + 1)
	{
		sector = &data->sectors[q];
		fwrite("sector  ", 8, 1, fp);
		fwri1(fp, data->sectors[q].floor);
		fwri1(fp, data->sectors[q].ceil);
		fwrite("    ", 4, 1, fp);
		while (sector->next != NULL)
		{
			fwri1(fp, num_ele(data, sector->x0, sector->y0));
			sector = sector->next;
		}
		fwrite("    ", 4, 1, fp);
		writte_walls(data, fp, q);
		fwrite("\n", 1, 1, fp);
	}
}

void	free_vertex(t_data *data)
{
	t_vertex	*vert;
	t_vertex	*tmp;
	int			q;

	q = 0;
	vert = &data->vertex;
	tmp = &data->vertex;
	while (vert->next != NULL)
	{
		if (vert->next->next == NULL)
		{
			free(vert->next);
			vert->next = NULL;
			vert = tmp;
		}
		else
			vert = vert->next;
	}
}

void	write_vertex(t_data *data, FILE *fp)
{
	int			num;
	t_vertex	*tmp;

	tmp = &data->vertex;
	while (tmp->next != NULL)
	{
		fwrite("vertex ", 7, 1, fp);
		num = tmp->y_vert;
		fwri1(fp, tmp->y_vert);
		while (tmp->y_vert == num && tmp->next != NULL)
		{
			fwri1(fp, tmp->x_vert);
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
			break ;
		fwrite("\n", 1, 1, fp);
	}
}

char	*name_icons(int x)
{
	if (x == 0)
		return ("player ");
	if (x == 1)
		return ("end ");
	if (x == 2)
		return ("door_sector ");
	if (x == 3)
		return ("health ");
	if (x == 4)
		return ("lift ");
	if (x == 5)
		return ("ammunition ");
	if (x == 6)
		return ("enemy ");
	if (x == 7)
		return ("armour ");
	if (x == 9)
		return ("green key ");
	if (x == 10)
		return ("red key ");
	if (x == 11)
		return ("yellow key ");
	return (NULL);
}

void	fwrite_icons(t_data *data, FILE *fp)
{
	int		q;

	q = -1;
	while (++q < data->object)
	{
		if (data->icons[q].flag == 0)
			continue;
		fwrite(name_icons(data->icons[q].obj),
			ft_strlen(name_icons(data->icons[q].obj)), 1, fp);
		if (data->icons[q].obj == 2 || data->icons[q].obj == 4)
		{
			fwri1(fp, data->icons[q].sector);
			fwrite("\n", 1, 1, fp);
			continue;
		}
		fwri1(fp, data->icons[q].x);
		fwri1(fp, data->icons[q].y);
		if (data->icons[q].obj == 0)
			fwrite("2  ", 3, 1, fp);
		fwri1(fp, data->icons[q].sector);
		fwrite("\n", 1, 1, fp);
	}
}

void	fwrite_textures(t_data *data, FILE *fp)
{
	int q;

	q = -1;
	while (++q <= data->current_sector)
	{
		fwrite("texture_sector ", ft_strlen("texture_sector "), 1, fp);
		fwri1(fp, q);
		fwri1(fp, data->sectors[q].texture);
		fwrite("\n", 1, 1, fp);
	}
}

void	sorting_list(t_data *data, FILE *fp)
{
	if (data->sectors[data->current_sector].next == NULL)
		data->current_sector -= 1;
	make_vertex_list(data);
	sort_list(data);
	write_vertex(data, fp);
	fwrite("\n\n", 2, 1, fp);
	write_sector(data, fp, -1);
	fwrite("\n\n", 2, 1, fp);
	free_vertex(data);
	fwrite_icons(data, fp);
	fwrite_textures(data, fp);
}

void	writting(t_data *data)
{
	FILE *fp;

	fp = fopen(data->name, "wb");
	if (fp == NULL)
	{
		ft_error("Not FILE");
	}
	sorting_list(data, fp);
	if (fclose(fp) != 0)
		ft_error("bad writting");
	fclose(fp);
}
