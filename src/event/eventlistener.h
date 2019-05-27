#pragma once

#include "event.h"

class IEventListener
{
public:
    virtual void OnEvent(Event event) = 0;
protected:
    virtual ~IEventListener() {}
};

