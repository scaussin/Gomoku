#include "../includes/Gomoku.hpp"

/*
** Threadpool INIT.
*/

ThreadPool::ThreadPool()
{
	for (int i = 0; i != THREADPOOL_SIZE; i++)
	{
		Workers.push_back(std::thread(&ThreadPool::Work, this));
	}
	std::cout << "Created ThreadPool" << std::endl;
}

ThreadPool::~ThreadPool()
{

}

void		ThreadPool::AddHeuristicReadlineTask(Board *board, t_Color *playerColor, t_vec2 *curPoint, int *dir, int *retval)
{
	t_HeuristickReadLineTask new_task;

	new_task.IsAssigned = false;
	new_task.IsDone = false;
	new_task.board = board;
	new_task.playerColor = playerColor;
	new_task.curPoint = curPoint;
	new_task.dir = dir;
	new_task.retval = retval;

	TasksMutex.lock();
	Tasks.push_back(new_task);
	TasksMutex.unlock();
}

void		ThreadPool::Work()
{
	t_HeuristickReadLineTask		*task_to_process = NULL;

	std::cout << "hello working!" << std::endl;
	while (1)
	{
		// Grab task;
		TasksMutex.lock();
		for (std::deque<t_HeuristickReadLineTask>::iterator it = Tasks.begin();
				it != Tasks.end();
				it++)
		{
			if ((*it).IsAssigned == false)
			{
				(*it).IsAssigned = true;
				task_to_process = &(*it);
				// std::cout << "worker grabbed a task" << std::endl;
			}
		}
		TasksMutex.unlock();
		if (task_to_process)
		{
			// std::cout << "worker work on a task" << std::endl;
			Heuristic::EvaluateOneDir(task_to_process->board,
				task_to_process->playerColor, task_to_process->curPoint,
				task_to_process->dir, task_to_process->retval);
			task_to_process->IsDone = true;
			task_to_process = NULL;
		}
	}
}

// TODO: Not working -> concurrent access crash.
void		ThreadPool::WaitForTasks()
{
	bool		tasks_done = false;
	bool		all_done = true;
	int			check_clock = 0;

	while (!tasks_done)
	{
		if (check_clock > 10000)
		{
			check_clock = 0;
			TasksMutex.lock();
			for (std::deque<t_HeuristickReadLineTask>::iterator it = Tasks.begin();
					it != Tasks.end();
					it++)
			{
				if ((*it).IsDone == false)
				{
					all_done = false;
					break;
				}
			}
			TasksMutex.unlock();
			if (all_done == true)
			{
				tasks_done = true;
			}
		}
		else
		{
			check_clock += 1;
		}
	}
	// -------> CRASH
	// for (int i = 0; i != THREADPOOL_SIZE; i++)
	// {
	// 	Workers[i].join();
	// }
	TasksMutex.lock();
	Tasks.clear();
	TasksMutex.unlock();
	//std::cout << "task done! task list size = " << Tasks.size() << std::endl;
}
