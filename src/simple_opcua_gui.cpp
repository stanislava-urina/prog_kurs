#include "../include/opcua_client.hpp"
#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>


#pragma comment(lib, "comctl32.lib")

void CreateGraphWindow(HWND hParent, const std::string& tagName, const std::string& unit);

OPCUAClient g_client;
HWND g_hList = NULL;

// Простой диалог записи
INT_PTR CALLBACK WriteDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITDIALOG: {
            // Центрируем диалог
            RECT rcOwner, rcDlg;
            HWND hwndOwner = GetParent(hDlg);
            GetWindowRect(hwndOwner, &rcOwner);
            GetWindowRect(hDlg, &rcDlg);
            
            int x = rcOwner.left + (rcOwner.right - rcOwner.left) / 2 - (rcDlg.right - rcDlg.left) / 2;
            int y = rcOwner.top + (rcOwner.bottom - rcOwner.top) / 2 - (rcDlg.bottom - rcDlg.top) / 2;
            SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            
            // Заполняем комбобокс тегами
            HWND hCombo = GetDlgItem(hDlg, 1001);
            auto tags = g_client.getTags();
            
            for (const auto& tag : tags) {
                SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)tag.name.c_str());
            }
            
            if (!tags.empty()) {
                SendMessage(hCombo, CB_SETCURSEL, 0, 0);
                
                // Показываем текущее значение первого тега
                char valueStr[50];
                sprintf_s(valueStr, "%.2f", tags[0].value);
                SetDlgItemText(hDlg, 1002, valueStr);
                
                // Показываем статус
                SetDlgItemText(hDlg, 1003, tags[0].is_written ? "WRITTEN" : "AUTO");
            }
            
            return TRUE;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) == 1001 && HIWORD(wParam) == CBN_SELCHANGE) {
                // Пользователь выбрал другой тег
                HWND hCombo = GetDlgItem(hDlg, 1001);
                int index = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                
                if (index != CB_ERR) {
                    char tagName[256];
                    SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)tagName);
                    
                    auto tagPtr = g_client.getTagByName(tagName);
                    if (tagPtr) {
                        char valueStr[50];
                        sprintf_s(valueStr, "%.2f", tagPtr->value);
                        SetDlgItemText(hDlg, 1002, valueStr);
                        SetDlgItemText(hDlg, 1003, tagPtr->is_written ? "WRITTEN" : "AUTO");
                    }
                }
            }
            else if (LOWORD(wParam) == IDOK) {
                HWND hCombo = GetDlgItem(hDlg, 1001);
                int index = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                
                if (index != CB_ERR) {
                    char tagName[256];
                    SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)tagName);
                    
                    // Получаем новое значение
                    char newValueStr[256];
                    GetDlgItemText(hDlg, 1004, newValueStr, 256);
                    
                    // Если поле пустое, используем текущее значение
                    if (strlen(newValueStr) == 0) {
                        GetDlgItemText(hDlg, 1002, newValueStr, 256);
                    }
                    
                    // Преобразуем в число
                    double value = atof(newValueStr);
                    
                    // Записываем значение
                    if (g_client.writeTagByName(tagName, value)) {
                        // Обновляем текущее значение в диалоге
                        auto tagPtr = g_client.getTagByName(tagName);
                        if (tagPtr) {
                            char valueStr[50];
                            sprintf_s(valueStr, "%.2f", tagPtr->value);
                            SetDlgItemText(hDlg, 1002, valueStr);
                            SetDlgItemText(hDlg, 1003, "WRITTEN");
                        }
                        
                        MessageBox(hDlg, "Value written successfully!", "Success", MB_OK | MB_ICONINFORMATION);
                    } else {
                        MessageBox(hDlg, "Failed to write value!", "Error", MB_OK | MB_ICONERROR);
                    }
                }
            } 
            else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, IDCANCEL);
            }
            break;
        }
        
        case WM_CLOSE:
            EndDialog(hDlg, IDCANCEL);
            break;
    }
    return FALSE;
}

// Диалог сброса статуса (упрощённый)
INT_PTR CALLBACK ResetDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITDIALOG: {
            // Центрируем диалог
            RECT rcOwner, rcDlg;
            HWND hwndOwner = GetParent(hDlg);
            GetWindowRect(hwndOwner, &rcOwner);
            GetWindowRect(hDlg, &rcDlg);
            
            int x = rcOwner.left + (rcOwner.right - rcOwner.left) / 2 - (rcDlg.right - rcDlg.left) / 2;
            int y = rcOwner.top + (rcOwner.bottom - rcOwner.top) / 2 - (rcDlg.bottom - rcDlg.top) / 2;
            SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            
            return TRUE;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDOK) {
                // Сбрасываем ВСЕ WRITTEN теги
                auto tags = g_client.getTags();
                int resetCount = 0;
                
                for (const auto& tag : tags) {
                    if (tag.is_written) {
                        auto tagPtr = g_client.getTagByName(tag.name);
                        if (tagPtr) {
                            tagPtr->is_written = false;  // Сбрасываем флаг
                            resetCount++;
                        }
                    }
                }
                
                char message[256];
                if (resetCount > 0) {
                    sprintf_s(message, "%d tag(s) reset to AUTO mode", resetCount);
                } else {
                    strcpy_s(message, "No WRITTEN tags found!");
                }
                
                MessageBox(hDlg, message, "Reset Complete", MB_OK | MB_ICONINFORMATION);
                EndDialog(hDlg, IDOK);
            } 
            else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, IDCANCEL);
            }
            break;
        }
        
        case WM_CLOSE:
            EndDialog(hDlg, IDCANCEL);
            break;
    }
    return FALSE;
}

// Обновляем список тегов
void UpdateTagList() {
    if (!g_hList) return;
    
    ListView_DeleteAllItems(g_hList);
    
    auto tags = g_client.getTags();
    
    for (size_t i = 0; i < tags.size(); i++) {
        LVITEM lvi = {0};
        lvi.mask = LVIF_TEXT;
        lvi.iItem = (int)i;
        lvi.iSubItem = 0;
        
        // Выделяем WRITTEN теги
        if (tags[i].is_written) {
            lvi.mask |= LVIF_STATE;
            lvi.state = LVIS_SELECTED;
            lvi.stateMask = LVIS_SELECTED;
        }
        
        lvi.pszText = (LPSTR)tags[i].name.c_str();
        ListView_InsertItem(g_hList, &lvi);
        
        // Значение
        char valueStr[50];
        sprintf_s(valueStr, "%.2f", tags[i].value);
        ListView_SetItemText(g_hList, i, 1, valueStr);
        
        // Единицы измерения
        ListView_SetItemText(g_hList, i, 2, (LPSTR)tags[i].unit.c_str());
        
        // Статус (WRITTEN или AUTO)
        char status[20];
        strcpy_s(status, tags[i].is_written ? "WRITTEN" : "AUTO");
        ListView_SetItemText(g_hList, i, 3, status);
        
        // Время
        ListView_SetItemText(g_hList, i, 4, (LPSTR)tags[i].timestamp.c_str());
        
        // Качество
        ListView_SetItemText(g_hList, i, 5, (LPSTR)tags[i].quality.c_str());
    }
}

// Обработчик главного окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Инициализация
            INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES };
            InitCommonControlsEx(&icex);
            
            // Кнопки
            CreateWindow("BUTTON", "Write Value",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                        10, 10, 100, 30, hWnd, (HMENU)1, NULL, NULL);
            
            CreateWindow("BUTTON", "Reset to AUTO",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                        120, 10, 100, 30, hWnd, (HMENU)2, NULL, NULL);
            
            CreateWindow("BUTTON", "Refresh",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                        230, 10, 100, 30, hWnd, (HMENU)3, NULL, NULL);
            
            CreateWindow("BUTTON", "Auto Update",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                        340, 10, 100, 30, hWnd, (HMENU)4, NULL, NULL);
            
            // Таблица тегов
            g_hList = CreateWindow(WC_LISTVIEW, "",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
                                  10, 50, 760, 300, hWnd, NULL, NULL, NULL);
            
            // Устанавливаем расширенный стиль для выделения строк
            ListView_SetExtendedListViewStyle(g_hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            
            // Колонки таблицы
            LVCOLUMN lvc = {0};
            lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
            lvc.fmt = LVCFMT_LEFT;
            
            // Колонка 0: Имя тега
            lvc.pszText = "TAG NAME";
            lvc.cx = 150;
            ListView_InsertColumn(g_hList, 0, &lvc);
            
            // Колонка 1: Значение
            lvc.pszText = "VALUE";
            lvc.cx = 100;
            ListView_InsertColumn(g_hList, 1, &lvc);
            
            // Колонка 2: Единицы измерения
            lvc.pszText = "UNIT";
            lvc.cx = 80;
            ListView_InsertColumn(g_hList, 2, &lvc);
            
            // Колонка 3: Статус
            lvc.pszText = "STATUS";
            lvc.cx = 80;
            ListView_InsertColumn(g_hList, 3, &lvc);
            
            // Колонка 4: Время
            lvc.pszText = "TIME";
            lvc.cx = 100;
            ListView_InsertColumn(g_hList, 4, &lvc);
            
            // Колонка 5: Качество
            lvc.pszText = "QUALITY";
            lvc.cx = 80;
            ListView_InsertColumn(g_hList, 5, &lvc);
            
            // Автоподключение и обновление
            g_client.connect("opc.tcp://localhost:4840");
            UpdateTagList();
            
            break;
        }
        
        case WM_NOTIFY: {
            LPNMHDR nmhdr = (LPNMHDR)lParam;
            
            if (nmhdr->hwndFrom == g_hList && nmhdr->code == NM_DBLCLK) {
                // Двойной клик по тегу
                LPNMITEMACTIVATE item = (LPNMITEMACTIVATE)lParam;
                if (item->iItem >= 0) {
                    // Получаем имя тега
                    char tagName[256];
                    ListView_GetItemText(g_hList, item->iItem, 0, tagName, 256);
                    
                    // Получаем единицы измерения
                    char unit[50];
                    ListView_GetItemText(g_hList, item->iItem, 2, unit, 50);
                    
                    // Создаём окно с графиком (упрощённая версия)
                    CreateGraphWindow(hWnd, tagName, unit);
                }
            }
            break;
        }

        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case 1: // Write Value
                    DialogBoxParam(GetModuleHandle(NULL),
                                   MAKEINTRESOURCE(1),
                                   hWnd,
                                   WriteDialogProc,
                                   0);
                    break;
                    
                case 2: // Reset to AUTO
                    DialogBoxParam(GetModuleHandle(NULL),
                                   MAKEINTRESOURCE(2),
                                   hWnd,
                                   ResetDialogProc,
                                   0);
                    // Обновляем таблицу после сброса
                    UpdateTagList();
                    break;
                    
                case 3: // Refresh
                    UpdateTagList();
                    break;
                    
                case 4: // Auto Update (вкл/выкл)
                    static bool autoUpdate = false;
                    autoUpdate = !autoUpdate;
                    
                    if (autoUpdate) {
                        SetTimer(hWnd, 1, 2000, NULL); // Каждые 2 секунды
                        MessageBox(hWnd, "Auto-update enabled (2 sec)", "Info", MB_OK);
                    } else {
                        KillTimer(hWnd, 1);
                        MessageBox(hWnd, "Auto-update disabled", "Info", MB_OK);
                    }
                    break;
            }
            break;
        }
        
        case WM_TIMER: // Автообновление
            if (wParam == 1) {
                g_client.updateValues();
                UpdateTagList();
            }
            break;
            
        case WM_SIZE:
            if (g_hList) {
                RECT rc;
                GetClientRect(hWnd, &rc);
                MoveWindow(g_hList, 10, 50, rc.right - 20, rc.bottom - 60, TRUE);
            }
            break;
            
        case WM_DESTROY:
            KillTimer(hWnd, 1);
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "SimpleOPCUA";
    
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window class registration failed", "Error", MB_ICONERROR);
        return 0;
    }
    
    HWND hWnd = CreateWindow("SimpleOPCUA", "OPC UA Monitor - Course Project",
                            WS_OVERLAPPEDWINDOW, 100, 100, 800, 400,
                            NULL, NULL, hInstance, NULL);
    
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}