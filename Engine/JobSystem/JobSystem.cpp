#include "JobSystem.h"
#include <map>
#include <string>
#include "JobQueue.h"
namespace Engine
{
	namespace JobSystem
	{

		bool shutdownSet = false;
		std::map<std::string, JobQueue*> allQueues;

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