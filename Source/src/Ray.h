#pragma once

#include "Vector3.h"
#include "Point3.h"

#include "OgreRay.h"
#include "types.h"

namespace AABSEngine
{
	namespace Core
	{
		class SceneManager;
	}

	namespace Rendering
	{
		class Camera;
	}

	namespace AI
	{
		/**
		* @class Ray
		*
		* @brief For ray casting...
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class Ray
		{
		public:	
			Ray(AABSEngine::Core::SceneManager* sceneMgr = 0);

			/**
			** @brief Set ray data
			** @param ray object
			**/
			void SetRayObject(const Ogre::Ray& ogreRay);

			/**
			** @brief Set ray direction
			** @param direction
			**/
			void SetRayHeading(const AABSEngine::Core::Vector3& heading, Decimal t = 1.0);

			/**
			** @brief Set ray direction
			** @param x,y,z directional coordinates
			**/
			void SetRayHeading(Decimal x, Decimal y, Decimal z, Decimal t = 1.0);

			/**
			** @brief Set ray origin
			** @param origin 
			**/
			void SetRayOrigin(const AABSEngine::Core::Point3& origin);

			/**
			** @brief Set ray direction
			** @param x,y,z positional coordinates
			**/
			void SetRayOrigin(Decimal x, Decimal y, Decimal z);

			/**
			** @brief Setup ray cast from aabs camera
			** @param aabs camera
			**/
			void ConfigureFromCamera(AABSEngine::Rendering::Camera* camera, Decimal castDistance = 1.0);

			/**
			** @brief Create the m_raySceneQuery object 
			** @param scene manager object
			**/
			bool ConstructSceneQuery(AABSEngine::Core::SceneManager* sceneMgr);

			/**
			** @brief Destory the m_raySceneQuery object 
			** @param scene manager object
			**/
			bool DestructSceneQuery(AABSEngine::Core::SceneManager* sceneMgr);

			/**
			** @brief Set mask in which this ray scene query can interrogate
			** @param 32 bit mask
			**/
			void SetQueryMask(uint32_t mask);

			/**
			** @brief
			** @param 32 bit mask
			**/
			void SetQueryTypeMask(uint32_t mask);

			/**
			** @brief Execute scene query
			** @return scene query results
			**/
			Ogre::MovableObject* CastQueryForNearestObject();

		private:
			Ray(const Ray& other){}

			Ray& operator=(const Ray& other){return *this;}

			Ogre::RaySceneQuery* m_ogreSceneQuery;
		};
	}
}
