#include <iostream>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define RANDOM_SEEDS 5
#define MAX_REFINEMENTS 100
#define SWAP_THRESHOLD .005
#define PATIENCE 300

unordered_map<string, double> pairscores = { {"di",-0.992358}, {" n",-0.474797}, {"ci",-2.27922}, {"nm",-6.0539}, {"um",-3.06653}, {"nq",-4.24834}, {"ff",-2.18966}, {"bs",-3.50185}, {"bm",-7.15251}, {"is",-0.0584823}, {"im",-1.09983}, {"mu",-1.97073}, {"ti",-0.500292}, {"av",-1.32209}, {"hy",-4.22132}, {"hw",-7.15251}, {"wk",-5.97385}, {"si",-0.887208}, {"lp",-4.73214}, {"rk",-3.82031}, {"lf",-2.09626}, {"et",-0.679777}, {"re",0.361063}, {"ef",-2.02261}, {"rw",-4.13208}, {"ol",-1.60831}, {"yn",-5.76622}, {" a",0.933054}, {"dj",-8.5388}, {"oz",-7.84566}, {" o",0.290861}, {"ch",-0.89676}, {"nj",-4.3047}, {"ul",-1.06687}, {"gm",-6.34158}, {"up",-2.44749}, {"bb",-6.59289}, {"fi",-1.88594}, {"ir",-1.25261}, {"pe",-1.14554}, {"mb",-3.25054}, {"il",-1.07372}, {"mt",-6.45936}, {"tt",-1.47234}, {"hl",-4.7776}, {"zw",-4.95529}, {"au",-2.31029}, {"za",-2.04808}, {"ag",-1.8054}, {"sh",-0.672849}, {"rh",-3.82031}, {"lg",-5.64843}, {"es",-0.369468}, {"oa",-3.91383}, {"ee",-0.997121}, {"rt",-1.37873}, {"oo",-1.36561}, {"ym",-4.7776}, {" b",-0.0330763}, {"dk",-8.5388}, {" p",-0.583028}, {"dy",-2.53245}, {"ck",-2.47968}, {"cy",-2.30832}, {"nk",-2.65548}, {"uk",-8.5388}, {"gl",-2.3444}, {"pf",-8.5388}, {"iq",-6.92937}, {"ma",-1.04549}, {"ic",-1.2533}, {"ms",-2.85183}, {"tu",-1.93351}, {"hm",-4.10799}, {"at",0.0895727}, {"su",-1.23631}, {"af",-2.48436}, {"sk",-3.95384}, {"lr",-5.2066}, {"ri",-0.929933}, {"er",0.79455}, {"ed",0.0557205}, {"ru",-2.85863}, {"on",0.154525}, {"yl",-5.70559}, {" c",-0.223482}, {"dd",-3.21093}, {" q",-3.01335}, {"va",-2.66669}, {"nh",-5.17151}, {"nz",-8.5388}, {"go",-2.27731}, {"bv",-8.5388}, {"fe",-1.52219}, {"py",-3.94368}, {"fy",-4.80113}, {"ip",-3.38551}, {"ib",-2.84171}, {"hn",-6.92937}, {"td",-8.5388}, {"st",-0.392964}, {"ae",-6.74704}, {"wl",-4.39567}, {"ls",-3.14518}, {"rn",-2.13192}, {"la",-1.39519}, {"eq",-3.3077}, {"oc",-3.16353}, {"ec",-1.1437}, {"oq",-7.15251}, {"yc",-8.5388}, {"kl",-5.64843}, {" d",-0.456093}, {"de",-0.720776}, {" r",-0.802934}, {"ce",-0.726021}, {"ni",-1.79592}, {"xp",-2.86205}, {"gn",-3.74301}, {"ui",-2.66107}, {"ba",-2.88983}, {"ft",-2.49143}, {"iw",-8.5388}, {"ph",-4.33411}, {"mo",-1.38341}, {"ia",-1.98061}, {"tw",-3.08348}, {"ho",-0.696918}, {"te",-0.153315}, {"zz",-3.94368}, {"az",-5.40331}, {"sw",-3.70252}, {"ad",-0.749764}, {"wo",-1.64312}, {"se",-0.295258}, {"ro",-1.03331}, {"ep",-2.10586}, {"ry",-1.35873}, {"ob",-2.71576}, {"eb",-4.87524}, {"ky",-5.76622}, {"ko",-7.84566}, {"op",-2.17405}, {"yb",-4.39567}, {" e",-0.683259}, {"df",-5.54307}, {" s",0.474913}, {"je",-3.1227}, {"vo",-3.07922}, {"cd",-7.44019}, {"nf",-3.12716}, {"xq",-8.5388}, {"gs",-3.13613}, {"nx",-4.68866}, {"ga",-2.10426}, {"uz",-7.44019}, {"bt",-3.87536}, {"fu",-2.67802}, {"iv",-1.75888}, {"pi",-2.51053}, {"mn",-5.49428}, {"mp",-1.97919}, {"tp",-8.5388}, {"tf",-4.0729}, {"ay",-1.46215}, {"sv",-7.84566}, {"ze",-5.0423}, {"ak",-2.1689}, {"wn",-2.40758}, {"sd",-4.98346}, {"rl",-2.40758}, {"lc",-5.17151}, {"eo",-4.0062}, {"oe",-3.99551}, {"ea",-0.504497}, {"kn",-2.3776}, {"os",-1.52309}, {"ya",-6.92937}, {" f",-0.256068}, {"dg",-3.73478}, {"ys",-2.70399}, {" t",1.08212}, {"du",-3.11827}, {"cu",-2.63891}, {"ng",-0.0649359}, {"gr",-2.12371}, {"ny",-2.16719}, {"ug",-1.78071}, {"uy",-6.92937}, {"bu",-1.86931}, {"fr",-1.8393}, {"iu",-5.70559}, {"mm",-3.07074}, {"ig",-1.76687}, {"ha",0.200252}, {"ax",-7.44019}, {"sq",-7.15251}, {"wa",-0.63152}, {"sg",-4.98346}, {"ll",-0.500292}, {"rm",-2.53245}, {"en",0.183287}, {"od",-2.25095}, {"ki",-2.52265}, {"or",-0.28714}, {" g",-1.13818}, {"yr",-7.44019}, {" u",-1.64009}, {"dv",-3.93363}, {"ju",-3.34585}, {"ct",-1.38497}, {"nd",0.0886776}, {"qu",-2.09945}, {"gu",-3.56207}, {"nv",-3.01734}, {"xa",-4.3047}, {"uf",-4.58756}, {"ux",-8.5388}, {"bj",-3.32387}, {"fa",-1.88982}, {"fs",-7.44019}, {"bd",-8.5388}, {"iz",-1.89632}, {"it",-0.11263}, {"ml",-5.89975}, {"if",-2.08676}, {"tr",-1.87185}, {"hb",-4.58756}, {"zy",-3.98493}, {"sp",-2.01818}, {"ai",-1.1838}, {"sf",-3.67899}, {"lm",-4.23474}, {"rb",-4.54982}, {"em",-1.31478}, {"og",-3.85667}, {"kh",-3.2658}, {"ou",0.195273}, {" h",0.649291}, {"da",-2.08203}, {" v",-1.7971}, {"dw",-5.59437}, {"ca",-1.42079}, {"ne",-0.266233}, {"xt",-3.54159}, {"gt",-4.84992}, {"nw",-5.01244}, {"gb",-4.06147}, {"ue",-2.57266}, {"by",-2.0557}, {"fn",-7.84566}, {"pp",-1.99489}, {"be",-0.292895}, {"ik",-3.07497}, {"pl",-1.75435}, {"ie",-1.23901}, {"ts",-2.33425}, {"ta",-1.20971}, {"ss",-1.02783}, {"ah",-8.5388}, {"wc",-6.92937}, {"sa",-1.34964}, {"ln",-5.49428}, {"rc",-2.01671}, {"kw",-5.83075}, {"el",-0.673616}, {"ke",-1.60246}, {"of",-0.261392}, {"dl",-3.53486}, {"ot",-0.645605}, {"yf",-6.59289}, {" i",0.146443}, {"db",-7.44019}, {"vy",-6.45936}, {"yp",-7.44019}, {" w",0.493127}, {"ji",-8.5388}, {"nb",-7.44019}, {"gy",-5.36075}, {"xu",-7.44019}, {"nt",-0.40375}, {"xc",-3.48895}, {"ge",-1.39598}, {"ud",-3.00147}, {"uv",-8.5388}, {"bh",-6.59289}, {"fo",-0.86094}, {"ix",-4.53147}, {"pm",-7.84566}, {"id",-1.35493}, {"tl",-1.99202}, {"as",-0.0710111}, {"hd",-6.34158}, {"tb",-8.5388}, {"hr",-3.4699}, {"sr",-6.59289}, {"zi",-6.92937}, {"ao",-5.76622}, {"ly",-0.802934}, {"ey",-1.48091}, {"lo",-1.49914}, {"ek",-4.09615}, {"rr",-2.18096}, {"oi",-2.72467}, {"dm",-4.09615}, {"ow",-1.02728}, {"ye",-2.88983}, {" j",-3.04164}, {"yw",-7.44019}, {"dq",-8.5388}, {"cc",-2.75806}, {"cq",-3.93363}, {"nc",-1.12906}, {"nu",-3.44505}, {"uc",-1.60636}, {"gd",-7.15251}, {"fl",-3.63353}, {"pr",-1.35645}, {"bi",-3.80261}, {"mi",-1.45207}, {"tm",-4.3047}, {"ar",-0.218843}, {"he",1.03868}, {"tc",-3.93363}, {"hs",-5.24297}, {"sm",-3.67899}, {"lt",-3.01335}, {"we",-1.11345}, {"an",0.418835}, {"sc",-2.7958}, {"ws",-4.09615}, {"ex",-1.95816}, {"ra",-1.34062}, {"ej",-4.75461}, {"rs",-0.997652}, {"oh",-6.59289}, {"kg",-7.84566}, {"dn",-4.42793}, {"ov",-2.29076}, {"vu",-7.44019}, {"yd",-3.40301}, {" k",-2.17923}, {" y",-0.978724}, {"cl",-2.76425}, {"jo",-3.56207}, {"dr",-3.06653}, {"vi",-1.79239}, {"nn",-1.88079}, {"xy",-8.5388}, {"gi",-2.25281}, {"nr",-5.89975}, {"xe",-4.39567}, {"ub",-3.09639}, {"gg",-5.01244}, {"ut",-1.02509}, {"ps",-3.52152}, {"pa",-1.67709}, {"mf",-4.47836}, {"ih",-6.92937}, {"po",-1.60929}, {"mh",-8.5388}, {"hh",-7.15251}, {"tn",-4.23474}, {"hf",-6.14091}, {"ac",-1.52399}, {"ht",-1.71552}, {"sl",-3.60433}, {"wd",-6.74704}, {"lu",-3.1227}, {"am",-1.35266}, {"sb",-4.53147}, {"wr",-3.72662}, {"ew",-2.61991}, {"li",-0.524468}, {"rf",-3.1917}, {"ei",-1.56901}, {"rp",-3.69462}, {"yi",-3.44505}, {"kf",-4.92789}, {"ok",-2.61188}, {"do",-1.77146}, {"vr",-8.5388}, {"oy",-4.23474}, {" l",-0.792071}, {"co",-0.599645}, {"ds",-2.53987}, {"cs",-6.59289}, {"no",-0.461046}, {"na",-2.23802}, {"xh",-6.59289}, {"uo",-6.59289}, {"gh",-1.22226}, {"ns",-1.25261}, {"xf",-8.5388}, {"ua",-2.42734}, {"us",-1.11942}, {"pt",-2.75498}, {"bo",-2.15024}, {"pb",-7.84566}, {"me",-0.496104}, {"io",-0.877748}, {"ty",-1.90286}, {"my",-1.97495}, {"hi",-0.149671}, {"to",0.00522586}, {"ap",-1.89241}, {"sy",-4.41167}, {"wi",-0.835796}, {"ab",-1.20643}, {"hu",-3.17751}, {"zl",-7.15251}, {"so",-1.05219}, {"lv",-3.85667}, {"al",-0.610398}, {"ld",-1.12002}, {"ev",-1.29887}, {"rg",-3.22068}, {"eh",-3.52817}, {"ks",-3.95384}, {"yh",-8.5388}, {"oj",-7.84566}, {"ka",-5.70559}, {"dh",-7.44019}, {"ox",-6.92937}, {" m",-0.0242142}, {"ve",-0.183189}, {"yt",-3.34031}, {"cr",-2.7799}, {"nl",-2.59077}, {"xi",-4.27612}, {"np",-5.49428}, {"un",-1.28675}, {"br",-2.86205}, {"ur",-0.671315}, {"pu",-3.43286}, {"bl",-1.62805}, {"in",0.664915}, {"tz",-4.95529}, {"th",0.939424}, {"aw",-2.73066}, {"wh",-0.888159}, {"sn",-5.59437}, {"lw",-3.75131}, {"wf",-7.44019}, {"wt",-8.5388}, {"rj",-8.5388}, {"le",-0.367487}, {"eu",-5.59437}, {"rd",-1.78887}, {"lk",-3.06653}, {"eg",-2.76425}, {"rv",-3.18222}, {"om",-0.845778}, {"yo",-1.00244} };
unordered_map<string, bool> englishwords;

string decrypkey = "";
string ciphtext = "";

unordered_map<string, double > commonwords;

void rank_word_freqs() { /* Applies a score to each word, 
	with more common words receiving higher scores */
	
	ifstream ffin("DownloadData/common_words.txt");
	string word;
	int rank = 0;
	while (ffin >> word) {
		rank++;
		commonwords[word] = 1.0 / (rank + 1000);
	}
	ffin.close();
}


void read_dictionary() { /* Creates lookup table for English words */
	ifstream ffin("DownloadData/words.txt");
	string word;
	while (ffin >> word) {
		for (int j = 0; j < word.length(); j++) {
			word[j] = tolower(word[j]);
		}
		englishwords[word] = 1;
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


double score(string curkey) { /* Tests plausibility of key by comparing
	frequencies of 2-letter patterns in decrypted text to English.
	Higher (less negative) scores are better */

	string guess = decode(curkey);

	double totcost = 0;
	for (int i = 0; i < guess.length() - 2; i++) {
		string curstr = guess.substr(i, 2);
		if (pairscores.find(curstr) != pairscores.end()) {
			totcost += pairscores[curstr];
		}
		else {
			totcost -= 50.0;
		}
	}
	return totcost;
}


string flip_letters(string word, char orig, char replacement) { /* Swap all 
	occurrences of orig or replacement with each other */

	for (int i = 0; i < word.length(); i++) {
		if (word[i] == orig) word[i] = replacement;
		else if (word[i] == replacement) word[i] = orig;
	}
	return word;
}


string modify_key(string decrypkey, int index, char replacement) { /* Returns a new key
	which modifies decrypkey so that the the translations of replacement and decrypkey[index]
	are swapped */

	for (int i = 0; i < 26; i++) {
		if (decrypkey[i] == replacement) {
			char tmp = decrypkey[i];
			decrypkey[i] = decrypkey[index];
			decrypkey[index] = tmp;
			break;
		}
	}
	return decrypkey;
}


string refine_key(string decrypkey) { /* Returns new decryption key which
	roughly tries to maximize number of English words up to a threshold */

	double repl[30][30];
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			repl[i][j] = 0;
		}
	}

	string plaintext = decode(decrypkey);
	
	bool brk = 0;
	string curword = "";
	for (int z = 0; z < plaintext.length(); z++) {
		if (plaintext[z] == ' ') {
			if (englishwords[curword] != 1 && curword.length() > 2) { // englishwords only contains words longer than 2 letters 

				for (int j = 0; j < curword.length(); j++) {
					for (int k = 0; k < 26; k++) {

						string newword = flip_letters(curword, curword[j], decrypkey[k]);

						if (commonwords.find(newword) != commonwords.end()) {
							repl[curword[j] - 'a'][decrypkey[k] - 'a'] += commonwords[newword];
							repl[decrypkey[k] - 'a'][curword[j] - 'a'] += commonwords[newword];
						}
					}

					for (int k = 0; k < 26; k++) {
						if (repl[curword[j] - 'a'][decrypkey[k] - 'a'] > SWAP_THRESHOLD) {

							string newkey = modify_key(decrypkey, k, curword[j]); 
							return newkey;

						}							
					}
				}

			}
			curword = "";
		}
		else {
			curword += plaintext[z];
		}
	}

	return decrypkey;
}


pair<string, double> find_plausible_key(string decrypkey) { /* This function takes in a seed key
	and makes random modifications to the key, computes the score based on pattern frequencies
	and accepts the new key if it achieves a higher score */

	double curscore = score(decrypkey);
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

		double newscore = score(newkey);

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
	string word;
	while (fin >> word) {
		ciphtext += word;
		ciphtext += " ";
	}
	for (int i = 0; i < 26; i++) {
		decrypkey += ('a' + i);
	}

	/* We first try to generate an initial guess at the key by choosing a key
	so that the decrypted text resembles English in frequencies of 2-letter patterns */
	double bestscore = score(decrypkey);
	string bestkey = "";

	cout << "Finding a plausible key...\n";
	for (int repeat = 0; repeat < RANDOM_SEEDS; repeat++) { 
		
		random_shuffle(decrypkey.begin(), decrypkey.end());

		pair<string, double> stringscore = find_plausible_key(decrypkey);
		string decrypkey = stringscore.first;
		double curscore = stringscore.second;
		
		if (curscore > bestscore) {
			bestscore = curscore;
			bestkey = decrypkey;
		}
	}

	decrypkey = bestkey;
	// cout << "First guess is:\n" << decrypkey << endl;
	// cout << decode (decrypkey) << endl;


	/* We know try to refine our initial guess by comparing our 
	decrypted ciphertext and seeing if words are close to real English
	words */
	rank_word_freqs();
	read_dictionary();

	cout << "Refining key...\n";
	for (int reps = 0; reps < MAX_REFINEMENTS; reps++) {

		string newkey = refine_key(decrypkey);
		if (newkey == decrypkey) {
			break;
		}
		decrypkey = newkey;

		// cout << "Refinement " << reps + 1 << "\n";
		// cout << decode (decrypkey) << endl;
	}
	cout << "Decoded text is: \n" << decode (decrypkey) << endl;

	return 0;
}