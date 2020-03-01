#include "JobRunner.h"
#include "JobSystem.h"
#include "JobQueue.h"
#include <map>
#include <string>
#include <assert.h>

namespace Engine
{
	namespace JobSystem
	{
		struct JobRunnerData
		{
			HANDLE threadHandle;
			DWORD threadID;
			RunnerQueue threadQueue;
		};

		struct JobQueueData
		{
			JobQueue queue;
			std::vector<JobRunnerData*> queueRunners;
		};

		bool shutdownSet = false;
		std::map<std::string, JobQueueData*> allQueues;

		void CreateQueue(std::string i_queueName, unsigned int i_numRunners)
		{
			assert(allQueues.find(i_queueName) == allQueues.end());
			JobQueueData* newQueue = new JobQueueData();

			allQueues[i_queueName] = newQueue;

			for (size_t i = 0; i < i_numRunners; i++)
			{
				AddRunner(i_queueName);
			}
		}

		bool HasJobs(const std::string& i_queueName)
		{
			if (allQueues.find(i_queueName) == allQueues.end())
			{
				return false;
			}

			return allQueues[i_queueName]->queue.HasJobs();
		}

		void AddRunner(const std::string& i_queueName)
		{
			JobRunnerData* newRunner = new JobRunnerData();
			allQueues[i_queueName]->queueRunners.push_back(newRunner);

			newRunner->threadQueue.queueHolder = &(allQueues[i_queueName]->queue);

			newRunner->threadHandle = CreateThread(NULL, 0, doJob, &(newRunner->threadQueue), CREATE_SUSPENDED, &newRunner->threadID);
		}

		void RequestShutdown()
		{
			shutdownSet = true;


		}

		bool ShutdownRequested()
		{
			return shutdownSet;
		}
	} //namespace JobSystem
} //namespace Engine