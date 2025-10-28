#include <windows.h>
#include <iostream>
#include <string>

void convertMilliseconds(ULONGLONG ms, int& days, int& hours, int& minutes, int& seconds) {
    ULONGLONG total_seconds = ms / 1000;
    seconds = static_cast<int>(total_seconds % 60);
    ULONGLONG total_minutes = total_seconds / 60;
    minutes = static_cast<int>(total_minutes % 60);
    ULONGLONG total_hours = total_minutes / 60;
    hours = static_cast<int>(total_hours % 24);
    days = static_cast<int>(total_hours / 24);
}

int main() {
    setlocale(LC_ALL, "ru");
    ULONGLONG uptimeMs = GetTickCount64();

    int days, hours, minutes, seconds;
    convertMilliseconds(uptimeMs, days, hours, minutes, seconds);

    std::cout << "Время работы системы: "
        << days << " дней, "
        << hours << " часов, "
        << minutes << " минут, "
        << seconds << " секунд"
        << std::endl;

    SYSTEMTIME systemTime;
    GetLocalTime(&systemTime);

    wchar_t timeStr[100];
    swprintf_s(timeStr, 100, L"Текущее время: %02d:%02d:%02d\nТекущая дата: %02d.%02d.%04d",
        systemTime.wHour, systemTime.wMinute, systemTime.wSecond,
        systemTime.wDay, systemTime.wMonth, systemTime.wYear);


    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);

    char userName[256];
    DWORD userNameSize = sizeof(userName);
    GetUserNameA(userName, &userNameSize);

    std::cout << "Имя компьютера: " << computerName << std::endl;
    std::cout << "Имя пользователя: " << userName << std::endl;

    MessageBox(NULL, timeStr, L"Текущее время и дата", MB_OKCANCEL | MB_ICONINFORMATION);

    return 0;
}