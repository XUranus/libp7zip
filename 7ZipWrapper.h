#ifndef P7ZIP_LIBRARY_WRAPPER_H
#define P7ZIP_LIBRARY_WRAPPER_H

#include <string>
#include <vector>

namespace p7zipwrapper {

class SevenZip {
public:
    static bool Archive(
        const std::vector<std::string>& inputPaths,
        const std::string& archivePath);

    static bool Extract(
        const std::string& archivePath,
        const std::string& extractPath);

};

}
#endif