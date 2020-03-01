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

			ResumeThread(newRunner->threadHandle);
		}

		void RunJob(const std::string i_queueName, std::function<void()> i_jobFunction)
		{
			auto iter = allQueues.find(i_queueName);
			iter->second->queue.AddJobs(new Job(i_jobFunction));
		}

		void RequestShutdown()
		{
			shutdownSet = true;
			std::vector<HANDLE> allThreads;

			auto iter = allQueues.begin();

			//Grab all Thread Handles
			while (iter != allQueues.end())
			{
				if (iter->second)
				{
					iter->second->queue.ShutdownRequest();
					const size_t count = iter->second->queueRunners.size();

					for (size_t i = 0; i < count; i++)
					{
						JobRunnerData* runner = iter->second->queueRunners[i];
						if (runner && runner->threadHandle != NULL)
						{
							allThreads.push_back(runner->threadHandle);
						}
					}

					iter++;
				}
			}

			//Wait for all Threads to finish
			DWORD result = WaitForMultipleObjects(static_cast<DWORD>(allThreads.size()), &allThreads[0], TRUE, INFINITE);
			assert(result == WAIT_OBJECT_0);

			//Delete Runner Data pointers
			iter = allQueues.begin();
			while (iter != allQueues.end())
			{
				if (iter->second)
				{
					const size_t count = iter->second->queueRunners.size();

					for (size_t i = 0; i < count; i++)
					{
						JobRunnerData* runner = iter->second->queueRunners[i];
						if (runner)
						{
							delete runner;
						}

						delete iter->second;
					}
				}
			}

			allQueues.clear();
		}

		bool ShutdownRequested()
		{
			return shutdownSet;
		}
	} //namespace JobSystem
} //namespace Engine