/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:15:35 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/07 15:10:06 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void wait_all_threads(t_table *table)
{
    while (!get_bool(&table->table_mtx, &table->all_threads_ready))
        usleep(100);
}

bool	all_threads_running(t_mtx *mutex, long *threads, long num_of_philos)
{
	bool	ret;
	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == num_of_philos)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	// printf(M "All threads are running now\n");
	return (ret);
}