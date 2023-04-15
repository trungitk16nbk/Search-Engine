#include "AddFile.h"

using namespace std;

string inputPaths() {
	cout << "Nhap Path... \n";
	string res;
	cin.ignore();
	getline(cin,res);
	return res;
}

int AddFile_load_toMetadata(string s, int cin_) { 
	if(cin_) s = inputPaths();
	fstream dir("Directions.txt");
	if (!dir) {
		cout << "Khong mo duoc file Directions.txt..." << endl;
		return 0;
	}
	dir.clear();
	dir.seekg(0, ios::end);
	string Path = getDir(s);
	dir << Path << endl;
	wifstream is16(s,ios::in);
	fstream rmStW("RemoveStopWords.txt");
	rmStW.clear();
	rmStW.seekg(0, ios::end);
	if (rmStW.fail()) {
		cout << "Khong mo duoc file RemoveStopWords.txt..." << endl;
		return 0;
	}
	size_t size_old = rmStW.tellg();
	if (is16.fail()) {
		cout << "Khong mo duoc file can THEM vao..." << endl;
		return 0;
	}
	// xoa stopwords
	string str,w;
	fstream st("StopWords.txt");
	if (st.fail()) {
		cout << "Khong mo duoc file StopWords.txt" << endl;
		return 0;
	}
	while (!is16.eof()) {
		str=fGetlines(is16, 100);
		stringHandling(str);
		while (getline(st, w)) {
			w = " " + w + " ";
			int len_w = w.length();
			int pos;
			while ((pos = str.find(w)) != string::npos) {
				str.erase(pos, len_w-1);
			}

		}
		rmStW << str;
	}
	rmStW << endl;
	rmStW.close();
	int tt;
	FILE* ttf = fopen("TotalFiles.txt", "r+");
	fscanf(ttf, "%d", &tt);
	fseek(ttf, 0, SEEK_SET);
	fprintf(ttf, "%d", tt+1);
	fclose(ttf);
	// load to metadata
	loading_metadata(tt,size_old);
	st.close();
	is16.close();
	return 1;
}