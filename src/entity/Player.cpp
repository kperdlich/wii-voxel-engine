/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#include "Player.h"
#include "../utils/MathHelper.h"
#include "../utils/Debug.h"

#define ROTATION_SPEED 50.0f
#define MOVEMENT_SPEED 5.0f
#define PITCH_MAX 90.0f


CPlayer::CPlayer()
{
	m_entityRenderer = new EntityRenderer(this);
    m_pInventory = new PlayerInventory();
	SetPlayer(true);
}

CPlayer::~CPlayer()
{
    delete m_pInventory;
}

void CPlayer::Update(float deltaSeconds)
{
    WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID( WII_PAD_0 );

	u32 padButtonHeld = pad->ButtonsHeld();
	u32 padButtonDown = pad->ButtonsDown();

#ifdef DEBUG
	auto pChunk = m_pWorld->GetChunkByWorldPosition( m_position );
	if ( pChunk )
    {		
        LOG( "Current Chunk: %d/%d/%d", (uint32_t) pChunk->GetCenterPosition().GetX(), (uint32_t) pChunk->GetCenterPosition().GetY(), (uint32_t) pChunk->GetCenterPosition().GetZ()  );
	}
#endif


	if ( pad->GetY() <= 15.0f )
	{
        Rotate( Vector3( -ROTATION_SPEED * deltaSeconds, 0, 0 )); // top
	}
	else if ( pad->GetY() >= rmode->viHeight - 45.0f )
	{
        Rotate( Vector3( ROTATION_SPEED * deltaSeconds, 0, 0 )); // bottom
	}

	if ( pad->GetX() >= rmode->viWidth - 120.0f )
	{
        Rotate( Vector3( 0, -ROTATION_SPEED * deltaSeconds, 0 )); // right
	}
	else if ( pad->GetX() <= 120.0f )
	{
        Rotate( Vector3( 0, ROTATION_SPEED * deltaSeconds, 0 )); // left
	}

    float playerY = m_position.GetY();

    Move(-(pad->GetNunchukAngleX()), -(pad->GetNunchukAngleY()), deltaSeconds);

	// shity physics
    Vector3 blockPositionUnderPlayer(m_position.GetX() + BLOCK_SIZE_HALF, playerY, m_position.GetZ() + BLOCK_SIZE_HALF);
	Vector3 newPosition = m_pWorld->GetNewPlayerPosition(blockPositionUnderPlayer);
	m_position.SetY(newPosition.GetY() + (2 * BLOCK_SIZE));


    Vector3 focusedBlockPos = MathHelper::CalculateNewWorldPositionByRotation(m_rotation,
                                Vector3(m_position.GetX() + BLOCK_SIZE_HALF, m_position.GetY(), m_position.GetZ() + BLOCK_SIZE_HALF),
                                -2*BLOCK_SIZE);

	m_pWorld->UpdateFocusedBlockByWorldPosition(focusedBlockPos);

	if ( padButtonDown & WPAD_BUTTON_B)
	{
		m_pWorld->RemoveBlockByWorldPosition( focusedBlockPos );
	}

	if ( padButtonDown & WPAD_BUTTON_A)
	{
		m_pWorld->AddBlockAtWorldPosition(focusedBlockPos, BlockType::DIRT );
	}

	// todo move to non-player related place
	if ( padButtonDown & WPAD_BUTTON_HOME)
	{
        Engine::Get().End();
	}

	UpdateInventory();

}

void CPlayer::UpdateInventory()
{
    WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID( WII_PAD_0 );

	u32 padButtonHeld = pad->ButtonsHeld();
	u32 padButtonDown = pad->ButtonsDown();


	if ( padButtonDown & WPAD_BUTTON_LEFT)
	{

	}

	if ( padButtonDown & WPAD_BUTTON_RIGHT )
	{

	}


}

void CPlayer::Move(float x, float y, float deltaSeconds)
{
	if ( y != 0.0f)
	{
		m_position = MathHelper::CalculateNewWorldPositionByRotation(
					m_rotation.GetY(),
					m_position,
                    y * MOVEMENT_SPEED * deltaSeconds);
	}

	if ( x != 0.0f)
	{
		float strafeValue = 0.0f;

		if ( x > 0 )
		{
			strafeValue = -90;
		}
		else if ( x < 0)
		{
			strafeValue = 90;
		}

		m_position = MathHelper::CalculateNewWorldPositionByRotation(
					m_rotation.GetY() + strafeValue,
					m_position,
                    fabs(x) * MOVEMENT_SPEED * deltaSeconds);
	}
}


void CPlayer::Rotate( const Vector3& rotation )
{
	if ( m_rotation.GetY() > 360 )
	{
		m_rotation.SetY(m_rotation.GetY() - 360);
	}
    else if(m_rotation.GetY() < 0)
	{
		m_rotation.SetY(m_rotation.GetY() + 360);
	}

	if ( m_rotation.GetZ() > 360 )
	{
		m_rotation.SetZ(m_rotation.GetZ() - 360);
	}
    else if(rotation.GetZ() < 0)
	{
		m_rotation.SetZ(m_rotation.GetZ() + 360);
	}

	m_rotation += rotation;
    m_rotation.SetX(MathHelper::Clamp(m_rotation.GetX(), -PITCH_MAX, PITCH_MAX));
}

void CPlayer::AddToInventory(IEquipable& item)
{
    m_pInventory->AddToInventory(item);
}
