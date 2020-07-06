#pragma once
#include <Windows.h>
#include <queue>
#include "JobSystem.h"
namespace Engine
{
	namespace JobSystem
	{
		class JobQueue
		{
		public:
			JobQueue();

			bool AddJobs(Job* i_newJob);
			bool HasJobs();
			Job* GetNewJob();
			void ReportFinished();
			void ShutdownRequest();
			bool ShutdownRequestCheck();
		private:
			JobQueue(const JobQueue&) = delete;
			JobQueue& operator=(const JobQueue&) = delete;

			std::queue<Job*> queueJobs;
			CONDITION_VARIABLE checkForJobs;
			mutable CRITICAL_SECTION queueModification;

			bool shuttingDown;
			bool runningJob;
		};
	} //namespace JobSystem
} //namespace Engine