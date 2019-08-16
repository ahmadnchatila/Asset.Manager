#ifndef IEngineHandler_h
#define IEngineHandler_h

#include "IInterface.hpp"

class IEngineHandler : public IInterface
{
    
public:
    virtual void onEngineRunning() = 0;
    virtual void onEngineFinished() = 0;
};

#endif /* IEngineHandler_h */
