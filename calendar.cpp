#include "calendar.h"
#include <fstream>


// constructor
// bir Calendar objesi oluþturulduðunda otomatik olarak * fonksiyonlarýný çaðýrarak maç sayýsý hesaplama, maç oluþturma, maç takvimi oluþturma gibi iþlemler yapýlýr
// *( CalculateNumberOfMatch(), produceMatch(), CreateCalendar() )

Calendar::Calendar() {

	CalculateNumberOfMatch();														// toplam maç sayýsý hesaplanýr

	matchID = new int[numberOfMatch];												// hesaplanan maç sayýsýna göre matchID için o kadar int veri tutacak yer ayrýlýr
	allmatch = new string[numberOfMatch];											// hesaplanan maç sayýsýna göre allmatch için o kadar string veri tutacak yer ayrýlýr
	
	ofstream calendarFile;															// dosya yazma modunda çalýþacak bir ofstream objesi oluþturulur

	calendarFile.open("TempCalFile.txt", ios::app);									// takvim için bir dosya açýlýr

	remove("CalendarFile.txt");														// eski oluþturulmuþ Calendar.txt dosyasý silinir

	rename("TempCalFile.txt", "CalendarFile.txt");									// yeni açýlmýþ dosyaya Calendar.txt ismi verilir

	calendarFile.close();
	

	cout << "please wait matches are being created...    ";							
	for (int i = 1; i <= 3; i++) {													// toplamda 3 saniye beklenir
		cout << i << "  ";
		this_thread::sleep_for(chrono::milliseconds(1000));							// 1 saniye (1000 milisaniye) bekleme kodu
	}
	produceMatch();																	// maçlar oluþturulur
	cout << "\nmatches created...\n\n";

	cout << "please wait calendar are being created...    ";						// bir üç saniye daha beklenir
	for (int i = 1; i <= 3; i++) {
		cout << i << "  ";
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	CreateCalendar();																// takvim oluþturulur
	cout << "\ncalendar created...\n\n";
	this_thread::sleep_for(chrono::milliseconds(2000));

}



// her takýmýn bir kez oynayacaðý þekilde kaç takým varsa ona göre maç sayýsý kadar maç üretir ve her takýma benzersiz maç id'si atar.
void Calendar::produceMatch() {

	srand(time(0));																	// rand() fonksiyonu o an ki saate göre yeni liste üretmesi için beslenir
	
	int notFound = 1;

	matchID[0] = rand() % 10000;													// ilk maç id'si atanýr
	allmatch[0] = "ga&fe";															// ilk maç gs&fb olarak atanýr

	for (int i = 1; i < numberOfMatch; i++) {										// mevcut maç sayýsý kadar 

		int id = rand() % 10000;													// random 0-10000 arasý id deðeri üretilir

		again:
		int randomTeam1 = (rand() % (Team::counter) );								// ilk takým seçimi için 0- mevcut takým sayýsý arasý bir sayý seçilir
		int randomTeam2 = (rand() % (Team::counter) );								// ikinci takým seçimi için 0- mevcut takým sayýsý arasý bir sayý daha seçilir

		string Team1 = "";
		string Team2 = "";
		string match = "";
		string sameMatch = "";

		Team1 = Team::AllTeam[randomTeam1]->team_alias;								// birinci takým için random seçilmiþ indexteki takma ad alýnýr

		Team2 = Team::AllTeam[randomTeam2]->team_alias;								// ikinci takým için random seçilmiþ indexteki takma ad alýnýr

		match = Team1 + "&" + Team2;												// takým1&takým2 formatýnda string oluþturulur
		sameMatch = Team2 + "&" + Team1;											// rövanþ olmadýðýndan takým2&takým1 de ayný maç sayýlýyor  

		//maç daha önce kayýt edilmiþ mi kontrol edilir
		for (int j = 0; j < numberOfMatch; j++) {

			if (Calendar::allmatch[j] != match || Calendar::allmatch[j] != sameMatch)  
			{
				notFound = 1;														//ayný maçý bulamadý
			}
			else 
			{
				notFound = 0;
			}			
		}

		if (notFound == 1)
		{
			Calendar::allmatch[i] = match;										//ayný maçý bulamadý ise maçý kayýt et
		}
		else
		{
			goto again;															//ayný maçý buldu ise again satýrýna gidilip yeniden maç üretilir
		}

		Calendar::matchID[i] = id;												// bir maç kayýtý sorunsuz bittikten sonra ilgili maçýn id'si de atanýr
	}
}

//bir dosyaya hazýr takvimi yazdýrýr.
void Calendar::CreateCalendar() {

	ofstream writeCalendar;

	writeCalendar.open("CalendarFile.txt", ios::app);
	writeCalendar.setf(ios::left);

	static int week = 0;
	static int index =0;

	
	if (writeCalendar.is_open())																			// dosya açýksa
	{
		writeCalendar << "     WEEK-" << setw(3) << ++week << endl;
		
		for (int i = 1; i <= numberOfMatch ;i++)															// mevcut maç sayýsýna kadar, i 1'den baþlýyor çünkü if'de 10'a bölüm kontrol edilirken division by 0 hatasý alabilirdik
		{
			if ((i % 10) == 0) {																			// bir haftada 10 maç olacaðýndan 10 ve katý maç yazdýrýldýkça yeni hafta dosyaya yazdýrýlýr
				writeCalendar << endl << "     WEEK-" << setw(3) << ++week << endl;										
			}

			writeCalendar << setw(5) << allmatch[index] << " -> " << setw(4) << matchID[index] << endl;		// sýrayla tüm maçlar ve id'leri dosyaya yazdýrýlýr
			index++;																						// maçlarý ayrý bir index deðiþkeni ile kontrol ediyoruz çünkü for içindeki i 1'den baþlýyor
		}
	}
	
	writeCalendar.close();
}

// tüm takvimi gösterir
void Calendar::ShowCalendar() {

	// Calendar.txt dosyasýndan sýrayla tüm satýrlarý alýp ekrana yazdýrýr

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

// sadece istenilen takýmýn maçlarýný ekrana yazdýrýr
// istenilen takýmýn takma adý parametre olarak verilir
void Calendar::ShowTeamCalendar(string team_alias) {

	string target_teamAlias = team_alias;
	string holdMatch;
	int holdID;
	int isFound;
	static int item = 1;																							// kaç maç olduðunu ekrana yazdýrmak için deðiþken

	for (int i = 0; i < Team::counter; i++) {																		// mevcut takým sayýsý kadar tüm takýmlarý kontrol ederek hedef takýmý arar
		if (AllTeam[i]->team_alias == target_teamAlias) {
			cout << "          ALL MATCHES OF " << AllTeam[i]->team_name << "\n\n";									// bulunca ekrana baþlýðý yazdýrýr
		}
	}

	for (int i = 0; i < numberOfMatch; i++) {																		// mevcut maç sayýsýna kadar allmatch ve matchID arraylerini tarar 
		holdMatch = allmatch[i];
		holdID = matchID[i];
		isFound = holdMatch.find(target_teamAlias);																	// maçlar arasýnda hedef takýmýn takma adýný arar
		if (isFound != string::npos)																				// buldu ise
		{
			cout << item << "- " << holdMatch << "___" << holdID << endl;											// ilgili maçýn takýmýn kaçýncý maçý olduðunu, ilgili maçý ve id'sini ekrana yazdýrýr
			item++;
		}
	}
}

// parametre olarak verilen maç id'sinin ait olduðu maçý yazdýrýr.
void Calendar::ShowMatch(int id) {

	int matchid = id;
	string chosenMatch;

	Team* team1 = new Team();													// verilerine ulaþmak için Team class'ýna ait iki boþ constructor'lý araç objesi
	Team* team2 = new Team();

	for (int i = 0; i < numberOfMatch; i++) {									// tüm maç id'leri taranýr ve ilgili maç ID'si aranýr

		if (matchID[i] == matchid) {

			chosenMatch = allmatch[i];											// bulundu ise o indexteki maç alýnýr
			goto matchFound;													// ve matchFound satýrýna gidilir
		}
	}
matchFound:

	int pos = chosenMatch.find("&");											// yukarýda aldýðýmýz maçýn içinde & karakteri aranýr
	string firstTeam = chosenMatch.substr(0, pos);								// bulunca ilk kýsmý birinci takýma takma ad olarak
	string secondTeam = chosenMatch.substr(pos + 1);							// &'dan sonraki kýsmý ikinci takýma takma ad olarak atanýr

	// iki takým için de elimizdeki takma adlar ile mevcut takýmlarýn takma adlarý arasýnda arama yapýlýr bulunca oluþturulmuþ Team objelerine bulunan takýmlar atanýr
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

	// iki takýmýnda kazanma yüzdesi tek tek hesaplanýr
	float sum = (team1->perform_ave) + (team2->perform_ave);
	team1winPercentage = ( (team1->perform_ave) * 100) / sum;
	team2winPercentage = ( (team2->perform_ave )* 100) / sum;

	cout << endl << endl;

	// sýrayla takýmlarýn takma adlarý, takým adlarý, teknik direktörleri, performans ortalamalarý, kazanma yüzdeleri ve takýmlarýn tüm oyuncularý pozisyon bilgileri ve isimleri ile birlikte ekrana yazdýrýlýr
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

// mevcut maç takým sayýsýna göre toplam maç sayýsýný (ToplamTakýmSayýsý)*(ToplamTakýmSayýsý-1)/2 formülüne göre hesaplar
void Calendar::CalculateNumberOfMatch() {

	int NumberOfTeam = Team::counter;

	numberOfMatch = ( (NumberOfTeam) * (NumberOfTeam - 1)) / 2;

}
