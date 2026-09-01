/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 18:26:03 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/01 18:26:53 by chguerr          ###   ########.ch       */
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
	pid = fork();
	if( pid == 0)
	{
		fd = open("sample.txt", O_WRONLY| O_CREAT| O_TRUNC , 0644);
		if(fd < 0)
		return(1);

		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve("/usr/bin/ls", cmd, envp);
		perror(cmd[0]);
		exit(127);
	}
	wait(NULL);
	return (0);
}