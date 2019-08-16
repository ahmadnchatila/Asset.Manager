#include "rapidxml-1.13/rapidxml_ext.h"
#include <iostream>

#include <fstream>
#include <streambuf>
#include <string.h>
#include <stdio.h>
#include "Utilities/StringHelpers.hpp"

#include "ghc/filesystem.hpp"
#include "EngineBase.hpp"

#define SIZE_BUFFER     1024

namespace fs = ghc::filesystem;

EngineBase::EngineBase(IEngineHandler & handler, IDEConfigurationModel & ideConfigurationModel, bool ignore)
: m_isRunnable(ignore ? false : ideConfigurationModel.getIsActive()),
    m_ideConfigModel(&ideConfigurationModel),
    m_handler(&handler)
{
    // do nothing...
}

EngineBase::~EngineBase()
{
    // do nothing...
}

string
EngineBase::parseVariables(string text)
{
    if (hasVariable(text))
    {
        auto variable = extractVariable(text);
        auto userVariable = GetVariableName(variable);
    
        auto value = getVariableValue(variable);
        
        auto newString = StringHelpers::replaceAll(text, userVariable, value);
        return parseVariables(newString);
    }
    
    return text;
}

bool
EngineBase::hasVariable(string text)
{
    bool open1 = false;
    bool open2 = false;
    
    for (int i = 0; i < text.length(); i++)
    {
        if (!open1 || !open2)
        {
            switch (text[i]) {
                case '$':
                    open1 = true;
                    break;
                    
                case '(':
                    open2 = open1 ? true : false;
                    break;
            }
            
            continue;
        }
        
        switch (text[i]) {
            case ')': return true;
        }
        
        continue;
    }
    
    return false;
}

string
EngineBase::extractVariable(string text)
{
    bool open1 = false;
    bool open2 = false;
    
    string value = "";
    
    for (int i = 0; i < text.length(); i++)
    {
        if (!open1 || !open2)
        {
            switch (text[i]) {
                case '$':
                    open1 = true;
                    break;
                    
                case '(':
                    open2 = open1 ? true : false;
                    break;
            }
            
            continue;
        }
        
        switch (text[i]) {
            case ')':
                return value;
                
            default:
                value += text[i];
                break;
        }
        
        continue;
    }
    
    return value;
}

string
EngineBase::getVariableValue(string variable)
{
    Variables* overrideVariables = m_ideConfigModel->getOverrideVariables();
    Variables* publicVariables = m_ideConfigModel->getPublicVariables();
        
    size_t length = 0;
    
    if ((length = overrideVariables->count(variable)) > 0)
    {
        return overrideVariables->find(variable)->second;
    }
        
    if ((length = publicVariables->count(variable)) > 0)
    {
        return publicVariables->find(variable)->second;
    }
    
    return variable;
}

bool
EngineBase::getIsRunnable()
{
    return m_isRunnable;
}

string
EngineBase::getVersionCode() const
{
    return m_versionCode;
}

void
EngineBase::updateContentInXmlFiles()
{
    auto xmlFiles = m_ideConfigModel->getUpdateContentInFiles()->m_pXmlFiles;
    
    assert( xmlFiles != nullptr );
    
    for (auto xmlFile : *xmlFiles)
    {
        auto filename = parseVariables(xmlFile->getFilename());
        
        std::ifstream t(filename);
        std::string str((std::istreambuf_iterator<char>(t)),
                         std::istreambuf_iterator<char>());
        
        rapidxml::xml_document<> doc;
        
        std::vector<char> buffer(str.begin(), str.end());
        buffer.push_back('\0');
        
        doc.parse<rapidxml::parse_no_utf8>(&buffer[0]);
        
        char* key = nullptr;
        char* value = nullptr;
        
        for (auto updateTarget : *xmlFile->getUpdateTargets())
        {
            if (!updateTarget->getAttributeName().empty() && updateTarget->getAttributes() != nullptr)
            {
                throw "attribute and attributeName cannot be specified at the same time. One of them has to be removed.";
            }
        
            if (updateTarget->getAttributeName().empty() && updateTarget->getAttributes() == nullptr)
            {
                throw "At least attribute or attributeName must be specified. None were given.";
            }
            
            if (!updateTarget->getAttributeName().empty() && updateTarget->getInnerValues() != nullptr)
                goto HandleCase1;
            goto HandleCase2;
            
        HandleCase1: // AttributeName, InnerValues
            {
                for (auto innerValue : *updateTarget->getInnerValues())
                {
                    auto node = rapidxml::custom::nav_to_node(doc, updateTarget->getNode());
                    
                    key = doc.allocate_string(static_cast<string>(innerValue.first).c_str());
                    value = doc.allocate_string(parseVariables(static_cast<string>(innerValue.second)).c_str());
                    
                    while (node)
                    {
                        auto attr = node->first_attribute();
                        
                        if (strcmp(attr->name(), updateTarget->getAttributeName().c_str()) != 0 ||
                            strcmp(attr->value(), key) != 0)
                        {
                            node = node->next_sibling();
                            continue;
                        }
                        
                        auto real_thing = node->first_node();
                        
                        if (real_thing != nullptr                         // these checks just demonstrate that
                            && real_thing->next_sibling() == nullptr      // it is there and how it is located
                            && real_thing->type() == rapidxml::node_data)  // when element does contain text data
                        {
                            real_thing->value( value );  // now that should work
                        }
                        
                        break;
                    }
                }
                
                std::ofstream outFile(filename);
                outFile << XMLEncodingSpecifier << doc;
                
                continue;
            }
            
        HandleCase2: // Attributes
            {
                for (auto attrib : *updateTarget->getAttributes())
                {
                    auto node = rapidxml::custom::nav_to_node(doc, updateTarget->getNode());
                    
                    auto attribute = node->first_attribute();
                    
                    if (attribute != nullptr)
                    {
                        key = doc.allocate_string(static_cast<string>(attrib.first).c_str());
                        value = doc.allocate_string(static_cast<string>(attrib.second).c_str());
                        
                        auto parsedValue = parseVariables(value).c_str();
                        
                        attribute->value( parsedValue );
                    }
                    
                    std::ofstream outFile(filename);
                    outFile << XMLEncodingSpecifier << doc;
                }
            }
        }
        
        t.close();
    }
}

void
EngineBase::updateContentInPbxprojFiles()
{
    auto pbxprojFiles = m_ideConfigModel->getUpdateContentInFiles()->m_pPbxprojFiles;
    
    assert( pbxprojFiles != nullptr );
    
    for (auto pbxprojFile : *pbxprojFiles)
    {
        auto filename = parseVariables(pbxprojFile->getFilename());
        
        for (auto updateTarget : *pbxprojFile->getUpdateTargets())
        {
            if (PathFileExists(filename.c_str()) == -1)
            {
                printf("The \"%s\" file cannot be located.\n", filename.c_str());
                continue;
            }
            
            auto newFilename = GetTempFilename(filename);
            
            string line;
            
            std::ifstream reader(filename);
            std::ofstream writer(newFilename);
            
            while(getline(reader, line))
            {
                if (line.find(updateTarget->getKey()) != string::npos)
                {
                    auto startIndex = line.find('=') + 1;
                    line = line.substr(0, startIndex);
                    
                    line += " " + parseVariables(updateTarget->getValue()) + ";";
                }
                
                writer << line << "\n";
            }
            
            writer.close();
            reader.close();
            
            std::remove(filename.c_str());
            std::rename(newFilename.c_str(), filename.c_str());
        }
    }
}

void
EngineBase::updateContentInPlistFiles()
{
    auto plistFiles = m_ideConfigModel->getUpdateContentInFiles()->m_pPlistFiles;
    
    assert( plistFiles != nullptr );
    
    for (auto plistFile : *plistFiles)
    {
        auto filename = parseVariables(plistFile->getFilename());
        
        for (auto updateTarget : *plistFile->getUpdateTargets())
        {
            if (PathFileExists(filename.c_str()) == -1)
            {
                printf("The \"%s\" file cannot be located.\n", filename.c_str());
                continue;
            }
            
            auto newFilename = GetTempFilename(filename);
            
            string line;
            bool foundKey = false;
            bool noSeek = false;
            
            std::ifstream reader(filename);
            std::ofstream writer(newFilename);
            
            while(getline(reader, line))
            {
                if (noSeek)
                {
                    writer << line;
                    continue;
                }
                
                if (foundKey)
                {
                    noSeek = true;
                    line = "\t<string>" + parseVariables(updateTarget->getValue()) + "</string>";
                }
                
                if (!foundKey && line.find(updateTarget->getKey()) != string::npos )
                {
                    foundKey = true;
                }
                
                writer << line << "\n";
            }
            
            writer.close();
            reader.close();
            
            std::remove(filename.c_str());
            std::rename(newFilename.c_str(), filename.c_str());
        }
    }
}

void 
EngineBase::updateContentInRawFiles()
{
    auto rawFiles = m_ideConfigModel->getUpdateContentInFiles()->m_pRawFiles;
    
    assert( rawFiles != nullptr );
    
    for (auto rawFile : *rawFiles)
    {
        auto filename = parseVariables(rawFile->getFilename());
        auto lineInt = rawFile->getLine();
        auto posInt = rawFile->getPosition();
        auto replace = rawFile->getReplace();
        auto str = rawFile->getString();
        
        if (PathFileExists(filename.c_str()) == -1)
        {
            printf("The \"%s\" file cannot be located.\n", filename.c_str());
            continue;
        }
        
        auto newFilename = GetTempFilename(filename);
        
        string line;
        
        std::ifstream reader(filename);
        std::ofstream writer(newFilename);
        
        int curr_line = 0;
        
        while(getline(reader, line))
        {
            if (curr_line != lineInt)
            {
                writer << line << "\n";
                curr_line += 1;
                continue;
            }
            
          //  string f_half = line.substr(0, posInt);
          //  string s_half = line.substr(posInt, line.length() - posInt);
            
            writer << str << "\n";
        }
        
        writer.close();
        reader.close();
        
        std::remove(filename.c_str());
        std::rename(newFilename.c_str(), filename.c_str());
    }
}

void
EngineBase::updateContentInGradleFiles()
{
    auto gradleFiles = m_ideConfigModel->getUpdateContentInFiles()->m_pGradleFiles;
    
    assert( gradleFiles != nullptr );
    
    for (auto gradleFile : *gradleFiles)
    {
        auto filename = parseVariables(gradleFile->getFilename());
        
        for (auto updateTarget : *gradleFile->getUpdateTargets())
        {
            if (PathFileExists(filename.c_str()) == -1)
            {
                printf("The \"%s\" file cannot be located.\n", filename.c_str());
                continue;
            }
            
            auto newFilename = GetTempFilename(filename);
            
            string line;
            
            std::ifstream reader(filename);
            std::ofstream writer(newFilename);
            
            while(getline(reader, line))
            {
                if (line.find(updateTarget.first) != string::npos)
                {
                    line = "\t" + updateTarget.first + " " + parseVariables(updateTarget.second);
                }
                
                writer << line << "\n";
            }
            
            writer.close();
            reader.close();
            
            std::remove(filename.c_str());
            std::rename(newFilename.c_str(), filename.c_str());
        }
    }
}

void
EngineBase::copyFiles()
{
    
}

void
EngineBase::copyFolders()
{
    auto replaceDirectories = m_ideConfigModel->getCopyFolders();
    
    for (auto elem : *replaceDirectories)
    {
        auto from = parseVariables(elem->getFrom());
        auto to = parseVariables(elem->getTo());
        
        for (auto& p: fs::directory_iterator(from))
        {
            if (!p.is_directory())
            {
                continue;
            }
            
            auto vec = elem->getExclusions();
            
            string to_new = std::string(to) + "/" + std::string(p.path().filename());
            
            if (vec == nullptr)
            {
                fs::copy(p.path().c_str(), to_new.c_str(), fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                continue;
            }
            
            auto is_excluded = std::find(vec->begin(), vec->end(), p.path().filename()) != vec->end();
            
            if (!is_excluded)
            {
                fs::copy(p.path().c_str(), to_new.c_str(), fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            }
        }
    }
}

void
EngineBase::start()
{
    assert( m_handler != nullptr );
    
    m_handler->onEngineRunning();
    
    if (!m_isRunnable)
    {
        printf("Skipped.");
        return;
    }
    
    printf("\n");
    
    assert( m_ideConfigModel != nullptr );
    
    copyFiles();
    copyFolders();
    updateContentInXmlFiles();
    updateContentInPbxprojFiles();
    updateContentInPlistFiles();
    updateContentInGradleFiles();
    updateContentInRawFiles();
}
