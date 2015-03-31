#pragma once

#include <Windows.h>

namespace AABSEngine
{
	namespace Utility
	{
		/**
		 * @class UpdateRegulator
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class UpdateRegulator
		{
		public:
			void SetUpdatesPerSecond(double updatesPerSecond);

			bool IsReady();

		private:
			double RandInterval()const;
	
			DWORD m_timeInterval;
			DWORD m_nextUpdateTime;
		};
	}
}