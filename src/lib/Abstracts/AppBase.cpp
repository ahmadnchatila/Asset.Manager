#include "AppBase.hpp"

#include "Common/Common.hpp"
#include <mach-o/dyld.h>
#include <limits.h>

AppBase::AppBase(int argc, const char* argv[]) :
    m_appName(__AssetManager_AppName),
    m_appVersion(__AssetManager_AppVersion),
    m_argParser(new ArgParser(argc, argv))
{
    // Get the app path...
    char buf [PATH_MAX];
    uint32_t bufsize = PATH_MAX;
    if(!_NSGetExecutablePath(buf, &bufsize))
        puts(buf);
    
    // Store the defined path here...
    m_appFilename = buf;
}

AppBase::~AppBase()
{
    delete m_argParser;
    m_argParser = nullptr;
}

string
AppBase::getAppName() const
{
    return m_appName;
}

string
AppBase::getAppVersion() const
{
    return m_appVersion;
}

string
AppBase::getAppFilename() const
{
    return m_appFilename;
}

string
AppBase::getAppDirectory() const
{
    assert( !m_appFilename.empty() );
    return getAppFilename().substr(0, m_appFilename.find_last_of('/'));
}

int
AppBase::run()
{
    m_argParser->validate();
    
    if (m_argParser->getIsUsable()) {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}
