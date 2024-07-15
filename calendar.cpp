#include "calendar.h"
#include <fstream>


// constructor
// bir Calendar objesi olu�turuldu�unda otomatik olarak * fonksiyonlar�n� �a��rarak ma� say�s� hesaplama, ma� olu�turma, ma� takvimi olu�turma gibi i�lemler yap�l�r
// *( CalculateNumberOfMatch(), produceMatch(), CreateCalendar() )

Calendar::Calendar() {

	CalculateNumberOfMatch();														// toplam ma� say�s� hesaplan�r

	matchID = new int[numberOfMatch];												// hesaplanan ma� say�s�na g�re matchID i�in o kadar int veri tutacak yer ayr�l�r
	allmatch = new string[numberOfMatch];											// hesaplanan ma� say�s�na g�re allmatch i�in o kadar string veri tutacak yer ayr�l�r
	
	ofstream calendarFile;															// dosya yazma modunda �al��acak bir ofstream objesi olu�turulur

	calendarFile.open("TempCalFile.txt", ios::app);									// takvim i�in bir dosya a��l�r

	remove("CalendarFile.txt");														// eski olu�turulmu� Calendar.txt dosyas� silinir

	rename("TempCalFile.txt", "CalendarFile.txt");									// yeni a��lm�� dosyaya Calendar.txt ismi verilir

	calendarFile.close();
	

	cout << "please wait matches are being created...    ";							
	for (int i = 1; i <= 3; i++) {													// toplamda 3 saniye beklenir
		cout << i << "  ";
		this_thread::sleep_for(chrono::milliseconds(1000));							// 1 saniye (1000 milisaniye) bekleme kodu
	}
	produceMatch();																	// ma�lar olu�turulur
	cout << "\nmatches created...\n\n";

	cout << "please wait calendar are being created...    ";						// bir �� saniye daha beklenir
	for (int i = 1; i <= 3; i++) {
		cout << i << "  ";
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	CreateCalendar();																// takvim olu�turulur
	cout << "\ncalendar created...\n\n";
	this_thread::sleep_for(chrono::milliseconds(2000));

}



// her tak�m�n bir kez oynayaca�� �ekilde ka� tak�m varsa ona g�re ma� say�s� kadar ma� �retir ve her tak�ma benzersiz ma� id'si atar.
void Calendar::produceMatch() {

	srand(time(0));																	// rand() fonksiyonu o an ki saate g�re yeni liste �retmesi i�in beslenir
	
	int notFound = 1;

	matchID[0] = rand() % 10000;													// ilk ma� id'si atan�r
	allmatch[0] = "ga&fe";															// ilk ma� gs&fb olarak atan�r

	for (int i = 1; i < numberOfMatch; i++) {										// mevcut ma� say�s� kadar 

		int id = rand() % 10000;													// random 0-10000 aras� id de�eri �retilir

		again:
		int randomTeam1 = (rand() % (Team::counter) );								// ilk tak�m se�imi i�in 0- mevcut tak�m say�s� aras� bir say� se�ilir
		int randomTeam2 = (rand() % (Team::counter) );								// ikinci tak�m se�imi i�in 0- mevcut tak�m say�s� aras� bir say� daha se�ilir

		string Team1 = "";
		string Team2 = "";
		string match = "";
		string sameMatch = "";

		Team1 = Team::AllTeam[randomTeam1]->team_alias;								// birinci tak�m i�in random se�ilmi� indexteki takma ad al�n�r

		Team2 = Team::AllTeam[randomTeam2]->team_alias;								// ikinci tak�m i�in random se�ilmi� indexteki takma ad al�n�r

		match = Team1 + "&" + Team2;												// tak�m1&tak�m2 format�nda string olu�turulur
		sameMatch = Team2 + "&" + Team1;											// r�van� olmad���ndan tak�m2&tak�m1 de ayn� ma� say�l�yor  

		//ma� daha �nce kay�t edilmi� mi kontrol edilir
		for (int j = 0; j < numberOfMatch; j++) {

			if (Calendar::allmatch[j] != match || Calendar::allmatch[j] != sameMatch)  
			{
				notFound = 1;														//ayn� ma�� bulamad�
			}
			else 
			{
				notFound = 0;
			}			
		}

		if (notFound == 1)
		{
			Calendar::allmatch[i] = match;										//ayn� ma�� bulamad� ise ma�� kay�t et
		}
		else
		{
			goto again;															//ayn� ma�� buldu ise again sat�r�na gidilip yeniden ma� �retilir
		}

		Calendar::matchID[i] = id;												// bir ma� kay�t� sorunsuz bittikten sonra ilgili ma��n id'si de atan�r
	}
}

//bir dosyaya haz�r takvimi yazd�r�r.
void Calendar::CreateCalendar() {

	ofstream writeCalendar;

	writeCalendar.open("CalendarFile.txt", ios::app);
	writeCalendar.setf(ios::left);

	static int week = 0;
	static int index =0;

	
	if (writeCalendar.is_open())																			// dosya a��ksa
	{
		writeCalendar << "     WEEK-" << setw(3) << ++week << endl;
		
		for (int i = 1; i <= numberOfMatch ;i++)															// mevcut ma� say�s�na kadar, i 1'den ba�l�yor ��nk� if'de 10'a b�l�m kontrol edilirken division by 0 hatas� alabilirdik
		{
			if ((i % 10) == 0) {																			// bir haftada 10 ma� olaca��ndan 10 ve kat� ma� yazd�r�ld�k�a yeni hafta dosyaya yazd�r�l�r
				writeCalendar << endl << "     WEEK-" << setw(3) << ++week << endl;										
			}

			writeCalendar << setw(5) << allmatch[index] << " -> " << setw(4) << matchID[index] << endl;		// s�rayla t�m ma�lar ve id'leri dosyaya yazd�r�l�r
			index++;																						// ma�lar� ayr� bir index de�i�keni ile kontrol ediyoruz ��nk� for i�indeki i 1'den ba�l�yor
		}
	}
	
	writeCalendar.close();
}

// t�m takvimi g�sterir
void Calendar::ShowCalendar() {

	// Calendar.txt dosyas�ndan s�rayla t�m sat�rlar� al�p ekrana yazd�r�r

	ifstream readCalendar;

	readCalendar.open("CalendarFile.txt", ios::app);
	string line;

	cout << "\n\n";

	if (readCalendar.is_open()) {
		while (!( readCalendar.eof() )) {
			getline(readCalendar, line);
			cout << line << endl;	
		}
	}
	cout << "\n\n";
	readCalendar.close();
}

// sadece istenilen tak�m�n ma�lar�n� ekrana yazd�r�r
// istenilen tak�m�n takma ad� parametre olarak verilir
void Calendar::ShowTeamCalendar(string team_alias) {

	string target_teamAlias = team_alias;
	string holdMatch;
	int holdID;
	int isFound;
	static int item = 1;																							// ka� ma� oldu�unu ekrana yazd�rmak i�in de�i�ken

	for (int i = 0; i < Team::counter; i++) {																		// mevcut tak�m say�s� kadar t�m tak�mlar� kontrol ederek hedef tak�m� arar
		if (AllTeam[i]->team_alias == target_teamAlias) {
			cout << "          ALL MATCHES OF " << AllTeam[i]->team_name << "\n\n";									// bulunca ekrana ba�l��� yazd�r�r
		}
	}

	for (int i = 0; i < numberOfMatch; i++) {																		// mevcut ma� say�s�na kadar allmatch ve matchID arraylerini tarar 
		holdMatch = allmatch[i];
		holdID = matchID[i];
		isFound = holdMatch.find(target_teamAlias);																	// ma�lar aras�nda hedef tak�m�n takma ad�n� arar
		if (isFound != string::npos)																				// buldu ise
		{
			cout << item << "- " << holdMatch << "___" << holdID << endl;											// ilgili ma��n tak�m�n ka��nc� ma�� oldu�unu, ilgili ma�� ve id'sini ekrana yazd�r�r
			item++;
		}
	}
}

// parametre olarak verilen ma� id'sinin ait oldu�u ma�� yazd�r�r.
void Calendar::ShowMatch(int id) {

	int matchid = id;
	string chosenMatch;

	Team* team1 = new Team();													// verilerine ula�mak i�in Team class'�na ait iki bo� constructor'l� ara� objesi
	Team* team2 = new Team();

	for (int i = 0; i < numberOfMatch; i++) {									// t�m ma� id'leri taran�r ve ilgili ma� ID'si aran�r

		if (matchID[i] == matchid) {

			chosenMatch = allmatch[i];											// bulundu ise o indexteki ma� al�n�r
			goto matchFound;													// ve matchFound sat�r�na gidilir
		}
	}
matchFound:

	int pos = chosenMatch.find("&");											// yukar�da ald���m�z ma��n i�inde & karakteri aran�r
	string firstTeam = chosenMatch.substr(0, pos);								// bulunca ilk k�sm� birinci tak�ma takma ad olarak
	string secondTeam = chosenMatch.substr(pos + 1);							// &'dan sonraki k�sm� ikinci tak�ma takma ad olarak atan�r

	// iki tak�m i�in de elimizdeki takma adlar ile mevcut tak�mlar�n takma adlar� aras�nda arama yap�l�r bulunca olu�turulmu� Team objelerine bulunan tak�mlar atan�r
	for (int i = 0; i < Team::counter; i++) {
		if ((AllTeam[i]->team_alias) == firstTeam) {
			team1 = AllTeam[i];
		}
	}
	for (int i = 0; i < Team::counter; i++) {
		if ((AllTeam[i]->team_alias) == secondTeam) {
			team2 = AllTeam[i];
		}
	}

	float team1winPercentage;
	float team2winPercentage;

	// iki tak�m�nda kazanma y�zdesi tek tek hesaplan�r
	float sum = (team1->perform_ave) + (team2->perform_ave);
	team1winPercentage = ( (team1->perform_ave) * 100) / sum;
	team2winPercentage = ( (team2->perform_ave )* 100) / sum;

	cout << endl << endl;

	// s�rayla tak�mlar�n takma adlar�, tak�m adlar�, teknik direkt�rleri, performans ortalamalar�, kazanma y�zdeleri ve tak�mlar�n t�m oyuncular� pozisyon bilgileri ve isimleri ile birlikte ekrana yazd�r�l�r
	cout << "                " << setw(3) << team1->team_alias << "                " << " |" << "                 " << team2->team_alias << endl;
	cout << "         " << setw(16) << team1->team_name << "          " << " |" << "         " << setw(16) << team2->team_name << endl;
	cout << "        " << setw(18) << team1->coach_name << "         " << " |" << "        " << setw(18) << team2->coach_name << endl;
	cout << "            " << setw(6) << "TPA: " << team1->perform_ave << "          " << "    |" << "           " << setw(6) << "TPA: " << team2->perform_ave << endl;
	cout << "                                    " << "|" << endl;
	cout << "            " << setw(11) << "win per: %" << team1winPercentage << "     " << "      |" << "            " << setw(11) << "win per: %" << team2winPercentage << endl;
	cout << "                                    " << "|" << endl;

	for (int i = 0; i < 11; i++) {

		cout << " " << setw(8) << team1->formasyon[i] << " " << setw(25) << team1->name[i] << " " << "| " << setw(8) << team2->formasyon[i] << " " << setw(25) << team2->name[i] << endl;
	}

}

// mevcut ma� tak�m say�s�na g�re toplam ma� say�s�n� (ToplamTak�mSay�s�)*(ToplamTak�mSay�s�-1)/2 form�l�ne g�re hesaplar
void Calendar::CalculateNumberOfMatch() {

	int NumberOfTeam = Team::counter;

	numberOfMatch = ( (NumberOfTeam) * (NumberOfTeam - 1)) / 2;

}
