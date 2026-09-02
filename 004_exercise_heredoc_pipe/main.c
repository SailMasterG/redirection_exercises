/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 20:00:54 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/02 20:49:15 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


int main (int argc, char *argv[], char **envp)
{
	int fd[2];
	pid_t pid1;
	pid_t pid2;
	int state;
	int code;
	char str[] = "Esta es una linea muy larga\n  Esta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\nEsta es una linea muy larga\n Esta es una linea muy larga\n ";
	
	(void)argc;
	(void)argv;
	pipe(fd);
	pid1 = fork();
	pid2 = fork();
	if(pid1 == 0)
	{
		close(fd[0]);
		write(fd[1], &str, strlen(str));
		close(fd[1]);
		exit(0);
	}
	if(pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve("/usr/bin/cat", (char *[]){"cat", NULL}, envp);
		perror("Error ");
		exit(127);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1,&state, 0);
	waitpid(pid2,&state, 0);

	if(WIFEXITED(state))
	{
		code = WEXITSTATUS(state);
	}
	
	
	return (code);
}