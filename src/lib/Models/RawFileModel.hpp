#ifndef RawFileModel_h
#define RawFileModel_h

#include <map>
#include <vector>
#include "Interfaces/IJsonObject.hpp"

struct RawFileModel : public IJsonObject
{
public:
    RawFileModel(string filename, int line, int pos, bool replace, string str) :
    m_filename(filename),
    m_line(line),
    m_position(pos),
    m_replace(replace),
    m_string(str)
    {
        // do nothing...
    }
    
    ~RawFileModel()
    {
        // do nothing...
    }
    
    string
    getFilename() const
    {
        return m_filename;
    }

    int
    getLine()
    {
        return m_line;
    }

    int
    getPosition()
    {
        return m_position;
    }

    bool
    getReplace()
    {
        return m_replace;
    }
    
    string
    getString() const
    {
        return m_string;
    }

private:
    string m_filename;
    int m_line;
    int m_position;
    bool m_replace;
    string m_string;
};

#endif /* PlistFileModel_h */
