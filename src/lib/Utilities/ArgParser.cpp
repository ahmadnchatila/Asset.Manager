#include "ArgParser.hpp"

#define __ArgParserHpp_Option_Ignore_Xcode             "--ignore-xcode"
#define __ArgParserHpp_Option_Ignore_AndroidStudio     "--ignore-androidstudio"
#define __ArgParserHpp_Command_Help1                   "-h"
#define __ArgParserHpp_Command_Help2                   "--help"

ArgParser::ArgParser(int argc, const char* argv[]) :
    m_isUsable(false)
{
    for (auto i = 1; i < argc; i++) {
        m_args.push_back(argv[i]);
    }
}

ArgParser::~ArgParser()
{
    // do nothing...
}

inline
void
ArgParser::printUsage()
{
    printf("\nUsage: %s [options]\n", __AssetManager_AppExe);
    
    printf("Options:\n\n");
    printf("  -h|--help\tDisplay help.\n");
    printf("  --version\tDisplay version.\n\n");
}

inline
void
ArgParser::printHelp()
{
    printf("\n%s Help\n", __AssetManager_AppExe);
    
    printf("Options:\n\n");
    printf("  %s\n\tSkips asset modification on Xcode project.\n\n", __ArgParserHpp_Option_Ignore_Xcode);
    printf("  %s\n\tSkips asset modification on Android Studio project.\n", __ArgParserHpp_Option_Ignore_AndroidStudio);
}

void
ArgParser::validate()
{    
    bool isHelpSpecified = isHelp();
    
    if (isHelpSpecified)
    {
        m_isUsable = false;
        printHelp();
        return;
    }
    
    bool isNoIdeSpecified = isIgnoreXcode() && isIgnoreAndroidStudio();
    
    if (isNoIdeSpecified)
    {
        throw "At least one IDE needs to be specified.";
    }
    
    m_isUsable = true;
}

bool
ArgParser::getIsUsable()
{
    return m_isUsable;
}

bool
ArgParser::isHelp()
{
    for (int i = 0; i < m_args.size(); i++) {
        auto arg = m_args[i];
        
        if (arg.find(__ArgParserHpp_Command_Help1) != std::string::npos ||
            arg.find(__ArgParserHpp_Command_Help2) != std::string::npos)
        {
            return true;
        }
    }
    
    return false;
}

bool
ArgParser::isIgnoreAndroidStudio()
{
    for (int i = 0; i < m_args.size(); i++) {
        auto arg = m_args[i];
        
        if (arg.find(__ArgParserHpp_Option_Ignore_AndroidStudio) != std::string::npos)
        {
            return true;
        }
    }
    
    return false;
}

bool
ArgParser::isIgnoreXcode()
{
    for (int i = 0; i < m_args.size(); i++) {
        auto arg = m_args[i];
        
        if (arg.find(__ArgParserHpp_Option_Ignore_Xcode) != std::string::npos)
        {
            return true;
        }
    }
    
    return false;
}
