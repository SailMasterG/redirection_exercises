/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 01/09/2026 19:24:48 by chguerr           #+#    #+#             */
/*   Updated: 01/09/2026 19:24:48 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	int fd;
	pid_t pid;
	(void)argc;
	(void)argv;
	
	pid = fork();
	if(pid == 0)
	{
		fd= open("append_txt.txt", O_WRONLY | O_CREAT | O_APPEND , 0644);
		if(fd < 0)
		{
			perror("No se pudo abrir el archivo");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve("/usr/bin/echo", (char *[]){"echo", "Hola Christian!", NULL}, envp);
		perror("/usr/bin/echo");
		exit(127);
	}
	wait(NULL);
	return (0);
}