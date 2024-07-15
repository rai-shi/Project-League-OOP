#include "teams.h"
//#include "storage.h"

Team** Team::AllTeam = new Team*[20];										// takým objelerini tutacak static AllTeam pointer-to-pointer için 20 Team pointerý tutacak yer ayrýldý
int Team::counter = 0;														

// araç olarak kullanýlacak Team objelerinin baþlatýlmasý için boþ constructor
Team::Team() {


}

// parametreli counstructor
// takým bilgilerini alýr, gerekli atamalarý yapar.
// team.txt dosyasýna takýmý ekler.
// takým objesinin diðer detay özelliklerinin atamasý için creat_team() fonksiyonunu çaðýrýr
Team::Team(string team_name, string coach_name, int formationinfo) {

	ifstream read;															// teams.txt dosyasýný okumak için ifstream objesi
	ofstream write;															// teams.txt dosyasýna yazmak için ofstream objesi

	read.open("teams.txt", ios::app);										// dosya içieriði sondan eklemeli olarak okuma modunda açýldý
	write.open("teams.txt", ios::app);									    // dosya içieriði sondan eklemeli olarak yazma modunda açýldý
	write.setf(ios::left);													// dosyaya yazarken soldan hizalý bir þekilde yazýlacak


	this->team_name = team_name;
	this->coach_name = coach_name;
	this->team_alias = (team_name.substr(0,2));								// objenin team_alias özelliðine girilen takým adýnýn ilk iki karakteri atandý
	this->formationinfo = formationinfo;


	string line;
	size_t isFound{};

	if (read.is_open()){													// eðer dosya açýksa
		
		while (!(read.eof())) {												// dosyanýn sonunda deðilsen
			
			getline(read, line);											// dosyadan bir satýr oku
		    
			isFound = (line.find(team_alias));								// satýr içerisinde team_aliasý ara, bulursan isFound'a satýrda bulduðun konumu döndür
			
			if (isFound != string::npos) {									// eðer isFound npos deðilse yani aranan string 
				isFound = 1;												// bulundu ise 1
				goto Found;													// Found kod satýrýna git
			}
			else {
				isFound = 0;												//bulamadý ise 0
			}
		}
		Found:
	    if (isFound)  {														// isFound=1 durumunda genel bilgiler teams.txt dosyasýna yazýlýr
			team_alias = this->team_name.substr(0, 3);						// ayný team_alias bulunduðundan bu sefer team_alias olarak team_name'in ilk üç karakteri kullanýlýr
			write <<setw(20)<< team_alias
				 << setw(20) << this->team_name
				 << setw(20) << this->coach_name << endl;
		}
		else {
			write <<setw(20)<< team_alias									// isFound=0 durumunda genel bilgiler olduðu gibi teams.txt dosyasýna yazýlýr
				<< setw(20) << this->team_name
				<< setw(20) << this->coach_name
				<< endl;
		}
	}

	for (int i = 0; i < 11; i++) {											// takým oluþturma fonksiyonu çaðrýlmadan önce özellikler sýfýrlanýr
		age[i] = 0;
		jersey[i] = 0;
		perform[i] = 0;
		name[i] = "";
	}

	creat_team();

	read.close();
	write.close();
}

// takým_oluþtur() takýmlarýn tüm bilgilerini oluþturulmuþtakýmlar.txt içerisine yazar.
// fonksiyon içerisinde, takýmlara oyuuncu seçer.
// oyuncularýn özelliklerini de ayrý fonksiyonlar ile belirler
// içerisinde checking_age_average(), checking_jersey_number(), performance_average(), formation_function() fonksiyonlarýný çalýþtýrýr.
void Team::creat_team() {

	takým_dosya.open("olusturulmustakimlar.txt", ios::app);					// dosya yazma ve sondan eklemeli modda açýlýyor
	
	takým_dosya.setf(ios::left);											// dosyaya yazým sola hizalý olacak þekilde olacak

	srand(time(0));															// rand() fonksiyonuna o an ki saate göre baþlangýç deðeri atanýyor

	for (int i = 0; i < 11; i++) {											// her 11 oyuncu için 11'lik for döngüsü

		isim_dosya.open("ad.txt");
		soyad_dosya.open("soyad.txt");

		int random = 0;

		string name_line;
		string sname_line;


		//isim soyad seçimi
		random = rand() % 532;												// 532 isim olduðundan rand 0-532 arasý random bir sayý döndürecek
		for (int x = 0; x <= random; x++)									
		{																	// random sayýya kadar isim ve soyad soyasýndan satýrlar tek tek çekilecek
			getline(isim_dosya, name_line);
			getline(soyad_dosya, sname_line);

			if (x == random) {												// x deðeri random yani hedef satýra ulaþtýðýnda o satýrdaki isim ve soyisimi name array'inin i. indexine atayacak
				name[i] = name_line + " " + sname_line;
			}
		}

		perform[i] = produce_performance(i);								// her 11 oyuncuya performans deðeri atanmasý

		age[i] = produce_age(i);												// her 11 oyuncuya yaþ deðeri atanmasý

		jersey[i] = produce_jersey_number();								// her 11 oyuncuya forma numarasý atanmasý

		isim_dosya.close();
		soyad_dosya.close();
	}

	perform_ave = performance_average();									// performans ortalamasý hesaplanýr, geri döndürülen deðer objenin perform_ave özelliðine atanýr
	
	age_ave = age_average();												// yaþ ortalamasý hesaplanýr, geri döndürülen deðer objenin age_ave özelliðine atanýr							
	
	assign_formation();														// verilen formasyon bilgisi inputuna göre formasyon bilgisi atanýr


	takým_dosya << "takým: " << team_alias << "-" << team_name << endl;		// detaylý bilgilerin olduðu olusturulmustakimlar.txt dosyasýna tüm atanmýþ deðerler yazdýrýlýr
	for (int i = 0; i < 11; i++) {
		takým_dosya 
			<<setw(25) << name[i]
			<<setw(10) <<formasyon[i]
			<< setw(10) << age[i]
			<< setw(11) << perform[i]
			<< setw(10) << jersey[i]
			<< endl;
	}

	takým_dosya << endl;
	takým_dosya.close();
}


// bir takýmýn her oyuncusuna 30-100 arasý performans deðeri üretir. 
// toplam takým performansýnýn 60'dan yüksek olmasýna dikkat eder.
// parametresi creat_team fonksiyonu kaçýncý oyuncuda ise onu belirtir ki ortalama için o sayýya bölebilsin

int Team::produce_performance(int num) {

	int currentPlayerIndex = num;
	int tempPerform;
    int sum = 0;
	int average = 0;


	tempPerform = (rand() % 71) + 30;										// 30-100 arasý random performans deðeri üretilir
	perform[currentPlayerIndex] = tempPerform;								// perform array'indeki creat_team fonksiyonu kaçýncý oyuncuda ise onun indexine geçici performans deðeri atanýr

	for (int i = 0; i < 11; i++) {											// perform arrayindeki tüm performans deðerleri toplanýr

		sum = sum + perform[i];
	}	

	average = sum / (currentPlayerIndex + 1);								// toplam performans, creat_team kaçýncý oyuncuda ise ona bölünür

	if (average >= 60) {													// ortalamanýn 60'dan büyüklüðü kontrol edilir
		return tempPerform;													// eðer 60'dan büyükse baþtaki geçici performans deðeri geri döndürülür
	}
	else {
		produce_performance(currentPlayerIndex);							// 60'dan küçük ise fonksiyon yeni bir performans deðeri üretmesi için tekrar çaðrýlýr
	}
}


// takým performans ortalamasýný hesaplar.

float Team::performance_average() {

	float sum = 0;

	for (int i = 0; i < 11; i++) {
		sum = sum + perform[i];
	}

	float perform_ave = sum / 11;

	return perform_ave;
}


// bir futbolcu yaþýný 18-36 arasý ve tüm takýmýn yaþ ortalamasýný da 25-32 yaþ arasý tutarak oyunculara yaþ atamasý yapar

int Team::produce_age(int num) {

	int currentPlayerIndex = num;
	int tempAge;
	int sum = 0;
	int average = 0;
	
	tempAge = (rand() % 19) + 18;											// yaþ için 18-36 arasý random sayý üretilir
	age[currentPlayerIndex] = tempAge;										// o an ki oyuncuya bu deðer atanýr

	for (int i = 0; i < 11; i++) {

		sum = sum + age[i];
	}

	average = sum / (currentPlayerIndex +1);								// yaþ ortalamasý hesaplanýr

	if (25 <= average && average <= 32) {									// yaþ ortalamasýnýn 25-32 arasýnda olduðu kontrol edilir
		return tempAge;														// öylseyse üretilmiþ yaþ geri döndürülür
	}
	else {
		produce_age(currentPlayerIndex);									// deðilse fonksiyon tekrar çaðrýlýr
	}	
}

//bir takýmýn yaþ ortlamasýný hesaplar
float Team::age_average() {

	float sum = 0;

	for (int i = 0; i < 11; i++) {
		sum = sum + age[i];
	}

	float age_ave = sum / 11;

	return age_ave;
}

//bir takým içerisinde hiçbir oyuncunun forma numarasý ayný gelmeyecek þekilde her oyuncuya özel forma numarasý atamasý yapýlýr
int Team::produce_jersey_number() {

	int tempJNumber = (rand() % 99) + 1;									// tempJNumber'a 1-100 arasý random sayý atanýr

	int isMatch = 1;														// ayný forma numarasýnýn eþleþme durumu þu an 1

	for (int i = 0; i < 11; i++) {											// takýmýn o an ki oyuncusuna kadar forma numaralarý kontrol edilecek

		if (tempJNumber != jersey[i]) {										
			isMatch = 0;													// uyuþma yoksa yani ayný forma numarasýndan bulunamadý ise eþleþme durumu, isMatch 0 olarak atanacak
		}
	}
	if (isMatch == 0) {														// isMatch 0 ise
		return tempJNumber;													// üretilmiþ forma numarasýný geri döndür
	}
	else {
		produce_jersey_number();											// isMatch hala bir ise ayný forma numarasýndan var demektir fonksiyon yeniden çaðrýlýr
	}
}


//seçilen formasyon bilgisine göre oyuncularýn pozisyonlarýný belirler.
void Team::assign_formation()
{
	switch (formationinfo)													// constructor da atanmýþ formasyon bilgisine göre takýmlarýn oyuncularýna pozisyon bilgileri atanýr
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
    calculatePosisionAve();													// oyuncularýn pozisyon bilgileri atandýktan sonra takýmýn pozisyon performans ortalamasý hesaplanýr

}

// takým objesinin formasyon bilgisine göre pozisyon performans ortalamasýný hesaplar
void Team::calculatePosisionAve() {

	int sumForvet =0;
	int sumDefans = 0;
	int sumOrtasaha = 0;

	int aveForvet = 0;
	int aveDefans = 0;
	int aveOrtasaha = 0;

	string position;

	for (int i = 0; i < 11; i++)											// 11 oyuncunun forvet, ortasaha ya da defans oyuncusu olmasýna göre toplam forvet, ortasaha, defans performans deðerleri hesaplanýr
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

	// takýmýn performans bilgisine göre pozisyon ortalamalarý hesaplanýr
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
	
	// hesaplanan pozisyon ortalama deðerleri atanýr
	forvet_ave = aveForvet;
	defans_ave = aveDefans;
	ortasaha_ave = aveOrtasaha;
}

// seçilen takýmýn detaylý bilgilerini gösterir
// bilgilerinin gösterilmesi istenen takýmýn takma adý parametre olarak fonksiyona verilir
void Team::show_team(string takma_ad) {


	ifstream readteam;														// takýmýn genel bilgilerini okumak için ifstream objesi
	ifstream readinfo;														// takýmýn detaylý bilgilerini okumak için ifstream objesi
	
	int counter = 0;

	readteam.open("teams.txt", ios::app);
	readinfo.open("olusturulmustakimlar.txt", ios::app);

	string target = takma_ad;												// hedef takým
	string line;
	size_t isFound{};
	
	cout << endl << "takim: " << endl;

	// takýmýn isim- takma ad- teknik direktör adý gibi genel bilgilerini almak için 

	if (readteam.is_open()) {												// teams.txt açýk ise

		while (!(readteam.eof())) {											// teams.txt dosyasýnýn sonunda deðilsen

			getline(readteam, line);										// satýr çek
			counter++;														// counterý bir arttýr, böylece oluþturulmuþ kaçýncý takým olduðunun bilgisini öðrenebiliyoruz

			isFound = (line.find(target));									// çekilmiþ her satýrda fonksiyona verilmiþ team_alias aranýr
			
			if (isFound != string::npos) {									// takým bulundu ise isFound'a bir atanýr ve founded satýrýna gidilir
				isFound = 1;
				goto found;
			}
			else {
				isFound = 0;
			}
		}
		found:
		if (isFound == 1) {													// isFound 1 ise
			
			cout << line;													// çekilmiþ satýr ekrana yazdýrýlýr

			// setprecision() yazdýrýlacak float verinin kaç basamaðýnýn ekrana verileceðini belirler
			// AllTeam pointer-to-pointer array'indeki (counter-1). indexteki takým objesinin yaþ ve performans verileri ekrana yazdýrýlýr
			// (counter-1). index çünkü ilk satýr çekildiðinde counter 1 deðerini alýyor fakat takým 0. indexte bulunuyor
			cout <<"\n\nteam age ave: " << setw(2) << std::setprecision(3) << Team::AllTeam[counter - 1]->age_ave << "\n"               
				<< "team perform ave: " << setw(2) << std::setprecision(3) << Team::AllTeam[counter-1]->perform_ave <<endl << endl;
		}
		else {
			cout << "takým bulunamadý..." << endl;
		}
	}

	// takým detaylý bilgileri için 

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
	
	if (readinfo.is_open()) {												// olusturulmustakimlar.txt açýk ise

		while (!(readinfo.eof())) {											// dosyanýn sonunda deðilken

			getline(readinfo, line);										// bir satýr al
			isFound = (line.find(target));									// satýr içinde fonksiyona argüman olarak verilmiþ team_alias verisini ara

			if (isFound != string::npos) {									
				isFound = 1;												// bulundu ise isFound'a 1 ata ve teamFound satýrýna git
				break;
			}
			else {
				isFound = 0;
			}
		}

		if (isFound == 1) {													// isFound 1 ise
			for (int i = 0; i < 11; i++) {									// 11 kez daha satýr çek ve yazdýr, bunlar futbolcu bilgileri olacak
				getline(readinfo, line);
				cout << line << endl;
			}
		}
	}
	*/
	readteam.close();
	readinfo.close();

}

// parametre olarak aldýðý oluþturulmuþ objeyi pointer-to-pointer array'ine yerleþtirir. ve her seferinde static Team deðiþkeni counter 1 arttýrýlýr
void Team::TeamLinkedList(Team* team) {

	Team* currentTeam = new Team;
	currentTeam = team;

	Team::AllTeam[counter] = currentTeam;
	Team::counter++;

}

