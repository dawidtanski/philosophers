/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:15:35 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/14 14:10:11 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_threads_ready))
		usleep(100);
}

// All threads running
bool	a_t_r(t_mtx *mutex, long *threads, long num_of_philos)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == num_of_philos)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	desynchronize_philos(t_philo *philo)
{
	long	philo_n;

	philo_n = get_long(&philo->table->table_mtx, &philo->table->num_of_philos);
	if (philo_n % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			precise_usleep(30000, philo->table);
	}
	else
	{
		if (philo->philo_id % 2)
			think(philo);
	}
}

void	wait_monitor(t_table *table, long p_num)
{
	while (!a_t_r(&table->table_mtx, &table->threads_running_nbr, p_num))
		usleep(100);
}
