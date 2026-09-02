/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 20:00:54 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/02 22:24:02 by chguerre         ###   ########.fr       */
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
	char str[] = "1Esta es una linea muy larga\n  2Esta es una linea muy larga\n 3Esta es una linea muy larga\n4Esta es una linea muy larga\n 5Esta es una linea muy larga\n6Esta es una l inea muy larga\n 7Esta es una linea muy larga\n8Esta es una linea muy larga\n 9Esta es una linea muy larga\n10Esta es una linea muy larga\n 11Esta es una linea muy larga\n12Esta es una linea muy larga\n 13Esta es una linea muy larga\n14Esta es una linea muy larga\n 15Esta es una linea muy larga\n16Esta es una linea muy larga\n";

	(void)argc;
	(void)argv;
	pipe(fd);

	pid1 = fork();
	if(pid1 == 0)
	{
		close(fd[0]);
		write(fd[1], &str, strlen(str));
		close(fd[1]);
		exit(0);
	}
	pid2 = fork();
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
