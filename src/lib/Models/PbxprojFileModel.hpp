#ifndef PbxprojFileModel_h
#define PbxprojFileModel_h

#include "Interfaces/IJsonObject.hpp"
#include <vector>

struct PbxprojUpdateTarget;

//
// For convenience
//
using PbxprojUpdateTargets = std::vector<PbxprojUpdateTarget*>;

struct PbxprojUpdateTarget : public IJsonObject {
    
public:
    PbxprojUpdateTarget(string key, string value) :
    m_key(key),
    m_value(value)
    {
        // do nothing...
    }
    
    ~PbxprojUpdateTarget()
    {
        // do nothing...
    }
    
public:
    
    string
    getKey() const
    {
        return m_key;
    }
    
    string
    getValue() const
    {
        return m_value;
    }
    
private:
    string m_key;
    string m_value;
    
};

struct PbxprojFileModel : public IJsonObject {
    
public:
    PbxprojFileModel(string filename, PbxprojUpdateTargets* pUpdateTargets) :
    m_filename(filename),
    m_pUpdateTargets(pUpdateTargets)
    {
        // do nothing...
    }
    
    ~PbxprojFileModel()
    {
        // do nothing...
    }
    
public:
    
    string
    getFilename() const
    {
        return m_filename;
    }
    
    PbxprojUpdateTargets*
    getUpdateTargets() const
    {
        return m_pUpdateTargets;
    }
    
    
private:
    string m_filename;
    PbxprojUpdateTargets* m_pUpdateTargets;
};

#endif /* PbxprojFileModel_h */
