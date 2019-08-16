#include "AndroidStudioEngine.hpp"

AndroidStudioEngine::AndroidStudioEngine(IEngineHandler & handler, IDEConfigurationModel & ideConfigurationModel, bool ignore)
: EngineBase(handler, ideConfigurationModel, ignore)
{
    // do nothing...
}

AndroidStudioEngine::~AndroidStudioEngine()
{
    // do nothing...
}

void
AndroidStudioEngine::start()
{
    printf("Updating project for \"%s\"...", "Android Studio");
    EngineBase::start();
    m_handler->onEngineFinished();
}
