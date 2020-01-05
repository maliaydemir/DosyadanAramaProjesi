#include <iostream>
#include <thread>
#include <future>
#include<time.h>
#include <stdio.h>
#include "classes.h"
#include <chrono>
#include <thread>
using namespace std;


void loadHash(HashTablosu *hash_t){
	clock_t time;
	time = clock();
	hash_t->yukle();
	cout << toUpper(hash_t->dosyaUzantisi()) << " Yükleme Suresi: " << (float)(clock() - time) / CLOCKS_PER_SEC << endl;
}
bool _tamEslesme(HashTablosu *hash_t,string kelime) {
	return hash_t->tamEslesme(kelime);
}

bool _yakinEslesme(HashTablosu *hash_t, string kelime) {
	return hash_t->yakinEslesme(kelime);
}
int main()
{
	setlocale(LC_ALL, "Turkish");


	system("FileConverter.exe");//docx ve pdf dnnüþtürme

	cout << "Kelimeler Yükleniyor.." << endl;
	this_thread::sleep_for(std::chrono::milliseconds(1500));
	HashTablosu hash1("txt");
	HashTablosu hash2("html");
	HashTablosu hash3("docx");
	HashTablosu hash4("pdf");
	HashTablosu* hashes[4];
	hashes[0] = &hash1;
	hashes[1] = &hash2;
	hashes[2] = &hash3;
	hashes[3] = &hash4;
	

	auto t1 = async(loadHash, &hash1);
	auto t2 = async(loadHash, &hash2);
	auto t3 = async(loadHash, &hash3);
	auto t4 = async(loadHash, &hash4);
	t1.get();
	t2.get();
	t3.get();
	t4.get();


	for (int i = 0; i < 4; i++)
	{
		cout<<toUpper(hashes[i]->dosyaUzantisi())<<" dosyasý kelime sayýsý: "<<hashes[i]->kelimeAdet()<<endl;
	}	

	string k;

	while (true) {
	remove("benzerleri.txt");
	
	cout << "Aramak istediðiniz Kelimeyi Girin: ";
	k = input();
	cout << endl;
	clock_t time;
	time = clock();
	
	bool tam = false;
	bool yakin = false;

	auto ta1 = async(_tamEslesme, hashes[0], k);
	tam += ta1.get();
	auto ta2 = async(_tamEslesme, hashes[1], k);
	tam += ta2.get();
	auto ta3 = async(_tamEslesme, hashes[2], k);
	tam += ta3.get();
	auto ta4 = async(_tamEslesme, hashes[3], k);
	tam += ta4.get();

	if (!tam)
	{
		for (int i = 0; i < 4; i++)
		{
			yakin += hashes[i]->yakinEslesme(k);
		}
	}
		
	time = clock() - time;
	cout << "HASH Arama Suresi: " << (float)time / CLOCKS_PER_SEC << endl;

	int cntHash = hashes[0]->karakterAdet(k.length());
	int cnt2 = hashes[0]->tamcnt;
	cout << k.length() << " karakterli kelime adedi: " << cntHash << " - arama iþlem adedi: " << cnt2<<endl;
	cout<<"yakýn arama iþlem adedi: " << hashes[0]->yakincnt<<endl;

	if (!tam)
	{
		if (yakin)
		{
			cout << "Benzerlerini kontrol edin." << endl;
			system("benzerleri.txt");
		}
		else
		{
			cout << "Aradýðýnýz kelime bulunamadý";
		}
	}
	system("pause");
	}
	system("pause");
}
