#include <malloc.h>
#include <cstring>
#include <ogcsys.h>
#include "renderer/displaylist.h"

DisplayList::DisplayList() {}

DisplayList::~DisplayList()
{
    Clear();
}

void DisplayList::Render() const
{
    if ( m_displayListSize > 0 )
    {
        GX_CallDispList(m_pDispList, m_displayListSize);
    }
}

void DisplayList::Begin(size_t sizeOfDisplayList)
{
    m_pDispList = memalign(32, sizeOfDisplayList);
    memset(m_pDispList, 0, sizeOfDisplayList);
    DCInvalidateRange(m_pDispList, sizeOfDisplayList);
    GX_BeginDispList(m_pDispList, sizeOfDisplayList);
}

void DisplayList::End()
{
    m_displayListSize = GX_EndDispList();
    m_bIsDirty = false;
    // Update display list size to the size returned by GX_EndDispList() to save memory
    realloc(m_pDispList, m_displayListSize);
}

void DisplayList::Clear()
{
    if (m_displayListSize > 0)
    {
        free(m_pDispList);
        m_displayListSize = 0;
        m_pDispList = nullptr;
        m_bIsDirty = true;
    }
}
