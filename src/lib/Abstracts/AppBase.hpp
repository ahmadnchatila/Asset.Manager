#ifndef AppBase_hpp
#define AppBase_hpp

#include "Common/Common.hpp"
#include "Utilities/ArgParser.hpp"

class AppBase {
    
public:
    AppBase(int argc, const char* argv[]);
    ~AppBase();
    
    virtual int run();
    
    string getAppFilename() const;
    string getAppVersion() const;
    string getAppName() const;
    string getAppDirectory() const;
    
private:
    string m_appName;
    string m_appVersion;
    string m_appFilename;
    
protected:
    ArgParser* m_argParser;
};

#endif /* AppBase_hpp */
