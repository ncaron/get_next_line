/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Niko <niko.caron90@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 22:57:47 by Niko              #+#    #+#             */
/*   Updated: 2017/01/11 18:44:35 by Niko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** 
*/

void		lst_free(t_list_gnl **list, int fd)
{
	t_list_gnl	*current;
	t_list_gnl	*previous;

	current = *list;
	previous = NULL;
	while (current != NULL)
	{
		if (current->fd == fd)
		{
			if (previous == NULL)
				*list = current->next;
			else
				previous->next = current->next;
			ft_strdel(&current->content);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

/*
**
*/

char		*lst_read(t_list_gnl *list, int fd)
{
	t_list_gnl	*current;
	char		*line;
	char		*tmp;
	int			end;

	current = list;
	while (current->fd != fd)
		current = current->next;
	end = ft_strlenchr(current->content, '\n');
	if (end == 0)
	{
		if (current->content[0] == '\n')
			line = ft_strdup("");
		else
			return (NULL);
	}
	else
		line = ft_strsub(current->content, 0, end);
	if (current->content[end] == '\0')
		end--;
	tmp = ft_strdup(&current->content[end + 1]);
	ft_strdel(&current->content);
	current->content = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (line);
}

/*
** Loops through the list to find the first unassigned node.
** Reads all the contents to the file and assigns it to the current node.
*/

t_list_gnl	*lst_add(t_list_gnl *list, int fd)
{
	int			ret;
	char		*tmp_read;
	char		*tmp_contents;

	tmp_read = ft_strnew(BUFF_SIZE);
	list = (t_list_gnl*)malloc(sizeof(t_list_gnl));
	list->fd = fd;
	list->content = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, tmp_read, BUFF_SIZE)))
	{
		if (ret == -1)
			return (NULL);
		tmp_read[ret] = '\0';
		tmp_contents = ft_strdup(list->content);
		ft_strdel(&list->content);
		list->content = ft_strjoin(tmp_contents, tmp_read);
		ft_strdel(&tmp_contents);
		ft_strclr(tmp_read);
	}
	ft_strdel(&tmp_read);
	list->next = NULL;
	return (list);
}

/*
** Loops through the list and checks all fd to the fd passed in.
** If there is a match, the fd is already opened and return 1.
** If there is not match, the fd is closed and return 0.
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
** If fd is negative or line doesn't exist, return -1.
** Uses check_open to see if the current file descriptor is already being read.
*/

int			get_next_line(const int fd, char **line)
{
	static t_list_gnl	*list;
	t_list_gnl			*current;

	if (fd < 0 || !line)
		return (-1);
	if (!list)
	{
		if ((list = lst_add(list, fd)) == NULL)
			return (-1);
		current = list;
	}
	else if (!check_open(list, fd))
	{
		current = list;
		while (current->next != NULL)
			current = current->next;
		if ((current->next = lst_add(current->next, fd)) == NULL)
			return (-1);
	}
	if ((*line = lst_read(list, fd)) == NULL)
	{
		lst_free(&list, fd);
		return (0);
	}
	return (1);
}
