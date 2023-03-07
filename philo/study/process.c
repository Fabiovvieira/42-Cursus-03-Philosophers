/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:28:26 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/21 18:14:07 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	int	x = 2;
	int	pid = fork();
	if (pid == -1)
	{
		return 1;
	}
	if (pid == 0)
	{
		x++;
	}
	sleep(2);
	printf("value of x : %d\n", x);
	if (pid != 0)
	{
		wait(NULL);
	}
	return 0;
}
