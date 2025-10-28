#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

//Прототипы ANSI-функций
int countwords(const char* str);
void reversestring(char* str);
BOOL isstringpalindrome(const char* str);
//Прототипы Unicode-функций
int countwords(const wchar_t* str);
void reversestring(wchar_t* str);
BOOL isstringpalindrome(const wchar_t* str);

void printError(DWORD errorCode);
//Подсчет слов
int countwords(const char* str) {
    if (str == NULL) return 0;

    bool inWord = false;
    int wordCount = 0;

    while (*str != '\0') {
        // Если текущий символ - часть слова (буква или цифра)
        if (isalnum((unsigned char)*str)) {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        }
        else {
            inWord = false;
        }
        str++;
    }
    return wordCount;
}
//Переворот строки
void reversestring(char* str) {
    if (!str) {
        printError(ERROR_INVALID_PARAMETER);
        return;
    };

    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        swap(str[i], str[length - 1 - i]);
    }
}
//Палидром
BOOL isstringpalindrome(const char* str) {
    if (!str) return FALSE;

    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        // Пропускаем не-буквы
        while (left < right && !isalnum(str[left])) left++;
        while (left < right && !isalnum(str[right])) right--;

        if (tolower(str[left]) != tolower(str[right])) {
            return FALSE; // Если символы не равны, строка не палиндром
        }

        left++;
        right--;
    }
    return TRUE; // Если все проверки пройдены, строка палиндром
}
//Для Unicode
int countwords(const wchar_t* str) {
    if (str == NULL) return 0;

    bool inWord = false;
    int wordCount = 0;

    while (*str != L'\0') {
        if (iswalnum(*str)) {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        }
        else {
            inWord = false;
        }
        str++;
    }
    return wordCount;
}
void reversestring(wchar_t* str) {
    if (!str) {
        printError(ERROR_INVALID_PARAMETER);
        return;
    }

    int length = wcslen(str);
    for (int i = 0; i < length / 2; i++) {
        swap(str[i], str[length - 1 - i]);
    }
}

BOOL isstringpalindrome(const wchar_t* str) {
    if (!str) return FALSE;

    int left = 0;
    int right = wcslen(str) - 1;

    while (left < right) {
        while (left < right && !iswalnum(str[left])) left++;
        while (left < right && !iswalnum(str[right])) right--;

        if (towlower(str[left]) != towlower(str[right])) {
            return FALSE;
        }

        left++;
        right--;
    }
    return TRUE;
}
//Вывод ошибки 
void printError(DWORD errorCode) {
    LPSTR errorMsg = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        errorCode,
        0,
        (LPSTR)&errorMsg,
        0,
        NULL
    );

    cout << "Ошибка " << errorCode << ": " << errorMsg << endl;
    LocalFree(errorMsg);
}



int main()
{
    setlocale(LC_ALL, "RU");
    //Работа ANSI-функций

    cout << "=== ANSI Functions Demo ===" << endl;
    //Тестовая строка
    char ansiStr[] = "а роза упала на лапу Азора";
    cout << "Original ANSI string: " << ansiStr << endl;
    // Подсчет слов
    cout << "Количество слов: " << countwords(ansiStr) << endl;
    //Переворот строки
    reversestring(ansiStr);
    cout << "После переворота: " << ansiStr << endl;
    //Палидром
    cout << "Строка является палиндромом? " << (isstringpalindrome(ansiStr) ? "YES" : "NO") << endl;

    //Работа Unicode-функций
    wcout << L"\n=== Unicode Functions Demo ===" << endl;
    //Тестовая строка
    wchar_t unicodeStr[] = L"Привет, мир! Hello, world!";
    wcout << L"Original UNICODE string: " << unicodeStr << endl;
    // Подсчет слов
    wcout << L"Количество слов: " << countwords(unicodeStr) << endl;
    //Переворот строки
    reversestring(unicodeStr);
    wcout << L"После переворота: '" << unicodeStr << L"'" << endl;
    //Палидром
    wcout << "Строка является палиндромом? " << (isstringpalindrome(unicodeStr) ? "YES" : "NO") << endl;

    cout << "\n=== Testing Error Handling ===" << endl;
    reversestring((char*)nullptr);
    reversestring((wchar_t*)nullptr);

    return 0;



}
