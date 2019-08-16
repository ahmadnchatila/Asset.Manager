#ifndef GradleFileModel_h
#define GradleFileModel_h

#include "Interfaces/IJsonObject.hpp"

//
// For convenience
//
using GradleUpdateTargets = std::map<string, string>;

struct GradleFileModel : public IJsonObject {

public:
    GradleFileModel(string filename, GradleUpdateTargets* pUpdateTargets) :
    m_filename(filename),
    m_pUpdateTargets(pUpdateTargets)
    {
        // do nothing...
    }
    
    ~GradleFileModel()
    {
        // do nothing...
    }
    
public:
    string
    getFilename() const
    {
        return m_filename;
    }
    
    GradleUpdateTargets*
    getUpdateTargets() const
    {
        return m_pUpdateTargets;
    }
    
    
private:
    string m_filename;
    GradleUpdateTargets* m_pUpdateTargets;
};

#endif /* GradleFileModel_h */
