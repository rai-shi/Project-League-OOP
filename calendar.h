
#ifndef CALENDAR_H
#define CALENDAR_H

#include "teams.h"

#include <random>
#include <chrono>
#include <string>


class Calendar : public Team
{

public:

	int numberOfMatch = 1;											// takým sayýsýna göre toplam maç sayýsýný tutacak deðiþken 

	Calendar();

	void produceMatch();											// maç üretecek fonksiyon
	void CreateCalendar();											// takvim oluþturacak fonksiyon

	//menü fonksiyonlarý
	void ShowCalendar();											// tüm takvimi gösterecek fonksiyon
	void ShowTeamCalendar(string team_alias);						// tek bir takýmýn takvimini gösterecek fonksiyon
	void ShowMatch(int match_id);									// tek bir maçý ayrýntýlarýyla gösteren fonksiyon

	void CalculateNumberOfMatch();									// mevcut takým sayýsýna göre maç sayýsýný hesaplayan fonksiyon

private:
	int* matchID;													// tüm maçlarýn id'lerini tutacak array iþlevi görecek pointer
	string* allmatch;												// tüm maçlarý tutacak array iþlevi görecek pointer

};

#endif