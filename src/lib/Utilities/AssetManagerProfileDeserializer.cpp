#include "AssetManagerProfileDeserializer.hpp"
#include "nlohmann/json.hpp"

AssetManagerProfileDeserializer::AssetManagerProfileDeserializer(string filename) :
m_appSettingsModel(nullptr)
{
    filename = "/Users/ahamd.shatila/Downloads/Asset.Manager/AssetManagerProfile.ArabianShield.json";
    std::ifstream i(filename);
    m_j = json::parse(i);
}

AssetManagerProfileDeserializer::~AssetManagerProfileDeserializer()
{
    // do nothing...
}

IDEConfigurationModel*
AssetManagerProfileDeserializer::deserializeIDEConfiguration(string name, Variables* publicVariables)
{
    const string updateContentInFilesString = "UpdateContentInFiles";
    const string copyFoldersString = "CopyFolders";
    const string copyFilesString = "CopyFiles";
    
    auto overrideVariablesObject = m_j[name]["Variables"];
    auto xmlFilesObject = m_j[name][updateContentInFilesString]["XmlFiles"];
    auto pbxprojFilesObject = m_j[name][updateContentInFilesString]["PbxprojFiles"];
    auto plistFilesObject = m_j[name][updateContentInFilesString]["PlistFiles"];
    auto gradleFilesObject = m_j[name][updateContentInFilesString]["GradleFiles"];
    auto copyFoldersObject = m_j[name][copyFoldersString];
    auto copyFilesObject = m_j[name][copyFilesString];
    
    auto pXmlFileModelVc = new std::vector<XmlFileModel*>();
    auto pPlistFileModelVc = new std::vector<PlistFileModel*>();
    auto pPbxprojFileModelVc = new std::vector<PbxprojFileModel*>();
    auto pGradleFileModelVc = new std::vector<GradleFileModel*>();
    auto pCopyFolderModelVc = new std::vector<CopyFolderModel*>();
    auto pCopyFilesModelVc = new std::vector<CopyFileModel*>();
    
    // ==================================================================
    // XML Files
    // ==================================================================
    
    assert ( pXmlFileModelVc != nullptr );
    
    for (auto &xmlFile : xmlFilesObject)
    {
        auto filename =  xmlFile["Filename"].get<string>();
        
        auto updateTargets = new XmlUpdateTargets();
        
        assert ( updateTargets != nullptr );
        
        for (auto currentUpdateTarget : xmlFile["UpdateTargets"])
        {
            string node = currentUpdateTarget["Node"];
            
            auto attributeNameObject = currentUpdateTarget["AttributeName"];
            auto innerValuesObject = currentUpdateTarget["InnerValues"];
            auto attributesObject = currentUpdateTarget["Attributes"];
            
            if (attributeNameObject != nullptr && innerValuesObject != nullptr)
                goto HandleCase1;
            goto HandleCase2;
            
        HandleCase1: // AttributeName, InnerValues
            {
                assert (attributeNameObject != nullptr);
                assert (innerValuesObject != nullptr);
                
                string attributeName = attributeNameObject;
                auto innerValues = new InnerValues();
                
                assert ( innerValues != nullptr );
                
                InnerValues currentInnerValues = innerValuesObject;
                
                for (auto innerValue : currentInnerValues)
                {
                    innerValues->insert( innerValue );
                }
                
                auto updateTarget = new XmlUpdateTarget(node, attributeName, innerValues, nullptr);
                
                assert ( updateTarget != nullptr );
                
                updateTargets->push_back(updateTarget);
                
            }
            continue;
            
        HandleCase2: // Attributes
            {
                assert (attributesObject != nullptr);
                
                auto attributes = new Attributes();
                
                assert ( attributes != nullptr );
                
                Attributes tempAttributes = attributesObject;
                
                for (auto attrib : tempAttributes)
                {
                    attributes->insert( attrib );
                }
                
                auto updateTarget = new XmlUpdateTarget(node, string_empty, nullptr, attributes);
                
                assert ( updateTarget != nullptr );
                
                updateTargets->push_back(updateTarget);
            }
            continue;
        }
        
        auto xmlFileModel = new XmlFileModel(filename, updateTargets);
        
        assert ( xmlFileModel != nullptr );
        
        pXmlFileModelVc->push_back(xmlFileModel);
    }
    
    // ==================================================================
    // Pbxproj Files
    // ==================================================================
    
    assert ( pPbxprojFileModelVc != nullptr );
    
    for (auto &pbxprojFile : pbxprojFilesObject)
    {
        auto filename = pbxprojFile["Filename"].get<string>();
        
        auto updateTargets = new PbxprojUpdateTargets();
        
        assert ( updateTargets != nullptr );
        
        for (auto currentUpdateTarget : pbxprojFile["UpdateTargets"])
        {
            string key = currentUpdateTarget["Key"];
            string value = currentUpdateTarget["Value"];
            
            auto updateTarget = new PbxprojUpdateTarget(key, value);
            
            assert( updateTarget != nullptr);
            
            updateTargets->push_back(updateTarget);
        }
        
        auto pbxprojFileModel = new PbxprojFileModel(filename, updateTargets);
        
        assert ( pbxprojFileModel != nullptr );
        
        pPbxprojFileModelVc->push_back(pbxprojFileModel);
    }
    
    // ==================================================================
    // Plist Files
    // ==================================================================
    
    assert ( pPlistFileModelVc != nullptr );
    
    for (auto &plistFile : plistFilesObject)
    {
        auto filename = plistFile["Filename"].get<string>();
        
        auto updateTargets = new PlistUpdateTargets();
        
        assert ( updateTargets != nullptr );
        
        for (auto currentUpdateTarget : plistFile["UpdateTargets"])
        {
            string key = currentUpdateTarget["Key"];
            string value = currentUpdateTarget["Value"];
            
            auto updateTarget = new PlistUpdateTarget(key, value);
            
            assert( updateTarget != nullptr);
            
            updateTargets->push_back(updateTarget);
        }
        
        auto plistFileModel = new PlistFileModel(filename, updateTargets);
        
        assert ( plistFileModel != nullptr );
        
        pPlistFileModelVc->push_back(plistFileModel);
    }
    
    // ==================================================================
    // Gradle Files
    // ==================================================================
    
    assert ( pGradleFileModelVc != nullptr );
    
    for (auto &gradleFile : gradleFilesObject)
    {
        auto filename = gradleFile["Filename"].get<string>();
        
        auto updateTargets = new GradleUpdateTargets();
        
        std::map<string, string> gradleFileUpdateTargets = gradleFile["UpdateTargets"];
        
        assert ( updateTargets != nullptr );
        
        for (auto currentUpdateTarget : gradleFileUpdateTargets)
        {
            string key = currentUpdateTarget.first;
            string value = currentUpdateTarget.second;
            
            updateTargets->insert( std::pair<string, string>(key, value) );
        }
        
        auto gradleFileModel = new GradleFileModel(filename, updateTargets);
        
        pGradleFileModelVc->push_back(gradleFileModel);
    }
    
    auto updateContentInFilesModel =
    new UpdateContentInFilesModel(pXmlFileModelVc, pPbxprojFileModelVc, pPlistFileModelVc, pGradleFileModelVc);
    
    auto overrideVariables = new Variables();
    
    assert( overrideVariables != nullptr );
    
    Variables currentOverrideVariables = overrideVariablesObject;
    
    for (auto vari : currentOverrideVariables)
    {
        overrideVariables->insert( std::pair<string, string>(vari.first, vari.second) );
    }
    
    auto pExclusionsList = new ExclusionsList();
    
    for (auto copyFolder : copyFoldersObject)
    {
        ExclusionsList exclusions = copyFolder["Exclusions"];
        
        for (auto excl : exclusions)
        {
            pExclusionsList->push_back(excl);
        }
        
       auto replaceDirModel = new CopyFolderModel(copyFolder["From"], copyFolder["To"], copyFolder["Overwrite"], pExclusionsList);
       pCopyFolderModelVc->push_back(replaceDirModel);
    }
    
    for (auto copyFile : copyFilesObject)
    {
        auto copyFileNew = new CopyFileModel(copyFile["From"], copyFile["To"], copyFile["Overwrite"]);
        pCopyFilesModelVc->push_back(copyFileNew);
    }
    
    
    auto ideConfig = new IDEConfigurationModel(m_j[name]["IsActive"], updateContentInFilesModel, pCopyFolderModelVc, pCopyFilesModelVc,
                                               publicVariables, overrideVariables);
    
    assert (ideConfig != nullptr);
    
    return ideConfig;
}

AssetManagerProfileModel*
AssetManagerProfileDeserializer::deserialize()
{
    if (m_appSettingsModel != nullptr)
    {
        return m_appSettingsModel;
    }
    
    auto publicVariables = new Variables();
    
    assert( publicVariables != nullptr );
    
    Variables currentPublicVariables = m_j["Variables"];
    
    for (auto vari : currentPublicVariables)
    {
        publicVariables->insert( std::pair<string, string>(vari.first, vari.second) );
    }
    
    m_appSettingsModel = new AssetManagerProfileModel(publicVariables,
                                                      deserializeIDEConfiguration("AndroidStudioConfiguration", publicVariables),
                                                      deserializeIDEConfiguration("XcodeConfiguration", publicVariables));
    
    return m_appSettingsModel;
}
