#include "read_nicolete_file.h"

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
    guids["{AF2B3281-7FCE-11D2-B2DE-00104B6FC652}"] = "SHORTSAMPLESGUID";
    guids["{89A091B3-972E-4DA2-9266-261B186302A9}"] = "DELAYLINESAMPLESGUID";
    guids["{291E2381-B3B4-44D1-BB77-8CF5C24420D7}"] = "GENERALSAMPLESGUID";
    guids["{5F11C628-FCCC-4FDD-B429-5EC94CB3AFEB}"] = "FILTERSAMPLESGUID";
    guids["{728087F8-73E1-44D1-8882-C770976478A2}"] = "DATEXDATAGUID";
    guids["{35F356D9-0F1C-4DFE-8286-D3DB3346FD75}"] = "TESTINFOGUID";

    std::map<std::string, std::string> dynamic_guids;
    dynamic_guids["BF7C95EF6C3B4E709E11779BFFF58EA7"] = "CHANNELGUID";
    dynamic_guids["8A19AA48BEA040D5B89F667FC578D635"] = "DERIVATIONGUID";
    dynamic_guids["F824D60C995E4D949578893C755ECB99"] = "FILTERGUID";
    dynamic_guids["0295036135BB4A229F0BC78AAA5DB094"] = "DISPLAYGUID";
    dynamic_guids["782B34E88E514BB997013227BB882A23"] = "ACCINFOGUID";
    dynamic_guids["A271CCCB515D4590B6A1DC170C8D6EE2"] = "TSGUID";
    dynamic_guids["D01B34A09DBD11D393D300500400C148"] = "AUDIOINFOGUID";

    std::vector<unsigned long> misc1(5);
    unsigned long unknown;
    unsigned long indexIdx;
    unsigned long nrTags;
    unsigned long tag_index;
    std::string tag;

    // Get init
    file.read(reinterpret_cast<char*>(misc1.data()), 5 * sizeof(unsigned long)); //#ok<NASGU>
    file.read(reinterpret_cast<char *>(&unknown), sizeof(unknown)); //#ok<NASGU>
    file.read(reinterpret_cast<char *>(&indexIdx), sizeof(indexIdx));

    //std::cout << misc1.at(0) << " "<< misc1.at(1) << " "<< misc1.at(2) << " "<< misc1.at(3) << " "<< misc1.at(4) << " "<< unknown << " " << indexIdx << std::endl;

    // Get TAGS structure and Channel IDS
    file.seekg(172); // fseek(h, 172,'bof');
    file.read(reinterpret_cast<char *>(&nrTags), sizeof(nrTags));
    //std::cout << "nrTags: " << nrTags << std::endl;
    //std::cout << file.tellg() << std::endl;

    for(int j = 0; j < int(nrTags); j++){
        Tag tag_struct;
        //        for(int i = 0; i < 80; i ++){ // like reading 40*int
        //            file.read(reinterpret_cast<char *>(&t), sizeof(t));
        //            tag += t;
        //        }

        // Read 40 uint16 values from the file
        std::vector<uint16_t> uint16Values(40);
        file.read(reinterpret_cast<char*>(uint16Values.data()), 40 * sizeof(uint16_t));

        // Convert uint16 values to characters
        std::vector<char> charValues(uint16Values.begin(), uint16Values.end());

        // Remove trailing white spaces
        charValues.erase(std::find_if(charValues.rbegin(), charValues.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), charValues.end());

        // Convert char values to std::string
        std::string tag(charValues.begin(), charValues.end());

        tag.erase(std::find(tag.begin(), tag.end(), '\0'), tag.end());

        file.read(reinterpret_cast<char *>(&tag_index), sizeof(tag_index));
        tag_struct.index = tag_index;
        tag_struct.tag = tag;
        if (guids.find(tag) == guids.end()){
            //std::cout << "not found" << std::endl;

            if (is_digits(tag)){
                //std::cout << "is digits" << std::endl;
                tag_struct.IDStr = tag;
            }
            else{
                tag_struct.IDStr = "UNKNOWN";
            }
        }
        else{
            tag_struct.IDStr = guids[tag];
        }
        sections.push_back(tag_struct);
        //        std::cout <<  "tag: " << tag_struct.tag << std::endl;
        //        std::cout << "tag_index: " << tag_struct.index << std::endl;
        //        std::cout << "IDStr: " << tag_struct.IDStr << std::endl;
        //        std::cout << "-------------------------------" << std::endl;
    }

    // QI index
    file.seekg(172208);
    unsigned long fidx;
    Qi qi;
    file.read(reinterpret_cast<char *>(&qi.nrEntries), sizeof(qi.nrEntries));
    file.read(reinterpret_cast<char *>(&qi.misc1), sizeof(qi.misc1));
    file.read(reinterpret_cast<char *>(&qi.indexIdx), sizeof(qi.indexIdx));
    file.read(reinterpret_cast<char *>(&qi.misc3), sizeof(qi.misc3));
    file.read(reinterpret_cast<char *>(&qi.LQi), sizeof(qi.LQi));

    for(int i = 0; i < 2*int(nrTags); i++){
        file.read(reinterpret_cast<char *>(&fidx), sizeof(fidx));
        if (fidx != 0){
            qi.firstIdx.push_back(fidx);
        }

    }

    //std::cout << "nrEntries: "<< qi.nrEntries << " misc1: " << qi.misc1 << " indexIdx: " << qi.indexIdx << " misc3: "<< qi.misc3 << " LQi: " << qi.LQi << std::endl;
    // for (const auto& i: qi.firstIdx)
    //     std::cout << i << std::endl;


    // ================================ Get Main Index ===============================================
    // Index consists of multiple blocks, after each block is the pointer to the next block. Total number of entries is in obj.Qi.nrEntries

    int curIdx = 0;
    unsigned long long nextIndexPointer = indexIdx;
    unsigned long long nrIdx;

    indices.reserve(int(qi.nrEntries)); // Preallocate indices

    while (curIdx < int(qi.nrEntries)){
        //std::cout << "curIdx: " << curIdx << std::endl;
        file.seekg(nextIndexPointer);
        file.read(reinterpret_cast<char *>(&nrIdx), sizeof(nrIdx));
        //std::cout << "nrIdx: " << nrIdx << std::endl;

        // Read nrIdx*3 uint64 values from the file
        std::vector<uint64_t> var(3*nrIdx); // preallocate it to 3* nrIdx // // tady vznik� probl�m, kdy� tam nab�hne moc velk� ��slo, nap�. 18239012444179594585
        file.read(reinterpret_cast<char*>(var.data()), 3 * nrIdx * sizeof(uint64_t));

        //std::cout << "after reading data: " << file.tellg() << std::endl;

        //std::cout << "var size: "<< var.size() << std::endl;
        //for (const auto& i: var)
        //  std::cout << i << std::endl;
        //std::cout << "make the index" << std::endl;

        for (unsigned long long i = 0; i < nrIdx; i++){
            Index index;
            index.sectionIdx = var.at(3*i); // 0,3,6,9
            index.offset = var.at(3*i+1); // 1,4,7,10
            index.blockL = var.at(3*i+2) % 4294967296; // 4294967296 = 2^32 // 2,5,8,10
            index.sectionL = round(var.at(3*i+2)/4294967296); // or you can use static_cast<unsigned long long>(pow(2,32))
            //std::cout << "sectionIdx: "<< index.sectionIdx << " offset: " << index.offset << " blockL: " << index.blockL << " sectionL: "<< index.sectionL << std::endl;
            indices.push_back(index);
        }
        file.read(reinterpret_cast<char *>(&nextIndexPointer), sizeof(nextIndexPointer)); // 49 168 chars apart
        //std::cout << "nextIndexPointer: " << nextIndexPointer << std::endl;
        curIdx = curIdx + nrIdx;

        if(nextIndexPointer == 0){
            break;
        }
    }

    // read the actual data

    NiconeHeader niconeHeader;

    // ===================================== Get PatientGUID =====================================================

    niconeHeader.patientInfo = readFileProperties("PATIENTINFOGUID",file);

    // ===================================== Get FileInfo =====================================================

    niconeHeader.studyInfo = readFileProperties("STUDYINFOGUID",file);

    // ===================================== Get Segment Start Times =====================================================

    niconeHeader.segmentTimes = readSegmentStartTimes(file);

//    for (int i = 0; i < 200; i++){
//        std::cout << i << " sectionIdx: "<< indices.at(i).sectionIdx << " offset: " << indices.at(i).offset << " blockL: " << indices.at(i).blockL << " sectionL: "<< indices.at(i).sectionL << std::endl;
//    }

    return niconeHeader;
}

read_nicolete_file::SegmentTimes read_nicolete_file::readSegmentStartTimes(std::ifstream &file){

    QDateTime beginning_of_epoch(QDate(1899, 12,30), QTime(0, 0, 0));
    QDateTime record_start;

    double dateOLE;
    double duration;

    SegmentTimes segmentTimes;

    Index Idx = getSectionIdx("SegmentStream");
    //std::cout << Idx.offset << std::endl;
    file.seekg(Idx.offset);
    int nrSegments = Idx.sectionL/152;

    //std::cout << file.tellg() << std::endl;

    //obj.segments = struct();

    for(int i = 0; i < nrSegments; i++){
        file.read(reinterpret_cast<char *>(&dateOLE), sizeof(dateOLE)); // number of days since 30.12.1899 (I think since that is what empty fields in patient info equal to)
        //std::cout << "dateOLE: " << dateOLE << std::endl;
        record_start = beginning_of_epoch.addSecs(3600*24*dateOLE);

        if(record_start.isDaylightTime()){
            record_start = record_start.addSecs(-3600); // not sure why this is not automatic
        }

        qDebug() << record_start.toString("dd.MM.yyyy hh:mm:ss");
        file.seekg(8,std::ios_base::cur); //fseek(h, 8 , 'cof'); //16
        file.read(reinterpret_cast<char *>(&duration), sizeof(duration));;//24
        //std::wcout << "duration: " << duration << std::endl;

        segmentTimes.segmentStartTimes.push_back(record_start);
        segmentTimes.durations.push_back(duration);

        file.seekg(128,std::ios_base::cur);// fseek(h, 128 , 'cof'); %152
    }

    return segmentTimes;
}


std::vector<QString> read_nicolete_file::readFileProperties(std::string sectionName, std::ifstream &file){
    unsigned long long lSection;
    unsigned long long nrValues;
    unsigned long long nrBstr;
    unsigned long long id;
    double value;
    double unix_time;
    QString value_str;
    std::vector<uint8_t> guid_vec(16);
    std::vector<QString> output;

    //    info = struct();

    //    infoProps = { 'patientID', 'firstName','middleName','lastName',...
    //        'altID','mothersMaidenName','DOB','DOD','street','sexID','phone',...
    //        'notes','dominance','siteID','suffix','prefix','degree','apartment',...
    //        'city','state','country','language','height','weight','race','religion',...
    //        'maritalStatus'};

    Index Idx = getSectionIdx(sectionName);
    file.seekg(Idx.offset);

    file.read(reinterpret_cast<char *>(guid_vec.data()), 16*sizeof(uint8_t));
    //    std::cout << "guid: " << std::endl;
    //    for (const auto& i: guid_vec)
    //        std::cout << int(i) << std::endl;
    file.read(reinterpret_cast<char *>(&lSection), sizeof(lSection));
    file.read(reinterpret_cast<char *>(&nrValues), sizeof(nrValues));
    //       reserved = fread(h, 3, 'uint16'); %#ok<NASGU>
    file.read(reinterpret_cast<char *>(&nrBstr), sizeof(nrBstr));


    //    std::cout << "lSection: " << lSection << std::endl;
    //    std::cout << "nrValues: " << nrValues << std::endl;
    //    std::cout << "nrBstr: " << nrBstr << std::endl;

    for(unsigned long long i = 0; i < nrValues; i++){
        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        switch(id){
        case 7:
        case 8:
            file.read(reinterpret_cast<char *>(&unix_time), sizeof(unix_time));
            unix_time = unix_time*(3600*24) - 2209161600; // 2208988800; %8
            //obj.segments(i).dateStr = datestr(unix_time/86400 + datenum(1970,1,1));
            //value = datevec( obj.segments(i).dateStr );
            //value = value([3 2 1]);
            break;
        case 23:
        case 24:
            file.read(reinterpret_cast<char *>(&value), sizeof(value));
            break;
        default:
            value = 0;
        }
        //info.(infoProps{id}) = value;

    }

    std::vector<unsigned long long> strSetup(nrBstr*2);
    file.read(reinterpret_cast<char*>(strSetup.data()), nrBstr*2*sizeof(uint64_t));

    //    for (const auto& i: strSetup)
    //        std::cout << i << std::endl;

    for(unsigned long long i = 0; i < nrBstr*2; i ++){
        //std::cout << "loop no: " << i << std::endl;
        if ( i % 2 == 0 ){
            id = strSetup.at(i);
            //std::cout << "strSetup.at(i): " << strSetup.at(i) << std::endl;
            //std::cout << "strSetup.at(i+1): " << strSetup.at(i+1) << std::endl;
            value_str = readUint16toQString(strSetup.at(i+1)+1,file);
            output.push_back(value_str);
            qDebug() << "value_str: " << value_str;
            //std::cout << "------------------" << std::endl;
            //info.(infoProps{id}) = value_str;
        }
    }

    return output;
}

read_nicolete_file::Index read_nicolete_file::getSectionIdx(std::string sectionName){

    std::cout << sectionName << std::endl;

    unsigned long long sectionIdx;
    //unsigned long long offset;

    auto it = std::find_if(sections.begin(), sections.end(),[&sectionName](const Tag& v) {
        return v.IDStr == sectionName;
    });

    if (it != sections.end())
    {
        std::cout << "it: " << (*it).index << std::endl;
        sectionIdx = (*it).index; // because the original is from MATLAB where indexing starts at 1
    }

    //std::cout << "sectionIdx: " << sectionIdx << std::endl;

    auto id = std::find_if(indices.begin(), indices.end(),[&sectionIdx](const Index& id) {
        return id.sectionIdx == sectionIdx;
    });

    if (id != indices.end())
    {
        std::cout << "id: " << (*id).offset << std::endl;
    }
    return (*id);
}

bool read_nicolete_file::is_digits(std::string& str){
    for (char ch : str) {
        if (!isdigit(ch)){
            return false;
        }
    }
    return true;
}

std::string read_nicolete_file::hexVectorTostring(std::vector<uint8_t>& vec){
    std::stringstream result;
    for (const auto& v : vec)
    {
        result
                << std::setfill('0') << std::setw(sizeof(v) * 2)
                << std::hex << +v;
    }
    return result.str();
}

std::string read_nicolete_file::formatGuid(const std::string& guidStr) {

    std::string upperStr = guidStr;

    for (unsigned long long i = 0; i < guidStr.length(); i++) {
        upperStr[i] = toupper(guidStr[i]);
    }

    // D01B34A0-9DBD-11D3-93D3-00500400C148
    if (guidStr.length() != 32) {
        // GUID should be a 32-character hexadecimal string
        return "{}";
    }

    // Insert hyphens at specific positions
    std::string formattedGuid = "{" +
            upperStr.substr(0, 8) + "-" +
            upperStr.substr(8, 4) + "-" +
            upperStr.substr(12, 4) + "-" +
            upperStr.substr(16,4) + "-" +
            upperStr.substr(20,12) + "}";
    return formattedGuid;
}

QString read_nicolete_file::readUint16toQString(int size, std::ifstream &file){
    // Read n uint16 values from the file
    std::vector<wchar_t> uint16Values(size);
    file.read(reinterpret_cast<char*>(uint16Values.data()), size * sizeof(uint16_t));

    //    for (const auto& i: uint16Values){
    //        std::wcout << i << " = " << char(i) << std::endl;
    //        //std::wcout << wchar_t(i) << std::endl;
    //    }

    QString res = QString::fromWCharArray(uint16Values.data()); // this has proven to be the simples way

    //qDebug() << res;
    // the rest of it is not needed since I use QString::fromWCharArray
    //    // Convert uint16 values to characters
    //    std::vector<wchar_t> charValues(uint16Values.begin(), uint16Values.end());

    //    // Remove trailing white spaces
    //    charValues.erase(std::find_if(charValues.rbegin(), charValues.rend(), [](int ch) {
    //        return !std::isspace(ch);
    //    }).base(), charValues.end());

    //    // Convert char values to std::string
    //    std::string chars(charValues.begin(), charValues.end());

    //    chars.erase(std::find(chars.begin(), chars.end(), '\0'), chars.end());
    //    return chars;
    return res;
}
