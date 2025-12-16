#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>
#include <mutex>
#include <map>

class OPCUAClient {
public:
    // Вложенные структуры должны быть публичными или нужно добавить геттеры
    struct TagData {
        std::string name;
        std::string nodeId;
        double value;
        std::string unit;
        std::string timestamp;
        std::string quality;
        bool is_written;
        
        TagData(const std::string& n, const std::string& id, const std::string& u)
            : name(n), nodeId(id), value(0.0), unit(u), quality("GOOD"), is_written(false) {}
        
        void update(double newValue, bool written = false);
        void updateTimestamp();
        void print() const;
    };
    
    struct TagHistory {
        std::vector<double> values;
        std::vector<std::string> timestamps;
        size_t maxHistory = 50;
        
        void addValue(double value, const std::string& timestamp);
        void clear();
    };
    
private:
    std::vector<TagData> tags;
    mutable std::mutex tags_mutex;
    std::string endpoint;
    bool connected;
    std::random_device rd;
    std::mt19937 gen;
    std::map<std::string, double> written_values;
    
    std::map<std::string, TagHistory> tagHistories;  // ← ОСТАВИТЬ ЭТУ СТРОКУ
    std::mutex history_mutex;  // ← ОСТАВИТЬ ЭТУ СТРОКУ
    
public:
    OPCUAClient();
    
    bool connect(const std::string& url);
    void disconnect();
    bool isConnected() const;
    
    void addTag(const std::string& name, const std::string& nodeId, 
                const std::string& unit, double minVal, double maxVal);
    
    void updateValues();
    std::vector<TagData> readAllTags();
    
    std::vector<TagData> getTags() const;
    
    bool writeTagByName(const std::string& tagName, double value);
    bool writeTagById(const std::string& nodeId, double value);
    
    size_t tagCount() const;
    TagData* getTagByName(const std::string& tagName);
    bool resetTagToAuto(const std::string& tagName);
    
    TagHistory* getTagHistory(const std::string& tagName);  // ← ОСТАВИТЬ ЭТУ СТРОКУ
    void addToHistory(const std::string& tagName, double value, const std::string& timestamp);  // ← ОСТАВИТЬ ЭТУ СТРОКУ

    // ★★★ УДАЛИТЬ ВСЕ СТРОКИ НИЖЕ ЭТОЙ КОММЕНТАРИЯ ★★★
    // private:
    //     std::map<std::string, TagHistory> tagHistories;  // ← УДАЛИТЬ (дубликат!)
    //     std::mutex history_mutex;  // ← УДАЛИТЬ (дубликат!)
    //     
    // public:
    //     TagHistory* getTagHistory(const std::string& tagName);  // ← УДАЛИТЬ (дубликат!)
    //     void addToHistory(const std::string& tagName, double value, const std::string& timestamp);  // ← УДАЛИТЬ (дубликат!)
};