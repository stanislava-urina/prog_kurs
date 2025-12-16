#include "DynamicTagManager.h"
#include <iostream>
#include <algorithm>
#include <sstream>

DynamicTagManager::DynamicTagManager(UA_Server* srv, UA_UInt16 nsIdx) 
    : server(srv), namespaceIndex(nsIdx), nextTagId(1000), nextInternalId(0) {
    std::cout << "[TagManager] Initialized with namespace index: " << nsIdx << std::endl;
}

DynamicTagManager::~DynamicTagManager() {
    clearAllTags();
}

int DynamicTagManager::createTag(const std::string& name, double initialValue, 
                                 const std::string& unit, const std::string& description,
                                 UA_NodeId parent) {
    if (name.empty()) {
        std::cerr << "[TagManager] Error: Tag name cannot be empty!" << std::endl;
        return -1;
    }
    
    // Проверяем, нет ли уже тега с таким именем
    if (findTagByName(name) != -1) {
        std::cerr << "[TagManager] Error: Tag '" << name << "' already exists!" << std::endl;
        return -1;
    }
    
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&attr.value, &initialValue, &UA_TYPES[UA_TYPES_DOUBLE]);
    
    // Формируем display name
    std::string displayName = name;
    if (!unit.empty()) {
        displayName += " [" + unit + "]";
    }
    
    attr.displayName = UA_LOCALIZEDTEXT("en-US", const_cast<char*>(displayName.c_str()));
    
    // Описание
    std::string desc = description.empty() ? "Dynamically created tag" : description;
    attr.description = UA_LOCALIZEDTEXT("en-US", const_cast<char*>(desc.c_str()));
    
    attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    attr.userAccessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    attr.minimumSamplingInterval = 100.0; // 100 ms
    
    // Создаем уникальный NodeId для нового тега
    int numericId = nextTagId++;
    UA_NodeId newNodeId = UA_NODEID_NUMERIC(namespaceIndex, numericId);
    
    UA_StatusCode status = UA_Server_addVariableNode(
        server,
        newNodeId,
        parent,
        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
        UA_QUALIFIEDNAME(namespaceIndex, const_cast<char*>(name.c_str())),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
        attr,
        NULL,
        NULL
    );
    
    if (status == UA_STATUSCODE_GOOD) {
        Tag newTag;
        newTag.nodeId = newNodeId;
        newTag.name = name;
        newTag.value = initialValue;
        newTag.isActive = true;
        newTag.unit = unit;
        newTag.description = desc;
        
        int internalId = nextInternalId++;
        tags[internalId] = newTag;
        
        std::cout << "[TagManager] Created tag: '" << name << "' "
                  << "(ID: " << internalId << ", NodeId: ns=" << namespaceIndex 
                  << ";i=" << numericId << ")" << std::endl;
        
        return internalId;
    }
    
    std::cerr << "[TagManager] Failed to create tag '" << name 
              << "': " << UA_StatusCode_name(status) << std::endl;
    return -1;
}

bool DynamicTagManager::deleteTag(int tagId) {
    auto it = tags.find(tagId);
    if (it == tags.end()) {
        std::cerr << "[TagManager] Tag ID " << tagId << " not found!" << std::endl;
        return false;
    }
    
    if (!it->second.isActive) {
        std::cerr << "[TagManager] Tag '" << it->second.name << "' is already deleted!" << std::endl;
        return false;
    }
    
    UA_StatusCode status = UA_Server_deleteNode(server, it->second.nodeId, true);
    
    if (status == UA_STATUSCODE_GOOD) {
        it->second.isActive = false;
        std::cout << "[TagManager] Deleted tag: '" << it->second.name 
                  << "' (ID: " << tagId << ")" << std::endl;
        return true;
    }
    
    std::cerr << "[TagManager] Failed to delete tag '" << it->second.name 
              << "': " << UA_StatusCode_name(status) << std::endl;
    return false;
}

bool DynamicTagManager::updateTagValue(int tagId, double newValue) {
    auto it = tags.find(tagId);
    if (it == tags.end() || !it->second.isActive) {
        return false;
    }
    
    UA_Variant var;
    UA_Variant_setScalar(&var, &newValue, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_StatusCode status = UA_Server_writeValue(server, it->second.nodeId, var);
    
    if (status == UA_STATUSCODE_GOOD) {
        it->second.value = newValue;
        return true;
    }
    
    return false;
}

DynamicTagManager::Tag* DynamicTagManager::getTag(int tagId) {
    auto it = tags.find(tagId);
    return (it != tags.end()) ? &it->second : nullptr;
}

const DynamicTagManager::Tag* DynamicTagManager::getTag(int tagId) const {
    auto it = tags.find(tagId);
    return (it != tags.end()) ? &it->second : nullptr;
}

int DynamicTagManager::findTagByName(const std::string& name) const {
    for (const auto& pair : tags) {
        if (pair.second.isActive && pair.second.name == name) {
            return pair.first;
        }
    }
    return -1;
}

std::vector<int> DynamicTagManager::getAllTags(bool onlyActive) const {
    std::vector<int> result;
    for (const auto& pair : tags) {
        if (!onlyActive || pair.second.isActive) {
            result.push_back(pair.first);
        }
    }
    return result;
}

std::vector<std::string> DynamicTagManager::getAllTagNames(bool onlyActive) const {
    std::vector<std::string> result;
    for (const auto& pair : tags) {
        if (!onlyActive || pair.second.isActive) {
            result.push_back(pair.second.name);
        }
    }
    return result;
}

DynamicTagManager::Statistics DynamicTagManager::getStatistics() const {
    Statistics stats{0, 0, 0};
    stats.totalTags = static_cast<int>(tags.size());
    
    for (const auto& pair : tags) {
        if (pair.second.isActive) {
            stats.activeTags++;
        } else {
            stats.deletedTags++;
        }
    }
    
    return stats;
}

std::vector<int> DynamicTagManager::createTags(const std::vector<std::string>& names, 
                                               const std::vector<double>& values) {
    std::vector<int> createdIds;
    
    if (names.size() != values.size()) {
        std::cerr << "[TagManager] Error: Names and values arrays must have the same size!" << std::endl;
        return createdIds;
    }
    
    for (size_t i = 0; i < names.size(); ++i) {
        int id = createTag(names[i], values[i]);
        if (id != -1) {
            createdIds.push_back(id);
        }
    }
    
    return createdIds;
}

bool DynamicTagManager::deleteTags(const std::vector<int>& tagIds) {
    bool allSuccess = true;
    for (int id : tagIds) {
        if (!deleteTag(id)) {
            allSuccess = false;
        }
    }
    return allSuccess;
}

void DynamicTagManager::clearAllTags() {
    std::vector<int> tagIds = getAllTags(true);
    
    if (!tagIds.empty()) {
        std::cout << "[TagManager] Clearing " << tagIds.size() << " tags..." << std::endl;
        deleteTags(tagIds);
        std::cout << "[TagManager] All tags cleared." << std::endl;
    }
}