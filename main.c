/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Niko <niko.caron90@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:14:18 by Niko              #+#    #+#             */
/*   Updated: 2017/01/05 19:29:17 by Niko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char **argv)
{
	(void)argc;
	char	*line;
	int		fd;
	int		status;

	fd = open(argv[1], O_RDONLY);
	while ((status = get_next_line(fd, &line)) == 1)
	{
		ft_putendl(line);
		//free(line);
	}
	//status = get_next_line(5, &line);
	return (0);
}
