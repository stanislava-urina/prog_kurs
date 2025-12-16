#pragma once

#include <open62541/server.h>
#include <string>
#include <map>
#include <vector>
#include <atomic>

class DynamicTagManager {
private:
    struct Tag {
        UA_NodeId nodeId;
        std::string name;
        double value;
        bool isActive;
        std::string unit;
        std::string description;
    };
    
    UA_Server* server;
    UA_UInt16 namespaceIndex;
    std::map<int, Tag> tags;
    int nextTagId;
    int nextInternalId;
    
public:
    DynamicTagManager(UA_Server* srv, UA_UInt16 nsIdx);
    ~DynamicTagManager();
    
    // Основные операции
    int createTag(const std::string& name, double initialValue, 
                  const std::string& unit = "", 
                  const std::string& description = "",
                  UA_NodeId parent = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER));
    
    bool deleteTag(int tagId);
    bool updateTagValue(int tagId, double newValue);
    
    // Получение информации
    Tag* getTag(int tagId);
    const Tag* getTag(int tagId) const;
    
    // Поиск
    int findTagByName(const std::string& name) const;
    
    // Списки
    std::vector<int> getAllTags(bool onlyActive = true) const;
    std::vector<std::string> getAllTagNames(bool onlyActive = true) const;
    
    // Статистика
    struct Statistics {
        int totalTags;
        int activeTags;
        int deletedTags;
    };
    
    Statistics getStatistics() const;
    
    // Массовые операции
    std::vector<int> createTags(const std::vector<std::string>& names, 
                                const std::vector<double>& values);
    
    bool deleteTags(const std::vector<int>& tagIds);
    void clearAllTags();
    
    // Информация о менеджере
    UA_UInt16 getNamespaceIndex() const { return namespaceIndex; }
    size_t getTagCount() const { return tags.size(); }
};