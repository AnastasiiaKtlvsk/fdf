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
	double a;
	double b;
	double c;

	a = 3.14 + 0.9;
	b = 3.14;
	c = 3.14 + 0.9;

//	a = 0;
//	b = 0;  
//	c = 0.4;
	k = -1;
	

		printf("ti->r = %i ti->px %i ti->py %i\n",ti->r, ti->px,ti->py);
	while (++k < ti->cp)
	{
		ti->cx[k] = ti->x[k] * cos(b) * cos(c) + ti->z[k] * sin(b) - ti->y[k] * cos(b) * sin(c);
		ti->cy[k] = (-1 * ti->z[k]) * cos(b) * sin(a) + ti->x[k] * (cos(c) * sin(a) * sin(b) + cos(a) * sin(c)) + ti->y[k] * (cos(a) * cos(c) - sin(a) * sin(b) * sin(c));
		

		ti->cy[k] = (ti->cy[k] * ti->r) + ti->py;
		ti->cx[k] = (ti->cx[k] * ti->r) + ti->px;
		printf("after x %i y %i\n",ti->cx[k],ti->cy[k]);

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

	dx = (ti->cx[d] - ti->cx[s] >= 0 ? 1 : -1);
	dy = (ti->cy[d] - ti->cy[s] >= 0 ? 1 : -1);
	length = ABS(ti->cx[s] - ti->cx[d]) > ABS(ti->cy[s] - ti->cy[d]) ? ABS(ti->cx[s] - ti->cx[d]) + 1 :
		ABS(ti->cy[s] - ti->cy[d]) + 1;
	(ABS(ti->cx[s] - ti->cx[d]) > ABS(ti->cy[s] - ti->cy[d])) ? dy *= (float)ABS(ti->cy[s] - ti->cy[d]) / (float)ABS(ti->cx[s] - ti->cx[d]) : 0;
	(ABS(ti->cx[s] - ti->cx[d]) <= ABS(ti->cy[s] - ti->cy[d])) ? dx *= (float)ABS(ti->cx[s] - ti->cx[d]) / (float)ABS(ti->cy[s] - ti->cy[d]) : 0;
	x = (float)ti->cx[s];
	y = (float)ti->cy[s];
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

void	test_brez(t_i *ti)
{
/*	ti->x[0] = 100;
	ti->y[0] = 100;

	ti->x[1] = 400;
	ti->y[1] = 100;

	ti->x[2] = 100;
	ti->y[2] = 200;

	ti->x[3] = 400;
	ti->y[3] = 200;

	rot_axis(ti);
	brez(ti, 0, 1);
	brez(ti, 0, 2);
	brez(ti, 1, 3);
	brez(ti, 2, 3);
*/

    ti->x[0] = 100;
	ti->y[0] = 100;

	ti->x[1] = 400;
	ti->y[1] = 100;

	ti->x[2] = 100;
	ti->y[2] = 200;

	ti->x[3] = 400;
	ti->y[3] = 200;

	rot_axis(ti);

	int j = -1;
	 while (++j < 4)
    {
		printf("here\n");
        if (j + 1 < 4  && ti->y[j] == ti->y[j + 1])
        {

			printf("right s =  %i d =  %i\n", j, j+1);
			brez(ti, j, j + 1);
        }
		if (j + 2 < 4  && ti->x[j] == ti->x[j + 2])
        {
			printf("down s =  %i d =  %i\n", j, j+2);
			brez(ti, j, j + 2);
        }
    }
}

void	prp_points(t_i *ti) // i = -1;
{

	ti->py = (ti->dc / 2) - ((ti->ys - 1) * ti->r) / 2;
	ti->px = (ti->dc / 2) - ((ti->xs - 1) * ti->r) / 2;
/*	while (++i < ti->cp)
	{
	//	printf("before x %i y %i\n",ti->x[i],ti->y[i]);
		c++;
	//	ti->x[i] -= (float)ti->y[i] * 0.433;
	//	ti->y[i] -= ((float)ti->y[i] * 0.75 );//- ti->z[i]);

	//	printf("after x %i y %i\n",ti->x[i],ti->y[i]);


		if (c == ti->xs)
		{
			c = 0;
			r++;
	//		printf(" r++ \n");
		}


	//	ti->x[i] = ti->y[i] * sin(1.2) * cos(1.2);
	//	ti->y[i] = ti->y[i] * sin(1.2) * sin(1.2) - ti->z[i];


		ti->y[i] = (ti->y[i] * ti->r) + py;
		ti->x[i] = (ti->x[i] * ti->r) + px;
	}*/
}

void    fill_dt(t_i *ti)
{
    int j;

	ti->cx = ft_memalloc(sizeof(int) * ti->cp);
	ti->cy = ft_memalloc(sizeof(int) * ti->cp);
	write(1, "fill_dt\n", 8);
    j = -1;
	//test_brez(ti);
	prp_points(ti);
	rot_axis(ti);
//	prp_points(ti, -1, 0, 0);


/*	ti->x[6] = ti->x[6] * 30;
	ti->y[6] = ti->y[6] * 30;
	ft_putnbr(ti->x[6]);
	write(1, " - x \n", 6);
	ft_putnbr(ti->y[6]);
	write(1, " - y \n", 6);
	brez(ti, 1, 6);*/
    while (++j < ti->cp - 1)
    {
		
        if (j + 1 < ti->cp && ti->y[j] == ti->y[j + 1])
        {
			brez(ti, j, j + 1);
        }
	/*	ft_putnbr(ti->y[j + ti->xs + 1]);
		write(1, " - y ", 5);
		ft_putnbr(ti->x[j]);
		write(1, " - x1 ", 6);
		ft_putnbr(ti->x[j + ti->xs + 1]);
		write(1, " - x2\n", 6);*/
		if (j + ti->xs < ti->cp && ti->x[j] == ti->x[j + ti->xs])
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




/*test()
{
	t_point p1;
	t_point p2;

	p1.x = ....
	p1.y = ....
	p2.x = ....
	p2.y = ....
	dr_line(map, p1,p2,color);
}
*/
