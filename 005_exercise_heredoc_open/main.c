/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 20:00:54 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/02 22:30:41 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	int fd;
	int fd2;
	pid_t pid;
	int status;
	int code = 0;
	char str[] = "Hola, espero que estes bien.\nMis vacaciones van genial.\nLastima tengo que volver al trabajo manana.";

	(void)argc;
	(void)argv;

	fd = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd < 0)
	{
		perror("Error");
		exit(1);
	}
	write(fd, &str, strlen(str));

	fd2 = open("temp.txt", O_RDONLY);
	if(fd2 < 0)
	{
		perror("Error");
		exit(1);
	}
	unlink("temp.txt");
	dup2(fd2, STDIN_FILENO);

	close(fd);
	close(fd2);
	pid = fork();
	if(pid == 0)
	{

		execve("/usr/bin/cat", (char *[]){"cat", NULL}, envp);
		perror("Error:");
		exit(127);
	}
	wait(&status);
	if(WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
	}
	return (code);
}
