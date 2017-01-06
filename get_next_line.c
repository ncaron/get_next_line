/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Niko <niko.caron90@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:09:37 by Niko              #+#    #+#             */
/*   Updated: 2017/01/05 20:17:37 by Niko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Reads the file, BUFF_SIZE at a time.
** Adds what is read to the end of what was already read.
** Repeat as long as there is something to be read.
** Returns the whole contents of the file.
*/

char		*get_content(int fd)
{
	int		ret;
	char	*tmp;
	char	*buf;

	tmp = ft_strnew(BUFF_SIZE);
	buf = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, tmp, BUFF_SIZE)))
	{
		if (ret == -1)
			return (NULL);
		tmp[ret] = '\0';
		buf = ft_strjoin(buf, tmp);
	}
	return (buf);
}

/*
** Creates a new list.
** Returns the created list.
*/

t_list_gnl	*lst_new(t_list_gnl *list, int fd, char *buf)
{
	list = (t_list_gnl*)malloc(sizeof(t_list_gnl));
	list->fd = fd;
	list->content = buf;
	list->next = NULL;
	return (list);
}

/*
** Loops through the list to find the last node and use lst_new
** to add to the end of the list.
** DELETE
*/

/*void	lst_add(t_list_gnl *list, int fd, char *buf)
{
	t_list_gnl *current;

	current = list;
	while (current->next != NULL)
		current = current->next;
	current->next = lst_new(current, fd, buf);
}*/

/*
** Loops through the list and checks all fd to the fd passed in.
** If there is a match, the fd is already opened and return 1.
** If there is no match, the list is closed and return 0.
*/

int			check_open(t_list_gnl *list, int fd)
{
	t_list_gnl *current;

	current = list;
	while (current != NULL)
	{
		if (current->fd == fd)
			return (1);
		current = current->next;
	}
	return (0);
}

/*
** Loops through the list to find the correct node by comparing fd.
** Find the end of the line by using ft_strlenchr.
** Assign to line the contents until end using ft_strsub.
** Content is then changed to end + 1 and the rest of the string.
** Returns the line that was read.
*/

char		*lst_read(t_list_gnl *list, int fd)
{
	t_list_gnl	*current;
	char		*line;
	int			end;

	current = list;
	while (current->fd != fd)
		current = current->next;
	end = ft_strlenchr(current->content, '\n');
	if (end == 0)
	{
		if (current->content[0] == '\n')
			line = ft_strsub(current->content, 0, 1);
		else
			return (NULL);
	}
	else
		line = ft_strsub(current->content, 0, end);
	current->content = &current->content[end + 1];
	return (line);
}

/*
** If fd is negative or line doesn't exist, return -1.
** If list doesn't exist, use lst_new to create a new one.
** If list exists, check if the fd is opened and if not, add it to the end 
** of the list.
** If lst_read is NULL, meaning there are no lines left to be read, return 0.
*/

int			get_next_line(const int fd, char **line)
{
	static t_list_gnl	*list;
	t_list_gnl			*current;
	char				*buf;

	if (fd < 0 || !line)
		return (-1);
	if (!list)
	{
		if ((buf = get_content(fd)) == NULL)
			return (-1);
		list = lst_new(list, fd, buf);
	}
	else if (!check_open(list, fd))
	{
		current = list;
		if ((buf = get_content(fd)) == NULL)
			return (-1);
		while (current->next != NULL)
			current = current->next;
		current->next = lst_new(list, fd, buf);
	}
	if ((*line = lst_read(list, fd)) == NULL)
		return (0);
	return (1);
}
