
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

	int     age[11];                                               // tak�m objesinin t�m oyuncular�n�n ya�lar�n� tutar

	int     formationinfo;                                         // kullan�c�dan al�nacak formasyon bilgisini tutacak

	ifstream isim_dosya;                                           // isimlerin oldu�u dosya i�in ifstream objesi, okuma modunda
	ifstream soyad_dosya;                                          // soyadlar�n oldu�u dosya i�in ifstream objesi, okuma modunda
	ofstream tak�m_dosya;                                          // bir tak�m objesi olu�turulduktan sonra t�m bilgilerinin tutuldu�u dosya i�in ofstream objesi, yazma modunda �al��an bir objedir

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

	string  name[11];                                                      // tak�m objesinin t�m oyuncular�n�n isimlerini tutar
	string  formasyon[11];                                                 // tak�m objesinin t�m oyuncular�n�n pozisyon bilgilerini tutar
	int     jersey[11];                                                    // tak�m objesinin t�m oyuncular�n�n forma numaralar�n� tutar
	int     perform[11];                                                   // tak�m objesinin t�m oyuncular�n�n performans de�erlerini tutar

	string  team_alias;                                                    // tak�m objesinin takma ismini tutacak de�i�ken 
	string  team_name;                                                     // tak�m objesinin  tak�m ad�n� tutacak de�i�ken 
	string  coach_name;                                                    // tak�m objesinin teknik direkt�r ad�n� tutacak de�i�ken 

	int forvet_ave;                                                        // tak�m objesinin genel forvet ortalamas�n� tutar
	int defans_ave;                                                        // tak�m objesinin genel defans ortalamas�n� tutar
	int ortasaha_ave;                                                      // tak�m objesinin genel ortasaha ortalamas�n� tutar

	float   perform_ave;                                                   // tak�m objesinin genel performans ortalamas�
	float   age_ave;                                                       // tak�m objesinin genel ya� ortalamas�

	int static counter;                                                    //toplam obje say�s�n� tutacak de�i�ken, static tan�ml�, objeye de�il class'�n genel �zelli�i olsu diye static tan�mml�
	static Team** AllTeam;                                                 // tak�m objelerini g�sterecek pointer-to-pointer, static tan�mland� ki class'�n genel �zelli�i olsun


	Team();                                                                // arac� tak�m objeleri i�in bo� constructor
	Team(string tak�m_ad�, string tek_dir_ad�, int formasyon=442);         // as�l constructor 													

	void creat_team();												       // tak�m objesinin �zelliklerini atayacak ve ayr�nt�l� dosyaya yazd�racak fonksiyon
	
	int produce_age(int );												   // her oyuncuya random ya� atamas� yapar 18-36 ya� aras� genel ya� ortalamas� 25 olacak �ekilde random ya� atamas� yapar
	float age_average();												   // tak�m�n genel ya� ortalamas�n� hesaplar
	
	int produce_performance(int );										   // her oyuncuya random performans atamas� yapar
	float performance_average();										   // tak�m�n genel ya� ortalamas�n� hesaplar

	int produce_jersey_number();										   // her oyuncuya random forma numaras� atamas� yapar
	
	void assign_formation();											   // tak�ma formasyon bilgisinin atamas�n� yapar

	void calculatePosisionAve();										   // tak�m objesinin posizyonlar�n�n �zel olarak performans ortalamas�n� hesaplar

	void static TeamLinkedList(Team* team);								   // tak�m objelerini AllTeam array'ine atar

	void show_team(string takma_ad);									   // tek bir tak�m bilgilerini g�sterecek fonksiyon

};

#endif