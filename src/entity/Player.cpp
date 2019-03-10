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
#include "../net/packet/PacketPlayerPosition.h"

#define ROTATION_SPEED 70.0f
#define MOVEMENT_SPEED 4.0f
#define PITCH_MAX 90.0f

constexpr float MAX_JUMP_HIGHT = 1.3f;
constexpr float PLAYER_GRAVITY = 4.0f;


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

    u32 padButtonDown = pad->ButtonsDown();

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

    const double playerY = m_position.GetY();

    Vector3 newPlayerPos = Move(-(pad->GetNunchukAngleX()), -(pad->GetNunchukAngleY()), deltaSeconds);
    newPlayerPos.SetY(playerY);

	// shity physics
    if (m_bPlayerSpawned)
    {
        const Vector3 blockPositionBeneathPlayer(newPlayerPos.GetX() + BLOCK_SIZE_HALF, newPlayerPos.GetY() - BLOCK_SIZE_HALF , newPlayerPos.GetZ() + BLOCK_SIZE_HALF);
        const BlockType blockTypeBeneathPlayer = m_pWorld->GetBlockByWorldPosition(blockPositionBeneathPlayer);
        const Vector3 blockPositionNewPlayerDirection(newPlayerPos.GetX() + BLOCK_SIZE_HALF, newPlayerPos.GetY() , newPlayerPos.GetZ() + BLOCK_SIZE_HALF);
        const BlockType blockTypeNewPlayerDirection = m_pWorld->GetBlockByWorldPosition(blockPositionNewPlayerDirection);

        if (blockTypeNewPlayerDirection == BlockType::AIR)
            m_position = newPlayerPos;

        if (blockTypeBeneathPlayer == BlockType::AIR && !m_bIsPlayerJumping)
        {
            m_position.SetY(m_position.GetY() - (PLAYER_GRAVITY * deltaSeconds));
        }

        if (m_bIsPlayerJumping)
        {
            static float direction = 1.0f;
            float jumpImpulse = (MAX_JUMP_HIGHT * deltaSeconds) * direction * PLAYER_GRAVITY;
            if (m_playerJumpOffset + jumpImpulse >= MAX_JUMP_HIGHT)
            {
                direction *= -1;
                jumpImpulse = MAX_JUMP_HIGHT - m_playerJumpOffset;
            }
            else if (m_playerJumpOffset + jumpImpulse <= 0.0f)
            {
                m_bIsPlayerJumping = false;
                direction = 1.0f;
                jumpImpulse = -m_playerJumpOffset;
            }
            m_playerJumpOffset += jumpImpulse;
            const Vector3 blockPositionUnderPlayer(m_position.GetX() + BLOCK_SIZE_HALF, m_position.GetY(), m_position.GetZ() + BLOCK_SIZE_HALF);
            const BlockType blockType = m_pWorld->GetBlockByWorldPosition(blockPositionUnderPlayer);
            if (blockType == BlockType::AIR)
            {
                m_position.SetY(m_position.GetY() + jumpImpulse);
            }
            else
            {
                const Vector3 newPlayerPos = m_pWorld->GetBlockPositionByWorldPosition(blockPositionUnderPlayer);
                m_position.SetY(newPlayerPos.GetY() + BLOCK_SIZE);
                m_bIsPlayerJumping = false;
                direction = 1.0f;
                m_playerJumpOffset = .0;
            }

        }
    }

    Vector3 focusedBlockPos = MathHelper::CalculateNewWorldPositionByRotation(m_rotation,
                                Vector3(m_position.GetX() + BLOCK_SIZE_HALF, m_position.GetY() + BLOCK_SIZE, m_position.GetZ() + BLOCK_SIZE_HALF),
                                -2*BLOCK_SIZE);


	m_pWorld->UpdateFocusedBlockByWorldPosition(focusedBlockPos);

	if ( padButtonDown & WPAD_BUTTON_B)
	{
        m_pWorld->RemoveBlockByWorldPosition(focusedBlockPos);
	}

    if ( padButtonDown & WPAD_NUNCHUK_BUTTON_Z)
	{
		m_pWorld->AddBlockAtWorldPosition(focusedBlockPos, BlockType::DIRT );
	}	


    if ((padButtonDown & WPAD_BUTTON_A) && !m_bIsPlayerJumping)
    {
        // jump
        m_bIsPlayerJumping = true;
    }

	UpdateInventory();


    if (m_bPlayerSpawned && (m_LastPlayerServerUpdate - ticks_to_millisecs(gettime())) > 10)
    {
        static double stanceOffset = .3, headOffset = BLOCK_SIZE, xOffset = 0.0, yOffset = .7;
        WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID( WII_PAD_0 );
        u32 padButtonHeld = pad->ButtonsHeld();
        u32 padButtonDown = pad->ButtonsDown();

        if ( padButtonDown & WPAD_BUTTON_LEFT)
        {            
            xOffset -= 0.01;
        }

        if ( padButtonDown & WPAD_BUTTON_RIGHT )
        {
            xOffset += 0.01;
        }

        if ( padButtonDown & WPAD_BUTTON_UP)
        {
            yOffset += 0.01;
        }

        if ( padButtonDown & WPAD_BUTTON_DOWN )
        {
            yOffset -= 0.01;
        }

        //LOG("OffsetX: %f, OffsetY: %f", xOffset, yOffset);

        double serverPlayerY =m_position.GetY() - headOffset;
        double serverPlayerStance = (m_position.GetY() - headOffset + stanceOffset);
        //double serverPlayerY = playerHeadDelta > 0 ? m_position.GetY() : m_position.GetY() - headOffset;
        //double serverPlayerStance = playerHeadDelta > 0 ? m_position.GetY() + stanceOffset : (m_position.GetY() - headOffset + stanceOffset);
        PacketPlayerPosition p{m_position.GetX() +xOffset, serverPlayerY, m_position.GetZ() + yOffset, serverPlayerStance, m_bOnTheGround};
        //p.Send();
        m_LastPlayerServerUpdate = ticks_to_millisecs(gettime());
    }
}

void CPlayer::UpdateInventory()
{

}

Vector3 CPlayer::Move(float x, float y, float deltaSeconds)
{
    Vector3 pos{m_position};
    if ( y != 0.0f)
    {
        pos = MathHelper::CalculateNewWorldPositionByRotation(
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

        pos = MathHelper::CalculateNewWorldPositionByRotation(
					m_rotation.GetY() + strafeValue,
                    pos,
                    fabs(x) * MOVEMENT_SPEED * deltaSeconds);
	}
    return pos;
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
