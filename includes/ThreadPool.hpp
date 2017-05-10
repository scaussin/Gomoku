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

/*
**		THREAD WORKER ELEMENT.
*/

class ThreadWorker
{
	public:
		int								ThreadIndex;
		bool							IsAsleep;
		t_HeuristickReadLineTask		*TaskToProcess;
		std::thread						Thread;

		std::mutex						WorkerMutex;


		ThreadWorker(int index);
		void							Work();
};

/*
**		GLOBAL THREAD POOL HANDLING WORKERS.
*/

class	ThreadPool
{
	public:
		std::vector<ThreadWorker *>				ThreadWorkers;
		// the threadworkers
		std::vector<std::thread>				Workers;

		// the tasks to accomplish
		std::deque<t_HeuristickReadLineTask>	Tasks;

		std::timed_mutex								TasksMutex;

		int										CurrentTaskNb;

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
