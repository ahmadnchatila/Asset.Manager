#ifndef App_hpp
#define App_hpp

#include "Utilities/AssetManagerProfileDeserializer.hpp"
#include "Interfaces/IEngineHandler.hpp"

#include "Abstracts/AppBase.hpp"
#include "Engine/AndroidStudioEngine.hpp"
#include "Engine/XcodeEngine.hpp"
#include "Models/AssetManagerProfileModel.hpp"

class App : public AppBase, public IEngineHandler {

public:
    App(int argc, const char* argv[]);
    ~App();
    
    string getAppFilename();
    int run();
    
private:
    
    void onEngineRunning();
    void onEngineFinished();
    
    
private:
    
    AssetManagerProfileModel* m_appSettings;
    
    XcodeEngine* m_xcodeEngine;
    AndroidStudioEngine* m_androidStudioEngine;
    
    AssetManagerProfileDeserializer* m_appSettingsDeserializer;
};

#endif /* App_hpp */
