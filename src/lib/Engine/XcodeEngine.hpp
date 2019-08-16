#ifndef XcodeEngine_hpp
#define XcodeEngine_hpp

#include "Abstracts/EngineBase.hpp"

class XcodeEngine : public EngineBase {
    
public:
    XcodeEngine(IEngineHandler & handler, IDEConfigurationModel & ideConfigurationModel, bool ignore);
    ~XcodeEngine();
    
    void start();
};

#endif /* XcodeEngine_hpp */
