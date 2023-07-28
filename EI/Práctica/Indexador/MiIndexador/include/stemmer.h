#ifndef _STEMMER_P_H_
#define _STEMMER_P_H_

#include <string>
#include <iostream>

using namespace std;

class stemmerPorter {
public:
	stemmerPorter();	// Por defecto se inicializa para español
	stemmerPorter(const stemmerPorter&);
	~stemmerPorter();
	stemmerPorter& operator=(const stemmerPorter &n);

	void stemmer(string  & cad, const int& numero);
	void stemmer(string  & cad, const int& numero, string & cadF);

	void  stemmer (char* & cad, const int& numero);
	void  stemmer (char*  & cad, const int& numero, char*& cadF);
private:
	char* cadena;
	int GtamCadena;
	char* stem;
	int GtamStem;
	char* tmp;
	int GtamTmp;

	void strip_affixes ( char *string );
	void to_lower_case( char *kwd );
	void clean ( char *kwd );
	int isvalid(char l);
	void strip_prefixes ( char *string );
	void strip_suffixes ( char *string );
	void step_1 ( char *string );
	void step_2 ( char *string );
	void step_3 ( char *string );
	void step_4 ( char *string );
	void step_5 ( char *string );
	int has_suffix ( char *word, char *suffix, char *stem );
	int cvc ( char *string );
	int vowel ( char ch, char prev );
	int measure ( char *stem );
	int contains_vowel ( char *word );
	char * removeSpanishAccent(char []);
	char * spanish_stemming (char word[]);

};


#endif
