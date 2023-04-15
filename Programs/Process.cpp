#include "Process.h"
#include "StringHandling.h"
#include "Document.h"
#include "Load_Meta.h"
#include <iomanip> 
#define MAX_FILE 15000
#define MAX_SIZE_WORDS 50
struct idfKeyWord {
	string keyWord;
	double idf;
};
struct table_Check {
	int check; // kiem tra coi tu co tu nao trong van ban do khong
	char check_Key[10]; // neu co thi tu khoa nao co trong do
};
string* input(int& n) {
	system("input.txt");
	fstream in("input.txt");
	in.seekg(26, in.beg);
	string s;
	getline(in, s);
	stringHandling(s);
	string* res = splitString(s, n);
	return res;
}
int* kmp_table(char*& w) {
	if (!w) return 0;
	int pos = 2, cnd = 0;
	int len = strlen(w);
	int* T = new int[len]; if (!T) return nullptr;
	T[0] = -1; T[1] = 0;

	while (pos < len) {
		if (w[pos - 1] == w[cnd]) { T[pos] = cnd + 1; pos++; cnd++; }
		else if (cnd > 0) cnd = T[cnd];
		else {
			T[pos] = 0; pos++;
		}
	}
	return T;

}
int kmp_search(char s[], char*& w) {

	if (!s && !w) return 0;
	int* T = kmp_table(w);
	if (!T) return 0;
	int m = 0, i = 0;
	int len = strlen(s);
	int len_w = strlen(w);
	if (len < len_w) return len;
	while (m + i < len) {
		if (w[i] == s[m + i]) {
			i++;
			if (i == len_w) {
				return m;
			}
		}
		else {
			if (T[i] > 0) {
				i = T[i];
				m = m + i - T[i];
			}
			else {
				i = 0; m++;
			}

		}
	}
	return len;
}
double idf_term(string& term,int index,table_Check table[MAX_FILE]) {
	FILE* f = fopen("RemoveStopWords.txt", "r");
	FILE* t = fopen("TotalFiles.txt", "r");
	if (!f || !t) return 0;
	int totalOfFile;
	fscanf(t, "%d", &totalOfFile);
	fclose(t);
	int len = term.length()+2;
	char* str = new char[len];
	string tmp =" "+ term+" ";
	str = _strdup(tmp.c_str());
	char s[50000];//50000
	int res = 0;
	int i = 0;
	while (fgets(s, 50000, f)) {
		size_t len_s = strlen(s);
		if (kmp_search(s, str) < len_s)
		{
			res++;
			table[i].check = 1;
			table[i].check_Key[index] = 1;
		}
		i++;
	}
	delete[] str;
	str = nullptr;
	fclose(f);

	return 1+log((double)totalOfFile / (1 + (double)res));
}

void getScores(List_document& l,idfKeyWord *idf, string* keywords, int n, table_Check table[MAX_FILE]) {
	time_t t = clock();

	for (int i = 0; i < n; i++) {
		idf[i].keyWord = keywords[i];
		idf[i].idf=idf_term(keywords[i],i,table); //tu khoa thu i
	}
	int realsize=0;
	fstream totalofFiles("TotalFiles.txt",ios::in);
	int totalFiles=0;
	totalofFiles >> totalFiles; // lay tong so file
	totalofFiles.close();
	double tf_query = 1 / (double)n;
	double euclid_query = 0;
	for (int i = 0; i < n; i++) {
		euclid_query += (tf_query * idf[i].idf) * (tf_query * idf[i].idf);
	}
	euclid_query = sqrt(euclid_query);

	for (int i = 0; i < totalFiles-1 ; i++) {
		if (table[i].check!= 1) continue;
		string s = "./sandbox/metadata" + to_string(i+1) + ".txt";
		char* dir = _strdup(s.c_str());
		char tmp[MAX_SIZE_WORDS];
		FILE* f = fopen(dir, "r"); // xu ly tung file trong folder sandbox
		delete[] dir;	
		dir = nullptr;
		if (f) {
			double tf_idf_term = 0;
			double euclid_dis = 0;
			int check = 0;
			double vector_product = 0;
			while (fgets(tmp, MAX_SIZE_WORDS, f)) {
				int len = strlen(tmp);
				table[i].check = 0;
				for (int j = 0; j < n ; j++) {
					if (table[i].check_Key[j] != 1) continue;
					string s_tmp = " " + idf[j].keyWord + ".";
					char* w = _strdup(s_tmp.c_str());

					if (kmp_search(tmp,w)<len)
					{
						check = 1;
						table[i+1].check_Key[j] = 0;
						double tf_term = stod(tmp);
						tf_idf_term = tf_term * idf[j].idf;
						vector_product += tf_idf_term * (tf_query * idf[j].idf);
						euclid_dis += tf_idf_term * tf_idf_term;
					}
					delete[] w;
					w = nullptr;
				}

				for (int j = 0; j < n; j++)
				{
					if (table[i].check_Key[j] ==1)
					{
						table[i].check = 1;
					}
				}

				if( table[i].check == 0) break;

			}
			if (check == 1) {
				check = 0;
				document doc;
				euclid_dis = sqrt(euclid_dis);
				doc.cosine_Similarity = vector_product / (euclid_dis * euclid_query);
				doc.index = i + 1;
				AddTail(l, doc);
				realsize++;
			}
			fclose(f);
		}
		

	}
	quickSort_docList(l);
	node* NODE = l.h;
	string DIR[10];
	FILE* Paths = fopen("Directions.txt", "r");
	if (!Paths) {
		cout << "Khong mo duoc file DirFiles.txt"; return;
	}
	int n10 = 10;
	cout << "Khoang " << realsize << " ket qua  duoc tim thay: \n";
	if (realsize < 10)
		n10 = realsize;
	cout << n10<< "  ket qua lien quan nhat (thoi gian tim kiem " <<((double)clock() - t) / (CLOCKS_PER_SEC) << " s!)" <<": \n";
	for (int i = 0; i < n10 && NODE; i++) {
		char tmp[256];
		int j = 0;

		while (NODE->doc.index != (j++)&&fgets(tmp, 256, Paths));
		string ss(tmp);
		DIR[i] = ss;
		fseek(Paths, 0, SEEK_SET);
		cout <<i+1 <<". Cosine similarity: " << NODE->doc.cosine_Similarity << "\t" << DIR[i] << endl;
		NODE = NODE->next;
	}
	cout << "Chon cac tai lieu tu 1 toi "<<n10<<" ..." << endl;
	cout << "Nhan 0... de thoat" << endl;
	while (1) {
		int nhap;
		cin >> nhap;
		int check_out = 0;
		switch (nhap)
		{
		case 0:check_out = 1; break;
		default:system(DIR[nhap-1].c_str());
			break;
		}
		if (check_out == 1)
			break;
	}
	fclose(Paths);
}

void process() {
	
	while (1) {
		List_document l;
		l.h = NULL;
		int n = 0;
		string* KeyWords = input(n);
		idfKeyWord* idf = new idfKeyWord[n];
		table_Check* table = new table_Check[MAX_FILE];
		
		cout << "\n";
		cout << setw(60) << right << "mSEARCH\n";
		getScores(l, idf, KeyWords, n, table);
		RemoveAll(l);
		delete[] idf;
		delete[] KeyWords;
		delete[] table;
		system("cls");
		cout << "Ban co muon nhap lai khong?" << endl;
		cout << "1. De nhap lai:" << endl;
		cout << "2. exit"<<endl;
		int in,check;
		cin >> in;
		switch (in)
		{
		case 1: check = 0; break;
		default:check = 1;
			break;
		}
		if (check == 1) break;
	}
}