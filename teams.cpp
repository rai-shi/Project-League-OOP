#include "teams.h"
//#include "storage.h"

Team** Team::AllTeam = new Team*[20];										// tak�m objelerini tutacak static AllTeam pointer-to-pointer i�in 20 Team pointer� tutacak yer ayr�ld�
int Team::counter = 0;														

// ara� olarak kullan�lacak Team objelerinin ba�lat�lmas� i�in bo� constructor
Team::Team() {


}

// parametreli counstructor
// tak�m bilgilerini al�r, gerekli atamalar� yapar.
// team.txt dosyas�na tak�m� ekler.
// tak�m objesinin di�er detay �zelliklerinin atamas� i�in creat_team() fonksiyonunu �a��r�r
Team::Team(string team_name, string coach_name, int formationinfo) {

	ifstream read;															// teams.txt dosyas�n� okumak i�in ifstream objesi
	ofstream write;															// teams.txt dosyas�na yazmak i�in ofstream objesi

	read.open("teams.txt", ios::app);										// dosya i�ieri�i sondan eklemeli olarak okuma modunda a��ld�
	write.open("teams.txt", ios::app);									    // dosya i�ieri�i sondan eklemeli olarak yazma modunda a��ld�
	write.setf(ios::left);													// dosyaya yazarken soldan hizal� bir �ekilde yaz�lacak


	this->team_name = team_name;
	this->coach_name = coach_name;
	this->team_alias = (team_name.substr(0,2));								// objenin team_alias �zelli�ine girilen tak�m ad�n�n ilk iki karakteri atand�
	this->formationinfo = formationinfo;


	string line;
	size_t isFound{};

	if (read.is_open()){													// e�er dosya a��ksa
		
		while (!(read.eof())) {												// dosyan�n sonunda de�ilsen
			
			getline(read, line);											// dosyadan bir sat�r oku
		    
			isFound = (line.find(team_alias));								// sat�r i�erisinde team_alias� ara, bulursan isFound'a sat�rda buldu�un konumu d�nd�r
			
			if (isFound != string::npos) {									// e�er isFound npos de�ilse yani aranan string 
				isFound = 1;												// bulundu ise 1
				goto Found;													// Found kod sat�r�na git
			}
			else {
				isFound = 0;												//bulamad� ise 0
			}
		}
		Found:
	    if (isFound)  {														// isFound=1 durumunda genel bilgiler teams.txt dosyas�na yaz�l�r
			team_alias = this->team_name.substr(0, 3);						// ayn� team_alias bulundu�undan bu sefer team_alias olarak team_name'in ilk �� karakteri kullan�l�r
			write <<setw(20)<< team_alias
				 << setw(20) << this->team_name
				 << setw(20) << this->coach_name << endl;
		}
		else {
			write <<setw(20)<< team_alias									// isFound=0 durumunda genel bilgiler oldu�u gibi teams.txt dosyas�na yaz�l�r
				<< setw(20) << this->team_name
				<< setw(20) << this->coach_name
				<< endl;
		}
	}

	for (int i = 0; i < 11; i++) {											// tak�m olu�turma fonksiyonu �a�r�lmadan �nce �zellikler s�f�rlan�r
		age[i] = 0;
		jersey[i] = 0;
		perform[i] = 0;
		name[i] = "";
	}

	creat_team();

	read.close();
	write.close();
}

// tak�m_olu�tur() tak�mlar�n t�m bilgilerini olu�turulmu�tak�mlar.txt i�erisine yazar.
// fonksiyon i�erisinde, tak�mlara oyuuncu se�er.
// oyuncular�n �zelliklerini de ayr� fonksiyonlar ile belirler
// i�erisinde checking_age_average(), checking_jersey_number(), performance_average(), formation_function() fonksiyonlar�n� �al��t�r�r.
void Team::creat_team() {

	tak�m_dosya.open("olusturulmustakimlar.txt", ios::app);					// dosya yazma ve sondan eklemeli modda a��l�yor
	
	tak�m_dosya.setf(ios::left);											// dosyaya yaz�m sola hizal� olacak �ekilde olacak

	srand(time(0));															// rand() fonksiyonuna o an ki saate g�re ba�lang�� de�eri atan�yor

	for (int i = 0; i < 11; i++) {											// her 11 oyuncu i�in 11'lik for d�ng�s�

		isim_dosya.open("ad.txt");
		soyad_dosya.open("soyad.txt");

		int random = 0;

		string name_line;
		string sname_line;


		//isim soyad se�imi
		random = rand() % 532;												// 532 isim oldu�undan rand 0-532 aras� random bir say� d�nd�recek
		for (int x = 0; x <= random; x++)									
		{																	// random say�ya kadar isim ve soyad soyas�ndan sat�rlar tek tek �ekilecek
			getline(isim_dosya, name_line);
			getline(soyad_dosya, sname_line);

			if (x == random) {												// x de�eri random yani hedef sat�ra ula�t���nda o sat�rdaki isim ve soyisimi name array'inin i. indexine atayacak
				name[i] = name_line + " " + sname_line;
			}
		}

		perform[i] = produce_performance(i);								// her 11 oyuncuya performans de�eri atanmas�

		age[i] = produce_age(i);												// her 11 oyuncuya ya� de�eri atanmas�

		jersey[i] = produce_jersey_number();								// her 11 oyuncuya forma numaras� atanmas�

		isim_dosya.close();
		soyad_dosya.close();
	}

	perform_ave = performance_average();									// performans ortalamas� hesaplan�r, geri d�nd�r�len de�er objenin perform_ave �zelli�ine atan�r
	
	age_ave = age_average();												// ya� ortalamas� hesaplan�r, geri d�nd�r�len de�er objenin age_ave �zelli�ine atan�r							
	
	assign_formation();														// verilen formasyon bilgisi inputuna g�re formasyon bilgisi atan�r


	tak�m_dosya << "tak�m: " << team_alias << "-" << team_name << endl;		// detayl� bilgilerin oldu�u olusturulmustakimlar.txt dosyas�na t�m atanm�� de�erler yazd�r�l�r
	for (int i = 0; i < 11; i++) {
		tak�m_dosya 
			<<setw(25) << name[i]
			<<setw(10) <<formasyon[i]
			<< setw(10) << age[i]
			<< setw(11) << perform[i]
			<< setw(10) << jersey[i]
			<< endl;
	}

	tak�m_dosya << endl;
	tak�m_dosya.close();
}


// bir tak�m�n her oyuncusuna 30-100 aras� performans de�eri �retir. 
// toplam tak�m performans�n�n 60'dan y�ksek olmas�na dikkat eder.
// parametresi creat_team fonksiyonu ka��nc� oyuncuda ise onu belirtir ki ortalama i�in o say�ya b�lebilsin

int Team::produce_performance(int num) {

	int currentPlayerIndex = num;
	int tempPerform;
    int sum = 0;
	int average = 0;


	tempPerform = (rand() % 71) + 30;										// 30-100 aras� random performans de�eri �retilir
	perform[currentPlayerIndex] = tempPerform;								// perform array'indeki creat_team fonksiyonu ka��nc� oyuncuda ise onun indexine ge�ici performans de�eri atan�r

	for (int i = 0; i < 11; i++) {											// perform arrayindeki t�m performans de�erleri toplan�r

		sum = sum + perform[i];
	}	

	average = sum / (currentPlayerIndex + 1);								// toplam performans, creat_team ka��nc� oyuncuda ise ona b�l�n�r

	if (average >= 60) {													// ortalaman�n 60'dan b�y�kl��� kontrol edilir
		return tempPerform;													// e�er 60'dan b�y�kse ba�taki ge�ici performans de�eri geri d�nd�r�l�r
	}
	else {
		produce_performance(currentPlayerIndex);							// 60'dan k���k ise fonksiyon yeni bir performans de�eri �retmesi i�in tekrar �a�r�l�r
	}
}


// tak�m performans ortalamas�n� hesaplar.

float Team::performance_average() {

	float sum = 0;

	for (int i = 0; i < 11; i++) {
		sum = sum + perform[i];
	}

	float perform_ave = sum / 11;

	return perform_ave;
}


// bir futbolcu ya��n� 18-36 aras� ve t�m tak�m�n ya� ortalamas�n� da 25-32 ya� aras� tutarak oyunculara ya� atamas� yapar

int Team::produce_age(int num) {

	int currentPlayerIndex = num;
	int tempAge;
	int sum = 0;
	int average = 0;
	
	tempAge = (rand() % 19) + 18;											// ya� i�in 18-36 aras� random say� �retilir
	age[currentPlayerIndex] = tempAge;										// o an ki oyuncuya bu de�er atan�r

	for (int i = 0; i < 11; i++) {

		sum = sum + age[i];
	}

	average = sum / (currentPlayerIndex +1);								// ya� ortalamas� hesaplan�r

	if (25 <= average && average <= 32) {									// ya� ortalamas�n�n 25-32 aras�nda oldu�u kontrol edilir
		return tempAge;														// �ylseyse �retilmi� ya� geri d�nd�r�l�r
	}
	else {
		produce_age(currentPlayerIndex);									// de�ilse fonksiyon tekrar �a�r�l�r
	}	
}

//bir tak�m�n ya� ortlamas�n� hesaplar
float Team::age_average() {

	float sum = 0;

	for (int i = 0; i < 11; i++) {
		sum = sum + age[i];
	}

	float age_ave = sum / 11;

	return age_ave;
}

//bir tak�m i�erisinde hi�bir oyuncunun forma numaras� ayn� gelmeyecek �ekilde her oyuncuya �zel forma numaras� atamas� yap�l�r
int Team::produce_jersey_number() {

	int tempJNumber = (rand() % 99) + 1;									// tempJNumber'a 1-100 aras� random say� atan�r

	int isMatch = 1;														// ayn� forma numaras�n�n e�le�me durumu �u an 1

	for (int i = 0; i < 11; i++) {											// tak�m�n o an ki oyuncusuna kadar forma numaralar� kontrol edilecek

		if (tempJNumber != jersey[i]) {										
			isMatch = 0;													// uyu�ma yoksa yani ayn� forma numaras�ndan bulunamad� ise e�le�me durumu, isMatch 0 olarak atanacak
		}
	}
	if (isMatch == 0) {														// isMatch 0 ise
		return tempJNumber;													// �retilmi� forma numaras�n� geri d�nd�r
	}
	else {
		produce_jersey_number();											// isMatch hala bir ise ayn� forma numaras�ndan var demektir fonksiyon yeniden �a�r�l�r
	}
}


//se�ilen formasyon bilgisine g�re oyuncular�n pozisyonlar�n� belirler.
void Team::assign_formation()
{
	switch (formationinfo)													// constructor da atanm�� formasyon bilgisine g�re tak�mlar�n oyuncular�na pozisyon bilgileri atan�r
	{
	case 443:
		for (int i = 0; i < 11; i++) {
			formasyon[i] = taktik433[i];
		}
		break;
	case 343:
		for (int i = 0; i < 11; i++) {
			formasyon[i] = taktik343[i];
		}
		break;
	case 352:
		for (int i = 0; i < 11; i++) {
			formasyon[i] = taktik352[i];
		}
		break;
	default:
		for (int i = 0; i < 11; i++) {
			formasyon[i] = taktik442[i];
		}
		break;
	}
    calculatePosisionAve();													// oyuncular�n pozisyon bilgileri atand�ktan sonra tak�m�n pozisyon performans ortalamas� hesaplan�r

}

// tak�m objesinin formasyon bilgisine g�re pozisyon performans ortalamas�n� hesaplar
void Team::calculatePosisionAve() {

	int sumForvet =0;
	int sumDefans = 0;
	int sumOrtasaha = 0;

	int aveForvet = 0;
	int aveDefans = 0;
	int aveOrtasaha = 0;

	string position;

	for (int i = 0; i < 11; i++)											// 11 oyuncunun forvet, ortasaha ya da defans oyuncusu olmas�na g�re toplam forvet, ortasaha, defans performans de�erleri hesaplan�r
	{
		position = formasyon[i];

		if (position == "forvet") {
			sumForvet = sumForvet + perform[i];
		}
		if (position == "defans") {
			sumDefans = sumDefans + perform[i];
		}
		if (position == "ortasaha") {
			sumOrtasaha = sumOrtasaha + perform[i];
		}
	}

	// tak�m�n performans bilgisine g�re pozisyon ortalamalar� hesaplan�r
	switch (formationinfo) 
	{
	case 442:
		aveDefans = sumDefans / 4;
		aveOrtasaha = sumOrtasaha / 4;
		aveForvet = sumForvet / 2;
		break;

	case 433:
		aveDefans = sumDefans / 4;
		aveOrtasaha = sumOrtasaha / 3;
		aveForvet = sumForvet / 3;
		break;

	case 343:
		aveDefans = sumDefans / 3;
		aveOrtasaha = sumOrtasaha / 4;
		aveForvet = sumForvet / 3;
		break;

	case 352:
		aveDefans = sumDefans / 2;
		aveOrtasaha = sumOrtasaha / 5;
		aveForvet = sumForvet / 3;
		break;

	}
	
	// hesaplanan pozisyon ortalama de�erleri atan�r
	forvet_ave = aveForvet;
	defans_ave = aveDefans;
	ortasaha_ave = aveOrtasaha;
}

// se�ilen tak�m�n detayl� bilgilerini g�sterir
// bilgilerinin g�sterilmesi istenen tak�m�n takma ad� parametre olarak fonksiyona verilir
void Team::show_team(string takma_ad) {


	ifstream readteam;														// tak�m�n genel bilgilerini okumak i�in ifstream objesi
	ifstream readinfo;														// tak�m�n detayl� bilgilerini okumak i�in ifstream objesi
	
	int counter = 0;

	readteam.open("teams.txt", ios::app);
	readinfo.open("olusturulmustakimlar.txt", ios::app);

	string target = takma_ad;												// hedef tak�m
	string line;
	size_t isFound{};
	
	cout << endl << "takim: " << endl;

	// tak�m�n isim- takma ad- teknik direkt�r ad� gibi genel bilgilerini almak i�in 

	if (readteam.is_open()) {												// teams.txt a��k ise

		while (!(readteam.eof())) {											// teams.txt dosyas�n�n sonunda de�ilsen

			getline(readteam, line);										// sat�r �ek
			counter++;														// counter� bir artt�r, b�ylece olu�turulmu� ka��nc� tak�m oldu�unun bilgisini ��renebiliyoruz

			isFound = (line.find(target));									// �ekilmi� her sat�rda fonksiyona verilmi� team_alias aran�r
			
			if (isFound != string::npos) {									// tak�m bulundu ise isFound'a bir atan�r ve founded sat�r�na gidilir
				isFound = 1;
				goto found;
			}
			else {
				isFound = 0;
			}
		}
		found:
		if (isFound == 1) {													// isFound 1 ise
			
			cout << line;													// �ekilmi� sat�r ekrana yazd�r�l�r

			// setprecision() yazd�r�lacak float verinin ka� basama��n�n ekrana verilece�ini belirler
			// AllTeam pointer-to-pointer array'indeki (counter-1). indexteki tak�m objesinin ya� ve performans verileri ekrana yazd�r�l�r
			// (counter-1). index ��nk� ilk sat�r �ekildi�inde counter 1 de�erini al�yor fakat tak�m 0. indexte bulunuyor
			cout <<"\n\nteam age ave: " << setw(2) << std::setprecision(3) << Team::AllTeam[counter - 1]->age_ave << "\n"               
				<< "team perform ave: " << setw(2) << std::setprecision(3) << Team::AllTeam[counter-1]->perform_ave <<endl << endl;
		}
		else {
			cout << "tak�m bulunamad�..." << endl;
		}
	}

	// tak�m detayl� bilgileri i�in 

	cout << left << setw(25) << "isim soyisim"
		<< left << setw(10) << "posizyon"
		<< left << setw(10) << "yas"
		<< left << setw(11) << "performans"
		<< left << setw(10) << "forma numarasi"
		<< endl;

	for (int i = 0; i < 11; i++) {

		cout << left << setw(25) << Team::AllTeam[counter - 1]->name[i]
			<< left << setw(10) << Team::AllTeam[counter - 1]->formasyon[i]
			<< left << setw(10) << Team::AllTeam[counter - 1]->age[i]
			<< left << setw(11) << Team::AllTeam[counter - 1]->perform[i]
			<< left << setw(10) << Team::AllTeam[counter - 1]->jersey[i]
			<< endl;

	}

	
/*
	
	if (readinfo.is_open()) {												// olusturulmustakimlar.txt a��k ise

		while (!(readinfo.eof())) {											// dosyan�n sonunda de�ilken

			getline(readinfo, line);										// bir sat�r al
			isFound = (line.find(target));									// sat�r i�inde fonksiyona arg�man olarak verilmi� team_alias verisini ara

			if (isFound != string::npos) {									
				isFound = 1;												// bulundu ise isFound'a 1 ata ve teamFound sat�r�na git
				break;
			}
			else {
				isFound = 0;
			}
		}

		if (isFound == 1) {													// isFound 1 ise
			for (int i = 0; i < 11; i++) {									// 11 kez daha sat�r �ek ve yazd�r, bunlar futbolcu bilgileri olacak
				getline(readinfo, line);
				cout << line << endl;
			}
		}
	}
	*/
	readteam.close();
	readinfo.close();

}

// parametre olarak ald��� olu�turulmu� objeyi pointer-to-pointer array'ine yerle�tirir. ve her seferinde static Team de�i�keni counter 1 artt�r�l�r
void Team::TeamLinkedList(Team* team) {

	Team* currentTeam = new Team;
	currentTeam = team;

	Team::AllTeam[counter] = currentTeam;
	Team::counter++;

}

