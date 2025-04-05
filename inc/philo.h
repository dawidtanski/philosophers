/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:44:56 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/05 08:13:03 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

// ANSI Escape Sequences for Bold Text Colors
# define R		"\033[1;31m" /*BOLD_RED*/
# define G		"\033[1;32m" /*BOLD_GREEN*/
# define Y		"\033[1;33m" /*BOLD_YELLOW*/
# define B		"\033[1;34m" /*BOLD_BLUE*/
# define M		"\033[1;35m" /*BOLD_MAGENTA*/
# define C		"\033[1;36m" /*BOLD_CYAN*/
# define W		"\033[1;37m" /*BOLD_WHITE*/

# define RST	"\033[0m" /*RESET*/

typedef pthread_mutex_t t_mtx;

typedef	enum s_status
{
	SLEEPING,
	GRAB_1ST_FORK,
	GRAB_2ND_FORK,
	EATING,
	THINKING,
	DIED,
}		t_status;

typedef	enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

typedef enum s_time_unit
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_time_unit;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}		t_fork;

typedef struct s_philo
{
	int		philo_id;
	int		meals_counter;
	long	last_meal_time;
	t_fork	first_fork;
	t_fork	second_fork;
	bool	full;
	pthread_t	thread_id;
	t_mtx	philo_mtx;
	t_table	*table

}		t_philo;

typedef struct s_table
{
	long		num_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_limit;
	long		start_simulation_time;
	bool		simulation_finished;
	pthread_t	waiter;
	t_philo		*philos_arr;
	t_fork		*forks_arr;
}		t_table;

// Main functions
data_init(&table);
philos_dinner(&table);
clean(&table);

// Parsing an input
int	parse_input(t_table *table, char *argv[]);

// Exit with error printed
int err_exit(const char *str);

// Safe functions
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

// Setters and getters
void	set_bool(t_mtx mutex, bool *dest, bool value);
bool	get_bool(t_mtx mutex, bool *src);
void	set_long(t_mtx mutex, long *dest, long value);
long	get_long(t_mtx mutex, long *src);
void	increase_long(t_mtx mutex, long *src);

// Time management
long get_time(t_time_unit unit);
void	go_sleep(long	time, t_time_unit	unit);

// Printing output
void	print_output(t_status status, t_philo *philo);



#endif