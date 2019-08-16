#ifndef PlistFileModel_h
#define PlistFileModel_h

#include <map>
#include <vector>
#include "Interfaces/IJsonObject.hpp"

struct PlistUpdateTarget;

//
// For convenience
//
using PlistUpdateTargets = std::vector<PlistUpdateTarget*>;

struct PlistUpdateTarget : public IJsonObject
{
public:
    PlistUpdateTarget(string key, string value) :
    m_key(key),
    m_value(value)
    {
        // do nothing...
    }
    
    ~PlistUpdateTarget()
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

struct PlistFileModel : public IJsonObject
{
public:
    PlistFileModel(string filename, PlistUpdateTargets* pUpdateTargets) :
    m_filename(filename),
    m_pUpdateTargets(pUpdateTargets)
    {
        // do nothing...
    }
    
    ~PlistFileModel()
    {
        // do nothing...
    }
    
    string
    getFilename() const
    {
        return m_filename;
    }
    
    PlistUpdateTargets*
    getUpdateTargets()
    {
        return m_pUpdateTargets;
    }
    
private:
    string m_filename;
    PlistUpdateTargets* m_pUpdateTargets;
};

#endif /* PlistFileModel_h */
