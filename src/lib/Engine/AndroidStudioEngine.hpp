#ifndef AndroidStudioEngine_hpp
#define AndroidStudioEngine_hpp

#include "Abstracts/EngineBase.hpp"

class AndroidStudioEngine : public EngineBase {
    
public:
    AndroidStudioEngine(IEngineHandler & handler, IDEConfigurationModel & ideConfigurationModel, bool ignore);
    ~AndroidStudioEngine();
    
    void start();
};

#endif /* AndroidStudioEngine_hpp */
