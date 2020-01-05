#include "helpers.h"
#include <iostream>
#include <math.h>

struct satirNode {
	int satirNo;
	satirNode *next=NULL;
};
struct kelimeNode {
	string kelime;
	int adet=0;
	satirNode *satirlar = NULL;

	string satirlariYaz() {
		string satirYazi = "";
		satirNode *yrd = satirlar;
		int i = 0;
		while (yrd!=NULL)
		{
			satirYazi += toString(yrd->satirNo);
			i++;
			if (satirYazi.length()>45)
			{
				satirYazi += "...";
				return satirYazi;
			}
			if (yrd->next!=NULL)
			{
				satirYazi += ",";
			}
			yrd = yrd->next;
			
			
		}
		return satirYazi;
	}
	void satirEkle(int sNo) {
		satirNode *yrd = satirlar;
		if (yrd==NULL)
		{
			satirlar = new satirNode;
			satirlar->satirNo = sNo;
			return;
		}
		while (yrd->next!=NULL)
		{
			if (yrd->satirNo ==sNo)
			{
				return;//bu satýr bu kelime için eklenmiþ zaten
			}
			yrd = yrd->next;
		}
		if (yrd->satirNo != sNo)
		{//son satirý dakontrol edip ona göre ekleme yapýyoruz
			yrd->next = new satirNode;
			yrd->next->satirNo = sNo;
		}
	}
};
class HashTablosu {
private: 
	int hashAdet = 0;
	int hashBoyut = 100000;
	
	
	string dosyaUzanti="";
	string dosyaAdi() {
		return "metin." + dosyaUzanti;
	}
	int hashIndisHesapla(string kelime) {
		int indis = ((int)pow(3, kelime.length()%19))%hashBoyut;
		return indis;
	}

public:
	
	int tamcnt = 0;
	int yakincnt = 0;
	kelimeNode **hashTablo;
	HashTablosu(string _dosyaUzanti) {
		dosyaUzanti = _dosyaUzanti;
		hashTablo = new kelimeNode*[hashBoyut];
		for (int i = 0; i < hashBoyut; i++)
		{
			hashTablo[i] = NULL;
		}
	}
	void ekle(string kelime, int satir) {

		int indis = hashIndisHesapla(kelime);
		indis = ara(kelime, indis);
		/*
			eklenecek olan kelime hash tablosunda aranýr
			kelime bulunursa kelimenin satýrý güncellenir
			kelime bulunamazsa ara fonksiyonundan eklenmesi gereken indis bize döndürülür (*-1 þeklinde)
		*/
		if (indis>-1)
		{
			//kelime tabloda zaten var satýr ekle
			if (hashTablo[indis]->kelime == kelime)
			{
				hashTablo[indis]->satirEkle(satir);
				hashTablo[indis]->adet++;
			}
		}
		else
		{
			//kelime tabloda yok gelen negatif indise eklenmesi gerekiyor
			indis *= -1;
			hashTablo[indis] = new kelimeNode;
			hashTablo[indis]->kelime = kelime;
			hashTablo[indis]->adet++;
			hashTablo[indis]->satirEkle(satir);
			hashAdet++;
		}
	}
	int ara(string kelime, int indis=-1) {
		int length = (kelime.length()) % 19;
		//kelimeyi hash tablosunda ara bulursan indisini döndür yoksa indis*-1 döndür
		if (indis==-1)
		{
			indis = hashIndisHesapla(kelime);
		}
		while (hashTablo[indis] != NULL)
		{
			if (hashTablo[indis]->kelime != kelime)
			{
				indis += pow(2,length)+length;
				if (indis>hashBoyut)
				{
					indis = indis%hashBoyut;
				}			
			}
			else
			{
				break;
			}
		
		}
		if (hashTablo[indis] == NULL)
		{
			return (indis)*-1;//bulunamadý ama bu indiste olmasý gerekiyor yenisi
		}
		return indis;//bulundu

	}
	bool tamEslesme(string kelime) {
		yakincnt = 0;
		tamcnt = 0;
		//tam eslesmeleri ekrana yazdýr
		//1 tane bile bulursa true döndür bulamazsa false
		int length = (kelime.length()) % 19;
		bool stat = false;
		int indis = hashIndisHesapla(kelime);
		while (hashTablo[indis] != NULL)
		{
			tamcnt++;
			if (toUpper(hashTablo[indis]->kelime) == toUpper(kelime))
			{
				cout << dosyaAdi() << "--> " << hashTablo[indis]->kelime << " - " << "Adet: " << hashTablo[indis]->adet << ", Satirlar: [" << hashTablo[indis]->satirlariYaz() << "]" << endl;
				stat = true;
			}
			indis += pow(2, length)+length;
			if (indis>hashBoyut)
			{
				indis = indis%hashBoyut;
			}
		}		
		return stat;
	}
	bool yakinEslesme(string kelime) {
		//yakin eslesmeleri dosyaya yazdir
		//1 tane bile bulursa true döndür bulamazsa false
		bool stat = false;
		ofstream dd("benzerleri.txt", ios::app);
		for (int i = -2; i < 3; i++)
		{
			if (kelime.length()+i<=0)
			{
				continue;
			}
			int length = (kelime.length()+i) % 19;

			int indis = (int)pow(3, (kelime.length()+i)%19)%hashBoyut;//baþlangýç indisi
			while (hashTablo[indis] != NULL)
			{
				yakincnt++;
				int lev = LevenshteinMesafesi(hashTablo[indis]->kelime,kelime);

				if (lev<3 && lev>0)
				{//bulduk yakýn
					dd << dosyaAdi() << "--> " << hashTablo[indis]->kelime << ": Adet: " << hashTablo[indis]->adet << ", Satirlar: [" << hashTablo[indis]->satirlariYaz() << "]" << endl;
					stat = true;
				}
				indis += pow(2, length)+length;
				if (indis>hashBoyut)
				{
					indis = indis%hashBoyut;
				}				
			}
		}
		dd.close();
		return stat;
	}
	void yukle() {
		//txt,html,docx,pdf dosyalarýný hash tablosuna ekler
		//docx ve pdf dosyalarýný ön iþlem ile docx.txt ve pdf.txt dönüþtürüp okuma yapýyoruz
		ifstream dosya;
		if (dosyaUzanti=="docx"||dosyaUzanti=="pdf")
		{
			dosya.open("metin." + dosyaUzanti+".txt", ios::in);
		}
		else
		{
			dosya.open("metin." + dosyaUzanti, ios::in);
		}
		
		string line;
		string tmp = "";
		int sNo = 0;

		while (!dosya.eof()) {
			bool tagStat = false;
			sNo++;
			getline(dosya, line);
			line = trim2(line);
			for (int i = 0; i < line.size(); i++)
			{
				if (line.length() == 0)
				{
					continue;
				}
				//html tag belirleme
				if (line[i] == '<')
				{ 
					tagStat = true;
					tmp = trim(tmp);
					if (tmp != "" && !tagStat)
					{
						ekle(tmp, sNo);
					}
					tmp = "";
					continue;
				}
				else if (tagStat)
				{
					if (line[i] == '>')
					{
						tagStat = false;

					}
					continue;
				}//html tag belirleme sonu


				if ((line[i] != ' ')&& i<line.length() - 1)
				{
					tmp += line[i];
				}
				else
				{
					if (i == line.length() - 1)
						tmp += line[i];
					//kelimeyi elde ettik
					tmp = trim(tmp);
					if (tmp != "")
					{
						ekle(tmp, sNo);
					}

					tmp = "";
				}
			}

		}
	}
	void yazdir() {
		for (int i = 0; i < hashBoyut; i++)
		{
			cout << i << ". indis: ";
			if (hashTablo[i]!=NULL)
			{				
				cout<< hashTablo[i]->kelime <<" : "<<hashTablo[i]->adet<< " : ["<<hashTablo[i]->satirlariYaz()<<"]"<< endl;
				cout << hashTablo[i]->kelime << endl;
			}
			else
			{
				cout << "" << endl;
			}			
		}
	}
	int kelimeAdet() {
		if (hashAdet>0)
		{
			return hashAdet;
		}
		for (int i = 0; i < hashBoyut; i++)
		{
			if (hashTablo[i] != NULL)
			{
				hashAdet++;
			}
		}
		return hashAdet;


	}
	string dosyaUzantisi() {
		return dosyaUzanti;
	}

	int karakterAdet(int x) {
		//tablodaki x karakterli kelimelerin sayýsý
		int cnt = 0;
		for (int i = 0; i < hashBoyut; i++)
		{
			if (hashTablo[i]!=NULL)
			{
				if (hashTablo[i]->kelime.length()==x)
				{
					cnt++;
				}
			}
		}
		return cnt;
	}
	
};

