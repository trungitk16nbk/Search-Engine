#include "Load_Meta.h"
#include "StringHandling.h"
#include <filesystem>

struct term {
	string s;
	int hash;
};
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(term*& t, int low, int high)
{
	int pivot = t[high].hash;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{

		if (t[j].hash < pivot)
		{
			i++;
			swap(&t[i].hash, &t[j].hash);
		}
	}
	swap(&t[i + 1].hash, &t[high].hash);
	return (i + 1);
}
void quickSort_temp(term*& t, int low, int high) {
	if (low < high)
	{
		int pi = partition(t, low, high);


		quickSort_temp(t, low, pi - 1);
		quickSort_temp(t, pi + 1, high);
	}
}
void quickSort(term*& t, int n) {
	quickSort_temp(t, 0, n - 1);
}

void loading_metadata(int doc,size_t loc)
{
	string s;
	fstream f("RemoveStopWords.txt");
	filesystem::create_directories("./sandbox");
	if (f.fail()) return;
	int kiemtra = 1;
	f.seekg(loc, ios::beg);
	while (getline(f, s)) {
		int n = 0;
		string dir = "sandbox/metadata" + to_string(doc) + ".txt";
		fstream meta(dir, ios::out);
		if (!meta) continue;
		string* file = splitString(s, n);
		term* t = new term[n];
		for (int i = 0; i < n; i++) {
			t[i].s = file[i];
			t[i].hash = hash<string>{} (t[i].s);
		}
		delete[] file;
		quickSort(t, n);

		for (int i = 0; i < n; i++) {
			int cnt = 1;
			int j;
			for (j = i + 1; j < n && t[i].hash == t[j].hash; j++) {
				cnt++;
			}
			double tf = (double)cnt / double(n);
			meta << tf << " " << t[i].s <<"."<< endl;
			i = j - 1;
		}
		meta.close();
		doc++;
		delete[] t;
	}
	f.close();
}
