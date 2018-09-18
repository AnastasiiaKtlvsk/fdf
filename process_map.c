/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 21:48:53 by akotilie          #+#    #+#             */
/*   Updated: 2018/09/03 21:48:55 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_axis(t_i *ti)
{
	int		k;

	k = -1;
	while (++k < ti->cp)
	{
		ti->cx[k] = ti->x[k] * cos(ti->b) * cos(ti->w) + ti->z[k] * sin(ti->b) -
		ti->y[k] * cos(ti->b) * sin(ti->w);
		ti->cy[k] = (-1 * ti->z[k]) * cos(ti->b) * sin(ti->a) + ti->x[k] * (cos(ti->w)
		* sin(ti->a) * sin(ti->b) + cos(ti->a) * sin(ti->w)) + ti->y[k] * (cos(ti->a)
		* cos(ti->w) - sin(ti->a) * sin(ti->b) * sin(ti->w));					
		ti->cy[k] = (ti->cy[k] * ti->r) + ti->dc / 2;
		ti->cx[k] = (ti->cx[k] * ti->r) + ti->dc / 2;
	}
}

void	choose_distance(t_i *ti)
{
	if (ti->ys < 110 && ti->xs < 110)
	{
		ti->r = 15;
		ti->dc = 800;
		if (ti->ys < 50 && ti->xs < 50)
		{
			ti->dc = 600;
		}
	} else if (ti->ys < 310 && ti->xs < 310)
	{
		ti->r = 5;
		ti->dc = 1300;
	} else 
	{
		ti->r = 1;
		ti->dc = 1400;
	}
}

void    put_pxl(t_i *ti, int x, int y, int c)
{
	int i;

	i = (ti->sl * y) + x * 4;
	if (c == 0)
		c = (int)0xffffff;
  	ti->d[i] = c;
  	ti->d[++i] = c >> 8;
  	ti->d[++i] = c >> 16;
  	ti->d[++i] = 0;
}

void	brez(t_i *ti, int s, int d)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	int		length;

	dx = (ti->cx[d] - ti->cx[s] >= 0 ? 1 : -1);
	dy = (ti->cy[d] - ti->cy[s] >= 0 ? 1 : -1);
	length = ABS(ti->cx[s] - ti->cx[d]) > ABS(ti->cy[s] - ti->cy[d]) ?
	ABS(ti->cx[s] - ti->cx[d]) + 1 : ABS(ti->cy[s] - ti->cy[d]) + 1;
	(ABS(ti->cx[s] - ti->cx[d]) > ABS(ti->cy[s] - ti->cy[d])) ? dy *=
	(float)ABS(ti->cy[s] - ti->cy[d]) / (float)ABS(ti->cx[s] - ti->cx[d]) : 0;
	(ABS(ti->cx[s] - ti->cx[d]) <= ABS(ti->cy[s] - ti->cy[d])) ? dx *=
	(float)ABS(ti->cx[s] - ti->cx[d]) / (float)ABS(ti->cy[s] - ti->cy[d]) : 0;
	x = (float)ti->cx[s];
	y = (float)ti->cy[s];
	while (length--)
	{
		if ((x < ti->sl && y < ti->sl) && (x >= 0 && y >= 0))
			put_pxl(ti, x, y, ti->c[s]);
		x += dx;
		y += dy;
	}
}

void	process(t_i *ti)
{
	write(1, "fill_dt\n", 8);
	int j;

    j = -1;
	rot_axis(ti);
    while (++j < ti->cp - 1)
    {
        if (j + 1 < ti->cp && ti->y[j] == ti->y[j + 1])
			brez(ti, j, j + 1);
		if (j + ti->xs < ti->cp && ti->x[j] == ti->x[j + ti->xs])
			brez(ti, j, j + ti->xs);
    }
}

void    fill_dt(t_i *ti)
{
 	ti->cx = ft_memalloc(sizeof(int) * ti->cp);
    ti->cy = ft_memalloc(sizeof(int) * ti->cp);
	ti->a = 3.14 + 0.9;
	ti->b = 3.14;
	ti->w = 3.14 + 0.9;

	process(ti);
}
