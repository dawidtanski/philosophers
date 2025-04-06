/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:06:49 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/06 16:17:52 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool philo_died(t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mtx, &philo->last_meal_time);
	if (elapsed >= get_long(&philo->table->table_mtx, &philo->table->time_to_die))
		return (true);
	return (false);
}

void *monitor(void	*data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!get_bool(&table->table_mtx, &table->simulation_finished) && !get_bool(&table->table_mtx, &table->all_threads_ready))
	{
		i = 0;
		while (i < table->num_of_philos && !get_bool(&table->table_mtx, &table->simulation_finished))
		{
			if (philo_died(table->philos_arr + i))
			{
				print_output(DIED, table->philos_arr + i);
				set_bool(&table->table_mtx, &table->simulation_finished, true);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}