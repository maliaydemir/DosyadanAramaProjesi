#include<string>
#include<fstream>
#include<iostream>
#include <locale.h>
#include <conio.h> 
using namespace std;

string toString(int id) {//girilen pozitif sayýyý stringe çevirir
	string _id = "";
	int r;
	if (id<0) {
		return "-1";
	}
	else if (id == 0) {
		return "0";
	}
	for (int i = 1; i <= id; i += 0) {
		i *= 10;
		r = (id / (i / 10)) % 10;
		_id = (char)(r + 48) + _id;
	}
	return _id;
}
int toInteger(string _id) {
	int tmp = 0;
	for (int i = 0; i<_id.length(); i++) {
		if (_id[i] >= 48 || _id[i] <= 57) {
			tmp = tmp + (((int)_id[i]) - 48)*pow(10, _id.length() - 1 - i);
		}
		else {
			return -1;
		}
	}
	return tmp;
}
string toLower(string str) {
	string tmp = "";
	for (int i = 0; i<str.length(); i++) {
		tmp += tolower(str[i]);
	}
	return tmp;


}
string trim2(string str, const string chars = "\t\n\v\f\r.,!:;()[]{}*\"=#$&%/? ") {
	//stringlerin basindaki bosluk ve noktalama isaretlerini siler
	// " test " --> "test"
	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < chars.length(); j++)
		{
			if (str[i]==chars[j])
			{
				str[i] = ' ';
			}
		}
	}
	return str;
}
string trim(string str) {
	//stringlerin basindaki bosluk ve noktalama isaretlerini siler
	// " test " --> "test"

	if (str.length() == 0)
	{
		return "";
	}
	int k = 0;
	while (!(str[k] >= 'a'&&str[k] <= 'z' || str[k] >= 'A'&&str[k] <= 'Z') && k<str.length())
	{
		k++;
	}
	string str2 = str.substr(k, str.length());
	if (str2.length() == 0)
	{
		return "";
	}

	k = str2.length();
	while (!(str2[k] >= 'a'&&str2[k] <= 'z' || str2[k] >= 'A'&&str2[k] <= 'Z') && k>-1)
	{
		k--;
	}
	string str3 = str2.substr(0, k + 1);

	return str3;
}
int eksi2(int x) 
{	
	if (x>2)
	{
		return x - 2;
	}
	return 1;
}
string input() {

	char tmp[50];
	cin >> tmp;
	return trim(tmp);
}

string toUpper(string kelime) {
	//harfleri buyuk hale getirir
	//ingilizce karakterler dýþýnda birþey varsa boþluk ile deðiþtirir
	for (int i = 0; i < kelime.length(); i++)
	{
		if (kelime[i] >= 'a'&&kelime[i] <= 'z')
		{
			kelime[i] -= 32;
		}
		else if (!(kelime[i] >= 'a' && kelime[i] <= 'z') && !(kelime[i] >= 'A' && kelime[i] <= 'Z') && !(kelime[i] >= 48 && kelime[i] <= 57))
		{
			kelime[i] = ' ';
		}
	}
	return kelime;
}

//yakýn eþleþme 
#define MIN(x,y) ((x) < (y) ? (x) : (y))
int levinsteinSearch(string str1, string str2) {
	str1 = toUpper(str1);
	str2 = toUpper(str2);
	int i, j, l1, l2, t, track;
	int dist[50][50];

	char *s1 = &str1[0];
	char *s2 = &str2[0];

	//stores the lenght of strings s1 and s2
	l1 = strlen(s1);
	l2 = strlen(s2);
	for (i = 0; i <= l1; i++) {
		dist[0][i] = i;
	}
	for (j = 0; j <= l2; j++) {
		dist[j][0] = j;
	}
	for (j = 1; j <= l1; j++) {
		for (i = 1; i <= l2; i++) {
			if (s1[i - 1] == s2[j - 1]) {
				track = 0;
			}
			else {
				track = 1;
			}
			t = MIN((dist[i - 1][j] + 1), (dist[i][j - 1] + 1));
			dist[i][j] = MIN(t, (dist[i - 1][j - 1] + track));
		}
	}
	
	return dist[l2][l1];

}

int minimum(int a, int b, int c) {
	if (a <= b && a <= c)
		return a;
	if (b <= c && b <= a)
		return b;
	if (c <= a && c <= b)
		return c;
	return 0;
}
int LevenshteinMesafesi(string s, string t) {
	s = toUpper(s) ;
	t = toUpper(t);
	const int m = s.length();
	const int n = t.length();

	int **d = new int*[m+1];
	for (int i = 0; i < m+1; i++)
	{
		d[i] = new int[n+1];
	}

	for (int i = 0; i < m; i++)
		d[i][0] = i;
	for (int i = 0; i < n; i++)
		d[0][i] = i;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {

			if (s[i - 1] == t[j - 1]) {

				d[i][j] = d[i - 1][j - 1];

			}
			else {
				d[i][j] = minimum
				(
					d[i - 1][j] + 1,
					d[i][j - 1] + 1,
					d[i - 1][j - 1] + 1
				);

			}
		}
	}
	return d[m-1][n-1]+1;
}






string strReverse(string str) {
	string tmp = "";
	for (int i = str.length()-1; i >= 0; i--)
	{
		tmp += str[i];
	}
	return tmp;

}

