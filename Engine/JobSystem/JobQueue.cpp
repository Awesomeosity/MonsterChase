#include "JobQueue.h"
#include <assert.h>

namespace Engine
{
	namespace JobSystem
	{
		JobQueue::JobQueue()
			: shuttingDown(false), runningJob(false)
		{
			InitializeConditionVariable(&checkForJobs);
			InitializeCriticalSection(&queueModification);
		}

		bool JobQueue::AddJobs(Job* i_newJob)
		{
			assert(i_newJob);
			bool added = false;

			EnterCriticalSection(&queueModification);
			if (!shuttingDown)
			{
				queueJobs.push(i_newJob);
				added = true;
			}
			LeaveCriticalSection(&queueModification);

			if (added)
			{
				WakeConditionVariable(&checkForJobs);
			}

			OutputDebugStringA("DEBUG (JobQueue): Adding new job.\n");
			return added;
		}

		bool JobQueue::HasJobs()
		{
			bool hasJob = true;
			EnterCriticalSection(&queueModification);
			if (!runningJob && queueJobs.empty())
			{
				hasJob = false;
			}
			LeaveCriticalSection(&queueModification);

			return hasJob;
		}

		Job* JobQueue::GetNewJob()
		{
			Job* retJob = nullptr;
			EnterCriticalSection(&queueModification);
			if (!shuttingDown && queueJobs.empty())
			{
#if _DEBUG
				bool result = SleepConditionVariableCS(&checkForJobs, &queueModification, INFINITE);
				assert(result != 0);
#else
				SleepConditionVariableCS(&checkForJobs, &queueModification, INFINITE);
#endif

				if (shuttingDown)
				{
					LeaveCriticalSection(&queueModification);
					return nullptr;
				}
			}

			if (!queueJobs.empty())
			{
				retJob = queueJobs.front();
				queueJobs.pop();
			}

			runningJob = true;
			LeaveCriticalSection(&queueModification);
			OutputDebugStringA("DEBUG (JobQueue): Retrieved new job.\n");
			return retJob;
		}

		void JobQueue::ReportFinished()
		{
			EnterCriticalSection(&queueModification);
			runningJob = false;
			LeaveCriticalSection(&queueModification);
		}

		void JobQueue::ShutdownRequest()
		{
			EnterCriticalSection(&queueModification);
			shuttingDown = true;
			LeaveCriticalSection(&queueModification);

			WakeAllConditionVariable(&checkForJobs);
		}

		bool JobQueue::ShutdownRequestCheck()
		{
			return shuttingDown;
		}

	} //namespace JobSystem
} //namespace Engine