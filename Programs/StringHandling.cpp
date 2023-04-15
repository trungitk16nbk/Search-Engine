#include "StringHandling.h"


string fGetlines(wifstream& is16, int lines) {
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
	is16.imbue(locale(is16.getloc(), new codecvt_utf16<wchar_t, 0x10ffff, little_endian>()));

	wstring wline;
	string u8line = "";
	for (int i = 0; i < lines && getline(is16, wline); i++) {
		wline = RemoveVietnameseTone(wline); // xoa dấu utf 16
		u8line += converter.to_bytes(wline);// chuyen utf 16 sang utf 8
	}
	return u8line;
}
wstring RemoveVietnameseTone(std::wstring& text) {
	std::wstring result(text);
	result = regex_replace(result, wregex(L"à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ|/g"), L"a");
	result = regex_replace(result, wregex(L"À|Á|Ạ|Ả|Ã|Â|Ầ|Ấ|Ậ|Ẩ|Ẫ|Ă|Ằ|Ắ|Ặ|Ẳ|Ẵ|/g"), L"A");
	result = regex_replace(result, wregex(L"è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ|/g"), L"e");
	result = regex_replace(result, wregex(L"È|É|Ẹ|Ẻ|Ẽ|Ê|Ề|Ế|Ệ|Ể|Ễ|/g"), L"E");
	result = regex_replace(result, wregex(L"ì|í|ị|ỉ|ĩ|/g"), L"i");
	result = regex_replace(result, wregex(L"Ì|Í|Ị|Ỉ|Ĩ|/g"), L"I");
	result = regex_replace(result, wregex(L"ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ|/g"), L"o");
	result = regex_replace(result, wregex(L"Ò|Ó|Ọ|Ỏ|Õ|Ô|Ồ|Ố|Ộ|Ổ|Ỗ|Ơ|Ờ|Ớ|Ợ|Ở|Ỡ|/g"), L"O");
	result = regex_replace(result, wregex(L"ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ|/g"), L"u");
	result = regex_replace(result, wregex(L"Ù|Ú|Ụ|Ủ|Ũ|Ư|Ừ|Ứ|Ự|Ử|Ữ|/g"), L"U");
	result = regex_replace(result, wregex(L"ỳ|ý|ỵ|ỷ|ỹ|/g"), L"y");
	result = regex_replace(result, wregex(L"Ỳ|Ý|Ỵ|Ỷ|Ỹ|/g"), L"y");
	result = regex_replace(result, wregex(L"đ"), L"d");
	result = regex_replace(result, wregex(L"Đ"), L"D");
	return result;
}
void DelExtraSpace(string& s) {
	while (s[0] == ' ') s.erase(0, 1);
	int len = s.length();
	if (len < 1) return;
	while (s[len - 1] == ' ') {
		s.erase(len - 1, 1); len--;
	}

	int i = 1;
	while (i < len - 1) {
		if (s[i] == ' ' && s[i + 1] == ' ') {
			s.erase(i, 1); len--;
		}
		else i++;
	}
}
void DelSign(string& s) {
	int k = 0;
	int len = s.length();
	int pos;
	while (k != len) {
		if (!((s[k] >= 'a' && s[k] <= 'z') || (s[k] <= '9' && s[k] >= '0'))) s[k] = ' ';
		k++;
	}
}
void stringHandling(string& s) {
	if (s == "") return;
	transform(s.begin(), s.end(), s.begin(), towlower); // chuyển in thường
	DelSign(s); // chỉ giữ lại chữ cái và số
	DelExtraSpace(s); // xóa dấu cách thừa
}
string* splitString(string& s, int& total) {

	int len = s.length();
	string tmp[10000];
	int i = 0, pos;
	string space = " ";
	while ((pos = s.find(space)) != string::npos) {
		tmp[i++] = s.substr(0, pos);
		s.erase(0, pos + 1);

	}
	tmp[i++] = s;
	string* res = nullptr;
	total = i;
	res = new string[total];
	for (i = 0; i < total; i++)
		res[i] = tmp[i];
	return res;
}