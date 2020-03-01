#pragma once
#include "JobRunner.h"
#include <assert.h>
namespace Engine
{
	namespace JobSystem
	{
		DWORD __stdcall doJob(void* i_threadInput)
		{
			assert(i_threadInput);
			assert(((RunnerQueue*)i_threadInput)->queueHolder);

			RunnerQueue* threadData = reinterpret_cast<RunnerQueue*>(i_threadInput);
			JobQueue* threadQueue = reinterpret_cast<JobQueue*>(threadData->queueHolder);

			bool finished = false;
			do
			{
				struct Job* newJob = threadQueue->GetNewJob();
				if (newJob)
				{
					newJob->Function();
					delete newJob;
					
					//Report to queue that job was finished
					threadQueue->ReportFinished();
				}

				finished = ShutdownRequested();
			} while (!finished);
			return 0;
		}
	} //namespace JobSystem
} //namespace Engine