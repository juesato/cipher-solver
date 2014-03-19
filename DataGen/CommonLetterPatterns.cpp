#include <iostream>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <fstream>
#include <math.h>
using namespace std;

// #define PATTERN_LENGTH 3 /* Looks at frequencies of all patterns of 2 characters */
#define NO_SPACES 1 /* Set this to 0 if you want to consider spaces */

unordered_map<string, int> n_letter_cts;


void incctr (string str) { /* Increments the counter for occurrences of pattern str */
	for (int i = 0; i < str.length(); i++) {
		if (isupper(str[i])) tolower(str[i]);
	}
	for (int i = 0; i < str.length(); i++) {
		if (!(str[i] >= 'a' && str[i] <= 'z' ) && str[i] != ' ') return;	
	}

	if (n_letter_cts.find(str) == n_letter_cts.end()) {
		n_letter_cts[str] = 1;
	}
	else {
		n_letter_cts[str]++;
	}
}


void n_letter_freq(string word, int n) {

	int len = word.length();
	word.insert(len, " ");
	word.insert(0, " ");
	len = word.length();

	for (int i = 0; i < len - n; i++) {
		string tmpstr = string(1, word[i]);
		for (int j = 1; j < n; j++) {
			tmpstr += word[i+j];
		}
		incctr(tmpstr);
	}
}


void print_freqs() { /* Prints the frequencies, formatted as an unordered_map.
	File has extra comma at the end that needs to be removed */

	double tot = 0.0;
	for (auto it = n_letter_cts.begin(); it != n_letter_cts.end(); ++it) {
		tot += it->second;
	}

	for (auto it = n_letter_cts.begin(); it != n_letter_cts.end(); ++it) {
		cout << it->first << " " << log( 100 * (double) it->second / tot) << "\n";
		// cout << "{\"" << it->first << "\"," << log (100 * (double) it->second / tot) << "}, ";
	}

}


int main() {

	int desired_length;

	if (!NO_SPACES) {
		cout << "Type in desired pattern length:\n";
		cin >> desired_length;
	}

	string output_file;
	cout << "Type in your desired output file name without quotes:\n";
	cin >> output_file;

	ifstream fin("corpus.txt");
	string word;
	if (NO_SPACES) {
		string alltext = "";
		while (fin >> word) {
			alltext += word;
		}

		// n_letter_freq(alltext, 2);
		n_letter_freq(alltext, 3);
		// n_letter_freq(alltext, 4);
	}
	else {
		while (fin >> word) {
			n_letter_freq(word, desired_length);
		}
	}

	freopen(output_file.c_str(),"w",stdout);

	print_freqs();
	return 0;
}