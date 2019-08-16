#ifndef UpdateContentInFilesModel_h
#define UpdateContentInFilesModel_h

#include "Interfaces/IJsonObject.hpp"

#include "Models/XmlFileModel.hpp"
#include "Models/PlistFileModel.hpp"
#include "Models/GradleFileModel.hpp"
#include "Models/PbxprojFileModel.hpp"

struct UpdateContentInFilesModel : public IJsonObject {

public:
    UpdateContentInFilesModel(std::vector<XmlFileModel*>* pXmlFiles,
                              std::vector<PbxprojFileModel*>* pPbxprojFiles,
                              std::vector<PlistFileModel*>* pPlistFiles,
                              std::vector<GradleFileModel*>* pGradleFiles) :
    m_pXmlFiles(pXmlFiles),
    m_pPbxprojFiles(pPbxprojFiles),
    m_pPlistFiles(pPlistFiles),
    m_pGradleFiles(pGradleFiles)
    {
        // do nothing...
    }
    
    ~UpdateContentInFilesModel() {
        
        assert ( m_pXmlFiles        != nullptr );
        assert ( m_pPbxprojFiles    != nullptr );
        assert ( m_pPlistFiles      != nullptr );
        assert ( m_pGradleFiles     != nullptr );
        
        for (auto *xmlFile : *m_pXmlFiles)
        {
            if (xmlFile == nullptr)
                continue;
            
            delete xmlFile;
            xmlFile = nullptr;
        }
        
        for (auto *pbxprojFile : *m_pPbxprojFiles)
        {
            if (pbxprojFile == nullptr)
                continue;
            
            delete pbxprojFile;
            pbxprojFile = nullptr;
        }
        
        for (auto plistFile : *m_pPlistFiles)
        {
            if (plistFile == nullptr)
                continue;
            
            delete plistFile;
            plistFile = nullptr;
        }
        
        for (auto gradleFile : *m_pGradleFiles)
        {
            if (gradleFile == nullptr)
                continue;
            
            delete gradleFile;
            gradleFile = nullptr;
        }
    }
    
    std::vector<XmlFileModel*>* m_pXmlFiles;            // XmlFiles
    std::vector<PbxprojFileModel*>* m_pPbxprojFiles;    // PbxprojFiles
    std::vector<PlistFileModel*>* m_pPlistFiles;        // PlistFiles
    std::vector<GradleFileModel*>* m_pGradleFiles;      // GradleFiles
};

#endif /* UpdateContentInFilesModel_h */
