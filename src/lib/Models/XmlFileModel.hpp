#ifndef XmlFileModel_h
#define XmlFileModel_h

#include "Interfaces/IJsonObject.hpp"

#include <map>
#include <vector>

struct XmlUpdateTarget;

//
// For convenience
//
using XmlUpdateTargets = std::vector<XmlUpdateTarget*>;
using InnerValues = std::map<string, string>;
using Attributes = std::map<string, string>;

struct XmlUpdateTarget : public IJsonObject
{
public:
    XmlUpdateTarget(string node, string attribName, InnerValues* pInnerValues, Attributes* pAttribs) :
    m_node(node),
    m_attributeName(attribName),
    m_pInnerValues(pInnerValues),
    m_pAttributes(pAttribs)
    {
        // do nothing...
    }
    
    ~XmlUpdateTarget()
    {
        // do nothing...
    }
    
public:
    
    string getNode()
    {
        return m_node;
    }
    
    string getAttributeName()
    {
        return m_attributeName;
    }
    
    InnerValues* getInnerValues()
    {
        return m_pInnerValues;
    }
    
    
    Attributes* getAttributes()
    {
        return m_pAttributes;
    }
    
private:
    string m_node;
    string m_attributeName;
    InnerValues* m_pInnerValues;
    Attributes* m_pAttributes;
};

struct XmlFileModel : public IJsonObject
{
public:
    
    XmlFileModel(string filename, XmlUpdateTargets* pUpdateTargets) :
    m_filename(filename),
    m_pUpdateTargets(pUpdateTargets)
    {
        // do nothing...
    }
    
    ~XmlFileModel()
    {
        // do nothing...
    }
    
public:
    
    string getFilename()
    {
        return m_filename;
    }
    
    XmlUpdateTargets*
    getUpdateTargets()
    {
        return m_pUpdateTargets;
    }
    
private:
    string m_filename;
    XmlUpdateTargets* m_pUpdateTargets;
};

#endif /* XmlFileModel_h */
