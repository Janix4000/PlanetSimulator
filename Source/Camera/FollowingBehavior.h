#pragma once

#include "../Objects/FreePhysics.h"
#include "../Objects/Planet.h"

class FollowingBehavior
{
public:

	enum class State
	{
		Free,
		Going,
		OnlyGoing,
		Following
	} state = State::Free;

	FollowingBehavior(FreePhysics& physic)
		:
		ownersPhysic(&physic)
	{
		holdTime = timeToArrive;
	}

	void update(float dt)
	{
		switch (state)
		{
		case State::Following:
			followTarget();
			break;
		case State::Going:
		case State::OnlyGoing:
			goToTarget(dt);
			break;
		}
	}

	void setTarget(const Planet& newTarget)
	{
		if (&newTarget != target)
		{
			target = &newTarget;

			changeStateToGoing();
		}
	}

	void changeStateToGoing()
	{
		resetHoldTime();
		state = State::Going;
	}

	void goTo(const Planet& newTarget)
	{
		if (&newTarget != target)
		{
			target = &newTarget;

			changeStateToGoingOnly();
		}
	}

	void changeStateToGoingOnly()
	{
		resetHoldTime();
		state = State::OnlyGoing;
	}

	void changeStateToFollowing()
	{
		state = State::Following;
	}

	void changeStateToFree()
	{
		stopObj();
		target = { nullptr };
		state = State::Free;
	}


private:

	const Planet* target{nullptr};
	FreePhysics* ownersPhysic{nullptr};

	void goToTarget(float dt)
	{
		const float dist = getDistToTarget();

		float d = (dist / holdTime);
		holdTime -= dt;

		auto newVel = target->getPosition() - ownersPhysic->pos;

		newVel.setLen(d);
		ownersPhysic->vel = newVel;
		ownersPhysic->acc *= 0.f;

		if (holdTime <= 0.f)
		{
			if (state == State::Going)
			{
				changeStateToFollowing();
			}
			else if (state == State::OnlyGoing)
			{
				changeStateToFree();
			}
		}
	}

	void resetHoldTime()
	{
		holdTime = timeToArrive;
	}

	void stopObj()
	{
		ownersPhysic->vel *= 0.f;
		ownersPhysic->acc *= 0.f;
	}

	void followTarget()
	{
		ownersPhysic->pos = target->getPosition();
		stopObj();
	}


	float getDistSqToTarget() const
	{
		auto distVec = ownersPhysic->pos - target->getPosition();
		return distVec.getLenSq();
	}

	float getDistToTarget() const
	{
		return sqrt(getDistSqToTarget());
	}


	const float timeToArrive = 0.5f;
	float holdTime = timeToArrive;

	

};