#include "../includes/Gomoku.hpp"


ThreadWorker::ThreadWorker(int index)
{
	ThreadIndex = index;
	IsAsleep = true;
	TaskToProcess = NULL;

	this->Thread = std::thread(&ThreadWorker::Work, this);
}

void		ThreadWorker::Work()
{
	std::cout << "hello working!" << std::endl;
	while (1)
	{
		WorkerMutex.lock();
		if (IsAsleep == false)
		{
			// std::cout << "<- thread #" << ThreadIndex << " working on task" KRESET << std::endl;
			Heuristic::EvaluateAllDir(TaskToProcess->get()->board,
				TaskToProcess->get()->playerColor, TaskToProcess->get()->curPoint, TaskToProcess->get()->retval);
			IsAsleep = true;
			TaskToProcess = NULL;
			break;
			// std::cout << KGRN "-> thread #" << ThreadIndex << " task done" KRESET << std::endl;
		}
		WorkerMutex.unlock();
	}
	this->Thread.join();
}

/*
** Threadpool INIT.
*/

ThreadPool::ThreadPool()
{
	// for (int i = 0; i != THREADPOOL_SIZE; i++)
	// {
	// 	Workers.push_back(std::thread(&ThreadPool::Work, this));

	// }
	CurrentTaskNb = 0;
	for (int i = 0; i != THREADPOOL_SIZE; i++)
	{
		ThreadWorkers.push_back(new ThreadWorker(i));
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


	// // while (!TasksMutex.try_lock())
	// // {
	// // 	// need access to add task;
	// // }
	// Tasks.push_back(new_task);
	// std::cout << KYEL "<- task added" KRESET << std::endl;
	// TasksMutex.unlock();
}

// TASK ORDONANCER.
void		ThreadPool::AddHeuristicTask(Board *board, t_Color *playerColor, t_vec2 *curPoint, int *retval)
{
	t_HeuristickReadLineTask	*new_task;
	bool						taskAssigned = false;
	static int					z = 0;
	static int					i;

	new_task = new t_HeuristickReadLineTask();
	new_task->IsAssigned = false;
	new_task->IsDone = false;
	new_task->board = board;
	new_task->playerColor = playerColor;
	new_task->curPoint = curPoint;
	//new_task.dir = dir;
	new_task->retval = retval;

	// wait for available thread.
	// std::cout << KYEL "Threadpool assigning task" << std::endl;
	while (taskAssigned == false)
	{
		for (i = 0; i != THREADPOOL_SIZE; ++i)
		{
			ThreadWorkers[i]->WorkerMutex.lock();
			if (ThreadWorkers[i]->IsAsleep == true)
			{
				ThreadWorkers[i]->TaskToProcess = new std::shared_ptr<t_HeuristickReadLineTask> (new_task);
				// ThreadWorkers[i]->TaskToProcess.IsAssigned = true;
				// ThreadWorkers[i]->TaskToProcess.IsDone = false;
				// ThreadWorkers[i]->TaskToProcess.board = board;
				// ThreadWorkers[i]->TaskToProcess.playerColor = playerColor;
				// ThreadWorkers[i]->TaskToProcess.curPoint = curPoint;
				// ThreadWorkers[i]->TaskToProcess.retval = retval;
				ThreadWorkers[i]->IsAsleep = false; // wake up thread to exec task.
				taskAssigned = true;
				// CurrentTaskNb += 1;
				// std::cout << KYEL "Task #" << z << " assigned to thread #" << i << KRESET << std::endl;
				ThreadWorkers[i]->WorkerMutex.unlock();
				z++;
				break ;
			}
			ThreadWorkers[i]->WorkerMutex.unlock();
		}
	}

	// while (!TasksMutex.try_lock())
	// {
	// 	// need access to add task;
	// }
	// Tasks.push_back(new_task);
	// // std::cout << KYEL "<- task added" KRESET << std::endl;
	// TasksMutex.unlock();
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
			Heuristic::EvaluateAllDir(task_to_process->board,
				task_to_process->playerColor, task_to_process->curPoint, task_to_process->retval);
			while (!TasksMutex.try_lock())
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
	bool		all_done = true;

	for (int i = 0; i != THREADPOOL_SIZE; i++)
	{
		ThreadWorkers[i]->WorkerMutex.lock();
		if (ThreadWorkers[i]->IsAsleep == false)
		{
			all_done = false;
		}
		ThreadWorkers[i]->WorkerMutex.unlock();
	}
	return (all_done);

	// bool		tasks_done = false;
	// bool		all_done = true;


	// while (!TasksMutex.try_lock_for(std::chrono::milliseconds(10)))
	// {}

	// // std::cout << "checking tasks" << std::endl;
	// for (std::deque<t_HeuristickReadLineTask>::iterator it = Tasks.begin();
	// 		it != Tasks.end();
	// 		it++)
	// {
	// 	if ((*it).IsDone == false)
	// 	{
	// 		all_done = false;
	// 	}
	// }
	// if (all_done == true)
	// {
	// 	// std::cout << KYEL "clearing tasks" KRESET << std::endl;
	// 	tasks_done = true;
	// 	Tasks.clear();
	// 	// std::cout << KGRN "tasks done and cleared" KRESET << std::endl;
	// }
	// TasksMutex.unlock();
	// return (tasks_done);
	// -------> CRASH
	// for (int i = 0; i != THREADPOOL_SIZE; i++)
	// {
	// 	Workers[i].join();
	// }

	//std::cout << "task done! task list size = " << Tasks.size() << std::endl;
}