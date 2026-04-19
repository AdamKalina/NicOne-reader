#include "read_nicolete_file.h"
#include "edflib.h"

read_nicolete_file::read_nicolete_file()
{

}

read_nicolete_file::NiconeHeader read_nicolete_file::read_nicolete_header(std::ifstream &file){

    std::map<std::string, std::string> guids;
    guids["ExtraDataTags"] = "ExtraDataTags";
    guids["SegmentStream"] = "SegmentStream";
    guids["DataStream"] = "DataStream";
    guids["InfoChangeStream"] = "InfoChangeStream";
    guids["InfoGuids"] = "InfoGuids";
    guids["{A271CCCB-515D-4590-B6A1-DC170C8D6EE2}"] = "TSGUID";
    guids["{8A19AA48-BEA0-40D5-B89F-667FC578D635}"] = "DERIVATIONGUID";
    guids["{F824D60C-995E-4D94-9578-893C755ECB99}"] = "FILTERGUID";
    guids["{02950361-35BB-4A22-9F0B-C78AAA5DB094}"] = "DISPLAYGUID";
    guids["{8E94EF21-70F5-11D3-8F72-00105A9AFD56}"] = "FILEINFOGUID";
    guids["{E4138BC0-7733-11D3-8685-0050044DAAB1}"] = "SRINFOGUID";
    guids["{C728E565-E5A0-4419-93D2-F6CFC69F3B8F}"] = "EVENTTYPEINFOGUID";
    guids["{D01B34A0-9DBD-11D3-93D3-00500400C148}"] = "AUDIOINFOGUID";
    guids["{BF7C95EF-6C3B-4E70-9E11-779BFFF58EA7}"] = "CHANNELGUID";
    guids["{2DEB82A1-D15F-4770-A4A4-CF03815F52DE}"] = "INPUTGUID";
    guids["{5B036022-2EDC-465F-86EC-C0A4AB1A7A91}"] = "INPUTSETTINGSGUID";
    guids["{99A636F2-51F7-4B9D-9569-C7D45058431A}"] = "PHOTICGUID";
    guids["{55C5E044-5541-4594-9E35-5B3004EF7647}"] = "ERRORGUID";
    guids["{223A3CA0-B5AC-43FB-B0A8-74CF8752BDBE}"] = "VIDEOGUID";
    guids["{0623B545-38BE-4939-B9D0-55F5E241278D}"] = "DETECTIONPARAMSGUID";
    guids["{CE06297D-D9D6-4E4B-8EAC-305EA1243EAB}"] = "PAGEGUID";
    guids["{782B34E8-8E51-4BB9-9701-3227BB882A23}"] = "ACCINFOGUID";
    guids["{3A6E8546-D144-4B55-A2C7-40DF579ED11E}"] = "RECCTRLGUID";
    guids["{D046F2B0-5130-41B1-ABD7-38C12B32FAC3}"] = "GUID TRENDINFOGUID";
    guids["{CBEBA8E6-1CDA-4509-B6C2-6AC2EA7DB8F8}"] = "HWINFOGUID";
    guids["{E11C4CBA-0753-4655-A1E9-2B2309D1545B}"] = "VIDEOSYNCGUID";
    guids["{B9344241-7AC1-42B5-BE9B-B7AFA16CBFA5}"] = "SLEEPSCOREINFOGUID";
    guids["{15B41C32-0294-440E-ADFF-DD8B61C8B5AE}"] = "FOURIERSETTINGSGUID";
    guids["{024FA81F-6A83-43C8-8C82-241A5501F0A1}"] = "SPECTRUMGUID";
    guids["{8032E68A-EA3E-42E8-893E-6E93C59ED515}"] = "SIGNALINFOGUID";
    guids["{30950D98-C39C-4352-AF3E-CB17D5B93DED}"] = "SENSORINFOGUID";
    guids["{F5D39CD3-A340-4172-A1A3-78B2CDBCCB9F}"] = "DERIVEDSIGNALINFOGUID";
    guids["{969FBB89-EE8E-4501-AD40-FB5A448BC4F9}"] = "ARTIFACTINFOGUID";
    guids["{02948284-17EC-4538-A7FA-8E18BD65E167}"] = "STUDYINFOGUID";
    guids["{D0B3FD0B-49D9-4BF0-8929-296DE5A55910}"] = "PATIENTINFOGUID";
    guids["{7842FEF5-A686-459D-8196-769FC0AD99B3}"] = "DOCUMENTINFOGUID";
    guids["{BCDAEE87-2496-4DF4-B07C-8B4E31E3C495}"] = "USERSINFOGUID";
    guids["{B799F680-72A4-11D3-93D3-00500400C148}"] = "EVENTGUID";
    guids["{AF2B3281-7FCE-11D2-B2DE-00104B6F4F70}"] = "SHORTSAMPLESGUID";
    guids["{89A091B3-972E-4DA2-9266-261B186302A9}"] = "DELAYLINESAMPLESGUID";
    guids["{291E2381-B3B4-44D1-BB77-8CF5C24420D7}"] = "GENERALSAMPLESGUID";
    guids["{5F11C628-FCCC-4FDD-B429-5EC94CB3AFEB}"] = "FILTERSAMPLESGUID";
    guids["{728087F8-73E1-44D1-8882-C770976478A2}"] = "DATEXDATAGUID";
    guids["{35F356D9-0F1C-4DFE-8286-D3DB3346FD75}"] = "TESTINFOGUID";

    std::vector<unsigned long> misc1(5);
    unsigned long unknown;
    unsigned long indexIdx;
    unsigned long nrTags;
    unsigned long tag_index;

    // Get init
    file.read(reinterpret_cast<char*>(misc1.data()), 5 * sizeof(unsigned long));
    file.read(reinterpret_cast<char *>(&unknown), sizeof(unknown));
    file.read(reinterpret_cast<char *>(&indexIdx), sizeof(indexIdx));

    // Get TAGS structure and Channel IDS
    file.seekg(172);
    file.read(reinterpret_cast<char *>(&nrTags), sizeof(nrTags));

    sections.clear();
    for(int j = 0; j < int(nrTags); j++){
        Tag tag_struct;
        std::vector<unsigned short> uint16Values(40);
        file.read(reinterpret_cast<char*>(uint16Values.data()), 40 * sizeof(unsigned short));
        std::vector<char> charValues(uint16Values.begin(), uint16Values.end());
        charValues.erase(std::find_if(charValues.rbegin(), charValues.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), charValues.end());
        std::string tag(charValues.begin(), charValues.end());
        tag.erase(std::find(tag.begin(), tag.end(), '\0'), tag.end());

        file.read(reinterpret_cast<char *>(&tag_index), sizeof(tag_index));
        tag_struct.index = tag_index;
        tag_struct.tag = tag;
        if (guids.count(tag)){
            tag_struct.IDStr = guids[tag];
        } else {
            if (is_digits(tag)) tag_struct.IDStr = tag;
            else tag_struct.IDStr = "UNKNOWN";
        }
        sections.push_back(tag_struct);
    }

    // QI index
    file.seekg(172208);
    Qi qi;
    file.read(reinterpret_cast<char *>(&qi.nrEntries), sizeof(qi.nrEntries));
    file.read(reinterpret_cast<char *>(&qi.misc1), sizeof(qi.misc1));
    file.read(reinterpret_cast<char *>(&qi.indexIdx), sizeof(qi.indexIdx));
    file.read(reinterpret_cast<char *>(&qi.misc3), sizeof(qi.misc3));
    file.read(reinterpret_cast<char *>(&qi.LQi), sizeof(qi.LQi));

    for(int i = 0; i < 2*int(nrTags); i++){
        unsigned long fidx;
        file.read(reinterpret_cast<char *>(&fidx), sizeof(fidx));
        if (fidx != 0) qi.firstIdx.push_back(fidx);
    }

    // Get Main Index
    int curIdx = 0;
    unsigned long long nextIndexPointer = indexIdx;
    indices.clear();
    indices.reserve(int(qi.nrEntries));

    while (curIdx < int(qi.nrEntries)){
        file.seekg(nextIndexPointer);
        unsigned long long nrIdx;
        file.read(reinterpret_cast<char *>(&nrIdx), sizeof(nrIdx));
        std::vector<unsigned long long> var(3*nrIdx);
        file.read(reinterpret_cast<char*>(var.data()), 3 * nrIdx * sizeof(unsigned long long));

        for (unsigned long long i = 0; i < nrIdx; i++){
            Index index;
            index.sectionIdx = var.at(3*i);
            index.offset = var.at(3*i+1);
            index.blockL = var.at(3*i+2) % 4294967296ULL;
            index.sectionL = var.at(3*i+2) / 4294967296ULL;
            indices.push_back(index);
        }
        file.read(reinterpret_cast<char *>(&nextIndexPointer), sizeof(nextIndexPointer));
        curIdx += (int)nrIdx;
        if(nextIndexPointer == 0) break;
    }

    NiconeHeader nHeader;
    nHeader.patientInfo = readFileProperties("PATIENTINFOGUID", file);
    nHeader.studyInfo = readFileProperties("STUDYINFOGUID", file);
    nHeader.segmentTimes = readSegmentStartTimes(file);
    nHeader.duration = 0;
    for(double d : nHeader.segmentTimes.durations) nHeader.duration += d;

    this->niconeHeader = nHeader;
    std::cout << "Detected " << nHeader.segmentTimes.durations.size() << " segments." << std::endl;

    readDynamicPackets(file);
    readTSInfo();
    std::cout << "Extracted TSInfo for " << tsInfos.size() << " configurations." << std::endl;
    readMontage(file);
    readAnnotationsInternal(file);
    reconstructTimeline();
    std::cout << "Timeline reconstructed with " << timeline.size() << " segments." << std::endl;

    return nHeader;
}

void read_nicolete_file::readDynamicPackets(std::ifstream &file) {
    dynamicPackets.clear();
    auto it = std::find_if(sections.begin(), sections.end(), [](const Tag& v) {
        return v.IDStr == "InfoChangeStream";
    });
    if (it == sections.end()) return;

    int infoIdx = (int)it->index;
    auto idxIt = std::find_if(indices.begin(), indices.end(), [infoIdx](const Index& v) {
        return v.sectionIdx == (unsigned long long)infoIdx;
    });
    if (idxIt == indices.end()) return;

    unsigned long long offset = idxIt->offset;
    int nrDynamicPackets = (int)(idxIt->sectionL / 48);
    file.seekg(offset);

    for (int i = 0; i < nrDynamicPackets; i++) {
        DynamicPacket pkt;
        pkt.offset = offset + i * 48;
        std::vector<uint8_t> guidMixed(16);
        file.read(reinterpret_cast<char*>(guidMixed.data()), 16);
        std::vector<uint8_t> guidNonMixed{guidMixed.at(3), guidMixed.at(2), guidMixed.at(1), guidMixed.at(0),
                                          guidMixed.at(5), guidMixed.at(4), guidMixed.at(7), guidMixed.at(6),
                                          guidMixed.at(8), guidMixed.at(9), guidMixed.at(10), guidMixed.at(11),
                                          guidMixed.at(12), guidMixed.at(13), guidMixed.at(14), guidMixed.at(15)};
        std::stringstream ss;
        for (uint8_t v : guidNonMixed) ss << std::setfill('0') << std::setw(2) << std::hex << (int)v;
        pkt.guid = ss.str();
        for (auto & c : pkt.guid) c = toupper(c);
        pkt.guidAsStr = formatGuid(pkt.guid);

        file.read(reinterpret_cast<char *>(&pkt.date), 8);
        file.read(reinterpret_cast<char *>(&pkt.datefrac), 8);
        file.read(reinterpret_cast<char *>(&pkt.internalOffsetStart), 8);
        file.read(reinterpret_cast<char *>(&pkt.packetSize), 8);

        auto tagIt = std::find_if(sections.begin(), sections.end(), [&](const Tag& v) {
            return v.tag == pkt.guidAsStr;
        });
        if (tagIt != sections.end()) {
            int dIdx = (int)tagIt->index;
            auto dIdxIt = std::find_if(indices.begin(), indices.end(), [dIdx](const Index& v) {
                return v.sectionIdx == (unsigned long long)dIdx;
            });
            if (dIdxIt != indices.end()) {
                pkt.data.resize(pkt.packetSize);
                std::streampos old = file.tellg();
                file.seekg(dIdxIt->offset + pkt.internalOffsetStart);
                file.read(reinterpret_cast<char*>(pkt.data.data()), pkt.packetSize);
                file.seekg(old);
            }
        }

        static std::map<std::string, std::string> gMap = {
            {"BF7C95EF6C3B4E709E11779BFFF58EA7", "CHANNELGUID"},
            {"8A19AA48BEA040D5B89F667FC578D635", "DERIVATIONGUID"},
            {"F824D60C995E4D949578893C755ECB99", "FILTERGUID"},
            {"0295036135BB4A229F0BC78AAA5DB094", "DISPLAYGUID"},
            {"782B34E88E514BB997013227BB882A23", "ACCINFOGUID"},
            {"A271CCCB515D4590B6A1DC170C8D6EE2", "TSGUID"},
            {"D01B34A09DBD11D393D300500400C148", "AUDIOINFOGUID"}
        };
        pkt.IDStr = gMap.count(pkt.guid) ? gMap[pkt.guid] : "UNKNOWN";
        dynamicPackets.push_back(pkt);
    }
}

void read_nicolete_file::readTSInfo() {
    tsInfos.clear();
    for (const auto& pkt : dynamicPackets) {
        if (pkt.IDStr == "TSGUID" && pkt.data.size() >= 761) {
            const uint8_t* d = pkt.data.data();
            uint32_t elems = *reinterpret_cast<const uint32_t*>(d + 752);
            std::vector<ChannelInfo> info;
            size_t off = 760;
            for (uint32_t i = 0; i < elems; i++) {
                if (off + 552 > pkt.data.size()) break;
                ChannelInfo ci;
                std::vector<wchar_t> labelW(TSLABELSIZE + 1, 0);
                std::memcpy(labelW.data(), d + off, TSLABELSIZE * 2);
                ci.label = QString::fromWCharArray(labelW.data()).trimmed();
                
                size_t iOff = TSLABELSIZE * 2;
                std::vector<wchar_t> actW(LABELSIZE + 1, 0);
                std::memcpy(actW.data(), d + off + iOff, LABELSIZE * 2);
                ci.activeSensor = QString::fromWCharArray(actW.data()).trimmed();
                iOff += TSLABELSIZE;

                std::vector<wchar_t> refW(5, 0);
                std::memcpy(refW.data(), d + off + iOff, 8);
                ci.refSensor = QString::fromWCharArray(refW.data()).trimmed();
                iOff += 64; // Correctly align to next block

                ci.dLowCut = *reinterpret_cast<const double*>(d + off + iOff);
                iOff += 8;
                ci.dHighCut = *reinterpret_cast<const double*>(d + off + iOff);
                iOff += 8;
                ci.dSamplingRate = *reinterpret_cast<const double*>(d + off + iOff);
                iOff += 8;
                ci.dResolution = *reinterpret_cast<const double*>(d + off + iOff);
                iOff += 8;
                iOff += 4; // bMark
                iOff += 4; // bNotch
                ci.dEegOffset = *reinterpret_cast<const double*>(d + off + iOff);
                ci.bOn = true;

                std::string tagStr = std::to_string(i);
                auto tIt = std::find_if(sections.begin(), sections.end(), [&](const Tag& v) {
                    return v.tag == tagStr;
                });
                ci.sectionIdx = (tIt != sections.end()) ? (int)tIt->index : -1;

                info.push_back(ci);
                off += 552;
            }
            tsInfos.push_back(info);
        }
    }
}

void read_nicolete_file::readMontage(std::ifstream &file) {
    montage.clear();
    auto it = std::find_if(sections.begin(), sections.end(), [](const Tag& v) {
        return v.IDStr == "DERIVATIONGUID";
    });
    if (it == sections.end()) return;

    int mIdx = (int)it->index;
    auto idxIt = std::find_if(indices.begin(), indices.end(), [mIdx](const Index& v) {
        return v.sectionIdx == (unsigned long long)mIdx;
    });
    if (idxIt == indices.end()) return;

    file.seekg(idxIt->offset + 40);
    file.seekg(64, std::ios::cur); // Skip name
    file.seekg(640, std::ios::cur); // Skip table

    uint32_t nD1, nD2;
    file.read(reinterpret_cast<char*>(&nD1), 4);
    file.read(reinterpret_cast<char*>(&nD2), 4);

    for (uint32_t i = 0; i < nD1; i++) {
        MontageEntry me;
        std::vector<uint16_t> b64(64), b32_1(32), b32_2(32);
        file.read(reinterpret_cast<char*>(b64.data()), 128);
        me.derivationName = QString::fromWCharArray(reinterpret_cast<const wchar_t*>(b64.data()), 64).trimmed();
        file.read(reinterpret_cast<char*>(b32_1.data()), 64);
        me.signalName1 = QString::fromWCharArray(reinterpret_cast<const wchar_t*>(b32_1.data()), 32).trimmed();
        file.read(reinterpret_cast<char*>(b32_2.data()), 64);
        me.signalName2 = QString::fromWCharArray(reinterpret_cast<const wchar_t*>(b32_2.data()), 32).trimmed();
        file.seekg(264, std::ios::cur);
        montage.push_back(me);
    }
}

void read_nicolete_file::readAnnotationsInternal(std::ifstream &file) {
    annotations.clear();
    auto it = std::find_if(sections.begin(), sections.end(), [](const Tag& v) { return v.tag == "Events"; });
    if (it == sections.end()) return;

    int eIdx = (int)it->index;
    auto idxIt = std::find_if(indices.begin(), indices.end(), [eIdx](const Index& v) { return v.sectionIdx == (unsigned long long)eIdx; });
    if (idxIt == indices.end()) return;

    unsigned long long base = idxIt->offset;
    unsigned long long totalL = idxIt->sectionL;
    file.seekg(base);

    static const std::vector<uint8_t> ePktGUID = {0x80, 0xF6, 0x99, 0xB7, 0xA4, 0x72, 0xD3, 0x11, 0x93, 0xD3, 0x00, 0x50, 0x04, 0x00, 0xC1, 0x48};
    QDateTime epoch(QDate(1899, 12, 30), QTime(0, 0, 0));

    unsigned long long curOff = base;
    while (curOff + 272 <= base + totalL) {
        std::vector<uint8_t> pGUID(16);
        if (!file.read(reinterpret_cast<char*>(pGUID.data()), 16) || pGUID != ePktGUID) break;
        uint64_t pLen;
        file.read(reinterpret_cast<char*>(&pLen), 8);
        unsigned long long next = curOff + pLen;

        file.seekg(8, std::ios::cur); // skip ID
        double eDate, eFrac;
        file.read(reinterpret_cast<char*>(&eDate), 8);
        file.read(reinterpret_cast<char*>(&eFrac), 8);
        QDateTime start = epoch.addMSecs((long long)(eDate * 86400000.0 + eFrac * 1000.0));
        if (start.isDaylightTime()) start = start.addSecs(-3600);

        double dur;
        file.read(reinterpret_cast<char*>(&dur), 8);
        QDateTime end = start.addMSecs(dur * 1000.0);

        file.seekg(48, std::ios::cur);
        std::vector<uint16_t> uW(12);
        file.read(reinterpret_cast<char*>(uW.data()), 24);
        QString uName = QString::fromWCharArray(reinterpret_cast<const wchar_t*>(uW.data()), 12).trimmed();
        
        uint64_t tLen;
        file.read(reinterpret_cast<char*>(&tLen), 8);
        std::vector<uint8_t> gM(16);
        file.read(reinterpret_cast<char*>(gM.data()), 16);
        std::vector<uint8_t> gN{gM.at(3), gM.at(2), gM.at(1), gM.at(0), gM.at(5), gM.at(4), gM.at(7), gM.at(6), gM.at(8), gM.at(9), gM.at(10), gM.at(11), gM.at(12), gM.at(13), gM.at(14), gM.at(15)};
        std::stringstream ss;
        ss << "{";
        for(int k=0; k<16; k++) {
            ss << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (int)gN[k];
            if(k==3 || k==5 || k==7 || k==9) ss << "-";
        }
        ss << "}";
        QString eGUID = QString::fromStdString(ss.str());

        Annotation an; an.start = start; an.end = end; an.system = true;
        if (eGUID == "{A5A95612-A7F8-11CF-831A-0800091B5BDA}" || eGUID == "{A5A95646-A7F8-11CF-831A-0800091B5BDA}") {
            an.system = false;
            file.seekg(80 + 32, std::ios::cur); // Reserved4 + Label + Reserved5
            if (tLen > 0 && tLen < 10000) {
                std::vector<uint16_t> tW(tLen);
                file.read(reinterpret_cast<char*>(tW.data()), tLen * 2);
                an.text = QString::fromWCharArray(reinterpret_cast<const wchar_t*>(tW.data()), (int)tLen).trimmed();
            }
            if (!uName.isEmpty() && !uName.contains("Nicolet", Qt::CaseInsensitive)) an.text = uName + ": " + an.text;
        } else {
            static std::map<QString, QString> sMap = {
                {"{08784382-C765-11D3-90CE-00104B6F4F70}", "Format change"},
                {"{6FF394DA-D1B8-46DA-B78F-866C67CF02AF}", "Photic"},
                {"{481DFC97-013C-4BC5-A203-871B0375A519}", "Posthyperventilation"},
                {"{725798BF-CD1C-4909-B793-6C7864C27AB7}", "Review progress"},
                {"{96315D79-5C24-4A65-B334-E31A95088D55}", "Exam start"},
                {"{A5A95608-A7F8-11CF-831A-0800091B5BDA}", "Hyperventilation"},
                {"{A5A95617-A7F8-11CF-831A-0800091B5BDA}", "Impedance"},
                {"{A71A6DB5-4150-48BF-B462-1C40521EBD6F}", "Amplifier Disconnect"},
                {"{6387C7C8-6F98-4886-9AF4-FA750ED300DE}", "Amplifier Reconnect"},
                {"{71EECE80-EBC4-41C7-BF26-E56911426FB4}", "Recording Paused"},
                {"{A5A95645-A7F8-11CF-831A-0800091B5BDA}", "ID_6_12HRS"}
            };
            if (sMap.count(eGUID)) an.text = sMap[eGUID];
            // Skip unknown noisy events
        }
        if (!an.text.isEmpty()) annotations.push_back(an);
        curOff = next; file.seekg(curOff);
    }
}

void read_nicolete_file::reconstructTimeline() {
    timeline.clear();
    for (size_t i = 0; i < niconeHeader.segmentTimes.segmentStartTimes.size(); i++) {
        TimelineSection sec;
        sec.start = niconeHeader.segmentTimes.segmentStartTimes[i];
        sec.durationSeconds = niconeHeader.segmentTimes.durations[i];
        sec.end = sec.start.addMSecs(sec.durationSeconds * 1000.0);
        sec.tsInfoIdx = (i < tsInfos.size()) ? (int)i : (int)tsInfos.size() - 1;
        timeline.push_back(sec);
    }
}

read_nicolete_file::SegmentTimes read_nicolete_file::readSegmentStartTimes(std::ifstream &file){
    QDateTime epoch(QDate(1899, 12, 30), QTime(0, 0, 0));
    SegmentTimes sT;
    Index Idx = getSectionIdx("SegmentStream");
    file.seekg(Idx.offset);
    int nr = (int)(Idx.sectionL/152);
    for(int i = 0; i < nr; i++){
        double dOLE;
        file.read(reinterpret_cast<char *>(&dOLE), 8);
        QDateTime rStart = epoch.addMSecs((long long)(dOLE * 86400000.0));
        if(rStart.isDaylightTime()) rStart = rStart.addSecs(-3600);
        qDebug() << rStart.toString("dd.MM.yyyy hh:mm:ss.zzz");
        file.seekg(8, std::ios_base::cur);
        double dur;
        file.read(reinterpret_cast<char *>(&dur), 8);
        sT.segmentStartTimes.push_back(rStart);
        sT.durations.push_back(dur);
        file.seekg(128, std::ios_base::cur);
    }
    return sT;
}

std::vector<QString> read_nicolete_file::readFileProperties(std::string sectionName, std::ifstream &file){
    std::vector<unsigned char> g(16);
    std::vector<QString> out;
    Index Idx = getSectionIdx(sectionName);
    file.seekg(Idx.offset);
    file.read(reinterpret_cast<char *>(g.data()), 16);
    unsigned long long lS, nV, nB;
    file.read(reinterpret_cast<char *>(&lS), 8);
    file.read(reinterpret_cast<char *>(&nV), 8);
    file.read(reinterpret_cast<char *>(&nB), 8);
    for(unsigned long long i = 0; i < nV; i++){
        unsigned long long id; double v;
        file.read(reinterpret_cast<char *>(&id), 8);
        if (id == 7 || id == 8 || id == 23 || id == 24) file.read(reinterpret_cast<char *>(&v), 8);
    }
    std::vector<unsigned long long> sS(nB*2);
    file.read(reinterpret_cast<char*>(sS.data()), nB*2*8);
    for(unsigned long long i = 0; i < nB; i++){
        out.push_back(readUint16toQString((int)sS.at(i*2+1)+1, file));
    }
    return out;
}

read_nicolete_file::Index read_nicolete_file::getSectionIdx(std::string sN){
    auto it = std::find_if(sections.begin(), sections.end(), [&](const Tag& v) { return v.IDStr == sN; });
    unsigned long long sIdx = (it != sections.end()) ? it->index : 0;
    auto id = std::find_if(indices.begin(), indices.end(), [&](const Index& v) { return v.sectionIdx == sIdx; });
    return (id != indices.end()) ? *id : Index{0,0,0,0};
}

bool read_nicolete_file::is_digits(std::string& str){
    for (char ch : str) if (!isdigit(ch)) return false;
    return true;
}

std::string read_nicolete_file::formatGuid(const std::string& gS) {
    if (gS.length() != 32) return "{}";
    std::string u = gS; for (char &c : u) c = toupper(c);
    return "{" + u.substr(0, 8) + "-" + u.substr(8, 4) + "-" + u.substr(12, 4) + "-" + u.substr(16,4) + "-" + u.substr(20,12) + "}";
}

QString read_nicolete_file::readUint16toQString(int size, std::ifstream &file){
    std::vector<wchar_t> w(size);
    file.read(reinterpret_cast<char*>(w.data()), size * 2);
    return QString::fromWCharArray(w.data()).trimmed();
}

int read_nicolete_file::readNicOneFile(QFileInfo info) {
    if (!info.exists()) return 1;
    file_info = info;
    std::ifstream file(info.absoluteFilePath().toLocal8Bit().constData(), std::ios::binary);
    if (!file.is_open()) return 1;
    read_nicolete_header(file);
    file.close();
    return 0;
}

int read_nicolete_file::exportToEdf(QFileInfo infoEdf, bool exportSystemAnnotations, bool anonymize, bool export2ascii) {
    if (timeline.empty()) return 1;
    std::string fN, pC; std::vector<int> bD;
    if (anonymize) { fN = "Anonymous"; pC = "X"; bD = {1901, 1, 1}; }
    else {
        fN = (niconeHeader.patientInfo.size() >= 4) ? (niconeHeader.patientInfo[2] + " " + niconeHeader.patientInfo[1]).toLocal8Bit().constData() : "Unknown";
        pC = (niconeHeader.patientInfo.size() >= 4) ? niconeHeader.patientInfo[3].toStdString() : "X";
        bD = birthDateFromID(pC);
    }

    std::ifstream file(file_info.absoluteFilePath().toLocal8Bit().constData(), std::ios::binary);
    std::map<unsigned long long, std::vector<const Index*>> gI;
    for (const auto& idx : indices) gI[idx.sectionIdx].push_back(&idx);

    for (int i = 0; i < (int)timeline.size(); i++) {
        const auto& sec = timeline[i];
        const auto& channels = tsInfos[sec.tsInfoIdx];
        std::string oP = infoEdf.absoluteFilePath().toStdString();
        if (timeline.size() > 1) { size_t dot = oP.find_last_of("."); oP.insert(dot, "_part_" + std::to_string(i + 1)); }
        int hdl = edfopen_file_writeonly(oP.c_str(), EDFLIB_FILETYPE_EDFPLUS, (int)channels.size());
        if (hdl < 0) return 1;

        edf_set_patientname(hdl, fN.c_str());
        edf_set_patientcode(hdl, pC.c_str());
        if (bD[0] > 0) edf_set_birthdate(hdl, bD[0], bD[1], bD[2]);
        edf_set_equipment(hdl, "Nicolet");
        edf_set_startdatetime(hdl, sec.start.date().year(), sec.start.date().month(), sec.start.date().day(), sec.start.time().hour(), sec.start.time().minute(), sec.start.time().second());

        for (int ch = 0; ch < (int)channels.size(); ch++) {
            const auto& ci = channels[ch];
            QString label = ci.label;
            // Try to map amplifier name to montage label
            for (const auto& me : montage) {
                if (me.signalName1 == ci.label || me.signalName1 == ci.activeSensor) {
                    label = me.derivationName; break;
                }
            }
            edf_set_samplefrequency(hdl, ch, (int)std::round(ci.dSamplingRate));
            edf_set_label(hdl, ch, label.toLocal8Bit().constData());
            edf_set_physical_dimension(hdl, ch, "uV");
            edf_set_digital_maximum(hdl, ch, 32767);
            edf_set_digital_minimum(hdl, ch, -32768);
            double phys = 32767.0 * ci.dResolution;
            if (std::abs(phys) < 0.0001) phys = 3276.7;
            edf_set_physical_maximum(hdl, ch, phys);
            edf_set_physical_minimum(hdl, ch, -phys);
        }

        double expD = 0;
        while (expD < sec.durationSeconds - 0.001) {
            double cD = std::min(300.0, sec.durationSeconds - expD);
            unsigned long long minO = 0xFFFFFFFFFFFFFFFFULL, maxO = 0;
            std::vector<std::vector<const Index*>> cC(channels.size());
            bool data = false;
            for (int ch = 0; ch < (int)channels.size(); ch++) {
                const auto& ci = channels[ch];
                if (ci.sectionIdx < 0 || !gI.count((unsigned long long)ci.sectionIdx)) continue;
                long long tS = (long long)std::floor(expD * ci.dSamplingRate);
                long long tE = (long long)std::ceil((expD + cD) * ci.dSamplingRate);
                long long cS = 0;
                for (const auto* idx : gI[(unsigned long long)ci.sectionIdx]) {
                    long long bS = idx->sectionL / 2;
                    if (cS + bS > tS && cS < tE) {
                        cC[ch].push_back(idx);
                        minO = std::min(minO, idx->offset);
                        maxO = std::max(maxO, idx->offset + idx->sectionL);
                        data = true;
                    }
                    cS += bS; if (cS >= tE) break;
                }
            }
            if (data && maxO > minO) {
                std::vector<int16_t> dBuf((maxO - minO) / 2);
                file.clear(); file.seekg(minO); file.read(reinterpret_cast<char*>(dBuf.data()), maxO - minO);
                int fS = (int)std::floor(cD);
                for (int s = 0; s < fS; s++) {
                    for (int ch = 0; ch < (int)channels.size(); ch++) {
                        const auto& ci = channels[ch];
                        int fs = (int)std::round(ci.dSamplingRate);
                        std::vector<double> pB(fs);
                        long long sS = (long long)std::round((expD + s) * ci.dSamplingRate);
                        long long bSS = 0; int sEx = 0;
                        if (gI.count((unsigned long long)ci.sectionIdx)) {
                            for (const auto* b : gI[(unsigned long long)ci.sectionIdx]) {
                                long long bSm = b->sectionL / 2;
                                if (bSS + bSm > sS) {
                                    long long oIB = std::max(0LL, sS - bSS);
                                    long long tT = std::min((long long)fs - sEx, bSm - oIB);
                                    size_t bP = (b->offset - minO) / 2 + oIB;
                                    for (int k = 0; k < (int)tT; k++) pB[sEx + k] = (double)dBuf[bP + k] * ci.dResolution;
                                    sEx += (int)tT;
                                }
                                bSS += bSm; if (sEx >= fs) break;
                            }
                        }
                        edfwrite_physical_samples(hdl, pB.data());
                    }
                }
                expD += fS;
            } else expD += cD;
        }

        for (const auto& ann : annotations) {
            if (!exportSystemAnnotations && ann.system) continue;
            if (ann.start >= sec.start && ann.start <= sec.end) {
                long long onset = sec.start.msecsTo(ann.start) * 10;
                long long duration = ann.start.msecsTo(ann.end) * 10;
                if (duration <= 0) duration = -1;
                if (export2ascii) edfwrite_annotation_ascii(hdl, onset, duration, ann.text.toLocal8Bit().constData());
                else edfwrite_annotation_utf8(hdl, onset, duration, ann.text.toUtf8().constData());
            }
        }
        edfclose_file(hdl);
    }
    file.close();
    return 0;
}

std::vector<int> read_nicolete_file::birthDateFromID(std::string id) {
    if (id == "0" || id.length() < 6) return {0, 0, 0};
    int y = std::stoi(id.substr(0, 2)), m = std::stoi(id.substr(2, 2)), d = std::stoi(id.substr(4, 2));
    if (m > 12) m -= 50;
    if (y < 54 && id.length() >= 10) y += 2000; else y += 1900;
    return {y, m, d};
}
