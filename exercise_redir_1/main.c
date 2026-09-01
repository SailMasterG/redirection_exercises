/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 08:01:43 by chguerre          #+#    #+#             */
/*   Updated: 2026/09/01 08:38:27 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
	int fd;
	pid_t pid;
	char *cmd[] = {"ls", NULL};
	char **envp = NULL;
	
	fd = open("sample.txt", O_WRONLY| O_CREAT| O_TRUNC , 0644);
	if(fd < 0)
		return(1);

	pid = fork();
	if( pid == 0)
	{

		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve("/usr/bin/ls", cmd, envp);
		perror(cmd[0]);
		exit(127);
	}
	close(fd);
	wait(NULL);
	return (0);
}