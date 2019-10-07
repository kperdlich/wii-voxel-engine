/***
 *
 * Copyright (C) 2018 DaeFennek
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

#include <string>
#include "net/ServerConnection.h"
#include "net/packet/PacketGlobals.h"
#include "net/packet/PacketKeepAlive.h"
#include "net/packet/PacketHandshake.h"
#include "net/packet/PacketLogin.h"
#include "net/packet/PacketSpawnPosition.h"
#include "net/packet/PacketPlayerAbilites.h"
#include "net/packet/PacketTimeUpdate.h"
#include "net/packet/PacketChatMessage.h"
#include "net/packet/PacketChunkAllocation.h"
#include "net/packet/PacketSpawnDroppedItem.h"
#include "net/packet/PacketEntityEquipment.h"
#include "net/packet/PacketUseEntity.h"
#include "net/packet/PacketUpdateHealth.h"
#include "net/packet/PacketRespawn.h"
#include "net/packet/PacketPlayer.h"
#include "net/packet/PacketPlayerPosition.h"
#include "net/packet/PacketPlayerLook.h"
#include "net/packet/PacketPlayerPositionAndLook.h"
#include "net/packet/PacketPlayerDigging.h"
#include "net/packet/PacketPlayerBlockPlacement.h"
#include "net/packet/PacketHeldItemChange.h"
#include "net/packet/PacketUseBed.h"
#include "net/packet/PacketAnimation.h"
#include "net/packet/PacketEntityAction.h"
#include "net/packet/PacketSpawnNamedEntity.h"
#include "net/packet/PacketCollectItem.h"
#include "net/packet/PacketSpawnObject.h"
#include "net/packet/PacketSpawnMob.h"
#include "net/packet/PacketSpawnPainting.h"
#include "net/packet/PacketSpawnExperienceOrb.h"
#include "net/packet/PacketEntityVelocity.h"
#include "net/packet/PacketDestroyEntity.h"
#include "net/packet/PacketEntity.h"
#include "net/packet/PacketEntityRelativeMove.h"
#include "net/packet/PacketEntityLook.h"
#include "net/packet/PacketEntityLookAndRelativeMove.h"
#include "net/packet/PacketEntityTeleport.h"
#include "net/packet/PacketEntityHeadLook.h"
#include "net/packet/PacketEntityStatus.h"
#include "net/packet/PacketAttachEntity.h"
#include "net/packet/PacketEntityMetadata.h"
#include "net/packet/PacketEntityEffect.h"
#include "net/packet/PacketRemoveEntityEffect.h"
#include "net/packet/PacketSetExperience.h"
#include "net/packet/PacketChunkData.h"
#include "net/packet/PacketMultiBlockChange.h"
#include "net/packet/PacketBlockChange.h"
#include "net/packet/PacketBlockAction.h"
#include "net/packet/PacketExplosion.h"
#include "net/packet/PacketSoundEffect.h"
#include "net/packet/PacketChangeGameState.h"
#include "net/packet/PacketThunderbolt.h"
#include "net/packet/PacketOpenWindow.h"
#include "net/packet/PacketCloseWindow.h"
#include "net/packet/PacketClickWindow.h"
#include "net/packet/PacketSetSlot.h"
#include "net/packet/PacketSetWindowItems.h"
#include "net/packet/PacketUpdateWindowProperty.h"
#include "net/packet/PacketConfirmTransaction.h"
#include "net/packet/PacketCreativeInventoryAction.h"
#include "net/packet/PacketEnchantItem.h"
#include "net/packet/PacketUpdateSign.h"
#include "net/packet/PacketItemData.h"
#include "net/packet/PacketUpdateTileEntity.h"
#include "net/packet/PacketIncrementStatistic.h"
#include "net/packet/PacketPlayerListItem.h"
#include "net/packet/PacketPluginMessage.h"
#include "net/packet/PacketServerListPing.h"
#include "net/packet/PacketDisconnect.h"

std::map<unsigned char, class Packet*> ServerConnection::s_PacketMap;

ServerConnection::ServerConnection()
{
    InitPacketMap();
}

void ServerConnection::InitPacketMap()
{
    if (!s_PacketMap.empty())
        return;

    // Register all s2c packets here:
    s_PacketMap[PACKET_KEEP_ALIVE] = new PacketKeepAlive();
    s_PacketMap[PACKET_HANDSHAKE] = new PacketHandshake();
    s_PacketMap[PACKET_LOGIN] = new PacketLogin();
    s_PacketMap[PACKET_SPAWN_POSITION] = new PacketSpawnPosition();
    s_PacketMap[PACKET_PLAYER_ABILITIES] = new PacketPlayerAbilites();
    s_PacketMap[PACKET_TIME_UPDATE] = new PacketTimeUpdate();
    s_PacketMap[PACKET_CHAT_MESSAGE] = new PacketChatMessage();
    s_PacketMap[PACKET_CHUNK_ALLOCATION] = new PacketChunkAllocation();
    s_PacketMap[PACKET_SPAWN_DROPPED_ITEM] = new PacketSpawnDroppedItem();
    s_PacketMap[PACKET_ENTITY_EQUIPMENT] = new PacketEntityEquipment();
    s_PacketMap[PACKET_USE_ENTITY] = new PacketUseEntity();
    s_PacketMap[PACKET_UPDATE_HEALTH] = new PacketUpdateHealth();
    s_PacketMap[PACKET_RESPAWN] = new PacketRespawn();
    s_PacketMap[PACKET_PLAYER] = new PacketPlayer();
    s_PacketMap[PACKET_PLAYER_POSITION] = new PacketPlayerPosition();
    s_PacketMap[PACKET_PLAYER_LOOK] = new PacketPlayerLook();
    s_PacketMap[PACKET_PLAYER_POSITION_AND_LOOK] = new PacketPlayerPositionAndLook();
    s_PacketMap[PACKET_PLAYER_DIGGING] = new PacketPlayerDigging();
    //s_PacketMap[PACKET_PLAYER_BLOCK_PLACEMENT] = new PacketPlayerBlockPlacement();
    s_PacketMap[PACKET_HELD_ITEM_CHANGE] = new PacketHeldItemChange();
    s_PacketMap[PACKET_USE_BED] = new PacketUseBed();
    s_PacketMap[PACKET_ANIMATION] = new PacketAnimation();
    s_PacketMap[PACKET_ENTITY_ACTION] = new PacketEntityAction();
    s_PacketMap[PACKET_SPAWN_NAMED_ENTITY] = new PacketSpawnNamedEntity();
    s_PacketMap[PACKET_COLLECT_ITEM] = new PacketCollectItem();
    s_PacketMap[PACKET_SPAWN_OBJECT] = new PacketSpawnObject();
    //s_PacketMap[PACKET_SPAWN_MOB] = new PacketSpawnMob();
    s_PacketMap[PACKET_SPAWN_PAINTING] = new PacketSpawnPainting();
    s_PacketMap[PACKET_SPAWN_EXPERIENCE_ORB] = new PacketSpawnExperienceOrb();
    s_PacketMap[PACKET_ENTITY_VELOCITY] = new PacketEntityVelocity();
    s_PacketMap[PACKET_DESTROY_ENTITY] = new PacketDestroyEntity();
    s_PacketMap[PACKET_ENTITY] = new PacketEntity();
    s_PacketMap[PACKET_ENTITY_RELATIVE_MOVE] = new PacketEntityRelativeMove();
    s_PacketMap[PACKET_ENTITY_LOOK] = new PacketEntityLook();
    s_PacketMap[PACKET_ENTITY_LOOK_RELATIVE_MOVE] = new PacketEntityLookAndRelativeMove();
    s_PacketMap[PACKET_ENTITY_TELEPORT] = new PacketEntityTeleport();
    s_PacketMap[PACKET_ENTITY_HEAD_LOOK] = new PacketEntityHeadLook();
    s_PacketMap[PACKET_ENTITY_STATUS] = new PacketEntityStatus();
    s_PacketMap[PACKET_ATTACH_ENTITY] = new PacketAttachEntity();
    //s_PacketMap[PACKET_ENTITY_METADATA] = new PacketEntityMetadata();
    s_PacketMap[PACKET_ENTITY_EFFECT] = new PacketEntityEffect();
    s_PacketMap[PACKET_REMOVE_ENTITY_EFFECT] = new PacketRemoveEntityEffect();
    s_PacketMap[PACKET_SET_EXPERIENCE] = new PacketSetExperience();
    s_PacketMap[PACKET_CHUNK_DATA] = new PacketChunkData();
    s_PacketMap[PACKET_MULTI_BLOCK_CHANGE] = new PacketMultiBlockChange();
    s_PacketMap[PACKET_BLOCK_CHANGE] = new PacketBlockChange();
    s_PacketMap[PACKET_BLOCK_ACTION] = new PacketBlockAction();
    s_PacketMap[PACKET_EXPLOSION] = new PacketExplosion();
    s_PacketMap[PACKET_SOUND_EFFECT] = new PacketSoundEffect();
    s_PacketMap[PACKET_CHANGE_GAME_STATE] = new PacketChangeGameState();
    s_PacketMap[PACKET_THUNDERBOLT] = new PacketThunderbolt();
    s_PacketMap[PACKET_OPEN_WINDOW] = new PacketOpenWindow();
    s_PacketMap[PACKET_CLOSE_WINDOW] = new PacketCloseWindow();
    //s_PacketMap[PACKET_CLICK_WINDOW] = new PacketClickWindow();
    s_PacketMap[PACKET_SET_SLOT] = new PacketSetSlot();
    s_PacketMap[PACKET_SET_WINDOW_ITEMS] = new PacketSetWindowItems();
    s_PacketMap[PACKET_UPDATE_WINDOW_PROPERTY] = new PacketUpdateWindowProperty();
    s_PacketMap[PACKET_CONFIRM_TRANSACTION] = new PacketConfirmTransaction();
    s_PacketMap[PACKET_CREATIVE_INVENTORY_ACTION] = new PacketCreativeInventoryAction();
    s_PacketMap[PACKET_ENCHANT_ITEM] = new PacketEnchantItem();
    s_PacketMap[PACKET_UPDATE_SIGN] = new PacketUpdateSign();
    s_PacketMap[PACKET_ITEM_DATA] = new PacketItemData();
    s_PacketMap[PACKET_UPDATE_TILE_ENTITY] = new PacketUpdateTileEntity();
    s_PacketMap[PACKET_INCREMENT_STATISTICS] = new PacketIncrementStatistic();
    s_PacketMap[PACKET_PLAYER_LIST_ITEM] = new PacketPlayerListItem();
    s_PacketMap[PACKET_PLUGIN_MESSAGE] = new PacketPluginMessage();
    s_PacketMap[PACKET_SERVER_LIST_PING] = new PacketServerListPing();
    s_PacketMap[PACKET_DISCONNECT] = new PacketDisconnect();
}

void ServerConnection::DestroyPacketMap()
{
    for (auto it = s_PacketMap.begin(); it != s_PacketMap.end(); ++it)
        delete it->second;
    s_PacketMap.clear();
}

Packet* ServerConnection::CreatePacketByID(char id)
{
    auto it = s_PacketMap.find(id);
    if (it != s_PacketMap.end())
    {
        return it->second->CreateInstance();
    }

    return nullptr;
}

void ServerConnection::DestroyQueue()
{
    while(!m_queue.IsEmpty())
        delete m_queue.Pop();
}

bool ServerConnection::Connect(const std::string &ip, uint16_t port)
{
    if (m_socket.Connect(ip, port))
    {
        return Start() == 0;
    }
    return false;
}

void ServerConnection::Destroy()
{
    Stop();
    m_socket.Disconnect();
    DestroyPacketMap();
    DestroyQueue();
}

void ServerConnection::PreExecute()
{
    while(true)
    {
        if (IsStopped())
            break;
        else
            Execute();
    }
}

void ServerConnection::Execute()
{
    char packetID = m_socket.Read<char>();
    Packet* p = CreatePacketByID(packetID);
    if (p && packetID != PACKET_DISCONNECT)
    {
        //LOG("Parse packetID %x", packetID);
        p->Read(m_socket);
        m_queue.Push(p);
    }
    else
    {
        //m_Socket.Close();
        if (packetID == PACKET_DISCONNECT)
            ERROR("Disconnected by server. Stop Packet reader");
        else
        {
            /*char buffer[20];
            buffer[19] = '\0';
            for (uint16_t i = 0; i < 19; ++i)
                buffer[i] = m_Socket.Read<char>();*/

            ERROR("Couldn't find/create instance of packetID %x. Stop Packet reader", packetID);
            //ERROR("Data: %s", buffer);
        }

        Engine::Get().End();
        Suspend();
    }
}
