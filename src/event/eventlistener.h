#ifndef IEVENTLISTENER_H
#define IEVENTLISTENER_H

#include "event.h"

class IEventListener
{
public:
    virtual void OnEvent(Event event) = 0;
protected:
    virtual ~IEventListener() {}
};

#endif // IEVENTLISTENER_H
