#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include "RemovingStopWords.h"
#include "Load_Meta.h"
#include "StringHandling.h"
#include "Document.h"
#include "Process.h"
#include "AddFile.h"
#include <iostream>
#include "RemoveFile.h"
#include "AddFolder.h"

using namespace std;
//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool dirExists(string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   

    return false;    
}

int main()
{
    cout << "\n\n";
    cout << "\t\t\t\t\tCHAO MUNG DEN VOI SEARCH ENGINE\n\n" << endl;
    int chon = 0;
    while (1) {
        cout << "Vui long chon cac muc sau: \n";
        cout << "1. Search: \n";
        cout << "2. Them file (Nhap duong dan)" << endl;
        cout << "3. Them Folder (Nhap duong dan)" << endl;
        cout << "4. Xoa file (Nhap duong dan)" << endl;
        cout << "5. Train cac tap tin" << endl;
        cout << "6. EXIT!" << endl;
        scanf("%d", &chon);
        int check = 0;
        string s1;
        string inputFolder;
        string inputFile;
        switch (chon) {
        case 1: process(); break;
        case 2: if (AddFile_load_toMetadata(inputFile,1) != 0) cout << "Add thanh cong\n";
              else cout <<"Loi duong dan || hoac cac file bi loi"; break;
        case 3:
            cout << "Nhap duong dan folder (thi du folder 123 o o D thi: D:/123)"<<endl;
            cin.ignore();
            getline(cin, inputFolder);
            if (!dirExists(inputFolder)) cout << "folder khong ton tai..." << endl;
            else {
                addFolder(inputFolder);
            }
            break;
        case 4: if(RemovingFile()!=0)cout << "Remove thanh cong\n";
              else cout << "Loi duong dan || hoac cac file bi loi";; break;
        case 5:
            s1 = "./sandbox";
            if (dirExists(s1)) {
                cout << "Da train tap tin\n";
                break;
            }
            cout << "Dang train..." << endl;
            Loading_RemoveStopWords();
            loading_metadata(1, 0);
            cout << "Train thanh cong!" << endl;
            break;
        default: check = 1; break;
        }
        //
        if (check == 1) break;
    }

}