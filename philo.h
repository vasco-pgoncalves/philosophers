/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 12:42:22 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/30 02:09:32 by vascopinto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		//printf
# include <stdlib.h>	//malloc, free
# include <unistd.h>	//write, usleep
# include <stdbool.h>	//bool
# include <pthread.h>	//mutex : init, destroy, lock, unlock
						//threads: create, join, detach
# include <sys/time.h>	//gettimeofday
# include <limits.h>	//INT_MAX

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_code;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

/*
	FORK
*/

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

/* 
	PHILO
*/

typedef struct s_philo
{
	int			id;
	int			nb_meals_had;
	bool		full;
	long		last_meal_time;	//time passed since last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mtx		philo_mutex; // lock and unlock to update last meal time
	pthread_t	thread_id;	//a philo is a thread
	t_table		*table;
}	t_philo;

/* 
	TABLE
	./philo	5 800 200 200 [5]
*/

typedef struct s_table
{
	long		philo_nb;
	long		time_to_die;		// values passed by the user in the input //
	long		time_to_eat;
	long		time_to_sleep;
	long		nb_limit_meals; // [5] | flag if -1
	long		start_simulation;
	long		threads_nb;		// current nb of threads running 
	bool		end_simulation;	//philo dies || all philos are full
	bool		all_threads_ready; // wait for every philo to sync
	t_mtx		table_mutex; //avoid races while reading from table
	t_mtx		print_mutex; // avoid printing incorectly
	pthread_t	monitor; // thread searching for death
	t_fork		*forks;	// array to all forks
	t_philo		*philos;	// array to all philosophers
}	t_table;

bool	ph_parsing(t_table	*table, char	*argv[]);
int		main(int argc, char *argv[]);
int		ft_isspace(char c);
int		safe_mutex_handle(t_mtx	*mutex, t_opcode	opcode);
void	data_init(t_table	*table);
void	*safe_malloc_cleanup(size_t size, void (*cleanup)(void *), void *data);
int		safe_thread_handle(pthread_t *thread,
			void *(*wildcard)(void *), void *arg, t_opcode opcode);
void	cleanup_table(void	*data);
long	get_time(t_time_code	time_code);
void	precise_usleep(long usec, t_table *table);
void	print_status(t_philo_status status, t_philo *philo);
void	*dinner_simulation(void	*data);
void	diner_start(t_table	*table);
bool	all_threads_running(t_mtx	*mutex, long *threads, long philo_nbr);
void	add_to_long(t_mtx	*mutex, long	*value);
void	*monitor_dinner(void	*data);
void	thinking(t_philo	*philo, bool pre_simulation);
void	de_sync_philos(t_philo	*philo);

// Set_Get
void	set_bool(t_mtx *mutex, bool *dest, bool value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);

// Sync 
void	wait_all_threads(t_table	*table);

#endif