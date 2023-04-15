#include "RemovingStopWords.h"
static int total = 0;
const wchar_t TRAIN[30]= L"D:/Data/new test/*";
const wchar_t TRAIN2[30]= L"D:/Data/new test/";
void RemoveStopwords(wifstream& is16, fstream& out) {
	string s = "", w = "";
	int len_w;
	int pos;

	fstream StopWordText("StopWords.txt");
	while (!is16.eof()) {
		s = fGetlines(is16, 100);
		stringHandling(s);
		while (getline(StopWordText, w)) {
			string temp = " "  + w + " ";
			len_w = w.length();
			while ((pos = s.find(temp)) != string::npos) //xoa o giua
				s.erase(pos, len_w + 1);
		}
		out << s;
		StopWordText.clear();
		StopWordText.seekg(0, StopWordText.beg);

	}
	
	out << "\n";
}
string getDir(string s) {
	int pos = 0;
	while ((pos = s.find(" ")) != string::npos)
		s.replace(pos, 1, "\%20");
	while ((pos = s.find("\\")) != string::npos)
		s.replace(pos, 1, "/");
	return "start file:///" + s;
}
void ReadOneFile(wchar_t FileFolder[], fstream& rm,fstream& Paths) {
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	wchar_t FileName[256];
	wcscpy(FileName, FileFolder);
	wcscat(FileName, L"*.txt");
	int i = 1;
	if ((hFind = FindFirstFile(FileName, &FindFileData)) != INVALID_HANDLE_VALUE) {
		do {
			wchar_t filename[256];
			wcscpy(filename, FileFolder);
			wcscat(filename, FindFileData.cFileName);
			wifstream is16(filename);
			if (!Paths) cout << "Khong mo duoc Directions.txt\n";
			char name[256];
			wcstombs(name, filename, 256);
			string dir(name);
			dir = getDir(dir);
			Paths<< dir << endl;
			if (is16) {
				total++;
				RemoveStopwords(is16, rm);
			}
			is16.close();
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}
void Loading_RemoveStopWords() {

	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	int d = 0;
	fstream removeSt("RemoveStopWords.txt");
	fstream fname("Directions.txt", ios::out);

	if (removeSt.fail()) { cout << "khong mo duoc file RemoveStopWords.txt"; return; }
	if (fname.fail()) {
		cout << "khong mo duoc file Paths.txt" << endl;
	}
	wchar_t Find_first_file[256];
	wcscpy(Find_first_file, TRAIN);
	if ((hFind = FindFirstFile(Find_first_file, &FindFileData)) != INVALID_HANDLE_VALUE) {
		do {
			d++;
			if (d > 2) {
				wchar_t filefolder[256];
				wcscpy(filefolder,TRAIN2);
				wcscat(filefolder, FindFileData.cFileName);
				wcscat(filefolder, L"/");
				ReadOneFile(filefolder, removeSt,fname);
			}

		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
	removeSt.close();
	fname.close();
	fstream totalFiles("TotalFiles.txt");
	totalFiles << total+1;
	totalFiles.close();
}
