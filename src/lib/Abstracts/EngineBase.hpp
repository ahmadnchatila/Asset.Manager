#ifndef EngineBase_hpp
#define EngineBase_hpp

#include <stdio.h>
#include "Common/Common.hpp"
#include "Models/AssetManagerProfileModel.hpp"
#include "Interfaces/IEngineHandler.hpp"

class EngineBase {

public:
    EngineBase(IEngineHandler &, IDEConfigurationModel &, bool);
    ~EngineBase();
    
    bool getIsRunnable();
    string getVersionCode() const;
    
    void updateContentInXmlFiles();
    void updateContentInPbxprojFiles();
    void updateContentInPlistFiles();
    void updateContentInGradleFiles();
    void updateContentInRawFiles();
    
    void copyFiles();
    void copyFolders();
    virtual void start();
    
private:
    
    inline
    string parseVariables(string text);
    
    inline
    bool hasVariable(string text);
    
    inline
    string extractVariable(string text);
    
    inline
    string getVariableValue(string variable);
    
    string m_versionCode;
    bool m_isRunnable;
    
protected:
    IDEConfigurationModel* m_ideConfigModel;
    IEngineHandler* m_handler;
    
};

#endif /* EngineBase_hpp */
