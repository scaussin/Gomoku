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
	// for (int i = 0; i != THREADPOOL_SIZE; i++)
	// {
	// 	Workers[i].join();
	// }
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

	while (!TasksMutex.try_lock())
	{
		// need access to add task;
	}
	Tasks.push_back(new_task);
	// std::cout << KYEL "<- task added" KRESET << std::endl;
	TasksMutex.unlock();
}

void		ThreadPool::Work()
{
	t_HeuristickReadLineTask		*task_to_process = NULL;

	std::cout << "hello working!" << std::endl;
	while (1)
	{
		// Grab task;
		if (TasksMutex.try_lock_for(std::chrono::milliseconds(10)))
		{
			for (std::deque<t_HeuristickReadLineTask>::iterator it = Tasks.begin();
					it != Tasks.end();
					it++)
			{
				if ((*it).IsAssigned == false)
				{
					(*it).IsAssigned = true;
					task_to_process = &(*it);
					// std::cout << KYEL "worker grabbed a task" KRESET << std::endl;
					break;
				}
			}
			TasksMutex.unlock();
		}
		
		if (task_to_process)
		{
			// std::cout << "worker processing task..." << std::endl;
			// std::cout << "worker work on a task" << std::endl;
			Heuristic::EvaluateOneDir(task_to_process->board,
				task_to_process->playerColor, task_to_process->curPoint,
				task_to_process->dir, task_to_process->retval);
			while (!TasksMutex.try_lock_for(std::chrono::milliseconds(10)))
			{}
			task_to_process->IsDone = true;
			TasksMutex.unlock();
			task_to_process = NULL;
			// std::cout << KGRN "-> worker processed task!" KRESET << std::endl;
		}
		//std::cout << "now waiting..." << std::endl;
	}
}

// TODO: Not working -> concurrent access crash.
bool		ThreadPool::WaitForTasks()
{
	bool		tasks_done = false;
	bool		all_done = true;


	while (!TasksMutex.try_lock_for(std::chrono::milliseconds(10)))
	{}

	// std::cout << "checking tasks" << std::endl;
	for (std::deque<t_HeuristickReadLineTask>::iterator it = Tasks.begin();
			it != Tasks.end();
			it++)
	{
		if ((*it).IsDone == false)
		{
			all_done = false;
		}
	}
	if (all_done == true)
	{
		// std::cout << KYEL "clearing tasks" KRESET << std::endl;
		tasks_done = true;
		Tasks.clear();
		// std::cout << KGRN "tasks done and cleared" KRESET << std::endl;
	}
	TasksMutex.unlock();
	return (tasks_done);
	// -------> CRASH
	// for (int i = 0; i != THREADPOOL_SIZE; i++)
	// {
	// 	Workers[i].join();
	// }

	//std::cout << "task done! task list size = " << Tasks.size() << std::endl;
}