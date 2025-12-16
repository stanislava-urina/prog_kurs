#include "DynamicTagManager.h"
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <csignal>
#include <iomanip>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// Глобальные переменные
volatile bool running = true;
DynamicTagManager* tagManager = nullptr;

// Обработчик сигналов
void signalHandler(int) {
    std::cout << "\n[INFO] Received stop signal..." << std::endl;
    running = false;
}

// Настройка консоли для Windows
void setConsoleEncoding() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

// Красивый вывод таблицы тегов
void printTagTable(const DynamicTagManager& manager) {
    auto stats = manager.getStatistics();
    auto activeTags = manager.getAllTags(true);
    
    std::cout << "\n==============================================" << std::endl;
    std::cout << "        OPC UA TAG MANAGEMENT SYSTEM        " << std::endl;
    std::cout << "==============================================" << std::endl;
    printf("   Active: %-3d   Deleted: %-3d   Total: %-3d   \n", 
           stats.activeTags, stats.deletedTags, stats.totalTags);
    std::cout << "==============================================" << std::endl;
    
    if (!activeTags.empty()) {
        std::cout << "\n+-----+-----------------+------------+--------------+" << std::endl;
        std::cout << "| ID  | Name            | Value      | Unit         |" << std::endl;
        std::cout << "+-----+-----------------+------------+--------------+" << std::endl;
        
        for (int id : activeTags) {
            const auto* tag = manager.getTag(id);
            if (tag) {
                printf("| %-3d | %-15s | %-10.2f | %-12s |\n", 
                       id, tag->name.c_str(), tag->value, tag->unit.c_str());
            }
        }
        std::cout << "+-----+-----------------+------------+--------------+" << std::endl;
    } else {
        std::cout << "\n[INFO] No active tags available." << std::endl;
    }
}

// Демонстрация: создание начальных тегов
void createInitialTags(DynamicTagManager& manager, UA_NodeId folderId) {
    std::cout << "\n[INIT] Creating initial tags..." << std::endl;
    
    // Создаем начальные теги
    manager.createTag("Temperature", 22.5, "°C", "Ambient temperature", folderId);
    manager.createTag("Humidity", 45.0, "%", "Relative humidity", folderId);
    manager.createTag("Pressure", 1013.25, "hPa", "Atmospheric pressure", folderId);
    manager.createTag("Voltage", 230.0, "V", "Mains voltage", folderId);
    manager.createTag("Current", 4.75, "A", "Current consumption", folderId);
    manager.createTag("Power", 1092.5, "W", "Power consumption", folderId);
}

// Демонстрация: автоматическое управление тегами
void autoManageTags(DynamicTagManager& manager, UA_NodeId folderId, int iteration) {
    static std::vector<std::string> possibleNewTags = {
        "FlowRate", "RPM", "Torque", "Vibration",
        "pH_Level", "Conductivity", "Turbidity", "Oxygen",
        "CO2", "NO2", "PM2_5", "Noise"
    };
    
    static int autoOpCounter = 0;
    autoOpCounter++;
    
    // Каждые ~15 секунд (45 итераций * 0.33с)
    if (autoOpCounter >= 45) {
        autoOpCounter = 0;
        
        auto stats = manager.getStatistics();
        
        if (stats.activeTags < 4 || (rand() % 3 == 0)) {
            // Создать новый тег
            if (!possibleNewTags.empty()) {
                std::string newName = possibleNewTags[rand() % possibleNewTags.size()];
                
                // Проверяем, нет ли уже такого тега
                if (manager.findTagByName(newName) == -1) {
                    double newValue = 10.0 + (rand() % 900) / 10.0;
                    
                    manager.createTag(newName, newValue, "units", "Auto-created tag", folderId);
                    
                    // Показываем обновленную таблицу
                    if (iteration % 200 == 0) {
                        printTagTable(manager);
                    }
                }
            }
        } else if (stats.activeTags > 3 && (rand() % 2 == 0)) {
            // Удалить случайный тег
            auto activeTags = manager.getAllTags(true);
            if (!activeTags.empty()) {
                int tagToDelete = activeTags[rand() % activeTags.size()];
                manager.deleteTag(tagToDelete);
                
                // Показываем обновленную таблицу
                if (iteration % 200 == 0) {
                    printTagTable(manager);
                }
            }
        }
    }
}

// Главная функция
int main() {
    // Настройка
    setConsoleEncoding();
    signal(SIGINT, signalHandler);
    srand(static_cast<unsigned>(time(nullptr)));
    
    std::cout << "==============================================" << std::endl;
    std::cout << "    DYNAMIC OPC UA TAG MANAGEMENT SERVER" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // 1. Создание сервера OPC UA
    UA_Server* server = UA_Server_new();
    if (!server) {
        std::cerr << "[ERROR] Failed to create OPC UA server!" << std::endl;
        return 1;
    }
    
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));
    std::cout << "\n[OK] OPC UA server instance created" << std::endl;
    
    // 2. Добавление namespace
    UA_UInt16 nsIndex = UA_Server_addNamespace(server, "DynamicTagsNS");
    std::cout << "[INFO] Namespace index: " << nsIndex << std::endl;
    
    // 3. Создание менеджера тегов
    tagManager = new DynamicTagManager(server, nsIndex);
    
    // 4. Создание папки для тегов
    UA_ObjectAttributes folderAttr = UA_ObjectAttributes_default;
    folderAttr.displayName = UA_LOCALIZEDTEXT("en-US", "SensorData");
    folderAttr.description = UA_LOCALIZEDTEXT("en-US", "Folder for sensor data tags");
    
    UA_NodeId folderId = UA_NODEID_NUMERIC(nsIndex, 9999);
    UA_Server_addObjectNode(
        server,
        folderId,
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
        UA_QUALIFIEDNAME(nsIndex, "SensorData"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
        folderAttr, NULL, NULL
    );
    
    // 5. Создание начальных тегов
    createInitialTags(*tagManager, folderId);
    
    // 6. Запуск сервера
    UA_StatusCode status = UA_Server_run_startup(server);
    if (status != UA_STATUSCODE_GOOD) {
        std::cerr << "[ERROR] Failed to start server: " << UA_StatusCode_name(status) << std::endl;
        delete tagManager;
        UA_Server_delete(server);
        return 1;
    }
    
    std::cout << "\n[SUCCESS] Server started successfully!" << std::endl;
    std::cout << "[ENDPOINT] opc.tcp://localhost:4840" << std::endl;
    
    printTagTable(*tagManager);
    
    // 7. Информация о режимах работы
    std::cout << "\n==============================================" << std::endl;
    std::cout << "              OPERATION MODES" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Value Update: Every 0.33 seconds" << std::endl;
    std::cout << "Auto Management: Every ~15 seconds" << std::endl;
    std::cout << "  - Randomly creates new tags" << std::endl;
    std::cout << "  - Randomly deletes existing tags" << std::endl;
    std::cout << "Statistics: Every 10 seconds" << std::endl;
    std::cout << "\nPress Ctrl+C to stop the server" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // 8. Настройка генераторов случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> valueChange(-2.5, 2.5);
    
    // 9. Главный цикл
    int iteration = 0;
    while (running) {
        // Обновление значений всех активных тегов
        auto activeTags = tagManager->getAllTags(true);
        for (int tagId : activeTags) {
            const auto* tag = tagManager->getTag(tagId);
            if (tag) {
                // Небольшое случайное изменение значения
                double change = valueChange(gen) * 0.05;
                double newValue = tag->value + change;
                
                // Ограничения значений в разумных пределах
                if (tag->name == "Temperature") newValue = (newValue < 15.0) ? 15.0 : (newValue > 35.0) ? 35.0 : newValue;
                else if (tag->name == "Humidity") newValue = (newValue < 30.0) ? 30.0 : (newValue > 80.0) ? 80.0 : newValue;
                else if (tag->name == "Pressure") newValue = (newValue < 980.0) ? 980.0 : (newValue > 1040.0) ? 1040.0 : newValue;
                else if (tag->name == "Voltage") newValue = (newValue < 210.0) ? 210.0 : (newValue > 250.0) ? 250.0 : newValue;
                else if (tag->name == "Current") newValue = (newValue < 0.0) ? 0.0 : (newValue > 10.0) ? 10.0 : newValue;
                else if (tag->name == "Power") newValue = (newValue < 0.0) ? 0.0 : (newValue > 2500.0) ? 2500.0 : newValue;
                else newValue = (newValue < 0.0) ? 0.0 : (newValue > 100.0) ? 100.0 : newValue;
                
                // Обновляем значение
                tagManager->updateTagValue(tagId, newValue);
            }
        }
        
        // Автоматическое управление тегами
        autoManageTags(*tagManager, folderId, iteration);
        
        // Периодический вывод статистики
        if (iteration % 30 == 0) {
            auto stats = tagManager->getStatistics();
            printf("\n[%04d] Statistics: %d active | %d total | %d deleted\n", 
                   iteration, stats.activeTags, stats.totalTags, stats.deletedTags);
        }
        
        iteration++;
        
        // Пауза и обработка запросов OPC UA
        std::this_thread::sleep_for(std::chrono::milliseconds(330));
        UA_Server_run_iterate(server, false);
    }
    
    // 10. Остановка и очистка
    std::cout << "\n==============================================" << std::endl;
    std::cout << "              SERVER SHUTDOWN" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // Финальная статистика
    printTagTable(*tagManager);
    
    // Очистка тегов
    std::cout << "\n[INFO] Cleaning up tags..." << std::endl;
    tagManager->clearAllTags();
    
    // Удаление менеджера
    delete tagManager;
    tagManager = nullptr;
    
    // Остановка сервера
    UA_Server_run_shutdown(server);
    UA_Server_delete(server);
    
    std::cout << "\n[SUCCESS] Server stopped successfully!" << std::endl;
    std::cout << "Goodbye!" << std::endl;
    
    return 0;
}