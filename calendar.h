
#ifndef CALENDAR_H
#define CALENDAR_H

#include "teams.h"

#include <random>
#include <chrono>
#include <string>


class Calendar : public Team
{

public:

	int numberOfMatch = 1;											// tak�m say�s�na g�re toplam ma� say�s�n� tutacak de�i�ken 

	Calendar();

	void produceMatch();											// ma� �retecek fonksiyon
	void CreateCalendar();											// takvim olu�turacak fonksiyon

	//men� fonksiyonlar�
	void ShowCalendar();											// t�m takvimi g�sterecek fonksiyon
	void ShowTeamCalendar(string team_alias);						// tek bir tak�m�n takvimini g�sterecek fonksiyon
	void ShowMatch(int match_id);									// tek bir ma�� ayr�nt�lar�yla g�steren fonksiyon

	void CalculateNumberOfMatch();									// mevcut tak�m say�s�na g�re ma� say�s�n� hesaplayan fonksiyon

private:
	int* matchID;													// t�m ma�lar�n id'lerini tutacak array i�levi g�recek pointer
	string* allmatch;												// t�m ma�lar� tutacak array i�levi g�recek pointer

};

#endif