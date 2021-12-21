#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "StaticLib1.lib")
#include "MathLibrary.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <csignal>
#include <conio.h>

using namespace std;

int main()
{
    std::ofstream erase("log.txt", std::ios::out);
    erase.close();
    std::ofstream out("log.txt", std::ios::app);
    SetFileAttributes(L"log.txt", FILE_ATTRIBUTE_READONLY);

    vector<string> arr;
    string str, instStr;
    //cin >> instStr;
    ifstream file("text.txt");
    if (file.is_open() != true) 
    {
        return 0;
    }

    while (getline(file, str)) {
        cout << str << endl;
    }
    int k = 10;
    for (int i = 0; i < 10; i++) {
        arr.push_back(str.substr(k - 10, 10));
        k += 10;
    }

    for (int i = 0; i < 10; i++) {
        cout << arr.at(i) << endl;
    }
    std::sort(arr.begin(), arr.end(), std::greater<string>()); 
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << arr.at(i) << endl;
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        string tmp = arr.at(i);
        tmp = MathLibrary::Operation::Replace(tmp, "9", "0");
        tmp = MathLibrary::Operation::Replace(tmp, "8", "0");
        tmp = MathLibrary::Operation::Replace(tmp, "7", "0");
        tmp = MathLibrary::Operation::Replace(tmp, "6", "0");
        tmp = MathLibrary::Operation::Replace(tmp, "1", "0");
        arr.at(i) = tmp;
    }
    std::sort(arr.begin(), arr.end(), std::greater<string>());
    for (int i = 0; i < 10; i++) {
        cout << arr.at(i) << endl;
        if (out.is_open())
        {
            out << arr.at(i) << endl;
        }
    }
    out.close();
    system("pause");
}
