/*
 * Player.cpp
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#include "Player.h"
#include "../utils/MathHelper.h"
#include "../utils/Debug.h"

#define CAMERA_ROTATION_SPEED 0.2f

Player::Player( Camera* playerCamera ) : m_pCamera( playerCamera )
{
	m_entityRenderer = new EntityRenderer(this);
	setPlayer(true);
}

Player::~Player() {

}

void Player::update() {
	static float oldX;

	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );

	// update camera angle
	if ( pad->getX() > oldX)
	{
		this->rotate( Vector3f( 0, -0.9f, 0 ));
	}
	else if ( pad->getX() < oldX )
	{
		this->rotate( Vector3f( 0, 0.9f, 0 ));
	}

	oldX = pad->getX();

	if ( pad->buttonsHeld() & WPAD_BUTTON_UP )
	{
		moveForward();
	}
	if ( pad->buttonsHeld() & WPAD_BUTTON_DOWN )
	{
		moveBackward();
	}
	if ( pad->buttonsHeld() & WPAD_BUTTON_LEFT )
	{
		moveLeft();
	}
	if ( pad->buttonsHeld() & WPAD_BUTTON_RIGHT )
	{
		moveRight();
	}
}

void Player::moveForward()
{

	m_pCamera->setWorldPosititon( MathHelper::calculateNewWorldPositionByRotation(
									m_pCamera->getWorldAngleY(),
									getWorldPosition(),
									CAMERA_ROTATION_SPEED,
									Vector3f::Forward()));
}

void Player::moveBackward()
{
	m_pCamera->setWorldPosititon( MathHelper::calculateNewWorldPositionByRotation(
									m_pCamera->getWorldAngleY(),
									getWorldPosition(),
									CAMERA_ROTATION_SPEED,
									Vector3f::Backward()));
}

void Player::moveLeft()
{
	m_pCamera->setWorldPosititon( MathHelper::calculateNewWorldPositionByRotation(
									m_pCamera->getWorldAngleY() - 90,
									getWorldPosition(),
									CAMERA_ROTATION_SPEED,
									Vector3f::Backward()));
}

void Player::moveRight()
{
	m_pCamera->setWorldPosititon( MathHelper::calculateNewWorldPositionByRotation(
									m_pCamera->getWorldAngleY() + 90,
									getWorldPosition(),
									CAMERA_ROTATION_SPEED,
									Vector3f::Backward()));

}


void Player::rotate( Vector3f rotation )
{
	m_pCamera->setWorldAngle( Vector3f(	getWorldAngle().getX() + rotation.getX(),
										getWorldAngle().getY() + rotation.getY(),
										getWorldAngle().getZ() + rotation.getZ()) );
}


Vector3f Player::getWorldAngle()
{
	return m_pCamera->getWorldAngle();
}

Vector3f Player::getWorldPosition()
{
	return m_pCamera->getWorldPosition();
}
