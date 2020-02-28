#include "JobSystem.h"
namespace Engine
{
	namespace JobSystem
	{

		bool shutdownSet = false;

		bool ShutdownRequested()
		{
			shutdownSet = true;
		}
	} //namespace JobSystem
} //namespace Engine