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
		 * @class ITensorCalculator
		 * @brief Provides an interface for calculating inertia tensors for discrete point masses based on a set of vertices
		 * Usage: 1) Set body mass total
		 *        2) Set vertices
		 *        3) Call CalculateITensor function
		 *        4) Retrieve inertia tensor via GetFinalITensor() 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class ITensorCalculator
		{
		public:
			typedef std::vector<AABSEngine::Core::Vector3> Vertices;

			virtual void CalculateITensor();
	
			virtual void CalculateCOM();

			AABSEngine::Core::Matrix3& GetBodyITensor();
			
			AABSEngine::Core::Point3& GetBodyCOM();

			AABSEngine::Core::Vector3& GetFirstMomentInertia();

			void SetVertices(Vertices& vtx);

			void SetBodyMass(Decimal bodyMass);

			void ClearCache();

			static AABSEngine::Core::Matrix3 CreateCuboidITensor(const AABSEngine::Core::Vector3& extent, Decimal objectMass);

			static AABSEngine::Core::Matrix3 CreateSphereITensor(Decimal radius, Decimal pointMass);
			
			static AABSEngine::Core::Matrix3 CreateCylinderITensor(Decimal radius, Decimal height, Decimal objectMass);

			static AABSEngine::Core::Matrix3 CreateElipsoidITensor(Decimal radiusX, Decimal radiusY, Decimal radiusZ, Decimal pointMass);
	
		protected:
			Vertices m_vertices;

			Decimal m_bodyMass;
			Decimal m_pointMass;

			AABSEngine::Core::Vector3 m_firstMomentInertia;
			AABSEngine::Core::Point3 m_centerOfMass;
			AABSEngine::Core::Matrix3 m_iTensor;
		};
	}
}