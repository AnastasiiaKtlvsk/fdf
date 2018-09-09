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
	int		i;

	i = 0;
	while (i < ti->cp)
	{
		ti->x[i] = ti->x[i] * cos(0.4) * cos(1.2) +
		ti->z[i] * sin(0.4) - ti->y[i] * cos(0.4) * sin(1.2);
		ti->y[i] = -ti->z[i] * cos(0.4) * sin(1.1) +
		ti->x[i] * (cos(1.2) * sin(1.1) * sin(0.4) +
		cos(1.1) * sin(1.2)) +
		ti->y[i] * (cos(1.1) * cos(1.2) -
		sin(1.1) * sin(0.4) * sin(1.2));
		i++;
	}
}


void	choose_distance(t_i *ti)
{
	write(1, "choose_distance\n", 15);
	if (ti->ys < 110 && ti->xs < 110)
	{
		ti->r = 15;
		ti->dc = 800;
		if (ti->ys < 50 && ti->xs < 50)
		{
			write(1, "size < 50\n", 10);
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
//	ti->d = ft_memalloc((ti->dc * 4) + 1);
	write(1, "choose_distance end\n", 20);
}

void    put_pxl(t_i *ti, int x, int y, int c)
{
//	write(1, "put_pxl\n", 8);
	int i;

	i = (ti->sl * y) + x * 4;
//	ft_putnbr(i);
//	write(1, " - i \n", 6);
	/*ti->d[i++] = (char)255;
	ti->d[i++] = (char)255;
	ti->d[i++] = (char)255;*/
	if (c == 0)
		c = (int)0xffffff;
  	ti->d[i] = c;
  	ti->d[++i] = c >> 8;
  	ti->d[++i] = c >> 16;
  	ti->d[++i] = 0;
}
	//c++;

void	brez(t_i *ti, int s, int d)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	int		length;
//	write(1, "brez\n", 5);

	dx = (ti->x[d] - ti->x[s] >= 0 ? 1 : -1);
	dy = (ti->y[d] - ti->y[s] >= 0 ? 1 : -1);
	length = ABS(ti->x[s] - ti->x[d]) > ABS(ti->y[s] - ti->y[d]) ? ABS(ti->x[s] - ti->x[d]) + 1 :
		ABS(ti->y[s] - ti->y[d]) + 1;
	(ABS(ti->x[s] - ti->x[d]) > ABS(ti->y[s] - ti->y[d])) ? dy *= (float)ABS(ti->y[s] - ti->y[d]) / (float)ABS(ti->x[s] - ti->x[d]) : 0;
	(ABS(ti->x[s] - ti->x[d]) <= ABS(ti->y[s] - ti->y[d])) ? dx *= (float)ABS(ti->x[s] - ti->x[d]) / (float)ABS(ti->y[s] - ti->y[d]) : 0;
	x = (float)ti->x[s];
	y = (float)ti->y[s];
	while (length--)
	{
	/*	ft_putnbr(x);
		write(1, " - x \n", 6);
		ft_putnbr(y);
		write(1, " - y \n", 6);
		ft_putnbr(ti->sl);
		write(1, " - sl \n", 7);*/
		if ((x < ti->sl && y < ti->sl) && (x >= 0 && y >= 0))
			put_pxl(ti, x, y, ti->c[s]);
		x += dx;
		y += dy;
	}
//	write(1, "end brez\n", 10);
}

void	prp_points(t_i *ti, int i, int px, int py) // i = -1;
{
	py = (ti->dc / 2) - ((ti->ys - 1) * ti->r) / 2;
	px = (ti->dc / 2) - ((ti->xs - 1) * ti->r) / 2;

	ft_putnbr(py);
	write(1, " - py ", 6);
	ft_putnbr(px);
	write(1, " - px \n", 7);

	while (++i < ti->cp)
	{
		ti->y[i] = (ti->y[i] * ti->r) + py;
		ti->x[i] = (ti->x[i] * ti->r) + px;
	}
}

void    fill_dt(t_i *ti)
{
    int j;
	write(1, "fill_dt\n", 8);
    j = -1;
	rot_axis(ti);
	prp_points(ti, -1, 0, 0);
/*	ti->x[6] = ti->x[6] * 30;
	ti->y[6] = ti->y[6] * 30;
	ft_putnbr(ti->x[6]);
	write(1, " - x \n", 6);
	ft_putnbr(ti->y[6]);
	write(1, " - y \n", 6);
	brez(ti, 1, 6);*/
    while (++j < ti->cp - 1)
    {
		
        if (ti->x[j + 1] && ti->y[j] == ti->y[j + 1])
        {
			brez(ti, j, j + 1);
        }
	/*	ft_putnbr(ti->y[j + ti->xs + 1]);
		write(1, " - y ", 5);
		ft_putnbr(ti->x[j]);
		write(1, " - x1 ", 6);
		ft_putnbr(ti->x[j + ti->xs + 1]);
		write(1, " - x2\n", 6);*/
		if (ti->y[j + ti->xs + 1] && ti->x[j] == ti->x[j + ti->xs])
        {
			brez(ti, j, j + ti->xs);
        }
    }
//	write(1, "fill_dt end\n", 13);
	write(1, "t->d\n", 5);
	j = -1;
	while (++j < ti->dc){
		write(1, &(ti->d[j]), 1);
	}
}
