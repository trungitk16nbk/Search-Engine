#include "AddFile.h"
#include "AddFolder.h"
using namespace std;
void addFolder(string dir) {
	for (auto& p : filesystem::recursive_directory_iterator(dir)) {
		if (p.is_regular_file())
		{
			string s = filesystem::absolute(p.path()).string();
			int pos = 0;
			while ((pos = s.find('\\')) != string::npos) {
				s.replace(pos, 1, "/");
			}
			if (AddFile_load_toMetadata(s, 0))
				cout << "ADD thanh cong file: " << s << endl;
		}
	}

}