/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 11:23:08 by akotilie          #+#    #+#             */
/*   Updated: 2018/08/19 11:25:25 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <unistd.h>
# include <math.h>
# include <stdio.h>

typedef	struct		s_i // image
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				xo;
	int				yo;
	int				dc;
	int				r;
	int				xs; // size x
	int				ys; // size y
	int				cp; // count of points
    char			*d; // data
	int				*x;
	int				*y;
	int				*z;
	int				*cx; //cx
	int				*cy;
	int				bpp;
	int				sl;
	int				ei;
	int				px;
	int				py;
	unsigned int	*c; //points
	
}					t_i;

int     read_map(t_i *ti, char *f, int i);
void    fill_dt(t_i *ti);
void	brez(t_i *ti, int s, int d);
void    free_type(t_i *ti);
void	choose_distance(t_i *ti);

void    print_state(t_i *ti); // temp


#endif