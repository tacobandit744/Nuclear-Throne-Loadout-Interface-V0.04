////////////////////////////////////////////////////////////////////
// Made by "Tacobandit"                                           //
// 02 February 2016                                               //
// Version 0.04                                                   //
////////////////////////////////////////////////////////////////////
// Fourth version of creating a save editor UI for Nuclear Throne //
// This Fourth prototype still has a totally text based UI        //
// It allows for the user to do everything in V0.03 but also	  //
// unlock locked characters, as well as unlock b-skins		      //
// It also allows the user to edit the protochest weapon and	  //
// unlock hardmode												  //
////////////////////////////////////////////////////////////////////

// Ignore the fruit names, I like naming things after fruit :D

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void editProtoChest(ifstream &reader, ofstream &newSave) {
	cout << "What weapon do you want to place in the protochest? Refer to the weapon guide.\n";
	string weapon;
	cin >> weapon;
	cin.ignore();
	weapon += ".";
	while (weapon.length() < 9) {
		weapon += "0";
	}
	weapon += ",";
	string mango = "protowep";
	string core;
	getline(reader, core);
	string fruitbasket = core;
	size_t finder = core.find(mango);
	finder += 11;
	fruitbasket.replace(finder, 10, weapon);
	newSave << fruitbasket;
}

void unlockHard(ifstream &reader, ofstream &newSave) {
	string mango = "hardgot";
	string core;
	getline(reader, core);
	string fruitbasket = core;
	size_t finder = core.find(mango);
	finder += 10;
	fruitbasket.replace(finder, 9, "1.000000,");
	newSave << fruitbasket;
}

bool inputChecker(string input) { // could make this more robust by adding low and high arguments (bounds), but too lazy
	std::ostringstream converter; // used to convert string to int
	string coconut; // for comparison
	bool sentinel = false;
	size_t finder;
	for (int i = 1; i < 13; i++) {
		converter << i;
		coconut = converter.str(); // puts the int into coconut
		finder = coconut.find(input);
		if (finder != std::string::npos && coconut.length() == input.length()) { // if we have a match
			sentinel = true;
			break;
		}
		converter.str(""); // empties converter
	}
	return sentinel;
}

void unlockChar(ifstream &reader, ofstream &newSave, string name) {
	string core;
	string pit = "\"charData_" + name + "\":"; // The character info we want to edit
	string cherry = "cgot";
	string strawberry = "cbgt";
	getline(reader, core); // core holds the entire save file
	string fruitbasket = core; // fruitbasket will eventually be the new save file
	std::size_t kiwi = core.find(pit); // kiwi is the character location of the start of the character info we are looking for
	std::size_t finder; // This finds the first "cgot" value in the string
	unsigned int position = 0; // This will hold the "cgot" position for the character we want
	unsigned int bSkinPosition = 0; // This will hold the "cbgt position for the character we want
	while (kiwi > position) {
		finder = core.find(cherry);
		if (finder != std::string::npos) {
			if (kiwi > position) {
				if (finder == 0) {
					position += 4;
					core = core.substr(finder + 4, core.length() + 1);
				}
				else {
					position += finder;
					core = core.substr(finder, core.length() + 1);
				}
			}
			else {
				position += finder;
			}
		}
	}
	// We are now at the "cgot" point in the save data
	finder = core.find(strawberry);
	bSkinPosition = position;
	bSkinPosition += finder;
	bSkinPosition += 7; // bSkinPosition now has the location for the bskin number
	position += 7;
	string newChar = "1.000000,";
	fruitbasket.replace(position, 9, newChar);
	fruitbasket.replace(bSkinPosition, 9, newChar);
	newSave << fruitbasket;
}

void editCrown(ifstream &reader, ofstream &newSave, string name) { // Works very similarly to editValue
	cout << "Which crown would you like to enable?\n";
	cout << "1 - Crown of Death\n";
	cout << "2 - Crown of Life\n";
	cout << "3 - Crown of Haste\n";
	cout << "4 - Crown of Guns\n";
	cout << "5 - Crown of Hatred\n";
	cout << "6 - Crown of Blood\n";
	cout << "7 - Crown of Destiny\n";
	cout << "8 - Crown of Love\n";
	cout << "9 - Crown of Luck\n";
	cout << "10 - Crown of Curses\n";
	cout << "11 - Crown of Risk\n";
	cout << "12 - Crown of Protection\n";
	string crown;
	cin >> crown;
	cin.ignore();
	bool sentinel = false;
	while (sentinel == false) {
		sentinel = inputChecker(crown);
		if (sentinel == false) {
			cout << "That's an invalid value, try again!";
			cin >> crown;
			cin.ignore();
		}
	}
	string core;
	string pit = "\"charData_" + name + "\":"; // The character info we want to edit
	string relish = "crowns";
	getline(reader, core); // core holds the entire save file
	string fruitbasket = core; // fruitbasket will eventually be the new save file
	size_t kiwi = core.find(pit); // kiwi is the character location of the start of the character info we are looking for
	size_t finder; // This finds the first "crowns" value in the string
	unsigned int position = 0; // This will hold the "crowns" position for the character we want
	while (kiwi > position) {
		finder = core.find(relish);
		if (finder != std::string::npos) {
			if (kiwi > position) {
				if (finder == 0) {
					position += 6;
					core = core.substr(finder + 6, core.length() + 1);
				}
				else {
					position += finder;
					core = core.substr(finder, core.length() + 1);
				}
			}
			else {
				position += finder;
			}
		}
	}
	// now we are at the crowns bit for the given character
	position += 31; // Jumps us to crown #1, Crown of Death;
	int displacement = std::stoi(crown, nullptr, 10); // converts crown input to integer;
	displacement--; // Because we start at the first crown already.
	displacement = displacement * 10; // how many jumps we need to do, and each crown value is 10 chars apart
	string newCrown = "1.000000,";
	position += displacement;
	fruitbasket.replace(position, 9, newCrown);
	newSave << fruitbasket; // new save file created
}

void editValue(ifstream &reader, ofstream &newSave, string name) {
	cout << "Enter 1 for crowns.\nEnter 2 to unlock character and character b-skin.\n" << 
		"Enter 3 to unlock hardmode.\nEnter 4 to edit the protochest weapon.\n" << 
		"Enter anything else to go to weapons.\n";
	string crown;
	cin >> crown;
	cin.ignore(); // skips enter input
	size_t finder1;
	size_t finder2;
	size_t finder3;
	size_t finder4;

	finder1 = crown.find("1");
	finder2 = crown.find("2");
	finder3 = crown.find("3");
	finder4 = crown.find("4");

	if (finder1 != std::string::npos && crown.length() == 1) {
		editCrown(reader, newSave, name);
	}
	else if (finder2 != std::string::npos && crown.length() == 1)
	{
		unlockChar(reader, newSave, name);
	}
	else if (finder3 != std::string::npos && crown.length() == 1) {
		unlockHard(reader, newSave);
	}
	else if (finder4 != std::string::npos && crown.length() == 1) {
		editProtoChest(reader, newSave);
	}
	else {
		cout << "Enter the number of the weapon you wish to replace. Refer to the NT weapon guide." << endl;
		string weapon;
		cin >> weapon;
		string core;
		string pit = "\"charData_" + name + "\":"; // The character info we want to edit
		string relish = "\"cgld\": "; // 8 length
		getline(reader, core); // core holds the entire save file
		string fruitbasket = core; // fruitbasket will eventually be the new save file
		size_t kiwi = core.find(pit); // kiwi is the character location of the start of the character info we are looking for
		size_t finder; // This finds the first "cgld" value in the string
		unsigned int position = 0; // This will hold the "cgld" position for the character we want
		while (kiwi > position) {
			finder = core.find(relish);
			if (finder != std::string::npos) {
				if (kiwi > position) {
					if (finder == 0) {
						position += 8;
						core = core.substr(finder + 8, core.length() + 1);
					}
					else {
						position += finder;
						core = core.substr(finder, core.length() + 1);
					}
				}
				else {
					position += finder;
				}
			}
		}
		string replacement = relish + weapon + "."; // eg "cgld": 100.
		while (replacement.length() < 18) { // appends extra 0's for simplicity's sake. It's 20 to ensure no errors.
			replacement += "0";
		}
		replacement += ",";
		fruitbasket.replace(position, 19, replacement);
		newSave << fruitbasket; // new save file created
	}
}

void displayFile(fstream &reader) { // I don't remember where I was going with this
	string output;
	while (!reader.eof()) {
		getline(reader, output);
		cout << output;
	}
}

int main() {
	ifstream reader("oldSave.sav", ios::in); // This reads the old save file
	ifstream tempSave; // This will be the intermediate save file that is read, should the user choose to make multiple edits.
	ofstream tempHold; // This will be the intermediate save file that is written, should the user choose to make multiple edits.
	ofstream newSave("nuclearthrone.sav", ios::out); // This will be the final save file
	if (reader) {
		string charSelect = ""; // Stores the number that represents the character
		size_t finder;
		int multiChange = 0;
		do{
			cout << "Hello. What character would you like to edit?\n\n";
			cout << "1 - fish\n2 - crystal\n3 - eyes\n4 - melting\n5 - plant\n6 - YV\n7 - Steroids\n" <<
				"8 - robot\n9 - chicken\n10 - rebel\n11 - horror\n12 - rogue\n";
			cout << "type \'exit\' to exit the program\n";
			cin >> charSelect;
			cin.ignore(); // Ignores the enter key input
			finder = charSelect.find("exit");
			if (finder != std::string::npos) {
				cout << "bye!";
			}
			else if (!inputChecker(charSelect)) { // if not correct input
				cout << "That's not a valid character. Try again.\n";
			}
			else {
				if (multiChange > 0){
					tempSave.open("tempSave.sav", ios::in);
					newSave.open("nuclearthrone.sav", ios::out);
					editValue(tempSave, newSave, charSelect);
					newSave.close();
					tempSave.close();
					tempSave.open("nuclearthrone.sav", ios::in);
					string holder;
					getline(tempSave, holder);
					tempHold.open("tempSave.sav", ios::out);
					tempHold << holder; // tempSave.sav now holds
					tempHold.close();
					tempSave.close();
				}
				else {
					editValue(reader, newSave, charSelect);
					reader.close();
					newSave.close();
					tempSave.open("nuclearthrone.sav", ios::in);
					string holder;
					getline(tempSave, holder);
					tempHold.open("tempSave.sav", ios::out);
					tempHold << holder; // tempSave.sav now holds intermediate save file
					tempSave.close();
					tempHold.close();
					multiChange++;
				}
			}
		} while (finder == std::string::npos);
		return 0;
	}
	else {
		cout << "Error! File not opened successfully!";
		int holdup;
		cin >> holdup;
	}
	return 0;
}
