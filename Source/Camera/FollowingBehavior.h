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
		Following
	} state = State::Free;

	FollowingBehavior(FreePhysics& physic)
		:
		ownersPhysic(&physic)
	{
		maxSpeed = 350.f;
		maxAcc = maxSpeed;

		retardationDist = 400.f;
		catchDist = 0.f;

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

	void changeStateToFollowing()
	{
		state = State::Following;
	}

	void changeStateToFree()
	{
		stopObj();
		state = State::Free;
	}


private:

	const Planet* target{nullptr};
	FreePhysics* ownersPhysic{nullptr};

	float maxSpeed;
	float maxAcc;

	float retardationDist;
	float catchDist;

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
		/*
		const auto pos = ownersPhysic->pos;

		auto distVec = target->getPosition() - pos;

		auto desire = makeDesire(distVec);

		auto force = makeForce(desire);

		ownersPhysic->acc += force;

		ownersPhysic->vel.limit(maxSpeed);

		handleCatching();
		*/

		ownersPhysic->pos = target->getPosition();
	}

	Vec2 makeDesire(Vec2& distVec)
	{
		const float distSqr = distVec.getLenSq();

		float mag = maxSpeed;
		if (isInRadius(distSqr, retardationDist))
		{
			float dist = sqrt(distSqr);
			mag = map(dist, 0.f, retardationDist, 0.f, maxSpeed);
		}

		Vec2 desire = distVec;

		desire.setLen(mag);
		return desire;
	}

	bool isInRadius(Vec2 distVec, float radius)
	{
		float distSqr = distVec.getLenSq();
		return isInRadius(distSqr, radius);
	}
	bool isInRadius(float distSqr, float radius)
	{
		return distSqr < pow(radius, 2);
	}

	Vec2 makeForce(const Vec2& desire)
	{
		const auto vel = ownersPhysic->vel;
		auto force = desire - vel;
		force.limit(maxAcc);
		return force;
	}

	void handleCatching()
	{
		Vec2 distVec = ownersPhysic->pos - target->getPosition();

		const float distSqr = distVec.getLenSq();

		if (!isInRadius(distSqr, catchDist))
		{
			auto maxDistVec = distVec;
			maxDistVec.setLen(catchDist);

			auto newPos = (target->getPosition() + maxDistVec);

			ownersPhysic->pos = newPos;
		}

		if (distSqr < 1.f)
		{
			ownersPhysic->vel *= 0.f;
		}
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

	void goToTarget(float dt)
	{
		const float dist = getDistToTarget();

		float d = (dist / holdTime);
		holdTime -= dt;

		auto newVel = target->getPosition() - ownersPhysic->pos;

		newVel.setLen(d);
		ownersPhysic->vel = newVel;
		ownersPhysic->acc *= 0.f;

		if (holdTime <= 0.f) changeStateToFollowing();
	}

};