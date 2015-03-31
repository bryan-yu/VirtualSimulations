#ifndef PLAYER_H
#define PLAYER_H

#include "Ray.h"
#include "IMovable.h"
#include "Camera.h"
#include "Object.h"
#include "InputUser.h"
#include "InputCallback.h"
#include "types.h"
#include "RigidBody.h"

namespace AABSEngine
{
	namespace Input
	{
		class InputManager;
	}

	namespace Rendering
	{
		class MouseCursor;
	}
}

/**
* @class Player
*
* @brief The main player class
*
* @author AABS
* @version X
* @date October 2013
*
*/
class Player : public AABSEngine::Core::GameObject, public AABSEngine::Core::IMovable, public AABSEngine::Core::InputUser<Player>
{
	

public:

	/**
	 * @brief default constructor
	 */
	Player();

	/**
	 * @brief default deconstructor
	 */
	~Player();

	/**
	 * @brief set movement speed
	 */
	void SetMoveSpeed(float movespeed);

	/**
	 * @brief set the attached camera
	 */
	void SetCamera(AABSEngine::Rendering::Camera *cam);

	/**
	 * @brief stop the player's velocity
	 */
	void ResetVelocity();

	/**
	 * @brief get the player's position - to update the camera
	 */
	AABSEngine::Core::Point3 GetPosition();

	//IMovable functions that need to be implemented
	virtual void MoveUp();
	virtual void MoveDown();
	virtual void MoveForward();
	virtual void MoveBackward();
	virtual void StrafeLeft();
	virtual void StrafeRight();
	virtual void RotateLeft();
	virtual void RotateRight();
	virtual void Rotate(int deltax, int deltay);

	/**
	** @brief Get visual ray for picking
	**/
	AABSEngine::AI::Ray* GetVisualRay();

	/**
	** @brief Search world 
	**/
	AABSEngine::Core::GameObject* SearchWorld(uint32_t searchMask);


	/**
	 * @brief locked a rigidbody object as if to pick up this object
	 */
	void PickUpObject(AABSEngine::Core::GameObject *target);

	/**
	 * @brief drop the rigidbody object
	 */
	AABSEngine::Physics::RigidBody* DropObject();

	/**
	 * @brief check if the player is holding an object or not
	 */
	bool IsHoldingObject();

	/**
	 * @brief set a target when the player picks up an object 
	 */
	void SetTarget(AABSEngine::Core::GameObject *target);

	/**
	 * @brief set a target when the player picks up an object 
	 */
	AABSEngine::Core::GameObject* GetTarget() const;

	/**
	 * @brief update the player when he is picking up object
	 */
	void Update();

private:
	float m_moveSpeed;

	AABSEngine::AI::Ray m_visualRay;
	AABSEngine::Rendering::Camera *m_camera;

	bool m_isHoldingObject; ///< flag for the player if holding an object
	AABSEngine::Core::GameObject *m_pickedObject; ///< the rigidBody object being picked
	AABSEngine::Core::Point3 m_prevObjectLocation;

	AABSEngine::Core::GameObject *m_target; ///< the player's target
};



#endif