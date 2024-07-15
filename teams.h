
#ifndef TEAMS_H
#define TEAMS_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include <thread>

using namespace std;

class Team
{
private:

	int     age[11];                                               // takým objesinin tüm oyuncularýnýn yaþlarýný tutar

	int     formationinfo;                                         // kullanýcýdan alýnacak formasyon bilgisini tutacak

	ifstream isim_dosya;                                           // isimlerin olduðu dosya için ifstream objesi, okuma modunda
	ifstream soyad_dosya;                                          // soyadlarýn olduðu dosya için ifstream objesi, okuma modunda
	ofstream takým_dosya;                                          // bir takým objesi oluþturulduktan sonra tüm bilgilerinin tutulduðu dosya için ofstream objesi, yazma modunda çalýþan bir objedir

	string  taktik442[11] = {
							"forvet","forvet",
							"ortasaha","ortasaha",
							"ortasaha","ortasaha",
							"defans", "defans",
							"defans", "defans",
							 "kaleci"
	};
	string  taktik433[11] = {
							"forvet",
							"forvet","forvet",
							"ortasaha","ortasaha",
							"ortasaha",
							"defans", "defans",
							"defans", "defans",
							 "kaleci"
	};
	string  taktik343[11] = {
							"forvet",
							"forvet","forvet",
							"ortasaha","ortasaha",
							"ortasaha","ortasaha",
							"defans","defans",
							"defans",
							 "kaleci"
	};
	string  taktik352[11] = {
							"forvet","forvet",
							"ortasaha","ortasaha","ortasaha",
							"ortasaha","ortasaha",
							"defans", "defans",
							"defans",
							"kaleci"
	};


public:

	string  name[11];                                                      // takým objesinin tüm oyuncularýnýn isimlerini tutar
	string  formasyon[11];                                                 // takým objesinin tüm oyuncularýnýn pozisyon bilgilerini tutar
	int     jersey[11];                                                    // takým objesinin tüm oyuncularýnýn forma numaralarýný tutar
	int     perform[11];                                                   // takým objesinin tüm oyuncularýnýn performans deðerlerini tutar

	string  team_alias;                                                    // takým objesinin takma ismini tutacak deðiþken 
	string  team_name;                                                     // takým objesinin  takým adýný tutacak deðiþken 
	string  coach_name;                                                    // takým objesinin teknik direktör adýný tutacak deðiþken 

	int forvet_ave;                                                        // takým objesinin genel forvet ortalamasýný tutar
	int defans_ave;                                                        // takým objesinin genel defans ortalamasýný tutar
	int ortasaha_ave;                                                      // takým objesinin genel ortasaha ortalamasýný tutar

	float   perform_ave;                                                   // takým objesinin genel performans ortalamasý
	float   age_ave;                                                       // takým objesinin genel yaþ ortalamasý

	int static counter;                                                    //toplam obje sayýsýný tutacak deðiþken, static tanýmlý, objeye deðil class'ýn genel özelliði olsu diye static tanýmmlý
	static Team** AllTeam;                                                 // takým objelerini gösterecek pointer-to-pointer, static tanýmlandý ki class'ýn genel özelliði olsun


	Team();                                                                // aracý takým objeleri için boþ constructor
	Team(string takým_adý, string tek_dir_adý, int formasyon=442);         // asýl constructor 													

	void creat_team();												       // takým objesinin özelliklerini atayacak ve ayrýntýlý dosyaya yazdýracak fonksiyon
	
	int produce_age(int );												   // her oyuncuya random yaþ atamasý yapar 18-36 yaþ arasý genel yaþ ortalamasý 25 olacak þekilde random yaþ atamasý yapar
	float age_average();												   // takýmýn genel yaþ ortalamasýný hesaplar
	
	int produce_performance(int );										   // her oyuncuya random performans atamasý yapar
	float performance_average();										   // takýmýn genel yaþ ortalamasýný hesaplar

	int produce_jersey_number();										   // her oyuncuya random forma numarasý atamasý yapar
	
	void assign_formation();											   // takýma formasyon bilgisinin atamasýný yapar

	void calculatePosisionAve();										   // takým objesinin posizyonlarýnýn özel olarak performans ortalamasýný hesaplar

	void static TeamLinkedList(Team* team);								   // takým objelerini AllTeam array'ine atar

	void show_team(string takma_ad);									   // tek bir takým bilgilerini gösterecek fonksiyon

};

#endif