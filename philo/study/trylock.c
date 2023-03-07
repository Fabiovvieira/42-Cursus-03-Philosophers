/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trylock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:18:07 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/25 16:53:12 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

// chefs = threads
// stove = shared data (+mutex)

pthread_mutex_t stoveMutex[4];
int stoveFuel[4] = { 100, 100, 100, 100 };

void* routine(void* args) {
    for (int i = 0; i < 4; i++) {
        if (pthread_mutex_trylock(&stoveMutex[i]) == 0) {
            int fuelNeeded = (rand() % 30);
            if (stoveFuel[i] - fuelNeeded < 0) {
                printf("No more fuel on stove %d... going home\n", i);
            } else {
                stoveFuel[i] -= fuelNeeded;
                usleep(500000);
                printf("Fuel left %d of stove %d\n", stoveFuel[i], i);
            }
            pthread_mutex_unlock(&stoveMutex[i]);
            break;
        } else {
            if (i == 3) {
                printf("No stove available yet, waiting...\n");
                usleep(300000);
                i = 0;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[10];
    for (int i = 0; i < 4; i++) {
        pthread_mutex_init(&stoveMutex[i], NULL);
    }
    for (int i = 0; i < 10; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    for (int i = 0; i < 4; i++) {
        pthread_mutex_destroy(&stoveMutex[i]);
    }
    return 0;
}
