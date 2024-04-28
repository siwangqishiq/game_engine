
#include "resource/asset_manager.h"
#include "log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

// #include <filesystem>

namespace purple{

    std::shared_ptr<AssetManager> AssetManager::getInstance(){
        static std::shared_ptr<AssetManager> instance_;
        if(instance_ == nullptr){
            #ifdef __ANDROID__
            instance_ = std::make_shared<AndroidAssetManager>();
            #else
            instance_ = std::make_shared<AssetManager>();
            #endif
        }
        return instance_;
    }

    std::wstring AssetManager::readTextFile(std::string path){
        std::string filePath = assetRootDir() + path;
        Log::i("asset" , "read file path %s" , filePath.c_str());
        return readFileAsWstring(filePath.c_str());
    }

    unsigned char* AssetManager::readFileAsBinRaw(std::string path , int &length){
        std::string filePath = path;
        Log::i("asset" , "read file path %s" , filePath.c_str());
        try{
            std::ifstream binFile(filePath, std::ios::binary);
            // Logi("asset" , "readBinaryFile is good? %d" , binFile.good);
            
            if(!binFile.is_open()){
                Log::i("asset" , "readBinaryFile is not existed!");
                return nullptr;
            }

            binFile.seekg(0 , std::ios::end);
            length = binFile.tellg();
            binFile.seekg(0 , std::ios::beg);
            Log::i("asset" , "readFileAsBin size %d" , length);
            unsigned char *pData = new unsigned char[length];
            binFile.read((char *)pData , length);
            binFile.close();
            return pData;
        }catch(std::exception &e){
            Log::e("error" , "readBinaryFile code %s" , e.what());
            length = -1;
        }
        return nullptr;
    }

    unsigned char* AssetManager::readAssetFileAsBinRaw(std::string path , int &length){
        std::string filePath = assetRootDir() + path;
        return readFileAsBinRaw(filePath , length);
    }

    std::unique_ptr<uint8_t[]> AssetManager::readFileAsBin(std::string path , int &length){
        std::string filePath = assetRootDir() + path;
        Log::i("asset" , "read file path %s" , filePath.c_str());

        try{
            std::ifstream binFile(filePath, std::ios::binary);
            // Logi("asset" , "readBinaryFile is good? %d" , binFile.good);
            
            if(!binFile.is_open()){
                Log::i("asset" , "readBinaryFile is not existed!");
                return nullptr;
            }

            binFile.seekg(0 , std::ios::end);
            
            length = binFile.tellg();
            binFile.seekg(0 , std::ios::beg);

            Log::i("asset" , "readFileAsBin size %d" , length);

            std::unique_ptr<uint8_t[]> pData = std::unique_ptr<uint8_t[]>(new uint8_t[length]);
            binFile.read((char *)pData.get() , length);
            binFile.close();
            
            return pData;
        }catch(std::exception &e){
            Log::e("error" , "readBinaryFile code %s" , e.what());
        }
        return nullptr;
    }

    int AssetManager::readBinaryFile(std::string path , std::vector<char> &dataVec){
        std::string filePath = assetRootDir() + path;
        Log::i("asset" , "read file path %s" , filePath.c_str());

        try{
            std::ifstream binFile(filePath, std::ios::binary);
            // Logi("asset" , "readBinaryFile is good? %d" , binFile.good);
            
            if(!binFile.is_open()){
                Log::i("asset" , "readBinaryFile is not existed!");
                return -1;
            }

            binFile.seekg(0 , std::ios::end);
            
            int length = binFile.tellg();
            binFile.seekg(0 , std::ios::beg);

            Log::i("asset" , "readBinaryFile size %d" , length);

            dataVec.resize(length);
            binFile.read(dataVec.data() , length);
            binFile.close();
            
            return length;
        }catch(std::exception &e){
            Log::e("error" , "readBinaryFile code %s" , e.what());
        }
        return -1;
    }

    std::unique_ptr<uint8_t> AssetManager::readAssetTextureFile(std::string path ,
            TextureFileConfig &fileConfig , bool needFlip){
        std::string filePath = assetRootDir() + path;
        Log::i("asset" , "read file path %s" , filePath.c_str());
        
        stbi_set_flip_vertically_on_load(needFlip);
        
        uint8_t *data = stbi_load(filePath.c_str(),
                            &fileConfig.width , 
                            &fileConfig.height , &fileConfig.channel , 0);
        fileConfig.dataSize = fileConfig.width * fileConfig.height * fileConfig.channel;
        Log::i("asset" , "read file size : %d , %d , %d" , fileConfig.width , fileConfig.height , fileConfig.channel);
        return std::unique_ptr<uint8_t>(data);
    }

    long AssetManager::writeFileWithBin(std::string &path , long size , uint8_t *data){
        std::fstream file;
        try{
            std::streampos fsize = 0;
            file.open(path , std::ios::out | std::ios::binary);
            fsize = file.tellg();
            file.write(reinterpret_cast<const char*>(data) , size);
            long ret = file.tellg() - fsize;
            file.close();
            return ret;
        }catch(std::exception &e){
            if(file.is_open()){
                file.close();
            }
            return -1;
        }
        return 0;
    }

    std::string AssetManager::ensureCacheDir() const{
        std::string dir = cacheRootDir();
        makedir(dir);
        return dir;
    }

    void AssetManager::makedir(std::string dir) const{
        #ifdef _WIN32
        mkdir(dir.c_str());
        #else
        int err = mkdir(dir.c_str() , 0x777);
        if(err != 0){
            perror("mkdir");
        }
        #endif
    }
}

