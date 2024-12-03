/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:43:40 by diana             #+#    #+#             */
/*   Updated: 2024/12/03 21:15:12 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int fd1 = open("doc1.txt", O_RDONLY);
	int fd2 = open("doc2.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error al abrir los archivos");
		return (1);
	}

	char *line1 = get_next_line(fd1);
	char *line2 = get_next_line(fd2);
	while (line1 || line2)
	{
		if (line1)
		{
			printf("Archivo 1:%s\n", line1);
			free(line1);
		}
		if (line2)
		{
			printf("Archivo 2:%s\n", line2);
			free(line2);
		}
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
	}
	close(fd1);
	close(fd2);
	return (0);
}
