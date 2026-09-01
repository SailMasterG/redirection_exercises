/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 20:00:54 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/01 20:24:46 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	int fd;
	pid_t pid;
	int status;
	int code;
	(void)argc;
	(void)argv;

	pid = fork();
	if(pid == 0)
	{
		fd = open("poem.txt", O_RDONLY);
		if(fd < 0)
		{
			perror("Error reading file.");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		execve("/usr/bin/cat", (char *[]){"cat", NULL}, envp);
		perror(" cat ");
		exit(127);
	}
	code = 0;
	wait(&status);
	if (WIFEXITED(status))
    	code = WEXITSTATUS(status);
	return (code);
}