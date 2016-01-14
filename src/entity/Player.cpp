/*
 * Player.cpp
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#include "Player.h"
#include "../utils/MathHelper.h"
#include "../utils/Debug.h"

#define CAMERA_ROTATION_SPEED 0.9f

Player::Player()
{
	m_entityRenderer = new EntityRenderer(this);
	setPlayer(true);
}

Player::~Player() {

}

void Player::update()
{
	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );

	u32 padButtonHeld = pad->buttonsHeld();

	if ( pad->getY() <= 15.0f )
	{
		this->rotate( Vector3f( -CAMERA_ROTATION_SPEED, 0, 0 )); // top
	}
	else if ( pad->getY() >= rmode->viHeight - 45.0f )
	{
		this->rotate( Vector3f( CAMERA_ROTATION_SPEED, 0, 0 )); // bottom
	}
	else if ( pad->getX() >= rmode->viWidth - 120.0f )
	{
		this->rotate( Vector3f( 0, -CAMERA_ROTATION_SPEED, 0 )); // right
	}
	else if ( pad->getX() <= 120.0f )
	{
		this->rotate( Vector3f( 0, CAMERA_ROTATION_SPEED, 0 )); // left
	}

	if ( padButtonHeld & WPAD_BUTTON_UP )
	{
		moveForward();
	}
	if ( padButtonHeld & WPAD_BUTTON_DOWN )
	{
		moveBackward();
	}
	if ( padButtonHeld & WPAD_BUTTON_LEFT )
	{
		moveLeft();
	}
	if ( padButtonHeld & WPAD_BUTTON_RIGHT )
	{
		moveRight();
	}
}



void Player::moveForward()
{
	m_position = MathHelper::calculateNewWorldPositionByRotation(
			m_rotation.getY(),
			m_position,
			CAMERA_ROTATION_SPEED,
			Vector3f::Forward());
}

void Player::moveBackward()
{
	m_position = MathHelper::calculateNewWorldPositionByRotation(
				m_rotation.getY(),
				m_position,
				CAMERA_ROTATION_SPEED,
				Vector3f::Backward());
}

void Player::moveLeft()
{
	m_position = MathHelper::calculateNewWorldPositionByRotation(
					m_rotation.getY() - 90,
					m_position,
					CAMERA_ROTATION_SPEED,
					Vector3f::Backward());

}

void Player::moveRight()
{

	m_position = MathHelper::calculateNewWorldPositionByRotation(
						m_rotation.getY() + 90,
						m_position,
						CAMERA_ROTATION_SPEED,
						Vector3f::Backward());

}


void Player::rotate( Vector3f rotation )
{
	if ( m_rotation.getX() > 360 )
	{
		m_rotation.setX(m_rotation.getX() - 360);
	}
	else if(m_rotation.getX() < -360)
	{
		m_rotation.setX(m_rotation.getX() + 360);
	}

	if ( m_rotation.getY() > 360 )
	{
		m_rotation.setY(m_rotation.getY() - 360);
	}
	else if(m_rotation.getY() < -360)
	{
		m_rotation.setY(m_rotation.getY() + 360);
	}

	if ( m_rotation.getZ() > 360 )
	{
		m_rotation.setZ(m_rotation.getZ() - 360);
	}
	else if(rotation.getZ() < -360)
	{
		m_rotation.setZ(m_rotation.getZ() + 360);
	}

	m_rotation.setX( m_rotation.getX() + rotation.getX() );
	m_rotation.setY( m_rotation.getY() + rotation.getY() );
	m_rotation.setZ( m_rotation.getZ() + rotation.getZ() );

}
