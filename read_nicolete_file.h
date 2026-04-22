#ifndef READ_NICOLETE_FILE_H
#define READ_NICOLETE_FILE_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstdint>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QFileInfo>

class read_nicolete_file
{
public:
    int LABELSIZE = 32;
    int TSLABELSIZE = 64;
    int UNITSIZE = 16;
    int ITEMNAMESIZE  = 64;

    struct Tag{
        std::string tag;
        long int index;
        std::string IDStr;
    };

    struct Qi{
        unsigned long nrEntries;
        unsigned long misc1;
        unsigned long indexIdx;
        unsigned long misc3;
        unsigned long LQi;
        std::vector<unsigned long long> firstIdx;
    };

    struct Index{
        unsigned long long sectionIdx;
        unsigned long long offset;
        unsigned long long blockL;
        unsigned long long sectionL;
    };

    struct DynamicPacket{
        unsigned long long offset;
        std::string guid;
        std::string guidAsStr;
        double date;
        double datefrac;
        unsigned long long internalOffsetStart;
        unsigned long long packetSize;
        std::vector<uint8_t> data;
        std::string IDStr;
    };

    struct SegmentTimes{
        std::vector<QDateTime> segmentStartTimes;
        std::vector<double> durations;
    };

    struct ChannelInfo {
        QString label;
        QString activeSensor;
        QString refSensor;
        double dSamplingRate;
        double dResolution;
        double dLowCut;
        double dHighCut;
        double dEegOffset;
        bool bOn;
        int sectionIdx; // Index in Tags for data stream
    };

    struct Annotation {
        QDateTime start;
        QDateTime end;
        QString text;
        bool system;
    };

    struct TimelineSection {
        QDateTime start;
        QDateTime end;
        double durationSeconds;
        int tsInfoIdx;
    };

    struct MontageEntry {
        QString derivationName;
        QString signalName1;
        QString signalName2;
    };

    struct NiconeHeader{
        std::vector<QString> patientInfo;
        std::vector<QString> studyInfo;
        SegmentTimes segmentTimes;
        double duration;
    };

    std::vector<Tag> sections;
    std::vector<Index> indices;
    std::vector<DynamicPacket> dynamicPackets;
    std::vector<std::vector<ChannelInfo>> tsInfos;
    std::vector<Annotation> annotations;
    std::vector<TimelineSection> timeline;
    std::vector<MontageEntry> montage;
    std::map<QString, std::vector<QString>> eventDictionary;
    NiconeHeader niconeHeader;
    QFileInfo file_info;

    read_nicolete_file();
    int readNicOneFile(QFileInfo info);
    NiconeHeader read_nicolete_header(std::ifstream &file);
    bool is_digits(std::string& str);
    std::string hexVectorTostring(std::vector<unsigned char>& vec);
    std::string formatGuid(const std::string& guidStr);
    QString readUint16toQString(int size, std::ifstream &file);
    Index getSectionIdx(std::string sectionName);
    std::vector<QString> readFileProperties(std::string sectionName, std::ifstream &file);
    SegmentTimes readSegmentStartTimes(std::ifstream &file);
    
    void readDynamicPackets(std::ifstream &file);
    void readTSInfo();
    void readAnnotationsInternal(std::ifstream &file);
    void readMontage(std::ifstream &file);
    void readEventDictionary(std::ifstream &file);
    void reconstructTimeline();
    int exportToEdf(QFileInfo infoEdf, bool exportSystemAnnotations = true, bool anonymize = false, bool export2ascii = false);
    QString GetGuidFromBytes(std::vector<uint8_t> &GUID);
private:
    std::vector<int> birthDateFromID(std::string id);
};

#endif // READ_NICOLETE_FILE_H
