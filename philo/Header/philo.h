/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:44:35 by vmoreau           #+#    #+#             */
/*   Updated: 2021/06/23 17:08:39 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define NC "\033[0m"

// STRUCTURE NTPE_TOT = NUMBER TIME PHILO EAT TOTAL NTPE = NUMBER TIME PHILO EAT
typedef struct s_arg
{
	unsigned int	time_start;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				ntpe_tot;
}				t_arg;

struct			s_data;
typedef struct s_philo
{
	int				id;
	t_arg			arg;
	int				ntpe;
	unsigned int	time_without_eat;
	unsigned int	reset;
	pthread_t		threads;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat_or_die;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				nb_philo;
	bool			is_philo_dead;
	t_arg			arg;
	t_philo			*philos;
	pthread_mutex_t	display;
}				t_data;

// PHILO
void			*start_philo(void *thread);

// INIT
bool			init(t_data *data, char **av, int ac);
bool			init_thread(t_data *data);

// TIME
unsigned int	get_time(bool start, unsigned int time_start);

// ACTION
void			find_id_fork(t_philo *philo, int *id_left);
void			t_fork(pthread_mutex_t *f_l, pthread_mutex_t *f_r, \
						t_philo *philo);
void			r_fork(pthread_mutex_t *f_l, pthread_mutex_t *f_r);
void			action_eat(t_philo *philo);
void			action_sleep(t_philo *philo);

// UTILS
void			display_status(t_philo *philo, char *status);
int				ft_strcmp(const char *s1, const char *s2);
bool			isnum(char *str);
int				ft_atoi(const char *str);
void			ft_wait(int delay, bool is_dead);

// EXIT_ERR
int				exit_err(int status, t_data *data);

// CHECK_ARGS
bool			check_args(char **av);

#endif
