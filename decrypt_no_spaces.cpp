#include <iostream>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define RANDOM_SEEDS 10

unordered_map<string, bool> englishwords;
unordered_map<string, double> triscores;

string decrypkey = "";
string ciphtext = "";

unordered_map<string, double > commonwords;


void read_triscores() {
	ifstream ffin("DataGen/3_no_spaces_freqs.txt");
	string pattern;
	double score;
	while (ffin >> pattern) {
		ffin >> score;
		triscores[pattern] = score;
	}
	ffin.close();
}


string decode(string curkey) { /* Returns guess at plaintext by
	decrypting ciphtext with curkey */

	string guess = "";
	for (int i = 0; i < ciphtext.length(); i++) {
		if (ciphtext[i] == ' ') {
			guess += " ";
		}
		else {
			guess += string (1, curkey[ciphtext[i] - 'a']);
		}		
	}
	return guess;
}


double tri_freq_score(string curkey) { /* Tests plausibility of key by comparing
	frequencies of 2-letter patterns in decrypted text to English.
	Higher (less negative) scores are better */

	string guess = decode(curkey);

	double totcost = 0;
	for (int i = 0; i < guess.length() - 3; i++) {
		string curstr = guess.substr(i, 3);
		if (triscores.find(curstr) != triscores.end()) {
			totcost += triscores[curstr];
		}
		else {
			totcost -= 50.0;
		}
	}
	return totcost;
}


pair<string, double> find_plausible_key(string decrypkey) { /* This function takes in a seed key
	and makes random modifications to the key, computes the score based on pattern frequencies
	and accepts the new key if it achieves a higher score */

	double curscore = tri_freq_score(decrypkey);
	int lastreset = 0;

	while (lastreset < PATIENCE) {
		lastreset++;
		int ran1 = rand() % 26;
		int ran2 = rand() % 26;

		string newkey = "";
		for (int i = 0; i < 26; i++) {
			if (i == ran1) {
				newkey += decrypkey[ran2];
			}
			else if (i == ran2) {
				newkey += decrypkey[ran1];
			}
			else {
				newkey += decrypkey[i];
			}
		}

		double newscore = tri_freq_score(newkey);

		if (newscore > curscore) {
			curscore = newscore;
			decrypkey = newkey;
			lastreset = 0;
			// cout << curscore << " " << newkey << endl;
		}
	}

	return pair<string, double> (decrypkey, curscore);
}


int main() {
	string cipher_file;
	cout << "\"Enter without quotes the relative path to the file you want to decode: \n";
	cin >> cipher_file;

	ifstream fin (cipher_file.c_str());
	fin >> ciphtext;
	fin.close();

	for (int i = 0; i < 26; i++) {
		decrypkey += ('a' + i);
	}

	read_triscores();
	
	/* We choose a key such that the decrypted text 
	resembles English in frequencies of 3-letter patterns */
	double bestscore = tri_freq_score(decrypkey);
	string bestkey = "";

	cout << "Searching for decryption key...\n";
	for (int repeat = 0; repeat < RANDOM_SEEDS; repeat++) { 
		
		random_shuffle(decrypkey.begin(), decrypkey.end());

		pair<string, double> stringscore = find_plausible_key(decrypkey);
		string decrypkey = stringscore.first;
		double curscore = stringscore.second;
		
		if (curscore > bestscore) {
			bestscore = curscore;
			bestkey = decrypkey;
		}

		// cout << "Current best key is: " << bestkey << "\nwith score of " << curscore << endl;
	}

	decrypkey = bestkey;
	cout << "Decoded text is:\n" << endl;
	cout << decode (decrypkey) << endl;

	return 0;
}