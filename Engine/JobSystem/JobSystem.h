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

		void CreateQueue(const std::string i_queueName, unsigned int i_numRunners);
		void RunJob(const std::string i_jobName, const std::string i_queueName, std::function<void()> i_jobFunction);
		void RequestShutdown();
		bool ShutdownRequested();
	};

}

