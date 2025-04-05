/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:01:37 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/03 21:14:26 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//[1 x1 2 x2 3 x3 4 x4 5 x1]
//[0, 1, 2, 3, 4]
static void assign_forks(t_philo *philo, t_fork *fork_arr, int philo_pos)
{
	int	num_of_philos;

	num_of_philos = philo->table->num_of_philos;
	
	if (philo->philo_id % 2 == 0)
	{
		if (philo_pos == num_of_philos)
			philo->first_fork = fork_arr[0];
		else
			philo->first_fork = fork_arr[philo_pos];
		philo->second_fork = fork_arr[philo_pos - 1];
	}
	else
	{
		philo->first_fork = fork_arr[philo_pos - 1];
		if (philo_pos == num_of_philos)
			philo->second_fork = fork_arr[0];
		else
			philo->first_fork = fork_arr[philo_pos];
	}
}

static void philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_of_philos)
	{
		philo = table->philos_arr + i;
		philo->philo_id = i;
		philo->full = false;
		philo->table = table;
		philo->meals_counter = 0;
		safe_mutex_handle(&philo->philo_mtx, INIT);
		assign_forks(philo, table->forks_arr, i);
		i++;
	}
}

static void table_init(t_table *table)
{
	int	i;

	i = 0;
	table->philos_arr = safe_malloc(sizeof(t_philo) * table->num_of_philos);
	table->forks_arr = safe_malloc(sizeof(t_fork) * table->num_of_philos);
	while (i < table->num_of_philos)
	{
		safe_mutex_handle(&table->forks_arr[i].fork, INIT);
		table->forks_arr[i].fork_id = i;
		i++;
	}
}

void	data_init(t_table *table)
{
	philo_init(&table);
	table_init(&table);
}