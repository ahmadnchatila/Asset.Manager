#ifndef AppSettingsModel_hpp
#define AppSettingsModel_hpp

#include "IDEConfigurationModel.hpp"
#include "Interfaces/IJsonObject.hpp"

using Variables = std::map<string, string>;

struct AssetManagerProfileModel : public IJsonObject {

public:
    AssetManagerProfileModel(Variables* publicVariables, IDEConfigurationModel* ideAndroid, IDEConfigurationModel* ideXcode) :
        m_variables(publicVariables),
        m_androidStudioConfiguration(ideAndroid),
        m_xcodeConfiguration(ideXcode) {
            // do nothing...
    }
    
    ~AssetManagerProfileModel() {
        if (m_androidStudioConfiguration != nullptr) {
            delete m_androidStudioConfiguration;
            m_androidStudioConfiguration = nullptr;
        }
        
        if (m_xcodeConfiguration != nullptr) {
            delete m_xcodeConfiguration;
            m_xcodeConfiguration = nullptr;
        }
    }
    
    IDEConfigurationModel*
    getAndroidStudioConfiguration() const
    {
        return m_androidStudioConfiguration;
    }
    
    IDEConfigurationModel*
    getXcodeConfiguration() const
    {
        return m_xcodeConfiguration;
    }
    
    Variables*
    getVariables()
    {
        return m_variables;
    }
    
    string
    getProfileName() const
    {
        return m_profileName;
    }
    
private:
    IDEConfigurationModel* m_androidStudioConfiguration;
    IDEConfigurationModel* m_xcodeConfiguration;
    Variables* m_variables;
    string m_profileName;
    
};

#endif /* AppSettingsModel_hpp */
