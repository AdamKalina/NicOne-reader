#include <iostream>
#include <fstream>
#include <locale.h>
#include <QFileInfo>
#include "read_nicolete_file.h"

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "czech");
    
    std::string path;
    bool exportSystem = true;
    bool anonymize = false;
    bool export2ascii = false;

    if (argc < 2) {
        std::cout << "Usage: Nicone <path> [--no-system] [--anonymize] [--ascii]" << std::endl;
        return -1;
    }

    path = argv[1];
    QFileInfo infoSig(QString::fromLocal8Bit(path.c_str()));

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--no-system") {
            exportSystem = false;
        }
        if (arg == "--anonymize") {
            anonymize = true;
        }
        if (arg == "--ascii") {
            export2ascii = true;
        }
    }

    if(path.empty()){
        std::cout << "Nothing to do..." << std::endl;
        return -1;
    }

    std::cout << "Processing: " << path << std::endl;
    if (!exportSystem) std::cout << "System annotations will be excluded." << std::endl;
    if (anonymize) std::cout << "Patient information will be anonymized." << std::endl;

    read_nicolete_file nicolete_reader;

    if (nicolete_reader.readNicOneFile(infoSig)) {
        std::cout << "Error processing the file" << std::endl;
        return 1;
    } else {
        std::string outputPath = path.substr(0, path.find_last_of(".")) + ".EDF";
        std::cout << "Exporting to " << outputPath << "..." << std::endl;
        QFileInfo infoEdf(QString::fromLocal8Bit(outputPath.c_str()));
        if (nicolete_reader.exportToEdf(infoEdf, exportSystem, anonymize, export2ascii) == 0) {
            std::cout << "Finished successfully!" << std::endl;
            return 0;
        } else {
            std::cout << "Export failed!" << std::endl;
            return 1;
        }
    }

    return 0;
}
