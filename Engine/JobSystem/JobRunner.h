#pragma once
#include "JobQueue.h"
#include <string>
namespace Engine
{
	namespace JobSystem
	{
		struct RunnerQueue
		{
			JobQueue* queueHolder; //The queue that this runner is attached to
		};

		DWORD WINAPI doJob(void* i_threadInput);
	} //namespace JobSystem
} //namespace Engine