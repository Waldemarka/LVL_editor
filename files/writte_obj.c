/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writte_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 12:45:08 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/09 12:45:10 by vomelchu         ###   ########.fr       */
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

char	*name_icons(int x)
{
	if (x == 0)
		return ("player ");
	if (x == 1)
		return ("end ");
	if (x == 2)
		return ("door_sector ");
	if (x == 3)
		return ("ammunition 2 ");
	if (x == 4)
		return ("lift ");
	if (x == 5)
		return ("ammunition 1 ");
	if (x == 6)
		return ("enemy ");
	if (x == 7)
		return ("ammunition 3 ");
	if (x == 9)
		return ("key 3 ");
	if (x == 10)
		return ("key 1 ");
	if (x == 11)
		return ("key 2 ");
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
		if (data->icons[q].obj == 2 || data->icons[q].obj == 4 ||
			data->icons[q].obj == 1)
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
