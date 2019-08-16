#include "App.hpp"

App::App(int argc, const char* argv[]) :
    AppBase(argc, argv)
{
    m_appSettingsDeserializer = new AssetManagerProfileDeserializer(AppBase::getAppDirectory());
    m_appSettings = m_appSettingsDeserializer->deserialize();
    
    m_xcodeEngine = new XcodeEngine(*this, *m_appSettings->getXcodeConfiguration(), m_argParser->isIgnoreXcode());
    m_androidStudioEngine = new AndroidStudioEngine(*this, *m_appSettings->getAndroidStudioConfiguration(), m_argParser->isIgnoreAndroidStudio());
}

App::~App()
{
    if (m_androidStudioEngine == nullptr) {
        delete m_androidStudioEngine;
        m_androidStudioEngine = nullptr;
    }
    
    if (m_xcodeEngine == nullptr) {
        delete m_xcodeEngine;
        m_xcodeEngine = nullptr;
    }
    
    if (m_appSettings == nullptr) {
        delete m_appSettings;
        m_appSettings = nullptr;
    }
    
    delete m_appSettingsDeserializer;
    m_appSettingsDeserializer = nullptr;
    
    printf("\n\n");
}

int
App::run()
{
    if (AppBase::run() == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    
    m_androidStudioEngine->start();
    m_xcodeEngine->start();
    
    return EXIT_SUCCESS;
}

void
App::onEngineRunning()
{
    
}

void
App::onEngineFinished()
{
    
}
