/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vascopinto <vascopinto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 12:42:22 by vascopinto        #+#    #+#             */
/*   Updated: 2026/06/29 18:06:08 by vascopinto       ###   ########.fr       */
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
	pthread_t	thread_id;	//a philo is a thread
	t_table		*table;
}	t_philo;

/* 
	TABLE
	./philo	5 800 200 200 [5]
*/

typedef struct s_table
{
	long	philo_nb;
	long	time_to_die;		// values passed by the user in the input //
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_limit_meals; // [5] | flag if -1
	long	start_simulation;
	bool	end_simulation;	//philo dies || all philos are full
	bool	all_threads_ready; // wait for every philo to sync
	t_mtx	table_mutex; //avoid races while reading from table
	t_fork	*forks;	// array to all forks
	t_philo	*philos;	// array to all philosophers
}	t_table;

bool	ph_parsing(t_table	*table, char	*argv[]);
int		main(int argc, char *argv[]);
int		ft_isspace(char c);
int		mutex_handle(t_mtx	*mutex, t_opcode	opcode);
int		data_init(t_table	*table);
void	*safe_malloc_cleanup(size_t size, void (*cleanup)(void *), void *data);
void	cleanup_table(void	*data);

#endif