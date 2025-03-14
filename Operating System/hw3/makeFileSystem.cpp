#include<iostream>
#include<fstream>
#include<cstring>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/file.h>
#include<cerrno>
#include<cstdint>
#include<vector>
using namespace std;

typedef  uint8_t  byte1;   // 1 byte
typedef  uint16_t  byte2; // 2 bytes
typedef  uint32_t  byte4; // 4 bytes






class SuperBlock{
private:
    char diskName[20];
    byte4 diskSize;
    float blockSize;
    byte4 numberOfEntry;
    byte4 numberOfBlock;
    byte4 totalByte;
    byte4 bootSectorPosition;
    byte4 fatTablePosition;
    byte4 rootDirPosition;
    byte4 dataStartPosition;

public:
    // getter methods
    char* getDiskName() { return diskName; }
    byte4 getDiskSize() { return diskSize; }
    float getBlockSize() { return blockSize; }
    byte4 getNumberOfEntry() { return numberOfEntry; }
    byte4 getNumberOfBlock() { return numberOfBlock; }
    byte4 getTotalByte() { return totalByte; }
    byte4 getBootSectorPosition() { return bootSectorPosition; }
    byte4 getFatTablePosition() { return fatTablePosition; }
    byte4 getRootDirPosition() { return rootDirPosition; }
    byte4 getDataStartPosition() { return dataStartPosition; }

    // setter methods
    void setDiskName(char* name) { strncpy(diskName, name, sizeof(diskName)); }
    void setDiskSize(byte4 size) { diskSize = size; }
    void setBlockSize(float size) { blockSize = size; }
    void setNumberOfEntry(byte4 number) { numberOfEntry = number; }
    void setNumberOfBlock(byte4 number) { numberOfBlock = number; }
    void setTotalByte(byte4 total) { totalByte = total; }
    void setBootSectorPosition(byte4 position) { bootSectorPosition = position; }
    void setFatTablePosition(byte4 position) { fatTablePosition = position; }
    void setRootDirPosition(byte4 position) { rootDirPosition = position; }
    void setDataStartPosition(byte4 position) { dataStartPosition = position; }
};

class Entry{
private:
    char fileName[8]; //8 byte
    char extension[3]; // 3 byte
    byte1 attributes; // 1 byte
    char reserved[10]; //10 byte
    byte2 time; // 2 byte
    byte2 date; // 2 byte
    byte2 firstBlockNumber; // 2 byte
    byte4 fileSize; // 4 byte

public:
    // getter methods
    char* getFileName() { return fileName; }
    char* getExtension() { return extension; }
    byte1 getAttributes() { return attributes; }
    char* getReserved() { return reserved; }
    byte2 getTime() { return time; }
    byte2 getDate() { return date; }
    byte2 getFirstBlockNumber() { return firstBlockNumber; }
    byte4 getFileSize() { return fileSize; }

    // setter methods
    void setFileName(char* name) { strncpy(fileName, name, sizeof(fileName)); }
    void setExtension(char* ext) { strncpy(extension, ext, sizeof(extension)); }
    void setAttributes(byte1 attr) { attributes = attr; }
    void setReserved(char* res) { strncpy(reserved, res, sizeof(reserved)); }
    void setTime(byte2 t) { time = t; }
    void setDate(byte2 d) { date = d; }
    void setFirstBlockNumber(byte2 number) { firstBlockNumber = number; }
    void setFileSize(byte4 size) { fileSize = size; }
};

class FAT {
private:
    std::vector<byte2> fatEntries; // Vector to store FAT entries
     // random example size
public:
    // Constructor
    FAT() {}

    // Load FAT table from file
    void loadFAT(const std::string& filename,int size);

    // Print FAT table
    void printFAT() {
        std::cout << "FAT Table Example First 7 Blocks" << std::endl;
        for (size_t i = 0; i < 7; i++) {
            std::cout << "Entry " << i << ": " << fatEntries[i] << std::endl;
        }
    }
};


int capacity = 0;

byte1 *freeBlocksBitmap = nullptr;

Entry *directories = nullptr;

void createFile(double blockSize, char *fileName);
int openFile(char *fileName);
void initSystem(float blockSize, char *fileName);
void printInfo(SuperBlock disk);

int main(int argc, char *argv[]){
    FAT fat;
    if (argc != 3){
        cout << "Arguments are wrong!!" << endl;
        exit(EXIT_FAILURE);
    }
    float blockSize = atof(argv[1]);
    createFile(blockSize, argv[2]);
    
    fat.loadFAT(argv[2],atoi(argv[1]));
    fat.printFAT();
    return 0;
}

int openFile(char *fileName){
    int fd = open(fileName, O_RDWR|O_CREAT|O_EXCL, 0666);
    if(fd < 0) {
        if (errno == EEXIST){
            remove(fileName);
            return openFile(fileName);
        }
        exit(EXIT_FAILURE);
    }
    return fd;
}

void createFile(double blockSize, char *fileName){
    int fileSize;
    if (blockSize == 0.50) {
        fileSize = 2048;
    }
    else if (blockSize == 1.0) {
        fileSize = 4096;
    }
    else if (blockSize == 2.0) {
        fileSize = 8192;
    }
    else if (blockSize == 4.0) {
        fileSize = 16384;
    }
    else{
        cout << "Wrong block Size, Try Again!" << endl;
        exit(EXIT_FAILURE);
    }
    int fd = openFile(fileName);
    ftruncate(fd, fileSize*1024);
    close(fd);
    initSystem(blockSize, fileName);
}

void initSystem(float blockSize, char *fileName){
    int fileSize;
    int mb;
    if (blockSize == 0.5) {
        fileSize = 2048;
        mb = 2;
    }
    else if (blockSize == 1.0) {
        fileSize = 4096;
        mb = 4;
    }
    else if (blockSize == 2.0) {
        fileSize = 8192;
        mb = 8;
    }
    else if (blockSize == 4.0) {
        fileSize = 16384;
        mb = 16;
    }
    SuperBlock disk;
    disk.setBlockSize(blockSize);
    disk.setDiskSize(mb);
    disk.setNumberOfEntry((fileSize*1024) / 32);
    disk.setNumberOfBlock(fileSize / blockSize);
    disk.setTotalByte(fileSize*1024);
    disk.setBootSectorPosition(0);
    disk.setFatTablePosition(disk.getTotalByte() - (disk.getTotalByte() - sizeof(SuperBlock)) + 1);
    disk.setRootDirPosition(disk.getTotalByte() - (disk.getTotalByte() - sizeof(SuperBlock) - (18 * disk.getBlockSize()*1024)));
    disk.setDataStartPosition(disk.getRootDirPosition() + sizeof(Entry) + 1);
    disk.setDiskName(fileName);
    printInfo(disk);
}

void printInfo(SuperBlock disk){
    cout << "           mySystem Disk Partition   "<< endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Disk Name: " << disk.getDiskName() << endl;
    cout << "Disk Size: " << disk.getDiskSize() << "MB" << endl;
    cout << "Block Size: " << disk.getBlockSize() << "KB" << endl;
    cout << "Number of Block: " << disk.getNumberOfBlock() << endl;
    cout << "Boot Sector Start Address: " << disk.getBootSectorPosition() << endl;
    cout << "FAT Table Start Address: " << disk.getFatTablePosition() << endl;
    cout << "Root Directory Start Address: " << disk.getRootDirPosition() << endl;
    cout << "Data Region Start Address: " << disk.getDataStartPosition() << endl;
    cout << "-----------------------------------------------------\n\n";
}

void FAT::loadFAT(const std::string& filename,int size) {
        std::ifstream file(filename, std::ios::binary);

        if (!file) {
            std::cout << "Failed to open FAT file: " << filename << std::endl;
            return;
        }

        byte2 entry;
        while (file.read(reinterpret_cast<char*>(&entry), sizeof(byte2))) {
            fatEntries.push_back(entry);
        }

        file.close();
    }