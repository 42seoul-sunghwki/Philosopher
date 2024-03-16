/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:27:26 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/12 23:11:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define INT_MAX	2147483647
# define INT_MIN	-2147483648
# define THOUSAND	1000

# define TRUE		1
# define FALSE		0

# define FUN_SUC	0
# define FUN_FAIL	1

# define NOT_CHECK	0
# define SLEEP		1
# define EAT		2
# define THINK		3
# define DIE		4

# define SLEEP_MSG	"is sleeping"
# define EAT_MSG	"is eating"
# define THINK_MSG	"is thinking"
# define TAKE_MSG	"has taken a fork"
# define UNTAKE_MSG	"drop a fork"
# define DIE_MSG	"died"

typedef struct s_info {
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_must_eat;
}	t_info;

typedef struct s_msg {
	pthread_mutex_t	*print;
	long			time;
	long			ph;
	long			flag;
	char			*msg;
}	t_msg;

typedef struct s_thread {
	pthread_mutex_t	*print;
	pthread_mutex_t	*count_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			info;
	long			*left_f;
	long			*right_f;
	long			ph_name;
	long			*count_eat;
	long			start_time;
	volatile int	*flag;
}	t_thread;

/* ft_lib.c */
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
int			ft_isspace(char s1);
long		ft_atol(const char *str);
long		ft_microsec_now(void);

/* init.c */
int			init_value(int argc, char **argv, t_info *info);
int			init_static_value(t_thread *ph, int size);
t_thread	*init_thread(int argc, char **argv);

/* helper.c */
int			msg_philo(t_thread *ph, t_msg *msg);
int			count_up(t_thread *ph);
int			lock_fork(pthread_mutex_t *fork, long *flag, int fork_flag);
int			check_atol(const char *input, long *output);

/* thread_helper.c */
int			check_status(t_thread *ph, long start_eating, int flag);

void		*philo(void *input);

#endif
