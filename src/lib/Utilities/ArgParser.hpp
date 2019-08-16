#ifndef ArgParser_hpp
#define ArgParser_hpp

#include "Common/Common.hpp"

class ArgParser {
    
public:
    ArgParser(int argc, const char* argv[]);
    ~ArgParser();
    
    void validate();
    inline void printUsage();
    inline void printHelp();
    
    bool getIsUsable();
    
    bool isHelp();
    bool isIgnoreAndroidStudio();
    bool isIgnoreXcode();
    
private:
    std::vector<string> m_args;
    
    bool m_isUsable;
};

#endif /* ArgParser_hpp */
