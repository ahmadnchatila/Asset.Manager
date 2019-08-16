#include "XcodeEngine.hpp"
#include "Client/App.hpp"

XcodeEngine::XcodeEngine(IEngineHandler & handler, IDEConfigurationModel & ideConfigurationModel, bool ignore)
    : EngineBase(handler, ideConfigurationModel, ignore)
{
    // do nothing...
}

XcodeEngine::~XcodeEngine()
{
    // do nothing...
}

void
XcodeEngine::start()
{
    printf("\nUpdating project for \"%s\"...", "Xcode");
    EngineBase::start();
    m_handler->onEngineFinished();
}
