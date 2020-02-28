#pragma once
#include "JobQueue.h"
#include <string>
namespace Engine
{
	namespace JobSystem
	{
		struct RunnerData
		{
			JobQueue* queueHolder; //The queue that this runner is attached to

#if _DEBUG
			std::string identifier;
#endif
		};

		DWORD WINAPI doJob(void* i_threadInput);
	} //namespace JobSystem
} //namespace Engine