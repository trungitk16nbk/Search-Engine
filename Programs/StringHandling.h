#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <wchar.h>
#include <iostream>
#include <codecvt>
#include <fstream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <regex>
using namespace std;
string fGetlines(wifstream& is16, int lines);
wstring RemoveVietnameseTone(wstring& text);
void DelExtraSpace(string& s);
void DelSign(string& s); 
void stringHandling(string& s);
string* splitString(string& s, int& total);