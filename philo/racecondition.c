/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   racecondition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:36:25 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/21 18:51:32 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int	mails = 0;

void	*routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		mails++;
	}
	return ((void *)1);
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	t1, t2;
	if(pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	if(pthread_create(&t2, NULL, &routine, NULL) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	if(pthread_join(t1, NULL) != 0)
	{
		printf("Error!\n");
		return (1);
	}
	if (pthread_join(t2, NULL) != 0)
	{
		printf("Error!\n");
		return (1);
	}
	printf("Number of mails %d\n", mails);
	return (0);
}
