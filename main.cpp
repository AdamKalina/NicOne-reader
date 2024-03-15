#include <iostream>
#include <fstream>
#include <locale.h>
#include "read_nicolete_file.h"

int main(int argc, char** argv)
{
    //setlocale(LC_ALL, "cs_CZ.UTF-8");
    setlocale(LC_ALL, "czech");
    std::string path;

    //std::cout << argv[1] << std::endl;

    path = argv[1];

    //path = "D:\Dropbox\Scripts\Cpp\EEGLEnest\NicOne\7939\Patient20_NICONERECW_t1.e";

    if(path.empty()){
        std::cout << "Nothing to do..." << std::endl;
        return -1;
    }

    std::cout << path << std::endl;

    std::ifstream file(path, std::ios::binary);

    if (!file){
        std::cout << "ERROR: Cannot open the file..." << std::endl;
        return -1;
    }


    if (file.fail()){
        std::cout << "ERROR: Cannot open the file..." << std::endl;
        return -1;
    }

    read_nicolete_file nicolete_reader = read_nicolete_file();
    read_nicolete_file::NiconeHeader niconeHeader = nicolete_reader.read_nicolete_header(file);

    // ===================================== Log ======================================================

    QFile log_file("nicolet_log.txt");
    if(log_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&log_file);
        stream << niconeHeader.patientInfo.at(1) + "|" + niconeHeader.patientInfo.at(2) + "|" + niconeHeader.patientInfo.at(3) + "|" + niconeHeader.studyInfo.at(3) + "|" + niconeHeader.segmentTimes.segmentStartTimes.at(0).toString("dd.MM.yyyy hh:mm:ss") + "|" + QString::fromStdString(path) +"\n";
        log_file.close();
    }

    return 0;
}
