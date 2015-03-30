#pragma once

#include "OgreSceneNode.h"

namespace AABSEngine
{
	namespace Helper
	{
		template<class Type>
		Type* CastSpecificFromAny(Ogre::SceneNode* node, std::string name)
		{
			return Ogre::any_cast<Type*>(node->getUserObjectBindings().getUserAny(name));
		}

		template<class Type>
		Type* CastSpecificFromAny(Ogre::SceneNode* node)
		{
			return node->getUserAny().get<Type*>();
		}

		class BitMaskManager
		{
		public:
			 
		};
	}
}