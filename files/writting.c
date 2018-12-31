/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:02:18 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/16 14:02:20 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	sort_list(t_data *data)
{
	vertex *orig;
	vertex *tmp;

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

void	write_sector(t_data *data, FILE *fp)
{
	t_sector *sector;
	int q;
	char *str;

	q = -1;
	while (++q != data->current_sector + 1)
	{
		sector = &data->sectors[q];
		fwrite("sector  ", 8, 1, fp);
		str = ft_itoa(data->sectors[q].floor);
		fwrite(str, ft_strlen(str), 1, fp);
		free(str);
		fwrite("  ", 2, 1, fp);
		str = ft_itoa(data->sectors[q].ceil);
		fwrite(str, ft_strlen(str), 1, fp);
		free(str);
		fwrite("    ", 4, 1, fp);
		while (sector->next != NULL)
		{
			str = ft_itoa(num_ele(data, sector->x0, sector->y0));
			fwrite(str, ft_strlen(str), 1, fp);
			free(str);
			fwrite(" ", 1, 1, fp);
			sector = sector->next;
		}
		fwrite("    ", 4, 1, fp);
		writte_walls(data, fp, q);
		fwrite("\n", 1, 1, fp);
	}
}

void	free_vertex(t_data *data)
{
	vertex *vert;
	vertex *tmp;
	int q;

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
	int num;
	vertex *tmp;
	char *str;

	tmp = &data->vertex;
	while (tmp->next != NULL)
	{
		fwrite("vertex ", 7, 1, fp);
		num = tmp->y_vert;
		str = ft_itoa(num);
		fwrite(str, ft_strlen(str), 1, fp);
		free(str);
		fwrite("    ", 4, 1, fp);
		while (tmp->y_vert == num && tmp->next != NULL)
		{
			str = ft_itoa(tmp->x_vert);
			fwrite(str, ft_strlen(str), 1, fp);
			fwrite(" ", 1, 1, fp);
			free(str);
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
			break;
		num = tmp->y_vert;
		fwrite("\n", 1, 1, fp);
	}
}

char	*name_icons(int x)
{
	if (x == 0)
		return ("player");
	if (x == 1)
		return ("end");
	if (x == 2)
		return ("door_sector");
	if (x == 3)
		return ("health");
	if (x == 4)
		return ("lift");
	if (x == 5)
		return ("ammunition");
	if (x == 6)
		return ("enemy");
	if (x == 7)
		return ("armour");
	if (x == 9)
		return ("green key");
	if (x == 10)
		return ("red key");
	if (x == 11)
		return ("yellow key");
	return(NULL);
}

void	fwri(FILE *fp, char *str)
{
	fwrite(str, ft_strlen(str), 1, fp);
	fwrite("  ", 2, 1, fp);
}

void	fwrite_icons(t_data *data, FILE *fp)
{
	int q;
	char *str;

	q = -1;
	while (++q < data->object)
	{
		if (data->icons[q].flag == 0)
			continue;
		str = name_icons(data->icons[q].obj);
		//printf("%d %s\n", data->icons[q].obj,str);
		fwri(fp, str);
		//free(str);
		if (data->icons[q].obj == 2 || data->icons[q].obj == 4)
		{
			str = ft_itoa(data->icons[q].sector);	
			fwri(fp, str);
			free(str);
			fwrite("\n", 1, 1, fp);
			continue;
		}
		str = ft_itoa(data->icons[q].x);
		fwri(fp, str);
		free(str);
		str = ft_itoa(data->icons[q].y);
		fwri(fp, str);
		free(str);
		if (data->icons[q].obj == 0)
			fwrite("2  ", 3, 1, fp);
		str = ft_itoa(data->icons[q].sector);
		fwri(fp, str);
		free(str);
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
 	write_sector(data, fp);
 	fwrite("\n\n", 2, 1, fp);
	free_vertex(data);
 	fwrite_icons(data, fp);
}


void	writting(t_data *data)
{
	FILE *fp;

    fp = fopen(data->name, "wb");
    if(fp == NULL) {
        ft_error("Not FILE");
    }
    sorting_list(data, fp);
    if (fclose(fp) != 0)
    	ft_error("bad writting");
    fclose(fp);
}
