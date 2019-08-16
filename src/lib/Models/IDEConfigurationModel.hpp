#ifndef IDEConfigurationModel_hpp
#define IDEConfigurationModel_hpp

#include "Interfaces/IJsonObject.hpp"
#include "Models/UpdateContentInFilesModel.hpp"
#include "Models/CopyFolderModel.hpp"
#include "Models/CopyFileModel.hpp"
#include "Models/RawFileModel.hpp"

using Variables = std::map<string, string>;
using CopyFoldersList = std::vector<CopyFolderModel*>;
using CopyFilesList = std::vector<CopyFileModel*>;

struct IDEConfigurationModel : public IJsonObject {

public:
    IDEConfigurationModel(bool isActive, UpdateContentInFilesModel* updateContentInFiles, CopyFoldersList* copyFolders, CopyFilesList* copyFiles, Variables* publicVariables, Variables* overrideVariables) :
    m_isActive(isActive),
    m_publicVariables(publicVariables),
    m_overrideVariables(overrideVariables),
    m_updateContentInFiles(updateContentInFiles),
    m_copyFiles(copyFiles),
    m_copyFolders(copyFolders) {
        // do nothing...
    }
    
    ~IDEConfigurationModel() {
        
        if (m_updateContentInFiles != nullptr) {
            delete m_updateContentInFiles;
            m_updateContentInFiles = nullptr;
        }
    }
    
    bool getIsActive()
    {
        return m_isActive;
    }
    
    
    UpdateContentInFilesModel*
    getUpdateContentInFiles()
    {
        return m_updateContentInFiles;
    }
    
    Variables*
    getPublicVariables()
    {
        return m_publicVariables;
    }
    
    Variables*
    getOverrideVariables()
    {
        return m_overrideVariables;
    }
    
    CopyFilesList*
    getCopyFiles()
    {
        return m_copyFiles;
    }
    
    CopyFoldersList*
    getCopyFolders()
    {
        return m_copyFolders;
    }
    
private:
    bool m_isActive;
    UpdateContentInFilesModel* m_updateContentInFiles;
    CopyFoldersList* m_copyFolders;
    CopyFilesList* m_copyFiles;
    Variables* m_publicVariables;
    Variables* m_overrideVariables;
};

#endif /* IDEConfigurationModel_hpp */
