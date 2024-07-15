#include <iostream>
#include<iomanip>

#include "teams.h"
#include "calendar.h"
#include <array>

//static std::array<Team, 20> allTeam;
//Team *allTeamlist = new Team[20];


using namespace std;

Team* Meanteam;                                                                                     // araç olarak kullanımlar için
Team* team = new Team();                                                                            //kullanıcının ekleyeceği takımlar için

void menu1();

void TeamSettings();                                                                                
Team* TeamSetFunc_addTeam();                                                                        
void TeamSetFunc_showAllTeam();
void TeamSetFunc_showTeam(string);
void TeamSetFuncChangePerform(string, string);


void CalenderInfo();


void Results();



int main()
{
    int answer;

    ofstream newfileGeneral;
    ofstream newfileDetailed;

    
    newfileGeneral.open("newfileGeneral.txt", ios::app);                                                    // iki yeni boş dosya açılır
    newfileDetailed.open("newfileDetailed.txt", ios::app);


    remove("olusturulmustakimlar.txt");                                                                     // eski oluşturulan takım bilgilerini tutan fonksiyonlar silinir
    remove("teams.txt");

    rename("newfileGeneral.txt", "teams.txt");                                                              // boş dosyaların adları silinenlerinkiyle değiştirilir
    rename("newfileDetailed.txt", "olusturulmustakimlar.txt");
    
    newfileGeneral.close();
    newfileDetailed.close();
    

    cout << "The program is starting, please wait." << endl;

    // 18 default takım
    // her birinin oluşturumunda benzersiz değerler atanabilmesi için her obje tanımlanması sonrası program 1 sn uyutuluyor
    // her obje oluşturulduktan sonra objeleri listeye koyacak Team'in static TeamLinkedList() fonksiyonu çalıştırılıyor 

    Team* gs = new Team("galatasaray", "fatih terim");
    Team::TeamLinkedList(gs);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* fb = new Team("fenerbahce", "erol bulut", 433);
    Team::TeamLinkedList(fb);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* ts = new Team("trabzonspor", "abdullah avci", 352);
    Team::TeamLinkedList(ts);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* bjk = new Team("besiktas", "onder karaveli");
    Team::TeamLinkedList(bjk);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* gos = new Team("goztepespor", "Nestor El Maestro" ,343);
    Team::TeamLinkedList(gos);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* ad = new Team("adana demirspor", "vincenzo montella" ,352);
    Team::TeamLinkedList(ad);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* ks = new Team("konyaspor", "ilhan palut");
    Team::TeamLinkedList(ks);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* bs = new Team("basaksehir", "emre belözoglu", 433);
    Team::TeamLinkedList(bs);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* as = new Team("antalyaspor", "nuri sahin", 343);
    Team::TeamLinkedList(as);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* hs = new Team("hatayspor", "omer erdogan", 343);
    Team::TeamLinkedList(hs);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* ss = new Team("sivasspor", "rıza calımbay", 352);
    Team::TeamLinkedList(ss);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* gis = new Team("giresunspor", "hasan keles", 433);
    Team::TeamLinkedList(gis);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* crs = new Team("caykur rizespor", "hamza hamzaoglu", 352);
    Team::TeamLinkedList(crs);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* ags = new Team("ankaragucu spor", "mustafa dalci");
    Team::TeamLinkedList(ags);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* als = new Team("alanyaspor", "bulent korkmaz", 433);
    Team::TeamLinkedList(als);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* els = new Team("elazıgspor", "orhan kaynak", 352);
    Team::TeamLinkedList(els);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* kas = new Team("kasımpasaspor", "hakan kutlu", 343);
    Team::TeamLinkedList(kas);
    this_thread::sleep_for(chrono::milliseconds(1000));

    Team* alts = new Team("altayspor", "mustafa denizli");
    Team::TeamLinkedList(alts);
    this_thread::sleep_for(chrono::milliseconds(1000));


    system("cls");                                                                               // bu kod terminal ekranını temizler

    cout << setw(45) << " " << "**************************" << endl;
    cout << setw(45) << " " << "***** virtual league *****" << endl;
    cout << setw(45) << " " << "**************************" << endl;
    
    cout << "welcome to virtual league program..." << endl
        << "we give some information about our program" << endl << endl
        << "-> in virtual league there is 18 team" << endl
        << "-> match number and how many weeks the league will last will be determined by the number of teams you enter." << endl
        << "\n-> Be careful not to enter Turkish characters when entering names in menu selections, etc., .\n\n";

    cout << "press 1 for continue the virtual league... ";
    cin >> answer;
    if (answer == 1) {
        system("cls");
        menu1();
    }
    else {
        cout << "\n\nyou pressed wrong key" << endl;
        cout << "press 1 for continue the virtual league... ";
        cin >> answer;
        if (answer == 1) {
            system("cls");          
            menu1();
            goto finish;
        }
    }
finish:
    return 0;
 //main sonu
}


void menu1() {
    int answer;

menu1:
    cout << setw(45) << " " << "**************************" << endl;
    cout << setw(45) << " " << "***** virtual league *****" << endl;
    cout << setw(45) << " " << "**************************" << endl; 

    cout << "\n***** MAIN MENU *****\n";

    cout << "1-team settings" << endl
        << "2-callender information" << endl
        << "3-results" << endl
        << "4-info about menu options" << endl
        << "5-close the program" << endl;
    cout << "pick: ";
    cin >> answer;
    cout << "\n\n";

    switch (answer) {

    case 1:
        system("cls");
        TeamSettings(); 
        break;

    case 2:
        system("cls");
        CalenderInfo();

        cout << "\npress 0 for return the top menu... ";
        cin >> answer;
        system("cls");
        goto menu1;
        break;

    case 3:
        system("cls");
        Results();

        cout << "press 0 for return the top menu... ";
        cin >> answer;
        system("cls");
        goto menu1;
        break;

    case 4:
        cout << "\n*****info about menu options*****" << "\n\n"
            << "With team settings," << endl
            << "you can add teams, view a specific team, or all teams." << "\n"
            << "With the calendar information," << endl
            << "you can view the entire calendar, view all the matches of a certain team, or view a certain match with the match ID." << "\n"
            << "With the results," << endl
            << "you can reach the match results and the virtual league score table." << "\n";

        cout << "press 0 for return the top menu... ";
        cin >> answer;
        system("cls");
        goto menu1;
        break;

    case 5:
        break;
    };

}

// Team Setting fonksiyonları
void TeamSettings() {

    int answer;
    string team_nickname;
    string line;

    system("cls");

    cout << "\n\n***** TEAM SETTINGS *****\n\n";

    cout << "1-add team" << endl
        << "2-show all team" << endl
        << "3-show the team" << endl
        << "4- info about the menu options" << endl
        << "5-return the top menu..."<<endl;
    cout << "pick: ";
    cin >> answer;
    cout << "\n\n";

    switch (answer) {

    case 1:
        system("cls");
        cout << "***** ADDING TEAM *****\n\n";
        team = (TeamSetFunc_addTeam());

        cout << "press 0 for returning team settings menu... ";
        cin >> answer;
        if (answer == 0) {
            TeamSettings();
        }
        break;

    case 2:
        system("cls");
        cout << "***** SHOW ALL TEAM *****" << "\n\n";
        TeamSetFunc_showAllTeam();
        break;

    case 3:
        system("cls");

        // takımlar takım takma ismi ile aranıp ekranan gösterildiğinden, önce kullanıcıya gireceği takımın takma adını bilip bilmediği sorulur

        cout << "\n***** SHOW THE TEAM *****" << "\n\n";
        cout << "Teams are searched by team alias." << endl << endl
            << "If you know the nickname of the team you want to view, press 1." << endl
            << "if you don't know, press 0 to access the nicknames of all teams." << endl
            << "pick: ";
        cin >> answer;
        cout << "\n";
     
        // biliyorsa takma isim alınıp gerekli fonksiyon çağırılır
        if (answer == 1) {
            cout << "enter the team alias: ";
            cin >> team_nickname;

            system("cls");

            TeamSetFunc_showTeam(team_nickname);
        }
        // bilinmiyorsa tüm takma isimler, takım isimleri ve teknik direktör isimleri ekranda gösterilir
        if (answer == 0) {
            ifstream read;
            read.open("teams.txt");
            if (read.is_open()) {
                while (!read.eof()) {
                    getline(read, line);
                    cout << line << endl;
                }
            }
            read.close();
            cout << "\nenter the team alias: ";
            cin >> team_nickname;

            system("cls");

            TeamSetFunc_showTeam(team_nickname);
        }
        break;
    case 4:

        system("cls");

        cout << "*****info about Team Settings menu options*****" << "\n\n"
            << "With add team," << endl
            << "you can add team in virtual league." << endl
            << "With show all team," << endl
            << "you can view all teams and their general team information," << endl           
            << "With show the team" << endl
            << "you can learn the information of the team you want by entering the team nickname.." << endl
            << "and also with this option you can change the players performance value." << "\n\n";

        cout << "press 0 for returning team settings menu... ";
        cin >> answer;
        if (answer == 0) {
            system("cls");
            TeamSettings();
        }
        else {
            cout << "you pressed wrong key" << endl;
            cout << "press 0 for returning team settings menu... ";
            cin >> answer;
            if (answer == 0) {
                system("cls");
                TeamSettings();
            }
        }
        break;

    case 5:
        cout << "returning main menu..." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("cls");
        menu1();
        break;
    }

}

// takım ekleme seçeneğinin fonksiyonu
Team* TeamSetFunc_addTeam() {
    
    int answer;

    string input_team_name;
    string input_coach_name;
    string input_coach_surname;
    string input_coach_fullname;
    int    position_info;

    cout << "be careful not to enter Turkish characters when entering names in menu selections, etc., ." << endl
         << "be careful you will enter name and surname separately." << "\n\n";

    cout << "available formation types:  " << "*** 442  433  343  352 ***" << "\n\n";

    cout << "enter team name: ";
    cin >> input_team_name;

    cout << "enter coach name: ";
    cin >> input_coach_name;

    cout << "enter coach surname: ";
    cin >> input_coach_surname;

    input_coach_fullname = input_coach_name + " " + input_coach_surname;

    cout << "enter formation info: ";
    cin >> position_info;

    Team* team = new Team(input_team_name, input_coach_fullname, position_info);
    Team::TeamLinkedList(team);                                                             // oluşturulan obje listeye eklenir

    cout << "\n\nwould you like to add a team once again?\n";
    cout << "1- yes" << endl
         << "2- no" << endl
         << "pick: ";
   cin >> answer;

   if (answer == 1) {
        system("cls");
        TeamSetFunc_addTeam();
   }
   else {
       cout << "press 0 for returning team settings menu... ";
       cin >> answer;
       if (answer == 0) {
           system("cls");
           TeamSettings();
       }
       else {
           cout << "\nyou pressed wrong key" << endl;
           cout << "press 0 for returning team settings menu... ";
           cin >> answer;
           if (answer == 0) {
               system("cls");
               TeamSettings();
           }
       }
   }
   return team;
}

// tüm takımları gösterme seçenğinin fonksiyonu
void TeamSetFunc_showTeam(string nickname) {

    int answer;
    Team team;                                                                                     //boş obje oluşturup fonksiyonu onunla çağırdım, objeyi araç olarak kullandım
    string team_nickname = nickname;
    string jerseyno;

    team.show_team(team_nickname);                                                                  

    cout << "\ndo you want to change players performance value? " << endl
        << "1-yes" << endl
        << "2-no" << endl;
    cin >> answer;

    if (answer == 1) {
        cout << "\n\nEnter the jersey number of the player whose performance number you want to change: " << endl;
        cin >> jerseyno;
        TeamSetFuncChangePerform(team_nickname,jerseyno);
    }
    else if(answer==2) {
        cout << "\npress 0 for returning team settings menu... ";
        cin >> answer;

        if (answer == 0) {
            system("cls");
            TeamSettings();
        }
        else {
            cout << "you pressed wrong key" << endl;
            cout << "press 0 for returning team settings menu... ";
            cin >> answer;
            if (answer == 0) {
                TeamSettings();
            }
        }
    }
}

// tüm takımları gösterme seçeneğinin fonksiyonu
void TeamSetFunc_showAllTeam(){

    int answer;

    // başlık yazdırılır
    cout << left << setw(20) << "team alias"
         << left << setw(20) << "team name"
         << left << setw(20) << "coach name"
         << left << setw(22) << "average performance"
         << left << setw(20) << "team average age"
         << endl;

    // tüm takım bilgileri mevcut takım sayısı kadar AllTeam listesinden çekilir
    for (int i = 0; i < Team::counter; i++) 
    {
        cout << left << setw(20) << Team::AllTeam[i]->team_alias
             << left << setw(20) << Team::AllTeam[i]->team_name
             << left << setw(20) << Team::AllTeam[i]->coach_name
             << left << setw(22) << Team::AllTeam[i]->perform_ave
             << left << setw(20) << Team::AllTeam[i]->age_ave << endl;
    }

    cout << "\n\npress 0 for returning team settings menu... ";
    cin >> answer;
    if (answer == 0) {
        TeamSettings();
    }
    else {
        cout << "you pressed wrong key" << endl;
        cout << "press 0 for returning team settings menu... ";
        cin >> answer;
        if (answer == 0) {
            TeamSettings();
        }
    }

}

// bir oyuncunun performans değerini değiştirme fonksiyonu
void TeamSetFuncChangePerform(string nickname, string jersey) {

    ifstream readForChanging;
    ofstream writeTempFile;

    readForChanging.open("olusturulmustakimlar.txt", ios::app);
    writeTempFile.open("Tempolusturulmustakimlar.txt", ios::app);


    string target_team = nickname;
    string target_player = jersey;

    int newPerform = 0;

    string line;
    size_t isFound{};
    string target_line;
    string perform;

    int answer;
    string jerseyno;

    // girilen string forma numarasını int yapma
    stringstream Convert;
    Convert << target_player;
    int target_jersey = 0;
    Convert >> target_jersey;

    
    // dosyada performansı değiştirme
    // yeni dosya açıp tüm verileri yazıyoruz 
    // seçilen oyuncunun değiştirilmiş performans değerini, oyuncunun olduğu satıra gelince eskisi ile değiştirip geriye kalan satırları da aynen yeni dosyaya geçirmeye deavam ediyoruz
    if (readForChanging.is_open() && writeTempFile.is_open()) {

        while (!(readForChanging.eof())) {

            getline(readForChanging, line);
            writeTempFile << line << endl;

            isFound = (line.find(target_team));
            
            if (isFound != string::npos) {

                 getline(readForChanging, line);

                 isFound = (line.find(target_player));

                 if (isFound != string::npos) {
                    target_line = line;
                    cout << "\nenter performans value between 30-100:  ";
                    cin >> perform;
                    target_line[45] = perform[0];
                    target_line[46] = perform[1];                    
                    writeTempFile << target_line << endl;

                    //girilen string perform numarasını int yapma
                    stringstream Convert;
                    Convert << perform;
                    Convert >> newPerform;
                 }  
                }              
        }
    }

    // perform arrayinde performans listesini değiştirme
    for (int i = 0; i < Team::counter; i++) {

        int sum = 0;
        int ave = 0;

        if ((Team::AllTeam[i]->jersey[i]) == target_jersey) {

            Team::AllTeam[i]->perform[i] = newPerform;

            for (int j = 0; j < 11; j++) {
                sum = sum + perform[i];
            }   
            ave = sum / 11;
            Team::AllTeam[i]->perform_ave = ave;
        }
    }

    cout << "changed the performance value of player #" << target_player << "\n\n";

    readForChanging.close();
    writeTempFile.close();
    
    // dosya değişimi
    remove("olusturulmustakimlar.txt");
    rename("Tempolusturulmustakimlar.txt", "olusturulmustakimlar.txt");

    
                   
    cout << "1-view the team again" << endl;
    cin >> answer;
    if (answer == 1) {
        TeamSetFunc_showTeam(target_team);
    }

    cout << "\n\npress 0 for returning team settings menu... ";
    cin >> answer;
    if (answer == 0) {
        TeamSettings();
    }
    else {
        cout << "you pressed wrong key" << endl;
        cout << "press 0 for returning team settings menu... ";
        cin >> answer;
        if (answer == 0) {
            TeamSettings();
        }
    }
              
}



//calender fonksiyonları

void CalenderInfo() {

    // bu menüye girer girmez bir Calendar objesi oluşturulur

    Calendar* calendar = new Calendar();

    int answer;
    string team_alias;

returnCalenderMenu:

    system("cls");

    cout << setw(45) << " " << "**************************" << endl;
    cout << setw(45) << " " << "***** virtual league *****" << endl;
    cout << setw(45) << " " << "**************************" << endl << endl;

    cout << "\n\n***** CALENDAR INFO *****\n\n";

    cout << "1-show all calender" << endl
        << "2-show one team matches" << endl
        << "3-show match" << endl
        << "4-info about the menu options" << endl
        << "5- return the top menu" << endl;
    cout << "pick: ";
    cin >> answer;
    cout << "\n\n";

    switch (answer) {

    case 1:
        system("cls");

        cout << "\n\n***** SHOW CALENDAR *****\n\n";

        calendar->ShowCalendar();

        cout << "\npress 0 for returning calendar info menu... ";
        cin >> answer;
        if (answer == 0) {
           goto returnCalenderMenu;
        }
        else {
            cout << "you pressed wrong key" << endl;
            cout << "press 0 for returning calendar info menu... ";
            cin >> answer;
            if (answer == 0) {
                goto returnCalenderMenu;
            }
        }
        break;

    case 2:
        system("cls");

        cout << "\n\n***** SHOW THE TEAM MATCHES *****\n\n";

        cout << "Enter the team alias which team would you like to view their matches: ";
        cin >> team_alias;
        cout << "\n\n";

        calendar->ShowTeamCalendar(team_alias);

        cout << "\npress 0 for returning calendar info menu... ";
        cin >> answer;
        if (answer == 0) {
            goto returnCalenderMenu;
        }
        else {
            cout << "you pressed wrong key" << endl;
            cout << "press 0 for returning calendar info menu... ";
            cin >> answer;
            if (answer == 0) {
                goto returnCalenderMenu;
            }
        }
        break;

    case 3:
        system("cls");

        cout << endl << "Enter the id of the match you want to view: ";
        cin >> answer;
        calendar->ShowMatch(answer);

        cout << "\npress 0 for returning calendar info menu... ";
        cin >> answer;
        if (answer == 0) {
            goto returnCalenderMenu;
        }
        else {
            cout << "you pressed wrong key" << endl;
            cout << "press 0 for returning calendar info menu... ";
            cin >> answer;
            if (answer == 0) {
                goto returnCalenderMenu;
            }
        }
        break;

    case 4:
        system("cls");

        cout << "*****info about Calendar Info menu options*****" << "\n\n"
            << "With show all calendar," << endl
            << "you can view the league match calendar." << endl
            << "With show the team calendar," << endl
            << "you can only view the match calendar of the team you want.," << endl
            << "With show the match" << endl
            << "you can only view the match you entered the match id" <<endl
            << "match id will be written right next to match on the calendar" << "\n\n";

        cout << "press 0 for returning calendar info menu... ";
        cin >> answer;
        if (answer == 0) {
            goto returnCalenderMenu;
        }
        else {
            cout << "you pressed wrong key" << endl;
            cout << "press 0 for returning calendar info menu... ";
            cin >> answer;
            if (answer == 0) {
                goto returnCalenderMenu;
            }
        }
        break;

    case 5:
        cout << "returning main menu..." << endl;
        break;
    }

}



void Results() {

}

