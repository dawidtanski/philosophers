/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:06:49 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/09 12:37:06 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	last_meal;
	long	t_t_die;

	t_t_die = get_long(&philo->philo_mtx, &philo->table->time_to_die);
	last_meal = get_long(&philo->philo_mtx, &philo->last_meal_time);
	elapsed = get_time(MILLISECOND) - last_meal;
	if (elapsed >= t_t_die)
		return (true);
	return (false);
}

void	*monitor(void	*data)
{
	t_table	*table;
	int		i;
	bool	sim_fin;
	long	p_num;

	table = (t_table *)data;
	sim_fin = get_bool(&table->table_mtx, &table->sim_end);
	p_num = get_long(&table->table_mtx, &table->num_of_philos);
	while (!a_t_r(&table->table_mtx, &table->threads_running_nbr, p_num))
		;
	while (!sim_fin && get_bool(&table->table_mtx, &table->all_threads_ready))
	{
		i = 0;
		while (i < p_num && !sim_fin)
		{
			if (philo_died(table->philos_arr + i))
			{
				print_output(DIED, table->philos_arr + i);
				set_bool(&table->table_mtx, &table->sim_end, true);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
