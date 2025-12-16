#include "../include/opcua_client.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

// Constructor
OPCUAClient::OPCUAClient() : connected(false), gen(rd()) {
    // Tags from Python example
    addTag("Voltage", "ns=2;i=2", "V", 190.0, 240.0);
    addTag("Current", "ns=2;i=3", "A", 1.0, 10.0);
    addTag("Power", "ns=2;i=4", "W", 500.0, 2400.0);
}

bool OPCUAClient::connect(const std::string& url) {
    endpoint = url;
    cout << "[OPC UA] Connecting to " << url << "..." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(500));
    
    if (url.find("localhost") != string::npos || url.find("4840") != string::npos) {
        connected = true;
        cout << "[OPC UA] Connected successfully!" << endl;
        return true;
    }
    
    cout << "[OPC UA] Simulation mode" << endl;
    connected = false;
    return false;
}

void OPCUAClient::disconnect() {
    if (connected) {
        cout << "[OPC UA] Disconnecting..." << endl;
        connected = false;
    }
}

bool OPCUAClient::isConnected() const {
    return connected;
}

void OPCUAClient::addTag(const std::string& name, const std::string& nodeId, 
                const std::string& unit, double minVal, double maxVal) {
    lock_guard<mutex> lock(tags_mutex);
    tags.emplace_back(name, nodeId, unit);
    cout << "[OPC UA] Tag added: " << name << " [" << nodeId << "]" << endl;
}

void OPCUAClient::updateValues() {
    lock_guard<mutex> lock(tags_mutex);
    
    for (auto& tag : tags) {
        // Если значение было записано вручную - не меняем его
        if (tag.is_written) {
            continue;
        }
        
        double minVal, maxVal;
        
        if (tag.name == "Voltage") {
            minVal = 190.0; maxVal = 240.0;
        } else if (tag.name == "Current") {
            minVal = 1.0; maxVal = 10.0;
        } else if (tag.name == "Power") {
            minVal = 500.0; maxVal = 2400.0;
        } else {
            minVal = 0.0; maxVal = 100.0;
        }
        
        uniform_real_distribution<double> dist(minVal, maxVal);
        double newValue = dist(gen);
        
        // Сохраняем в историю перед обновлением
        addToHistory(tag.name, tag.value, tag.timestamp);
        
        tag.update(newValue, false);
    }
}

std::vector<OPCUAClient::TagData> OPCUAClient::readAllTags() {
    updateValues();
    lock_guard<mutex> lock(tags_mutex);
    return tags;
}

std::vector<OPCUAClient::TagData> OPCUAClient::getTags() const {
    lock_guard<mutex> lock(tags_mutex);
    return tags;
}

bool OPCUAClient::writeTagByName(const std::string& tagName, double value) {
    lock_guard<mutex> lock(tags_mutex);
    
    for (auto& tag : tags) {
        if (tag.name == tagName) {
            // Сохраняем старое значение в историю
            addToHistory(tagName, tag.value, tag.timestamp);
            
            // Обновляем текущее значение
            written_values[tagName] = value;
            tag.update(value, true);
            
            if (connected) {
                cout << "[OPC UA] Writing to server: " 
                      << tag.name << " = " << value << " " << tag.unit 
                      << " (SAVED)" << endl;
            } else {
                cout << "[OPC UA] Simulation write: " 
                      << tag.name << " = " << value << " " << tag.unit 
                      << " (SAVED)" << endl;
            }
            return true;
        }
    }
    
    cout << "[OPC UA] Error: Tag '" << tagName << "' not found" << endl;
    return false;
}

bool OPCUAClient::writeTagById(const std::string& nodeId, double value) {
    lock_guard<mutex> lock(tags_mutex);
    
    for (auto& tag : tags) {
        if (tag.nodeId == nodeId) {
            written_values[tag.name] = value;
            tag.update(value, true);
            
            if (connected) {
                cout << "[OPC UA] Writing to server (by ID): " 
                      << tag.name << " [" << nodeId << "] = " 
                      << value << " " << tag.unit << endl;
            } else {
                cout << "[OPC UA] Simulation write (by ID): " 
                      << tag.name << " [" << nodeId << "] = " 
                      << value << " " << tag.unit << endl;
            }
            return true;
        }
    }
    
    cout << "[OPC UA] Error: NodeId '" << nodeId << "' not found" << endl;
    return false;
}

size_t OPCUAClient::tagCount() const {
    lock_guard<mutex> lock(tags_mutex);
    return tags.size();
}

OPCUAClient::TagData* OPCUAClient::getTagByName(const std::string& tagName) {
    lock_guard<mutex> lock(tags_mutex);
    for (auto& tag : tags) {
        if (tag.name == tagName) {
            return &tag;
        }
    }
    return nullptr;
}

bool OPCUAClient::resetTagToAuto(const std::string& tagName) {
    lock_guard<mutex> lock(tags_mutex);
    
    for (auto& tag : tags) {
        if (tag.name == tagName && tag.is_written) {
            tag.is_written = false;
            cout << "[OPC UA] Tag reset to AUTO: " << tagName << endl;
            return true;
        }
    }
    
    cout << "[OPC UA] Tag not found or not WRITTEN: " << tagName << endl;
    return false;
}

// ★★★★ МЕТОДЫ ДЛЯ ГРАФИКОВ ★★★★

// Реализация методов TagData
void OPCUAClient::TagData::update(double newValue, bool written) {
    value = newValue;
    is_written = written;
    updateTimestamp();
}

void OPCUAClient::TagData::updateTimestamp() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    tm tm;
    localtime_s(&tm, &time);
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &tm);
    timestamp = timeStr;
}

void OPCUAClient::TagData::print() const {
    cout << left 
          << setw(15) << name 
          << setw(10) << fixed << setprecision(2) << value 
          << setw(5) << unit 
          << setw(25) << timestamp 
          << setw(10) << quality 
          << (is_written ? " [WRITTEN]" : "")
          << endl;
}

// Реализация методов TagHistory
void OPCUAClient::TagHistory::addValue(double value, const std::string& timestamp) {
    values.push_back(value);
    timestamps.push_back(timestamp);
    
    // Ограничиваем размер истории
    if (values.size() > maxHistory) {
        values.erase(values.begin());
        timestamps.erase(timestamps.begin());
    }
}

void OPCUAClient::TagHistory::clear() {
    values.clear();
    timestamps.clear();
}

// Получить историю тега
OPCUAClient::TagHistory* OPCUAClient::getTagHistory(const std::string& tagName) {
    lock_guard<mutex> lock(history_mutex);
    auto it = tagHistories.find(tagName);
    if (it != tagHistories.end()) {
        return &it->second;
    }
    return nullptr;
}

// Добавить значение в историю
void OPCUAClient::addToHistory(const std::string& tagName, double value, const std::string& timestamp) {
    lock_guard<mutex> lock(history_mutex);
    tagHistories[tagName].addValue(value, timestamp);
}