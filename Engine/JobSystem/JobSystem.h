#pragma once
#include <functional>

namespace Engine
{
	namespace JobSystem
	{
		struct Job
		{
			std::function<void()> Function;

			Job(std::function<void()> i_function) :
				Function(i_function)
			{

			}
		};

		void CreateQueue();
		void RunJob();
		void RequestShutdown();
		bool ShutdownRequested();
	};

}

