#include "fdf.h"

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
    return (j);
}


int     validate_row(t_i **ti, char *s, int y, int i) // n - norma , j = -1, i = -1
{
    char    **row;
    unsigned int     c;

    row = ft_strsplit(s, ' ');
    while (row[++i])
    {
      //  int c = (*ti)->cp + '0';
     //   write(1, &c , 1);
     //   write(1, "\n" , 1);
     //   write(1, "3\n", 2);
      
        (*ti)->y[(*ti)->cp] = y;
      //  write(1, "3 0\n", 4);
        (*ti)->x[(*ti)->cp] = i;
     //    write(1, "3 a\n", 4);
        (*ti)->z[(*ti)->cp] = ft_atoi(row[i]);
     //    write(1, "3 b\n", 4);
        c = 0;
        if (ft_strchr(row[i], ','))
        {
            (ft_strchr(row[i], 'x')) ? c = atoi_hex(ft_strchr(row[i], 'x') + 1) : 0;
            (ft_strchr(row[i], 'X')) ? c = atoi_hex(ft_strchr(row[i], 'X') + 1) : 0;
        }
        if (c > 2147483647)
           return (-1);
        (*ti)->c[(*ti)->cp] = (int)c;
        (*ti)->cp++;
    }
   // write(1, "5\n", 2);
    if (i != (*ti)->xs)
    {
        printf("return x temp != xs");
        return (-1);
    }
   return (1);
}


int     read_map(t_i **ti, char *f, int i) // i = -1 ; f - file name
{
    char *temp;
    int fd;

    (*ti)->cp = 0;
    (*ti)->ys = 0;
    fd = open(f, O_RDONLY);
    while (get_next_line(fd, &temp) > 0)
        (*ti)->ys++;
    close(fd);
  //  write(1, "1\n", 2);
    printf("count y = %i",(*ti)->ys);
    fd = open(f, O_RDONLY);
    if (get_next_line(fd, &temp) > 0)
    {
        (*ti)->xs = count(temp);
         printf("count x = %i",(*ti)->xs);
        (*ti)->y = (int*)ft_memalloc(sizeof(int) * (*ti)->xs * (*ti)->ys);
        (*ti)->x = (int*)ft_memalloc(sizeof(int) * (*ti)->xs * (*ti)->ys);
        (*ti)->z = (int*)ft_memalloc(sizeof(int) * (*ti)->xs * (*ti)->ys);
        (*ti)->c = (unsigned int*)ft_memalloc(sizeof(unsigned int) * (*ti)->xs * (*ti)->ys);
  //      write(1, "2\n", 2);
        if (validate_row(ti, temp, ++i, -1) < 0)
            return (-1);
        free(temp);
    //    write(1, "1\n", 2);
        while (get_next_line(fd, &temp) > 0)
        {
            if (validate_row(ti, temp, ++i, -1) < 0)
                return (-1);
            free(temp);
        }
    }
    print_state(ti);
    free((*ti)->lm);
    return (1);
}

void    print_state(t_i **ti)
{
    int i = -1;
    printf(" TI->LM %s\n", (*ti)->lm);
    printf(" xs =  %i\n", (*ti)->xs);
    while (++i < (*ti)->cp){
        printf(" y x z = %i %i %i c = %i\n", (*ti)->y[i], (*ti)->x[i], (*ti)->z[i], (*ti)->c[i]);
    }
    
}

