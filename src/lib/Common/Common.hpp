#ifndef Common_h
#define Common_h

#include <string>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <unistd.h>

#define __AssetManager_AppName                         "Asset Manager"
#define __AssetManager_AppExe                          "Asset.Manager"
#define __AssetManager_AppVersion                      "1.0"

using string = std::string;
const string string_empty = "";

//
// Checks for file's existence on disk.
//
#define PathFileExists(f) access(f,0)

//
// Returns a temporary file name of a file.
//
#define GetTempFilename(f) f + ".tmp"

#define CreateTagWithValue(name, value) "<" + name + ">" + value "</" + name + ">"

#define GetVariableName(f) "$(" + f + ")"

#define XMLEncodingSpecifier "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"

#endif /* Common_h */
