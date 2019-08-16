#ifndef CopyFileModel_h
#define CopyFileModel_h

#include "Interfaces/IJsonObject.hpp"
#include <vector>

//
// For convenience
//
using ExclusionsList = std::vector<string>;

struct CopyFileModel : public IJsonObject {
    
public:
    CopyFileModel(string from, string to, bool overwrite) :
    m_from(from),
    m_to(to),
    m_overwrite(overwrite)
    {
        // do nothing...
    }
    
    ~CopyFileModel()
    {
        // do nothing...
    }
    
public:
    
    string
    getFrom() const
    {
        return m_from;
    }
    
    string
    getTo() const
    {
        return m_to;
    }
    
    bool
    getOverwrite()
    {
        return m_overwrite;
    }
    
private:
    string m_from;
    string m_to;
    bool m_overwrite;
    
};

#endif /* CopyFileModel_h */
