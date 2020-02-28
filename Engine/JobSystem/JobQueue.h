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
			Job* getNewJob();
			void reportFinished();

		private:
		};
	} //namespace JobSystem
} //namespace Engine