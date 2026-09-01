/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 19:14:22 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/01 19:17:02 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	int fd;
	pid_t pid;
	
	char *cmd[] = {"ls", NULL};
	(void)argc;
	(void)argv;
	//char **envp = NULL;
	pid = fork();
	if( pid == 0)
	{
		fd = open("sample.txt", O_WRONLY| O_CREAT| O_TRUNC , 0644);
		if(fd < 0)
			return(1);

		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve("/usr/bin/env", (char *[]){"env", NULL}, envp);
		perror(cmd[0]);
		exit(127);
	}
	wait(NULL);
	return (0);
}