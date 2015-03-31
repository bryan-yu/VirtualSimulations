#pragma once

#include "Point3.h"
#include "Vector3.h"
#include "Matrix3.h"

#include <vector>

namespace AABSEngine
{
	namespace Utility
	{
		/**
		 * @class ITensorCombiner
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class ITensorCombiner
		{
		public:
			void AddData(AABSEngine::Core::Matrix3& iTensor, AABSEngine::Core::Point3& partCog, Decimal mass);

			void SetFinalCOG(const AABSEngine::Core::Point3& cog);

			void ClearITensors();

			void CombineITensors();

			float CalculateTotalMass();

			AABSEngine::Core::Point3 GetFinalCOG() { return m_finalCOG; }

			AABSEngine::Core::Matrix3& GetFinalITensor() { return m_finalITensor; }

		private:
			void CalculateCombinedCOG();

			AABSEngine::Core::Matrix3 m_finalITensor;

			AABSEngine::Core::Point3 m_finalCOG;

			std::vector<AABSEngine::Core::Point3> m_partCOG;

			std::vector<Decimal> m_masses;

			std::vector<AABSEngine::Core::Matrix3> m_iTensors;
		};
	}
}