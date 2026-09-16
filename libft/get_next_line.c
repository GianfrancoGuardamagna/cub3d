/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:33 by carmegon          #+#    #+#             */
/*   Updated: 2025/12/01 21:43:46 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_read_line(int fd, char *stash)
{
	char	*str;
	ssize_t	bytes_read;

	if (!stash)
	{
		stash = malloc(1 * sizeof(char));
		stash[0] = '\0';
		if (!stash)
			return (ft_free_gnl(&stash));
	}
	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0 && !ft_strchr_gnl(stash, '\n'))
	{
		str = malloc(BUFFER_SIZE + 1 * sizeof(char));
		if (!str)
			return (NULL);
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free_gnl(&stash), ft_free_gnl(&str));
		str[bytes_read] = '\0';
		stash = ft_strjoin_gnl(stash, str);
		ft_free_gnl(&str);
	}
	return (stash);
}

char	*ft_extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
	{
		stash = NULL;
		return (NULL);
	}
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr_gnl(stash, 0, i);
	if (!line)
	{
		ft_free_gnl(&stash);
		ft_free_gnl(&line);
	}
	return (line);
}

char	*ft_update_line(char *stash)
{
	char	*aux;
	int		i;

	i = 0;
	if (!stash[i])
	{
		stash = NULL;
		return (NULL);
	}
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	aux = ft_substr_gnl(stash, i, ft_strlen_gnl(stash + i));
	if (!aux)
	{
		ft_free_gnl(&stash);
		ft_free_gnl(&aux);
	}
	ft_free_gnl(&stash);
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_line(fd, stash);
	if (!stash || stash[0] == '\0')
		return (ft_free_gnl(&stash));
	line = ft_extract_line(stash);
	if (!line)
		return (NULL);
	stash = ft_update_line(stash);
	if (!stash)
		return (NULL);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("archivo.txt", O_RDONLY);
	//fd = open("oneline.txt", O_RDONLY);
	//fd = open("vacio.txt", O_RDONLY);
	fd = open("peque.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LÍNEA OBTENIDA DEL MAIN: %s]", line);
		free(line);
	}
	close(fd);
	return (0);
} */
/* int main(void)
{
	char *line;

	write(1, "Escribe algo (Ctrl + D para terminar):\n", 39);
	while ((line = get_next_line(0)) != NULL)
	{
		printf(">> %s", line);
		free(line);
	}
	return (0);
} */