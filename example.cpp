#include <string>
#include <iostream>
#include "7ZipWrapper.h"

int main(int argc, char** argv)
{
    if (!p7zipwrapper::SevenZip::Archive(
        std::vector<std::string> {
            "/home/xuranus/workspace/libp7zip/build/dir1",
            "/home/xuranus/workspace/libp7zip/build/file1",
            "/home/xuranus/workspace/libp7zip/build/file2"
        },
        "/home/xuranus/workspace/libp7zip/build/out.7z")) {
        std::cerr << "failed to archive" << std::endl;
    } else {
        std::cout << "archive success" << std::endl;
    }
    return 0;
}