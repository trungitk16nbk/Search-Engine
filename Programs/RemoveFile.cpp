#include "RemoveFile.h"
#include "RemovingStopWords.h"
#include "Process.h"
#include <iostream>

using namespace std;
string input() {
	string res;
	cout << "\nMoi ban nhap duong dan: " << endl;
	cin.ignore();
	getline(cin, res);
	return res;
}
int RemovingFile() {
	int check = 1;
	string dir=input();
	string direction = getDir(dir);
	char* dir_c = _strdup(direction.c_str());
	if (!dir_c) {
		cout << "Het bo nho cap phat...\n";
		return 0;
	}
	FILE* f = fopen("Directions.txt", "r");
	FILE* rmST = fopen("RemoveStopWords.txt", "r");
	if (!f||!rmST) {
		cout << "Khong mo duoc file Directions.txt ||RemoveStopWords.txt\n";
		return 0;
	}
	FILE* out_dir = fopen("Dir_tmp.txt", "w");
	FILE* out_rmST = fopen("RemoveStopWords_tmp.txt", "w");
	char check_dir[512];
	int i = 0;
	while (fgets(check_dir, 512, f)) {
		++i;
		if (kmp_search(check_dir, dir_c) < strlen(check_dir))
		{
			check = 0;
			break;
		}
		
	}
	delete[] dir_c;
	char path[512], st[50000];
	if (check == 1) return 0;
	fseek(f, 0, SEEK_SET);
	int j = 0;

	string removeMeta = "./sandbox/metadata" + to_string(i) + ".txt";
	remove(removeMeta.c_str());
	FILE* totalf=fopen("TotalFiles.txt", "r+");
	if (!totalf) {
		cout << "khong mo duoc TotalFiles.txt" << endl;
		return 0;
	}
	int totalF=0;
	fscanf(totalf, "%d", &totalF);
	totalF--;
	fseek(totalf, 0, SEEK_SET);
	fprintf(totalf, "%d", totalF);
	for (int k = i + 1; k <= totalF; k++)
	{
		string dir_old= "./sandbox/metadata" + to_string(k) + ".txt";
		string dir_new = "./sandbox/metadata" + to_string(k-1) + ".txt";
		char* tmp1 = _strdup(dir_old.c_str());
		char* tmp2 = _strdup(dir_new.c_str());
		rename(tmp1, tmp2);
		delete[] tmp1;
		delete[] tmp2;
	}
	while (fgets(path, 512, f) && fgets(st, 50000, rmST)) {
		++j;
		if (j == i)
			continue;
		fputs(path, out_dir);
		fputs(st, out_rmST);
	}
	
	fclose(f);
	fclose(rmST);
	fclose(out_dir);
	fclose(out_rmST);
	remove("RemoveStopWords.txt");
	remove("Directions.txt");
	rename("Dir_tmp.txt", "Directions.txt");
	rename("RemoveStopWords_tmp.txt", "RemoveStopWords.txt");
	return 1;
}


