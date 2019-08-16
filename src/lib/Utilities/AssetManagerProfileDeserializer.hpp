#ifndef AssetManagerProfileDeserializer_hpp
#define AssetManagerProfileDeserializer_hpp

#include "Models/AssetManagerProfileModel.hpp"
#include "Models/IDEConfigurationModel.cpp"

class AssetManagerProfileDeserializer {
    
public:
    AssetManagerProfileDeserializer(string filename);
    ~AssetManagerProfileDeserializer();
    
    AssetManagerProfileModel* deserialize();
    
private:
    IDEConfigurationModel* deserializeIDEConfiguration(string name, Variables* publicVariables);
    
    AssetManagerProfileModel* m_appSettingsModel;
    
    json m_j;
};

#endif /* AssetManagerProfileDeserializer_hpp */
