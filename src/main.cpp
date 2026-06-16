#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>

namespace fs = std::filesystem;

void checkSaveFile (const char* homeDir) {
    fs::path saveDirPath = fs::path(homeDir) / "Documents/repos/RogueLikeGame/save";
    fs::path saveFilePath = saveDirPath / "saveFile.txt";

    if (!fs::exists(saveDirPath)) {
        fs::create_directories(saveDirPath);
    }

    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile.close();
    } else {
        std::cerr << "Failed to create the file." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    const char* homeDir = std::getenv("HOME");
    if (!homeDir) {
        std::cerr << "Could not find home directory." << std::endl;
        return 1;
    }

    checkSaveFile(homeDir);



    return 0;
}
