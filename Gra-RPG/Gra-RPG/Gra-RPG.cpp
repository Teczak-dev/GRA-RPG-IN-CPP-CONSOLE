#include<iostream>
#include<string>
#include<windows.h>
#include<cstdlib>
using namespace std;

bool isGame = true, isArmor = false;
string name, place = "Miasto";
string dane[4];
string eq[10];
int kasa = 10000, w = 100, indeksMapy = 1; // kasa, wypłata, index
int zdrowie = 100, maxhp = 100, pancerz = 0, poziom = 1, atak = 5;
int playerExp = 0, maxexp = 100;
// posiadłość zmienne:
int poziomy[9];
int przychody = 20;
int zebrano = 20;
int zboze1 = 0, zboze2 = 0, zboze3 = 0;
int poziom1 = 3000, poziom2 = 5000, poziom3 = 7500, poziom4 = 10000,  poziom5 = 125000;
int konie1 = 0, konie2 = 0;
string mlyn1[7], mlyn2[7], stodola[10];

//
// funkcje tworzenia postaci
//

// kreator (skończone)
void rasa() {
	system("cls");
	int rasa;
	cout << "Wybierz rase:\n1 - Czlowiek\n2 - Elf\n3 - Krasnolud" << endl << ": ";
	cin >> rasa;
	if (rasa == 1) {
		dane[1] = "Czlowiek";
	}
	else if (rasa == 2) {
		dane[1] = "Elf";
	}
	else if (rasa == 3) {
		dane[1] = "Krasnolud";
	}
	system("cls");
}

// ubior (skończone)
void ubior() {
	int ubior;
	cout << "Wybierz ubior: \n1 - ludowe\n2 - ubrania rodowe\n3- brak ubrań" << endl << ": ";
	cin >> ubior;
	switch (ubior) {
	case 1:
		dane[2] = "ludowe";
		break;
	case 2:
		dane[2] = "rodowe";
		break;
	case 3:
		dane[2] = "brak";
		break;
	default:
		break;
	}
	system("cls");
}

// loalizacja (skończone)
void location() {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int loc;
	cout << "Wybierz Lokalizacje: \n1 - wies\n2 - miasto\n3- polana" << endl << ": ";
	cin >> loc;
	switch (loc) {
	case 1:
		dane[3] = "wies";
		place = "Wieś";
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		indeksMapy = 2;
		w = 2;
		break;
	case 2:
		dane[3] = "miasto";
		place = "Miasto";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
		indeksMapy = 1;
		w = 10;
		break;
	case 3:
		dane[3] = "Polana";
		place = "Polana";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		indeksMapy = 3;
		w = 0;
		break;
	default:
		break;
	}
	system("cls");
}


//
// praca i zarządzanie ekwipunkiem
//


//praca (nie opłacalne i tylko na wsi) (skończone)
void work() {
	system("cls");
	kasa += w;
}

// sprzedawanie przedmiotów (skończone)
void sell() {
	system("cls");
	int wyb;
	int ilosc;
	int pusteSloty=0;
	system("cls");
	for (int i = 0; i < 10; i++) {
		if (eq[i] == "slot") {
			pusteSloty++;
		}
		if (i < 9) {
			cout << i + 1 << " - " << eq[i] << ",";
		}
		else {
			cout << i + 1 << " - " << eq[i] << endl;
		}
	}
	if (pusteSloty < 10) {
		cout << "Ile chcesz sprzedać przedmiotów? (podaj ilość od 1 do 10): ";
		cin >> ilosc;
		for (int i = 0; i < ilosc; i++) {
			system("cls");
			for (int j = 0; j < 10; j++) {
				if (i < 9) {
					cout << j + 1 << " - " << eq[j] << ",";
				}
				else {
					cout << j + 1 << " - " << eq[j] << endl;
				}
			}
			cout << "Wybierz slot który chcesz sprzedać( od 1 do 10): ";
			cin >> wyb;
			if (wyb > 10) {
				wyb = 10;
			}
			else if (wyb < 1) {
				wyb = 1;
			}
			if (eq[wyb - 1] == "slot") {
				cout << "Wybrano wbledne pole!!!" << endl;
			}
			else {
				if (eq[wyb - 1] == "zbroja") {
					kasa += 500;
					cout << "Udało się sprzedać " << eq[wyb - 1] << "za 500PLN" << endl;
					isArmor = false;
				}
				else if (eq[wyb - 1] == "eliksir") {
					kasa += 50;
					cout << "Udało się sprzedać " << eq[wyb - 1] << "za 50PLN" << endl;
				}
				else if (eq[wyb - 1] == "kusza") {
					kasa += 100;
					cout << "Udało się sprzedać " << eq[wyb - 1] << "za 15PLN" << endl;
				}
				else if (eq[wyb - 1] == "chleb") {
					kasa += 5;
					cout << "Udało się sprzedać " << eq[wyb - 1] << "za 5PLN" << endl;
				}
				else if (eq[wyb - 1] == "owoce") {
					kasa += 10;
					cout << "Udało się sprzedać " << eq[wyb - 1] << "za 10PLN" << endl;
				}
				else if (eq[wyb - 1] == "pierogi") {
					kasa += 20;
					cout << "Udało się sprzedać " << eq[wyb - 1] << "za 20PLN" << endl;
				}
				else if (eq[wyb - 1] == "kiełbasa") {
					kasa += 15;
					cout << "Udało się sprzedać " << eq[wyb - 1] << "za 15PLN" << endl;
				}
				eq[wyb - 1] = "slot";
			}
		}
		system("cls");
	}
	system("cls");

}

// kupowanie przedmiotów (skończone)
void buy() {
	system("cls");
	int sel;
	bool isEnd = false;
	while (true) {
		system("cls");
		cout << "Masz: " << kasa << "PLN" << endl << "1 - eliksir(50 hp+) 200PLN\n2 - zbroja 1000PLN(można mieć w eq tylko jedną)\n3 - kusza 300PLN\n4 - chleb(20 hp+) 20PLN\n5 - owoce(25 hp+) - 30PLN\n6 - pierogi(100 hp+) - 150PLN\n7 - kiełbasa(75 hp+) 70PLN\n8 - wyjdz" << endl << ": ";
		cin >> sel;
		// eleksir
		if (sel == 1) {
			if (kasa >= 200) {
				cout << "Wybierz slot: ";
				for (int i = 0; i < 10; i++) {
					if (i < 9) {
						cout << i + 1 << "-" << eq[i] << ",";
					}
					else {
						cout << i + 1 << "-" << eq[i] << endl;
					}
				}
				cin >> sel;
				if (sel > 10) {
					system("cls");
					cout << "Podałeś za dużą liczbę i zakup się nie udał\n";
					isEnd = true;

				}
				else if (sel < 1) {
					system("cls");
					cout << "Podałeś za małą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				if (eq[sel - 1] != "slot" && !isEnd) {
					system("cls");
					cout << "czy na pewno chcesz kupić ten przedmiot w tym slocie(jest on już zajęty? (tak/nie)\n:";
					string des;
					cin >> des;
					if (des == "tak") {
						eq[sel - 1] = "eliksir";
						kasa -= 200;
						system("cls");
					}
					else {
						system("cls");
						cout << "Ponawianie zakupu\n";
					}
				}
				else {
					system("cls");
					eq[sel - 1] = "eliksir";
					kasa -= 200;
				}
			}
			else {
				system("cls");
				cout << "masz za mało pieniedzy";
			}
		}
		// zbroja
		else if (sel == 2 && !isArmor) {
			if (kasa >= 1000) {
				cout << "Wybierz slot: " << endl << ": ";
				for (int i = 0; i < 10; i++) {
					if (i < 9) {
						cout << i + 1 << " - " << eq[i] << ",";
					}
					else {
						cout << i + 1 << " - " << eq[i] << endl;
					}
				}
				cin >> sel;
				if (sel > 10) {
					system("cls");
					cout << "Podałeś za dużą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				else if (sel < 1) {
					system("cls");
					cout << "Podałeś za małą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				if (eq[sel - 1] != "slot" && !isEnd) {
					system("cls");
					cout << "czy na pewno chcesz kupić ten przedmiot w tym slocie(jest on już zajęty? (tak/nie)\n:";
					string des;
					cin >> des;
					if (des == "tak") {
						eq[sel - 1] = "zbroja";
						isArmor = true;
						pancerz = 100;
						kasa -= 1000;
						system("cls");
					}
					else {
						system("cls");
						cout << "Ponawianie zakupu\n";
					}
				}
				else {
					system("cls");
					eq[sel - 1] = "zbroja";
					isArmor = true;
					pancerz = 100;
					kasa -= 1000;
				}
			}
			else {
				system("cls");
				cout << "masz za mało pieniedzy";
			}
		}
		// kusza
		else if (sel == 3) {
			if (kasa >= 300) {
				cout << "Wybierz slot: " << endl << ": ";
				for (int i = 0; i < 10; i++) {
					if (i < 9) {
						cout << i + 1 << " - " << eq[i] << ",";
					}
					else {
						cout << i + 1 << " - " << eq[i] << endl;
					}
				}
				cin >> sel;
				if (sel > 10) {
					system("cls");
					cout << "Podałeś za dużą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				else if (sel < 1) {
					system("cls");
					cout << "Podałeś za małą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				if (eq[sel - 1] != "slot" && !isEnd) {
					system("cls");
					cout << "czy na pewno chcesz kupić ten przedmiot w tym slocie(jest on już zajęty? (tak/nie)\n:";
					string des;
					cin >> des;
					if (des == "tak") {
						eq[sel - 1] = "kusza";
						kasa -= 300;
						system("cls");
					}
					else {
						system("cls");
						cout << "Ponawianie zakupu\n";
					}
				}
				else {
					eq[sel - 1] = "kusza";
					kasa -= 300;
				}
			}
			else {
				system("cls");
				cout << "masz za mało pieniedzy";
			}
		}
		// chleb
		else if (sel == 4) {
			if (kasa >= 20) {
				cout << "Wybierz slot: " << endl << ": ";
				for (int i = 0; i < 10; i++) {
					if (i < 9) {
						cout << i + 1 << " - " << eq[i] << ",";
					}
					else {
						cout << i + 1 << " - " << eq[i] << endl;
					}
				}
				cin >> sel;
				if (sel > 10) {
					system("cls");
					cout << "Podałeś za dużą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				else if (sel < 1) {
					system("cls");
					cout << "Podałeś za małą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				if (eq[sel - 1] != "slot" && !isEnd) {
					system("cls");
					cout << "czy na pewno chcesz kupić ten przedmiot w tym slocie(jest on już zajęty? (tak/nie)\n:";
					string des;
					cin >> des;
					if (des == "tak") {
						eq[sel - 1] = "chleb";
						kasa -= 20;
						system("cls");
					}
					else {
						system("cls");
						cout << "Ponawianie zakupu\n";
					}
				}
				else {
					system("cls");
					eq[sel - 1] = "chleb";
					kasa -= 20;
				}
			}
			else {
				system("cls");
				cout << "masz za mało pieniedzy";
			}
		}
		// owoce
		else if (sel == 5) {
			if (kasa >= 30) {
				cout << "Wybierz slot: " << endl << ": ";
				for (int i = 0; i < 10; i++) {
					if (i < 9) {
						cout << i + 1 << " - " << eq[i] << ",";
					}
					else {
						cout << i + 1 << " - " << eq[i] << endl;
					}
				}
				cin >> sel;
				if (sel > 10) {
					system("cls");
					cout << "Podałeś za dużą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				else if (sel < 1) {
					system("cls");
					cout << "Podałeś za małą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				if (eq[sel - 1] != "slot" && !isEnd) {
					system("cls");
					cout << "czy na pewno chcesz kupić ten przedmiot w tym slocie(jest on już zajęty? (tak/nie)\n:";
					string des;
					cin >> des;
					if (des == "tak") {
						eq[sel - 1] = "owoce";
						kasa -= 30;
						system("cls");
					}
					else {
						system("cls");
						cout << "Ponawianie zakupu\n";
					}
				}
				else {
					system("cls");
					eq[sel - 1] = "owoce";
					kasa -= 30;
				}
			}
			else {
				system("cls");
				cout << "masz za mało pieniedzy";
			}
		}
		//pierogi
		else if (sel == 6) {
			if (kasa >= 150) {
				cout << "Wybierz slot: " << endl << ": ";
				for (int i = 0; i < 10; i++) {
					if (i < 9) {
						cout << i + 1 << " - " << eq[i] << ",";
					}
					else {
						cout << i + 1 << " - " << eq[i] << endl;
					}
				}
				cin >> sel;
				if (sel > 10) {
					system("cls");
					cout << "Podałeś za dużą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				else if (sel < 1) {
					system("cls");
					cout << "Podałeś za małą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				if (eq[sel - 1] != "slot" && !isEnd) {
					system("cls");
					cout << "czy na pewno chcesz kupić ten przedmiot w tym slocie(jest on już zajęty? (tak/nie)\n:";
					string des;
					cin >> des;
					if (des == "tak") {
						eq[sel - 1] = "pierogi";
						kasa -= 150;
						system("cls");
					}
					else {
						system("cls");
						cout << "Ponawianie zakupu\n";
					}
				}
				else {
					system("cls");
					eq[sel - 1] = "pierogi";
					kasa -= 150;
				}
			}
			else {
				system("cls");
				cout << "masz za mało pieniedzy";
			}
		}
		//kiełbasa
		else if (sel == 7) {
			if (kasa >= 70) {
				cout << "Wybierz slot: " << endl << ": ";
				for (int i = 0; i < 10; i++) {
					if (i < 9) {
						cout << i + 1 << " - " << eq[i] << ",";
					}
					else {
						cout << i + 1 << " - " << eq[i] << endl;
					}
				}
				cin >> sel;
				if (sel > 10) {
					system("cls");
					cout << "Podałeś za dużą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				else if (sel < 1) {
					system("cls");
					cout << "Podałeś za małą liczbę i zakup się nie udał\n";
					isEnd = true;
				}
				if (eq[sel - 1] != "slot" && !isEnd) {
					system("cls");
					cout << "czy na pewno chcesz kupić ten przedmiot w tym slocie(jest on już zajęty? (tak/nie)\n:";
					string des;
					cin >> des;
					if (des == "tak") {
						eq[sel - 1] = "kiełbasa";
						kasa -= 70;
						system("cls");
					}
					else {
						system("cls");
						cout << "Ponawianie zakupu\n";
					}
				}
				else {
					system("cls");
					eq[sel - 1] = "kiełbasa";
					kasa -= 70;
				}
			}
			else {
				system("cls");
				cout << "masz za mało pieniedzy";
			}
		}
		// wyjscie
		else if (sel == 8) {
			system("cls");
			break;

		}
		cout << endl;
		isEnd = false;
	}
	system("cls");

}

// wyświetlanie ekwipunku (skończony)
void Inv() {
	system("cls");
	int dec;
	cout << "Zdrowie: " << zdrowie << "/" << maxhp;
	if (isArmor) {
		cout << "\nPancerz: " << pancerz << "%";
	}
	cout << "\nKasa: " << kasa << " \nmasz w ekwipunku: ";
	while (true) {
		dec = 0;
		for (int i = 0; i < 10; i++) {
			if (i < 9) {
				cout << i + 1 << " - " << eq[i] << ",";
			}
			else {
				cout << i + 1 << " - " << eq[i] << endl;
			}
		}
		cout << "Co chcesz zrobić?\n1 - użyj przedmiotu\n2 - wyrzuć przedmiot\n3 - wyjdź\n:";
		cin >> dec;
		if (dec == 1) {
			cout << "Którego przedmiotu chcesz użyć (podaj index np. 1 - chleb)\n:";
			cin >> dec;
			//  
			// przedmioty zdrowotne
			//
			if (eq[dec - 1] == "chleb") {
				if (zdrowie == maxhp) {
					cout << "Masz już pełne zdrowie";
				}
				else if (zdrowie < maxhp) {
					zdrowie += 20;
					if (zdrowie > maxhp) {
						zdrowie = maxhp;
					}
					eq[dec - 1] = "slot";
				}
			}
			else if (eq[dec - 1] == "eleksir") {
				if (zdrowie == maxhp) {
					cout << "Masz już pełne zdrowie";
				}
				else if (zdrowie < maxhp) {
					zdrowie += 50;
					if (zdrowie > maxhp) {
						zdrowie = maxhp;
					}
					eq[dec - 1] = "slot";
				}
			}
			else if (eq[dec - 1] == "owoce") {
				if (zdrowie == maxhp) {
					cout << "Masz już pełne zdrowie";
				}
				else if (zdrowie < maxhp) {
					zdrowie += 25;
					if (zdrowie > maxhp) {
						zdrowie = maxhp;
					}
					eq[dec - 1] = "slot";
				}
			}
			else if (eq[dec - 1] == "pierogi") {// najlepsze pierogi [ polski klimat ;) ]
				if (zdrowie == maxhp) {
					cout << "Masz już pełne zdrowie";
				}
				else if (zdrowie < maxhp) {
					zdrowie += 100;
					if (zdrowie > maxhp) {
						zdrowie = maxhp;
					}
					eq[dec - 1] = "slot";
				}
			}
			else if (eq[dec - 1] == "kiełbasa") {
				if (zdrowie == maxhp) {
					cout << "Masz już pełne zdrowie";
				}
				else if (zdrowie < maxhp) {
					zdrowie += 75;
					if (zdrowie > maxhp) {
						zdrowie = maxhp;
					}
					eq[dec] = "slot";
				}
			}
			else {
				cout << "Wybrałeś błędny przedmiot lub jest to pusty slot";
			}
		}
		else if (dec == 2) {
			cout << "Który przedmiot chcesz wyrzucić (podaj index np. 1)\n:";
			cin >> dec;
			if (eq[dec] == "slot") {
				system("cls");
				cout << "Czemu prubujesz usunąć pusty slot?";
			}
			else {
				if (eq[dec] == "zbroja") {
					isArmor = false;
				}
				eq[dec] = "slot";
			}
		}
		else if (dec == 3) {
			break;
		}
		else {
			system("cls");
			cout << "Błąd";
		}


	}
	system("cls");

}

// kowal (skończone)
void Smith() {
	system("cls");
	int select;
	if (isArmor) {
		if (pancerz < 100) {
			while (true) {
				cout << "Kasa: " << kasa << endl;
				cout << "Twój pancerz aktualnie posiada " << pancerz << "%";
				cout << "\nCo chcesz zrobić?\n";
				cout << "1 - napraw 15%(1000PLN)\n2 - napraw 30%(2500PLN)\n3 - napraw 50%(3500PLN)\n4 - napraw 75%(4250PLN)\n5 - napraw 100%(5500PLN)\n6 - wyjdź\n:";
				cin >> select;
				if (select == 1) {
					// 15%
					if (kasa >= 1000) {
						pancerz += 15;
						kasa -= 1000;
						system("cls");
						cout << "Udało się naprawić pancerz :)\n";
					}
					else {
						system("cls");
						cout << "Masz za mało kasy\n";
					}
				}
				// 30%
				else if (select == 2) {
					if (kasa >= 2500) {
						pancerz += 30;
						kasa -= 2500;
						system("cls");
						cout << "Udało się naprawić pancerz :)\n";
					}
					else {
						system("cls");
						cout << "Masz za mało kasy\n";
					}
				}
				// 50%
				else if (select == 3) {
					if (kasa >= 3500) {
						pancerz += 50;
						kasa -= 3500;
						system("cls");
						cout << "Udało się naprawić pancerz :)\n";
					}
					else {
						system("cls");
						cout << "Masz za mało kasy\n";
					}
				}
				// 75%
				else if (select == 4) {
					if (kasa >= 4250) {
						pancerz += 75;
						kasa -= 4250;
						system("cls");
						cout << "Udało się naprawić pancerz :)\n";
					}
					else {
						system("cls");
						cout << "Masz za mało kasy\n";
					}
				}
				// 100%
				else if (select == 5) {
					if (kasa >= 5500) {
						pancerz += 100;
						kasa -= 5500;
						system("cls");
						cout << "Udało się naprawić pancerz :)\n";
					}
					else {
						system("cls");
						cout << "Masz za mało kasy\n";
					}
				}
				// exit
				else if (select == 6) {
					break;
				}
				// other
				else {
					system("cls");
					cout << "Błędna opcja\n";
				}
				if (pancerz > 100) {
					pancerz = 100;
				}
			}
		}
		else {
			cout << "Twój pancesz ma już 100%\n";
		}
	}
	else {
		cout << "Nie posiadasz pancerzu\naby wyjść napisz dowolną liczbę\n:";
		cin >> select;
	}
}


//
// System walki
//


// walka z przeciwnikiem (skończone)
void Fight() {
	system("cls");
	int enemyHp = 0;
	int enemyLvl = 1;
	int enemyDamage = 5;
	int decyzja = 0;
	bool los = 0;
	bool isFight = true;
	string enemyName;
	if (place == "Polana") {
		enemyLvl = (rand() % 4) + 1;
		enemyHp = ((rand() % 10) + 1) * enemyLvl;
		enemyDamage = (((rand() % 5) + 1) * enemyLvl);
		decyzja = (rand() % 4) + 1;// losuje typ przeciwnika
		if (decyzja == 1) {
			enemyName = "Królik";
		}
		else if (decyzja == 2) {
			enemyName = "Elf Leśny";
		}
		else {
			enemyName = "Kwiat";
		}
	}

	// pustynia

	else if (place == "Pystynia") {
		enemyLvl = (rand() % 11) + 1;
		enemyHp = ((rand() % 221) + 1) * enemyLvl;
		enemyDamage = (((rand() % 16) + 1) * enemyLvl);
		decyzja = (rand() % 4) + 1;// losuje typ przeciwnika
		if (decyzja == 1) {
			enemyName = "Kaktus";
		}
		else if (decyzja == 2) {
			enemyName = "Skorpion";
		}
		else {
			enemyName = "Zombie";
		}
	}

	// Góry

	if (place == "Góry") {
		enemyLvl = (rand() % 21) + 10;
		enemyHp = ((rand() % 431) + 10) * enemyLvl;
		enemyDamage = (((rand() % 21) + 1) * enemyLvl);
		decyzja = (rand() % 4) + 1;// losuje typ przeciwnika
		if (decyzja == 1) {
			enemyName = "Koza";
		}
		else if (decyzja == 2) {
			enemyName = "Góral";
		}
		else {
			enemyName = "Drzewiec";
		}
	}

	while (isFight == 1) {
		if (enemyHp <= 0) {
			cout << "Przeciwnik pokonany\n";
			kasa += (enemyLvl * enemyDamage) + 10;
			playerExp += (enemyLvl * enemyDamage);
			if (playerExp >= maxexp) {
				maxexp = (maxexp * 2) + 100;
				poziom++;
				maxhp = (maxhp * 2) * poziom;
			}
			isFight = 0;
			break;
		}
		if (zdrowie <= 0) {
			cout << "Zostałeś pokonany\n";
			kasa = kasa - (kasa / 50);
			isFight = 0;
			zdrowie = 1;
			break;
		}
		cout << "Przeciwnik: " << enemyName << endl;
		cout << "Zdrowie: " << enemyHp << endl;
		cout << "Lvl: " << enemyLvl << endl;
		cout << "--------------------" << endl;
		cout << dane[0] << ":" << endl;
		cout << "Zdrowie: " << zdrowie << "/" << maxhp << endl;
		if (isArmor) {
			cout << "Pancerz: " << pancerz << "%" << endl;
		}
		cout << "Lvl: " << poziom << endl;
		cout << "Co chcesz zrobić?\n1 - walka mieczem\n2 - strzał z kuszy(wymagana kusza)\n3 - ekwipunek\n4 - ucieczka(10% szansy powodzenia)\n:";
		cin >> decyzja;// decyzja gracza co zrobi;
		system("cls");
		if (decyzja == 1) {
			enemyHp -= atak;
			los = (rand() % 2) + 0;
			if (los == 0) {
				if (pancerz >= enemyDamage) {
					pancerz -= enemyDamage / enemyLvl;
				}
				else if (pancerz > 0 && enemyDamage > pancerz) {
					zdrowie -= enemyDamage - pancerz;
					pancerz = 0;
				}
				else if (pancerz > 0 && enemyDamage < pancerz) {
					zdrowie -= pancerz - enemyDamage;
					pancerz = 0;
				}
				else {
					zdrowie -= enemyDamage;
				}
			}
		}
		else if (decyzja == 2) {
			for (int i = 0; i < 10; i++) {
				if (eq[i] == "kusza") {
					enemyHp -= atak;
					los = (rand() % 10) + 0;
					if (los == 0) {
						if (pancerz >= enemyDamage) {
							pancerz -= enemyDamage / 4;
						}
						else if (pancerz > 0 && enemyDamage > pancerz) {
							zdrowie -= enemyDamage - pancerz;
							pancerz = 0;
						}
						else if (pancerz > 0 && enemyDamage < pancerz) {
							zdrowie -= pancerz - enemyDamage;
							pancerz = 0;
						}
						else {
							zdrowie -= enemyDamage;
						}
					}
					i = 9;
					system("cls");
					cout << "Strzelono z kuszy\n";
					break;
				}
				else {
					system("cls");
					cout << "Nie posiadasz kuszy\n";
				}
			}
		}
		else if (decyzja == 3) {
			system("cls");
			Inv();
		}
		else if (decyzja == 4) {
			los = (rand() % 11) + 0;
			if (los == 0) {
				cout << "Udało ci się ucieć\n";
				isFight = false;
				break;
			}
			else {
				cout << "nie udało ci się ucieć\n";

			}
		}
		else {
			cout << "Błąd";
			system("cls");
		}
	}
}


//
// funkcje lokacji oraz ich systemy działania
//

// Lokacje (skończone)
void mapka() {
	system("cls");
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	extern string place;
	extern int indeksMapy;
	setlocale(LC_ALL, "Polish");
	int miejsce;
	cout << "Aktualne miejsce: " << place << endl;
	cout << " ________________________" << endl;
	cout << "|    |    |    |    |    |" << endl;
	cout << "| 01 | 02 | 03 | 04 | 05 |" << endl;
	cout << "|____|____|____|____|____|____" << endl;
	cout << "|    |    |    |    |    |    |" << endl;
	cout << "| 06 | 07 | 08 | 09 | 10 | 00 |" << endl;
	cout << "|____|____|____|____|____|____|" << endl;
	cout << "|    |    |    |    |    |" << endl;
	cout << "| 11 | 12 | 13 | 14 | 15 |" << endl;
	cout << "|____|____|____|____|____|" << endl;
	cout << "Legenda: \n00 - Twoja posiadłość\n01,08,12 - miasto\n02,09,13 - wieś\n03,10,14 - Polana(zalecane od lvl 1)\n04,06,15 - Pustynia(zalecane od lvl 4)\n05,07,11 - Góry(zalecane od lvl 8)\n";
	cout << "Wybierz lokalizację: ";
	cin >> miejsce;
	switch (miejsce) {
	case 0:
		place = "Posiadłość";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		indeksMapy = miejsce;
		break;
	case 1:
	case 8:
	case 12:
		place = "Miasto";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
		indeksMapy = miejsce;
		w = 10 * poziom;
		break;
	case 2:
	case 9:
	case 13:
		place = "Wieś";
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		indeksMapy = miejsce;
		w = 2 * poziom;
		break;
	case 3:
	case 10:
	case 14:
		place = "Polana";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		indeksMapy = miejsce;
		system("cls");
		break;
	case 4:
	case 6:
	case 15:
		place = "Pystynia";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		indeksMapy = miejsce;
		system("cls");
		break;
	case 5:
	case 7:
	case 11:
		place = "Góry";
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		indeksMapy = miejsce;
		system("cls");
		break;
	default:
		break;
	}
	system("cls");
}

// dom (skończone)
void dom() {
	string wybor;
	system("cls");
	int poziomPosiadlosci=0;
	for (int i = 0; i < 9; i++) {
		poziomPosiadlosci += poziomy[i];
	}
	cout << "Poziom posiadłości: " << poziomPosiadlosci << "/40" << endl;
	cout << "Przychody: " << przychody << "PLN/H" << endl;
	cout << "Udało się zarobić :" << zebrano << "PLN" << endl;
	cout << "Chcesz wyjąć z skarbca pieniądze? (t - tak/n - nie)\n:";
	cin >> wybor;
	if (wybor == "t" || wybor == "tak") {
		kasa += zebrano;
		zebrano = 0;
	}
	system("cls");
}

// pola uprawne (w trakcie)
void pole(string wybor) {
	int nrPola;
	int pd;
	int koszt;
	system("cls");
	if (wybor == "LP") {
		nrPola = 0;
	}
	else if (wybor == "SP") {
		nrPola = 1;
	}
	else if (wybor == "RP") {
		nrPola = 2;
	}
	cout << "Poziom: " << poziomy[nrPola] << "/5" << endl;
	cout << "ilosc zebranego zboża: ";
	if (nrPola == 0) {
		cout << zboze1;
	}
	else if (nrPola == 1) {
		cout << zboze2;
	}
	else if (nrPola == 2) {
		cout << zboze3;
	}
	cout << "/" << poziomy[nrPola];
	cout << "\nco chcesz zrobić?\n1 - sprzedaj zboże\n2 - transportuj do stodoły\n3 - transportuj do młynu\n4 - Ulepsz pole(koszt: ";
	// warunek (wyświetlenie)
	if (poziomy[nrPola] == 0) {// poziom 0
		cout << poziom1 << "PLN)";
		koszt = poziom1;
	}
	else if (poziomy[nrPola] == 1) {// poziom 1
		cout << poziom2 << "PLN)";
		koszt = poziom2;
	}
	else if (poziomy[nrPola] == 2) {// poziom 2
		cout << poziom3 << "PLN)";
		koszt = poziom3;
	}
	else if (poziomy[nrPola] == 3) {// poziom 3
		cout << poziom4 << "PLN)";
		koszt = poziom4;
	}
	else if (poziomy[nrPola] == 4) {// poziom 4
		cout << poziom5 << "PLN)";
		koszt = poziom5;
	}
	else {// poziom 5
		cout << "Brak, Masz już maksymalny poziom";
	}
	cout << "\n5 - wróć\n:";
	cin >> pd;
	// opcje pola 0
	if (pd == 1 && nrPola == 0) {
		system("cls");
		cout << "Sprzedano\n";
		for (int i = 0; i < zboze1; i++) {
			kasa += 20;
		}
	}
	else if (pd == 2 && nrPola == 0) {// dodawanie do stodoły
		system("cls");
		// pole 1
		if (nrPola == 0) {
			for (int i = 0; i < zboze1; i++) {
				for (int j = 0; j < poziomy[7]+5; j++) {
					if (stodola[j] == "pusto") {
						stodola[j] = "zboże";
						zboze1--;
					}
				}
			}
		}
		// pole 2
		else if (nrPola == 1) {
			for (int i = 0; i < zboze2; i++) {
				for (int j = 0; j < poziomy[7]+5; j++) {
					if (stodola[j] == "pusto") {
						stodola[j] = "zboże";
						zboze2--;
					}
				}
			}
		}
		// pole 3
		else if (nrPola == 2) {
			for (int i = 0; i < zboze3; i++) {
				for (int j = 0; j < poziomy[7]+5; j++) {
					if (stodola[j] == "pusto") {
						stodola[j] = "zboże";
						zboze3--;
					}
				}
			}
		}
		cout << "Dodawanie do stodoły...\n";
	}
	else if (pd == 3 && nrPola == 0) {
		system("cls");
		if (nrPola == 0) {
			for (int i = 0; i < zboze1; i++) {
				for (int j = 0; j < poziomy[6]+2; j++) {
					if (mlyn1[j] == "pusto") {
						mlyn1[j] = "zboże";
						zboze1--;
					}
				}
			}
			for (int i = 0; i < zboze1; i++) {
				for (int j = 0; j < poziomy[8]+2; j++) {
					if (mlyn2[j] == "pusto") {
						mlyn2[j] = "zboże";
						zboze1--;
					}
				}
			}
		}
		// pole 2
		else if (nrPola == 1) {
			for (int i = 0; i < zboze2; i++) {
				for (int j = 0; j < poziomy[6]+2; j++) {
					if (mlyn1[j] == "pusto") {
						mlyn1[j] = "zboże";
						zboze2--;
					}
				}
			}
			for (int i = 0; i < zboze2; i++) {
				for (int j = 0; j < poziomy[8]+2; j++) {
					if (mlyn2[j] == "pusto") {
						mlyn2[j] = "zboże";
						zboze2--;
					}
				}
			}
		}
		// pole 3
		else if (nrPola == 2) {
			for (int i = 0; i < zboze3; i++) {
				for (int j = 0; j < poziomy[6]+2; j++) {
					if (mlyn1[j] == "pusto") {
						mlyn1[j] = "zboże";
						zboze3--;
					}
				}
			}
			for (int i = 0; i < zboze3; i++) {
				for (int j = 0; j < poziomy[8]+2; j++) {
					if (mlyn2[j] == "pusto") {
						mlyn2[j] = "zboże";
						zboze3--;
					}
				}
			}
		}
		cout << "Dodawanie do młynów...\n";
	}
	else if (pd == 4 && nrPola == 0) {
		if (kasa >= koszt) {
			kasa -= koszt;
			poziomy[0]++;
			system("cls");
			cout << "Ulepszono na poziom " << poziomy[nrPola] << endl;
		}
		else {
			system("cls");
			cout << "Masz za mało kasy!!!" << endl;
		}
	}
}

// stajnia (w trakcie)
void stajnia(string wybor) {
	system("cls");
	int index, koszty, stajnia, Poz;
	if (wybor == "LS") {
		index = 3;
	}
	else if (wybor == "RS") {
		index = 5;
	}
	cout << "Poziom: " << poziomy[index] << "/5" << endl;
	cout << "Ilość posiadanych konii: ";
	if (index == 3) {
		cout << konie1 << "/" << poziomy[index + 2] << endl;
		koszty = 1000 * konie1;
	}
	else if (index == 5) {
		cout << konie2 << "/" << poziomy[index + 2] << endl;
		koszty = 1000 * konie2;
	}
	cout << "Co chcesz z nimi zrobić?\n1 - Sprzedaj\n2 - ulepsz stajnię\n3 - wroć\nDecyzja: ";
	cin >> stajnia;
	// sprzedawanie
	if (stajnia == 1) {
		kasa += koszty;
		poziomy[index]++;
	}
	// ulepszanie
	else if (stajnia == 2) {
		system("cls");
		if (poziomy[index] < 5) {
			if (poziomy[index] == 0) {// poziom 1
				cout << "Czy chcesz kupić stajnię na 1 poziom za " << poziom1 << "PLN?" << endl;
				Poz = poziom1;
			}
			else if (poziomy[index] == 1) {// poziom 2
				cout << "Czy chcesz ulepszyć stajnię na 2 poziom za " << poziom2 << "PLN?" << endl;
				Poz = poziom2;
			}
			else if (poziomy[index] == 2) {// poziom 3
				cout << "Czy chcesz ulepszyć stajnię na 3 poziom za " << poziom3 << "PLN?" << endl;
				Poz = poziom3;
			}
			else if (poziomy[index] == 3) { // poziom 4
				cout << "Czy chcesz ulepszyć stajnię na 4 poziom za " << poziom4 << "PLN?" << endl;
				Poz = poziom4;
			}
			else if (poziomy[index] == 4) {// poziom 5
				cout << "Czy chcesz ulepszyć stajnię na 5 poziom za " << poziom5 << "PLN?" << endl;
				Poz = poziom5;
			}
			cout << "(tak/nie):";
			string yesNo;
			cin >> yesNo;
			if (yesNo == "tak") {
				if (kasa >= Poz) {
					poziomy[index]++;
					kasa -= Poz;
					system("cls");
					cout << "Ulepszono na poziom " << poziomy[index] << endl;
				}
				else {
					system("cls");
					cout << "Masz za mało kasy" << endl;
				}
			}

		}
		else {
			cout << "Już masz maksymalny poziom";
		}

	}

	else if (stajnia == 3) {
		system("cls");
		cout << "Powrót";
	}
	system("cls");
}

// mlyn (w trakcie)
void mlyn(string wybor) {
	system("cls");
	int id;
	int iloscmaki = 0;
	int ilosczboza = 0;
	if (wybor == "LM") {
		id = 6;
	}
	else if (wybor == "RM") {
		id = 8;
	}
	while (true) {
		iloscmaki = 0;
		ilosczboza = 0;
		cout << "Poziom: " << poziomy[id] << "/5\n";
		if (id == 6) {
			for (int i = 0; i < poziomy[id] + 2; i++) {
				cout <<i+1<<" - " << mlyn1[i] << "; ";
				if (mlyn1[i] == "zboże") {
					ilosczboza++;
				}
				if (mlyn1[i] == "mąka") {
					iloscmaki++;
				}
			}
			cout << "\nCo chcesz zrobić?\n1 - zrób mąkę(wymaga zboze)\n2  - zrob chleb(Potrzba mąki i miejca w stodole)\n3 - ulepsz mlyn\n4 - wróć\n:";
			int mlydec;
			cin >> mlydec;
			if (mlydec == 1) {
				if (ilosczboza > 0) {
					ilosczboza--;
					iloscmaki++;
					for (int i = 0; i < poziomy[id] + 2; i++) {
						if (mlyn1[i] == "zboże") {
							mlyn1[i] = "mąka";
							break;
						}
					}
				}
			}
			else if (mlydec == 2) {
				if (iloscmaki > 0) {
					iloscmaki--;
					for (int i = 0; i < poziomy[7]+5; i++) {
						if (stodola[i] == "pusto") {
							stodola[i] = "chleb";
							break;
						}
					}
					system("cls");
					cout << "Chleb został stworzony i transportowany do stodoły\n";
				}
			}
			else if (mlydec == 3) {
				cout << "Poziom: " << poziomy[id];
				cout << "Następny poziom kosztuje: ";
				int mlykoszt;
				if (poziomy[id] < 5) {
					if (poziomy[id] == 0) {
						cout << poziom1 << "PLN\n";
						mlykoszt = poziom1;
					}
					else if (poziomy[id] == 1) {
						cout << poziom2 << "PLN\n";
						mlykoszt = poziom2;
					}
					else if (poziomy[id] == 2) {
						cout << poziom3 << "PLN\n";
						mlykoszt = poziom3;
					}
					else if (poziomy[id] == 3) {
						cout << poziom4 << "PLN\n";
						mlykoszt = poziom4;
					}
					else if (poziomy[id] == 4) {
						cout << poziom5 << "PLN\n";
						mlykoszt = poziom5;
					}
					cout << "Chcesz kupić?(tak/nie): ";
					string mlysel;
					cin >> mlysel;
					if (mlysel == "tak") {
						if (kasa >= mlykoszt) {
							kasa -= mlykoszt;
							poziomy[id]++;
							system("cls");
							cout << "Ulepszono na poziom: " << poziomy[id]<<endl;

						}
					}
				}
				else {
					cout << "0PLN (Posiadasz już maksymalny poziom)\n";
				}
			}
			else if (mlydec == 4) {
				break;
			}
		}
		// mlyn 2
		else if (id == 8) {
			for (int i = 0; i < poziomy[id] + 2; i++) {
				cout << "1 - " << mlyn2[i] << "; ";
				if (mlyn2[i] == "zboże") {
					ilosczboza++;
				}
				if (mlyn2[i] == "maka") {
					iloscmaki++;
				}
			}
			cout << "\nCo chcesz zrobić?\n1 - zrób mąkę(wymaga zboze)\n2  - zrob chleb(Potrzba mąki i miejca w eq)\n3 - ulepsz mlyn\n4 - wróć\n:";
			int mlydec;
			cin >> mlydec;
			if (mlydec == 1) {
				if (ilosczboza > 0) {
					ilosczboza--;
					iloscmaki++;
					for (int i = 0; i < poziomy[id] + 2; i++) {
						if (mlyn2[i] == "zboże") {
							mlyn2[i] = "mąka";
							break;
						}
					}
				}
			}
			else if (mlydec == 2) {
				if (iloscmaki > 0) {
					iloscmaki--;
					for (int i = 0; i < 10; i++) {
						if (eq[i] == "slot") {
							eq[i] = "chleb";
							break;
						}
					}
				}
			}
			else if (mlydec == 3) {
				cout << "Poziom: " << poziomy[id];
				cout << "Następny poziom kosztuje: ";
				int mlykoszt;
				if (poziomy[id] < 5) {
					if (poziomy[id] == 0) {
						cout << poziom1 << "PLN\n";
						mlykoszt = poziom1;
					}
					else if (poziomy[id] == 1) {
						cout << poziom2 << "PLN\n";
						mlykoszt = poziom2;
					}
					else if (poziomy[id] == 2) {
						cout << poziom3 << "PLN\n";
						mlykoszt = poziom3;
					}
					else if (poziomy[id] == 3) {
						cout << poziom4 << "PLN\n";
						mlykoszt = poziom4;
					}
					else if (poziomy[id] == 4) {
						cout << poziom5 << "PLN\n";
						mlykoszt = poziom5;
					}
					cout << "Chcesz kupić?(tak/nie): ";
					string mlysel;
					cin >> mlysel;
					if (mlysel == "tak") {
						if (kasa >= mlykoszt) {
							kasa -= mlykoszt;
							poziomy[id]++;
							system("cls");
							cout << "Ulepszono na poziom: " << poziomy[id];

						}
					}
				}
				else {
					cout << "0PLN (Posiadasz już maksymalny poziom)\n";
				}
			}
			else if (mlydec == 4) {
				break;
			}
		}
	}
	system("cls");
}

// stodoła (w trakcie)
void stodolaPosiadlosc() {
	int indexBread = 0;
	while (true) {
		cout << "Poziom " << poziomy[7] << "/5" << endl;
		for (int i = 0; i < poziomy[7] + 5; i++) {
			cout << stodola[i] << "; ";
			if (stodola[i] == "chleb") {
				indexBread = i;
			}
		}
		cout << "Co chesz zrobić?\n1 - sprzedać\n2 - daj do ekwipunku\n3 - daj do młynu\n4 - Ulepsz stodołę\n5 - wyjdź\n:";
		int sel;
		cin >> sel;

		if (sel == 1) { // sprzedawanie
			for (int i = 0; i < poziomy[7] + 5; i++) {
				if (stodola[i] == "zboże") {
					kasa += 5;
					stodola[i] = "pusto";
				}
				else if (stodola[i] == "mąka") {
					kasa += 10;
					stodola[i] = "pusto";
				}
				else if (stodola[i] == "chleb") {
					kasa += 15;
					stodola[i] = "pusto";
				}
			}
		}

		else if (sel == 2) {// do eq
			for (int i = 0; i < 7; i++) {
				if (eq[i] == "slot") {
					eq[i] = "chleb";
					stodola[indexBread] = "pusto";
					break;
					system("cls");
					cout << "Dodano chleb do ekwipunku";
				}
				else {
					system("cls");
					cout << "W stodole są przedmioty które nie można dodać do ekwipunku";
				}
			}
		}

		else if (sel == 3) {
			for (int i = 0; i < poziomy[7] + 5; i++) {
				for (int j = 0; j < poziomy[6] + 2; i++) {
					if (stodola[i] != "pusto" && mlyn1[j] == "pusto") {
						mlyn1[j] = stodola[i];
						stodola[i] = "pusto";
					}
				}
				for (int j = 0; j < poziomy[8] + 2; i++) {
					if (stodola[i] != "pusto" && mlyn2[j] == "pusto") {
						mlyn2[j] = stodola[i];
						stodola[i] = "pusto";
					}
				}
			}
		}
		else if (sel == 5) {
			break;
		}
	}

}

// Posiadłość Gracza( w trakcie)
void House() {
	system("cls");
	string wybor;
	int maxgodzin = 3;
	int zarobki = (rand() % 2) + 0;
	if (zarobki == 0) {
		if (poziomy[0] > 0) {
			zboze1 = (rand() % poziomy[0]) + 1;
		}
		if (poziomy[1] > 0) {
			zboze2 = (rand() % poziomy[1]) + 1;
		}
		if (poziomy[2] > 0) {
			zboze3 = (rand() % poziomy[2]) + 1;
		}
		//zboże
		if (zboze1 > poziomy[0]) {
			zboze1 == poziomy[0];
		}
		if (zboze2 > poziomy[1]) {
			zboze2 == poziomy[1];
		}
		if (zboze3 > poziomy[2]) {
			zboze3 == poziomy[2];
		}
		//konie
		int szansa = (rand() % 100) + 1;
		if (szansa <= 20) {
			konie1 += (rand() % poziomy[3]) + 1;
			konie2 += (rand() % poziomy[5]) + 1;
		}
	}
	while (true) {
		system("cls");
		cout << "Miejce: " << place << endl;
		cout << "      EXIT     " << endl;
		cout << " ____ ____ ____" << endl;
		cout << "|    |    |    |" << endl;
		cout << "| LP | SP | RP |" << endl;// 0 1 2
		cout << "|____|____|____|" << endl;
		cout << "|    |    |    |" << endl;
		cout << "| LS | SR | RS |" << endl;// 3 4 5
		cout << "|____|____|____|" << endl;
		cout << "|    |    |    |" << endl;
		cout << "| LM | ST | RM |" << endl;// 6 7 8
		cout << "|____|____|____|" << endl;
		cout << "LEGENDA:\nLP/SP/RP - Lewe Pole Upawne/Środkowe Pole Uprawne/Prawe Pole Uprawne\nSR - środek(Mieszkanie)\nLS/RS - Lewa Stajnia/Prawa Stajnia\nLM/RM - Lewy Młyn/Prawy Młyn\nST - Stodoła\nEXIT - opuszczenie posiadłości\nJakie miejsce chcesz edytować?: ";
		cin >> wybor;
		// Środek ( DOM )
		if (wybor == "SR" || wybor == "środek" || wybor == "sr") {
			dom();
		}
		// LP,SP,RP( Pola uprawne)
		else if (wybor == "LP" || wybor == "SP" || wybor == "RP") {
			pole(wybor);
		}
		// LS RS (stajnie)
		else if (wybor == "LS" || wybor == "RS") {
			stajnia(wybor);
		}
		// LM RM (młyny)
		else if (wybor == "LM" || wybor == "RM") {
			mlyn(wybor);
		}
		// ST(stodoła)
		else if (wybor == "ST") {
			stodolaPosiadlosc();
		}
		//EXIT
		else if (wybor == "EXIT" || wybor == "E") {
			break;
		}

	}
	mapka();
}

// wioska (skończone)
void Village() {
	int dec;
	cout << "Poziom: " << poziom << " Exp:" << playerExp << "/" << maxexp << "\nZdrowie: " << zdrowie << "/" << maxhp;
	if (isArmor) {
		cout << "\nPancerz: " << pancerz << "%";
	}
	cout << "\nKasa: " << kasa << "PLN\nWybierz czynnosc:\n1 - Otwórz mapę\n2 - pracowanie \n3 - sprzedawanie \n4 - kupowanie \n5 - ekwipunek\n6 - Wyjdz z gry" << endl << ": ";
	cin >> dec;
	switch (dec) {
	case 1:
		mapka();
		break;
	case 2:
		work();
		break;
	case 3:
		sell();
		break;
	case 4:
		buy();
		break;
	case 5:
		Inv();
		break;
	case 6:
		isGame = false;
		break;
	default:
		break;
	}
}

// polana (skończone)
void Polana() {
	int dec;
	cout << "Poziom: " << poziom << " Exp:" << playerExp << "/" << maxexp << "\nZdrowie: " << zdrowie << "/" << maxhp;
	if (isArmor) {
		cout << "\nPancerz: " << pancerz << "%";
	}
	cout << "\nKasa: " << kasa << "PLN\nWybierz czynność:\n1 - Otwórz mapę\n2 - Walka \n3 - ekwipunek\n4 - Wyjdż z gry" << endl << ": ";
	cin >> dec;
	switch (dec) {
	case 1:
		mapka();
		break;
	case 2:
		system("cls");
		Fight();
		break;
	case 3:
		Inv();
		break;
	case 4:
		isGame = false;
		break;
	default:
		break;

	}
	system("cls");
}

// pustynia (skończone)
void Desert() {
	int dec;
	cout << "Poziom: " << poziom << " Exp:" << playerExp << "/" << maxexp << "\nZdrowie: " << zdrowie << "/" << maxhp;
	if (isArmor) {
		cout << "\nPancerz: " << pancerz << "%";
	}
	cout << "\nKasa: " << kasa << "PLN\nWybierz czynność:\n1 - Otwórz mapę\n2 - Walka \n3 - ekwipunek\n4 - Wyjdź z gry" << endl << ": ";
	cin >> dec;
	switch (dec) {
	case 1:
		mapka();
		break;
	case 2:
		Fight();
		system("cls");
		break;
	case 3:
		Inv();
		break;
	case 4:
		isGame = false;
		break;
	default:
		break;

	}
	system("cls");
}

// gory (skończone)
void Gory() {
	int dec;
	cout << "Poziom: " << poziom << " Exp:" << playerExp << "/" << maxexp << "\nZdrowie: " << zdrowie << "/" << maxhp;
	if (isArmor) {
		cout << "\nPancerz: " << pancerz << "%";
	}
	cout << "\nKasa: " << kasa << "PLN\nWybierz czynność:\n1 - Otwórz mapę\n2 - Walka \n3 - ekwipunek\n4 - Wyjdź z gry" << endl << ": ";
	cin >> dec;
	switch (dec) {
	case 1:
		mapka();
		break;
	case 2:
		Fight();
		system("cls");
		break;
	case 3:
		Inv();
		break;
	case 4:
		isGame = false;
		break;
	default:
		break;

	}
	system("cls");
}

// miasto (skończone)
void City() {
	int dec;
	cout << "Poziom: " << poziom << " Exp:" << playerExp << "/" << maxexp << "\nZdrowie: " << zdrowie << "/" << maxhp;
	if (isArmor) {
		cout << "\nPancerz: " << pancerz << "%";
	}
	cout << "\nKasa: " << kasa << "PLN\nWybierz czynność : \n1 - Otwórz mapę\n2 - pracowanie \n3 - sprzedawanie \n4 - kupowanie \n5 - kowal\n6 - ekwipunek\n7 - Wyjdź z gry" << endl << ": ";
	cin >> dec;
	switch (dec) {
	case 1:
		mapka();
		break;
	case 2:
		work();
		break;
	case 3:
		sell();
		break;
	case 4:
		buy();
		break;
	case 5:
		Smith();
		break;
	case 6:
		Inv();
		break;
	case 7:
		isGame = false;
		break;
	default:
		break;

	}
}



// 
// funkcje odpowiedzialne za funkcjonowanie gry
//

//// zmiana lokalizacji itd. (ważne)(skończone)
void game() {
	if (indeksMapy == 0) {
		House();
	}
	else if (indeksMapy == 1 || indeksMapy == 8 || indeksMapy == 12) {
		City();
	}
	else if (indeksMapy == 2 || indeksMapy == 9 || indeksMapy == 13) {
		Village();
	}
	else if (indeksMapy == 3 || indeksMapy == 10 || indeksMapy == 14) {
		Polana();
	}
	else if (indeksMapy == 4 || indeksMapy == 6 || indeksMapy == 15) {
		Desert();
	}
	else if (indeksMapy == 5 || indeksMapy == 7 || indeksMapy == 11) {
		Gory();
	}
}

// gra się zaczyna (skończone)
void start() {
	int menu;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "| Medieval Life Simulator |" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "1 - start\n2 - wyjdź\n:";
	cin >> menu;
	system("cls");
	if (menu == 1) {
		for (int i = 0; i < 7; i++) {// młyn 1 tablica
			mlyn1[i] = "pusto";
		}
		for (int i = 0; i < 7; i++) {// młyn 2 tablica
			mlyn2[i] = "pusto";
		}
		for (int i = 0; i < 10; i++) {// stodoła tablica
			stodola[i] = "pusto";
		}
		for (int i = 0; i < 9; i++) {//poziomy różnych budowli w posiadłości tablica
			if (i == 4) {
				poziomy[i] = 1;
			}
			else {
				poziomy[i] = 0;
			}
		}
		cout << "Podaj nazwe postaci: " << endl << ": ";
		cin >> name;
		dane[0] = name;
		rasa();
		ubior();
		location();
		cout << "Zebrano nastepujące informacje:\nimie - " << dane[0] << "\nrasa - " << dane[1] << "\nubior - " << dane[2] << "\nlokalizacja - " << dane[3] << endl;

		for (int i = 0; i < 10; i++) { // pętla ustawiająca wartość slot do każdego elementu tablicy eq (ekwipunek jest pusty)
			eq[i] = "slot";
		}
		cout << "Aby przejść dalej wpisz (1): ";
		cin >> name;
		if (name == "1") {
			system("cls");
			game();
		}
		else {
			system("cls");
			game();
		}
	}
	else {
		isGame = false;
	}
}

int main()
{
	setlocale(LC_ALL, "Polish");
	start();
	while (isGame) {
		game();
	}
	return 0;
}

