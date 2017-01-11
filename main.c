/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Niko <niko.caron90@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:14:18 by Niko              #+#    #+#             */
/*   Updated: 2017/01/11 00:42:57 by Niko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	char	*line;
	int		fd1;
//	int		fd2;
//	int		ret;
	int		status;

	fd1 = open(argv[1], O_RDONLY);
//	fd2 = open(argv[2], O_RDONLY);
	while ((status = get_next_line(fd1, &line)) == 1)
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
//	status = get_next_line(fd1, &line);
//	ft_putendl(line);
//	status = get_next_line(fd2, &line);
//	ft_putendl(line);
//	ret = close(fd1);
//	ret = close(fd2);
	return (0);
}*/

#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int				main(void)
{
    char		*line1;
    char		*line2;
    char		*line3;
    int			fd1;
    int			fd2;
    int			fd3;
    int			ret1;
    int			ret2;
    int			ret3;
    char		*filename1;
    char		*filename2;
    int			errors;
    
    filename1 = "gnl11_1.txt";
    filename2 = "gnl11_2.txt";
    fd1 = open(filename1, O_RDONLY);
    fd2 = open(filename2, O_RDONLY);
    fd3 = -1;
    if (fd1 > 2 && fd2 > 2)
    {
        errors = 0;
        line1 = NULL;
        line2 = NULL;
        line3 = NULL;
        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret2 = get_next_line(fd2, &line2);

        
        ret2 = get_next_line(fd2, &line2);

        
        ret2 = get_next_line(fd2, &line2);

        
        ret2 = get_next_line(fd2, &line2);

        
        ret3 = get_next_line(fd3, &line3);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret1 = get_next_line(fd1, &line1);

        
        ret2 = get_next_line(fd2, &line2);

        
        ret2 = get_next_line(fd2, &line2);
 
        
        ret1 = get_next_line(fd1, &line1);

        
        ret2 = get_next_line(fd2, &line2);

        
        close(fd1);
        close(fd2);
        if (errors == 0)
            printf("OK\n");
    }
    else
        printf("An error occured while opening files %s and/or %s\n", filename1, filename2);
    return (0);
}
