/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 03:14:07 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 20:05:49 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define STR_ERR_INPUT_DIGIT "Error : input must be a digit"
# define STR_ERR_INPUT_POFLOW "Error : number of philosophers is out of range"
# define STR_MAX_PHILOS "Max number of philosophers exceeded"
# define MAX_PHILOS 250
# define STR_USAGE "%s note : ./philo <num_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[num_of_times_each_philo_must_eat]\n"

typedef struct s_donnee
{
	time_t			time_to_start;
	pthread_mutex_t	afficher;
	pthread_mutex_t	verify_if_death;
	pthread_mutex_t	food_to_eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	time;
	time_t			time_to_sleep;
	time_t			time_to_die;
	time_t			time_to_eat;
	int				finish;
	int				max_food_to_eat;
	int				death_statu;
	int				num_of_philosophers;
	int				id;
}	t_donnee;

typedef struct s_mouvmt
{
	t_donnee			*donner;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	pthread_t			thread;
	time_t				time_to_sleep;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_start;
	int					eating_time;
	int					num_philo;
	int					eating_statu;
	int					id;
	struct s_mouvmt		*next;
	struct s_mouvmt		*prev;
}	t_mouvmt;

typedef struct s_list
{
	t_mouvmt	*begining;
	t_mouvmt	*end;
	size_t		size;
}	t_list;

typedef enum s_check_type
{
	CHECK_DEATH_STATUS,
	CHECK_MEALS_EATEN
}t_check_type;

time_t		time_in_milis(void);
t_mouvmt	*creat_philo(t_donnee **donner);
t_donnee	*init(int ac, char **av);
t_list		*list_initializ(void);
t_list		*list_creation(char **av, t_donnee **donner);
t_list		*list(void);
int			start_philos_threads(t_list *philo_list);
int			main(int ac, char **av);
int			initialize_and_validate(int ac, char **av,
				t_donnee **donner, t_list **list);
int			verify_valu(int ac, t_donnee *donner);
int			error_msg(const char *string, t_list *list);
int			last_checking(t_mouvmt *philo);
int			death_eating_status(t_mouvmt *philo, t_check_type type);
int			perfom_action(t_mouvmt *philo, void (*action)(t_mouvmt *));
int			verify_mx_food(t_mouvmt *philo);
int			atoi(const char *str);
int			digit_num(const char *str);
int			valid_num(int argc, char **argv);
void		cleanup_mutex(t_list *list);
void		free_msg(t_list *list);
void		initialization_philo(char **av, t_donnee **donner, t_list **list);
void		drop_forks(t_mouvmt *philo);
void		hold_forks(t_mouvmt *philo);
void		thinkig(t_mouvmt *philo);
void		he_sleep(t_mouvmt *philo);
void		message(t_mouvmt *philo, char *str);
void		verify_death_philo(t_mouvmt *philo, time_t cur_time);
void		ft_usleep(time_t ms);
void		eating(t_mouvmt *philo);
void		ajout_a_list(t_list **list, t_mouvmt **philo);
void		set_left_fork(t_list *list);
void		for_one_philo(t_mouvmt *philo);
void		philo_thinking(t_mouvmt *philo);
void		*process(void *arg);
void		collec_thread(t_mouvmt *philo, t_list *list);
void		simulatition_cleanup(t_donnee *donner, t_list *list);
void		free_extra_list(t_list *list);

#endif