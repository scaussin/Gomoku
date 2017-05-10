#ifndef THREADPOOL_HPP
# define THREADPOOL_HPP

# include "Gomoku.hpp"

typedef struct	s_HeuristickReadLineTask
{
	bool			IsAssigned;
	bool			IsDone;
	Board			*board;
	t_Color			*playerColor;
	t_vec2			*curPoint;
	int				*dir;
	int				*retval;

}				t_HeuristickReadLineTask;

class	ThreadPool
{
	public:
		// the threadworkers
		std::vector<std::thread>				Workers;

		// the tasks to accomplish
		std::deque<t_HeuristickReadLineTask>	Tasks;

		std::timed_mutex								TasksMutex;

		ThreadPool();

		~ThreadPool();

		void	AddHeuristicReadlineTask(
			Board *board, t_Color *playerColor,
			t_vec2 *curPoint, int *dir, int *retval);

		void	AddHeuristicTask(Board *board,
			t_Color *playerColor, t_vec2 *curPoint,
			int *retval);

		bool	WaitForTasks();

		void	ClearTasks();

	private:
		void Work(); // for the thread workers.





	
};

#endif
