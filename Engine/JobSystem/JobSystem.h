#pragma once
#include <functional>
#include <string>

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

		void CreateQueue(std::string i_queueName, unsigned int i_numRunners);
		bool HasJobs(const std::string& i_queueName);
		void AddRunner(const std::string& i_queueName);
		
		void RunJob(const std::string i_queueName, std::function<void()> i_jobFunction);
		void RequestShutdown();
		bool ShutdownRequested();
	};

}

