#include "fdf.h"


void    free_type(t_i *ti)
{
    int i;
  
    i = -1;
  //  free((*ti)->d); 
	free(ti->x);
	free(ti->y);
	free(ti->z);
	free(ti->c);
}

int     check_digits(char *str)
{
    int i;

    i = -1;
    if (!str)
        return (-1);
    while (str[++i])
    {
        if (!((str[i] >= '0' && str[i] <= '9') ||
            str[i] == 'x' || str[i] == 'X' || str[i] == ',' || str[i] == '-'))
            return (0);
    }
    return (1);
}

unsigned int		atoi_hex(char *str)
{
	unsigned long long	nbr;
	int					i;
    int                 r;

	i = -1;
	nbr = 0;
    r = -1;
	while (str[++i])
	{
        (str[i] == 'a' || str[i] == 'A') ? r = 10 : 0;
        (str[i] == 'b' || str[i] == 'B') ? r = 11 : 0;
        (str[i] == 'c' || str[i] == 'C') ? r = 12 : 0;
        (str[i] == 'd' || str[i] == 'D') ? r = 13 : 0;
        (str[i] == 'e' || str[i] == 'E') ? r = 14 : 0;
        (str[i] == 'F' || str[i] == 'F') ? r = 15 : 0;
        (ft_isdigit(str[i])) ? r = str[i] - '0' : 0;
        if (r < 0)
            return (0);    
		nbr = nbr * 16 + r;
	}
	return (nbr);
}

int     count(char *s)
{
    int     j;
    int     t;
    char    **row;

    j = 0;
    row = ft_strsplit(s, ' ');
    while (row[j])
        j++;
    t = -1;
    while (++t < j)
        free(row[t]);
    free(row);
    return (j);
}

void    free_array(char **ar, int l)
{
    int i;

    i = -1;
    while (++i < l) 
        free(ar[i]);
    free(ar);
}

int     validate_row(t_i *ti, char *s, int y, int i) // n - norma , j = -1, i = -1
{
    char            **row;
    unsigned int    c;
    int             f;

    f = 1;
    row = ft_strsplit(s, ' ');
    while (row[++i])
    {
        ti->y[ti->cp] = y;
        ti->x[ti->cp] = i;
        ti->z[ti->cp] = ft_atoi(row[i]);
        c = 0;
        if (ft_strchr(row[i], ','))
        {
            (ft_strchr(row[i], 'x')) ? c = atoi_hex(ft_strchr(row[i], 'x') + 1) : 0;
            (ft_strchr(row[i], 'X')) ? c = atoi_hex(ft_strchr(row[i], 'X') + 1) : 0;
        }
        (c > 2147483647 || check_digits(row[i]) == 0) ? f = 0 : 0;
        ti->c[ti->cp] = (int)c;
        ti->cp++;
    }
   free_array(row, i);
    if (i != ti->xs || f == 0){
        return (-1);
    }

   return (1);
}


int     read_map(t_i *ti, char *f, int i) // i = -1 ; f - file name
{
    char *temp;
    int fd;
    int k;

    k = 1;
    ti->cp = 0;
    ti->ys = 0;
    fd = open(f, O_RDONLY);
    while (get_next_line(fd, &temp) > 0)
    {
        ti->ys++;
        free(temp);
    }
    close(fd);
    fd = open(f, O_RDONLY);
    if (get_next_line(fd, &temp) > 0)
    {
        ti->xs = count(temp);
        ti->y = (int*)ft_memalloc(sizeof(int) * ti->xs * ti->ys);
        ti->x = (int*)ft_memalloc(sizeof(int) * ti->xs * ti->ys);
        ti->z = (int*)ft_memalloc(sizeof(int) * ti->xs * ti->ys);
        ti->c = (unsigned int*)ft_memalloc(sizeof(unsigned int) * ti->xs * ti->ys);
        if (validate_row(ti, temp, ++i, -1) < 0)
            k = -1;
        free(temp);
        while (k > 0 && get_next_line(fd, &temp) > 0)
        {
            if (validate_row(ti, temp, ++i, -1) < 0)
                k = -1;
            free(temp);
        }
    }
  //  print_stateti;
    
   // free_type(ti);
    return (k);
}

void    print_state(t_i *ti)
{
    int i = -1;
    printf(" xs =  %i\n", ti->xs);
    while (++i < ti->cp){
        printf(" y x z = %i %i %i c = %i\n", ti->y[i], ti->x[i], ti->z[i], ti->c[i]);

    }
    
}

