#ifndef IJsonObject_h
#define IJsonObject_h

#include "Common/Common.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

class IJsonObject {

public:
    virtual ~IJsonObject() { }
};

#endif /* IJsonObject_h */
