#ifndef CopyFolderModel_h
#define CopyFolderModel_h

#include "Interfaces/IJsonObject.hpp"
#include <vector>

//
// For convenience
//
using ExclusionsList = std::vector<string>;

struct CopyFolderModel : public IJsonObject {
    
public:
    CopyFolderModel(string from, string to, bool overwrite, ExclusionsList* exclusions) :
    m_from(from),
    m_to(to),
    m_overwrite(overwrite),
    m_exclusions(exclusions)
    {
        // do nothing...
    }
    
    ~CopyFolderModel()
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
    
    ExclusionsList*
    getExclusions()
    {
        return m_exclusions;
    }
    
private:
    string m_from;
    string m_to;
    bool m_overwrite;
    ExclusionsList* m_exclusions;
    
};

#endif /* CopyFolderModel_h */
