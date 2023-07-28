 
#include <string>
#include <stdlib.h>
#include "stemmer.h"
#define EXIT_STEMMER 3

using namespace std;


			/* ==== :INFO/STRIP.C ==== */

/*
 * AUTHOR	: Stuart J. Barr
 * DATE:	: c. September 1986, give or take a few months...
 */

/*
 * to save confusion...
 * USAGE	: define KEYWORDSIZE (6 is a good value, in practise)
 *		  define FALSE, TRUE
 *		  if you want to strip prefixes, define PREFIXES
 *		  Write a wee C function to call
 *			strip_affixes(string)
 *		  where string is a char *.
 */

#include <stdio.h>
#include <string.h>



/*#include "defs.h"*/
#define TRUE   1
#define FALSE  0
#define KEYWORDSIZE 30
#define TAMANYO_MAX_PAL 50
#define PREFIXES 1








stemmerPorter::stemmerPorter() {
	GtamCadena = TAMANYO_MAX_PAL;
	GtamStem = TAMANYO_MAX_PAL;
	GtamTmp = TAMANYO_MAX_PAL;
	cadena = new char [GtamCadena];
	stem = new char [GtamStem];
	tmp = new char [GtamTmp];
}

stemmerPorter::stemmerPorter(const stemmerPorter& n) {
	GtamCadena = TAMANYO_MAX_PAL;
	GtamStem = TAMANYO_MAX_PAL;
	GtamTmp = TAMANYO_MAX_PAL;
	cadena = new char [GtamCadena];
	stem = new char [GtamStem];
	tmp = new char [GtamTmp];
	strcpy( cadena, n.cadena );
	strcpy( stem, n.stem );
	strcpy( tmp, n.tmp );
}

stemmerPorter::~stemmerPorter() {
	delete [] cadena;
	GtamCadena = 0;
	delete [] stem;
	GtamStem = 0;
	delete [] tmp;
	GtamTmp = 0;
}

stemmerPorter& stemmerPorter::operator=(const stemmerPorter &n)
{
   // Si no somos el operando..
  if(this!=&n)
  {
	  (*this).~stemmerPorter();
	  GtamCadena = n.GtamCadena;
	  GtamStem = n.GtamStem;
	  GtamTmp = n.GtamTmp;
	  cadena = new char [GtamCadena];
	  stem = new char [GtamStem];
	  tmp = new char [GtamTmp];
	  strcpy( cadena, n.cadena );
	  strcpy( stem, n.stem );
	  strcpy( tmp, n.tmp );
  }
  return *this;
}

void stemmerPorter::strip_affixes ( char *string )
{
	to_lower_case(string);
	clean(string);
#ifdef PREFIXES
	strip_prefixes(string);
#endif 
	strip_suffixes(string);
	string[KEYWORDSIZE] = '\0';
}

void stemmerPorter::to_lower_case( char *kwd )
{
	int i;
	for ( i=0 ; i < strlen(kwd) ; i++ )
		if ( (kwd[i] >= 'A') && (kwd[i] <= 'Z') )
			kwd[i] += 'a' - 'A';
}

void stemmerPorter::clean ( char *kwd )
{
	int i,j,last=strlen(kwd);
	for ( i=0 ; i < last ; i++ ) {
		if ( isvalid(kwd[i]) != 0 ) {
			for ( j = i ; j < last-1 ; j++ )
				kwd[j] = kwd[j+1];
			kwd[last-1] = '\0';
			last--;
			i--;
		}
	}
}

int stemmerPorter::isvalid(char l)
{
	if ( (l >= 'a') && (l <= 'z') )
		return(0);
	if ( (l >= 'A') && (l <= 'Z') )
		return(0);
	if ( (l >= '0') && (l <= '9') )
		return(0);
	return(1);
}

#ifdef PREFIXES
void stemmerPorter::strip_prefixes ( char *string )
{
	char *prefixes[] = { (char*) "kilo", (char*) "micro", (char*) "milli", (char*) "intra", (char*) "ultra",
					(char*) "mega", (char*) "nano", (char*) "pico", (char*) "pseudo", 0 };
	int i;
	for ( i=0 ; prefixes[i] != 0 ; i++ ) {
		if ( strncmp(prefixes[i],string,strlen(prefixes[i])) == 0 ) {
			int j;
			for ( j=0 ; j<strlen(string)-strlen(prefixes[i]) ; j++ )
				string[j] = string[j+strlen(prefixes[i])];
			string[j] = '\0';
			return;
		}
	}
}
#endif 

void stemmerPorter::strip_suffixes ( char *string )
{
	step_1 ( string );
	step_2 ( string );
	step_3 ( string );
	step_4 ( string );
	step_5 ( string );
}

void stemmerPorter::step_1 ( char *string )
{
	if(strlen(string) >= GtamStem) {
		delete [] stem;
		GtamStem = strlen(string) + 1;
		stem = new char [GtamStem];
		cerr << "ERROR SOLUCIONADO: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
	}

//	if(strlen(string) >= TAMANYO_MAX_PAL) {
//		cerr << "ERROR: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
//		exit(EXIT_STEMMER);
//	}

	if ( string[strlen(string)-1] == 's' ) {
		if ( (has_suffix(string,(char*) "sses",stem) == TRUE) ||
				(has_suffix(string,(char*) "ies",stem) == TRUE ) )
			string[strlen(string)-2] = '\0';
		else
			if ( string[strlen(string)-2] != 's' )
				string[strlen(string)-1] = '\0';
		}
	if ( has_suffix(string,(char*) "eed",stem) == TRUE ) {
		if ( measure(stem) > 0 )
			string[strlen(string)-1] = '\0';
	}
	else {	if ( ( (has_suffix(string,(char*) "ed",stem) == TRUE )
				|| (has_suffix(string,(char*) "ing",stem) == TRUE ) )
				&& (contains_vowel(stem) == TRUE ) ) {
			string[strlen(stem)] = '\0';
			if ( ( has_suffix(string,(char*) "at",stem) == TRUE )
				|| ( has_suffix(string,(char*) "bl",stem) == TRUE )
				|| ( has_suffix(string,(char*) "iz",stem) == TRUE ) ) {
				string[strlen(string)+1] = '\0';
				string[strlen(string)] = 'e';
			}
			else {	int length = strlen(string);
				if ( (string[length-1] == string[length-2])
						&& (string[length-1] != 'l')
						&& (string[length-1] != 's')
						&& (string[length-1] != 'z') )
					string[length-1] = '\0';
				else
					if ( measure(string) == 1 ) {
					     if ( cvc(string) == TRUE ) {
						string[strlen(string)+1] = '\0';
						string[strlen(string)] = 'e';
						}
					}
			}
		}
	}
	if ( (has_suffix(string,(char*) "y",stem) == TRUE) &&
					(contains_vowel(stem) == TRUE) )
		string[strlen(string)-1] = 'i';
	if ( has_suffix(string,(char*) "th",stem) == TRUE)		//ING añadido para que quite 50th y deje 50
		string[strlen(string)-2] = '\0';
}

void stemmerPorter::step_2 ( char *string )
{
	char *suffixes[][2] =  { { (char*) "ational", (char*) "ate" },
				        { (char*) "tional",  (char*) "tion" },
				        { (char*) "enci",    (char*) "ence" },
					{ (char*) "anci",    (char*) "ance" },
					{ (char*) "izer",    (char*) "ize" },
					{ (char*) "iser",    (char*) "ize" },
					{ (char*) "abli",    (char*) "able" },
					{ (char*) "alli",    (char*) "al" },
					{ (char*) "entli",   (char*) "ent" },
					{ (char*) "eli",     (char*) "e" },
					{ (char*) "ousli",   (char*) "ous" },
					{ (char*) "ization", (char*) "ize" },
					{ (char*) "isation", (char*) "ize" },
					{ (char*) "ation",   (char*) "ate" },
					{ (char*) "ator",    (char*) "ate" },
					{ (char*) "alism",   (char*) "al" },
					{ (char*) "iveness", (char*) "ive" },
					{ (char*) "fulness", (char*) "ful" },
					{ (char*) "ousness", (char*) "ous" },
					{ (char*) "aliti",   (char*) "al" },
					{ (char*) "iviti",   (char*) "ive" },
					{ (char*) "biliti",  (char*) "ble" },
					{  0,        0     } };
//	char stem[TAMANYO_MAX_PAL];
//	if(strlen(string) >= TAMANYO_MAX_PAL) {
//		cerr << "ERROR: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
//		exit(EXIT_STEMMER);
//	}
	if(strlen(string) >= GtamStem) {
		delete [] stem;
		GtamStem = strlen(string) + 1;
		stem = new char [GtamStem];
		cerr << "ERROR SOLUCIONADO: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
	}
	register int index;
	for ( index = 0 ; suffixes[index][0] != 0 ; index++ ) {
		if ( has_suffix ( string, suffixes[index][0], stem ) == TRUE ) {
			if ( measure ( stem ) > 0 ) {
				sprintf ( string, "%s%s", stem, suffixes[index][1] );
				return;
			}
		}
	}
	return;
}

void stemmerPorter::step_3 ( char *string )
{
	char *suffixes[][2] = { { (char*) "icate", (char*) "ic" },
				       { (char*) "ative", (char*) "" },
				       { (char*) "alize", (char*) "al" },
				       { (char*) "alise", (char*) "al" },
				       { (char*) "iciti", (char*) "ic" },
				       { (char*) "ical",  (char*) "ic" },
				       { (char*) "ful",   (char*) "" },
				       { (char*) "ness",  (char*) "" },
				       { 0,       0 } };
//	char stem[TAMANYO_MAX_PAL];
//	if(strlen(string) >= TAMANYO_MAX_PAL) {
//		cerr << "ERROR: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
//		exit(EXIT_STEMMER);
//	}
	if(strlen(string) >= GtamStem) {
		delete [] stem;
		GtamStem = strlen(string) + 1;
		stem = new char [GtamStem];
		cerr << "ERROR SOLUCIONADO: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
	}
	register int index;
	for ( index = 0 ; suffixes[index][0] != 0 ; index++ ) {
		if ( has_suffix ( string, suffixes[index][0], stem ) == TRUE )
			if ( measure ( stem ) > 0 ) {
				sprintf ( string, "%s%s", stem, suffixes[index][1] );
				return;
			}
	}
	return;
}

void stemmerPorter::step_4 ( char *string )
{
	char *suffixes[] = { (char*) "al", (char*) "ance", (char*) "ence", (char*) "er", (char*) "ic", (char*) "able",
		(char*) "ible", (char*) "ant", (char*) "ement", (char*) "ment", (char*) "ent", (char*) "sion", (char*) "tion",
		(char*) "ou", (char*) "ism", (char*) "ate", (char*) "iti", (char*) "ous", (char*) "ive", (char*) "ize", (char*) "ise", 0 };
//	char stem[TAMANYO_MAX_PAL];
//	if(strlen(string) >= TAMANYO_MAX_PAL) {
//		cerr << "ERROR: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
//		exit(EXIT_STEMMER);
//	}
	if(strlen(string) >= GtamStem) {
		delete [] stem;
		GtamStem = strlen(string) + 1;
		stem = new char [GtamStem];
	}
	register int index;
	for ( index = 0 ; suffixes[index] != 0 ; index++ ) {
		if ( has_suffix ( string, suffixes[index], stem ) == TRUE )
			if ( measure ( stem ) > 1 ) {
				strcpy( string, stem );
				return;
			}
	}
	return;
}

void stemmerPorter::step_5 ( char *string )
{
	if ( string[strlen(string)-1] == 'e' ) {
		if ( measure(string) > 1 )
			/* measure(string)==measure(stem) if ends in vowel */
			string[strlen(string)-1] = '\0';
		else
			if ( measure(string) == 1 ) {
				char stem[TAMANYO_MAX_PAL];
				if(strlen(string) > TAMANYO_MAX_PAL) {
					cerr << "ERROR: palabra: " << string << " a stemmerizar de longitud: " << strlen(string) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
					exit(EXIT_STEMMER);
				}
				strcpy(stem,"");
				strncat( stem, string, strlen(string)-1 );
				if ( cvc(stem) == FALSE )
					string[strlen(string)-1] = '\0';
			}
	}
	if ( (string[strlen(string)-1] == 'l')
				&& (string[strlen(string)-2] == 'l')
				&& (measure(string) > 1) )
		string[strlen(string)-1] = '\0';
}

int stemmerPorter::has_suffix ( char *word, char *suffix, char *stem )
{
//	char tmp[TAMANYO_MAX_PAL];
//	if(strlen(word) >= TAMANYO_MAX_PAL) {
//		cerr << "ERROR: palabra: " << word << " a stemmerizar de longitud: " << strlen(word) << " mayor que el máximo previsto: " << TAMANYO_MAX_PAL << endl;
//		exit(EXIT_STEMMER);
//	}
  
//	int lstem = strlen(stem);
//	int lsuffix = strlen(suffix);
//	if( (strlen(stem) + strlen(suffix) ) >= GtamTmp) {
	if( strlen(word) >= GtamTmp) {
		delete [] tmp;
		GtamTmp = strlen(stem) + strlen(suffix) + 1;
		tmp = new char [GtamTmp];
	}

	if ( strlen(word) <= strlen(suffix) )
		return(FALSE);
	if ( (strlen(suffix) > 1) &&
			( word[strlen(word)-2] != suffix[strlen(suffix)-2] ) )
		return(FALSE);
	strcpy ( stem, "" );
	strncat ( stem, word, strlen(word) - strlen(suffix) );
	strcpy ( tmp, stem );
	strcat ( tmp, suffix );
	if ( strcmp (  tmp, word ) == 0 )
		return(TRUE);
	else
		return(FALSE);
}

int stemmerPorter::cvc ( char *string )
{
	int length=strlen(string);
	if ( length < 3 )
		return(FALSE);
	if ( (vowel(string[length-1],string[length-2]) == FALSE)
			&& (string[length-1] != 'w')
			&& (string[length-1] != 'x')
			&& (string[length-1] != 'y')
			&& (vowel(string[length-2],string[length-3]) == TRUE)
			&& ( ( (length==3) && (vowel(string[0],'a') == FALSE) )
			|| (vowel(string[length-3],string[length-4])==FALSE) ) )
		return(TRUE);
	else
		return(FALSE);
}

int stemmerPorter::vowel ( char ch, char prev )
{
	switch ( ch ) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u': return(TRUE);
		case 'y': return( vowel(prev,'?') == TRUE );
		default : return(FALSE);
	}
return(TRUE);
}

int stemmerPorter::measure ( char *stem )
{
	register int i=0, count = 0;
	int length=strlen(stem);
	while ( i < length ) {
		for ( ; i < length ; i++ ) {
			if ( i > 0 ) {
				if ( vowel(stem[i],stem[i-1]) == TRUE )
					break;
			}
			else {	if ( vowel(stem[i],'a') == TRUE )
					break;
			}
		}
		for ( i++ ; i < length ; i++ ) {
			if ( i > 0 ) {
				if ( vowel(stem[i],stem[i-1]) == FALSE )
					break;
			}
			else {	if ( vowel(stem[i],'?') == FALSE )
					break;
			}
		}
		if ( i < length ) {
			count++;
			i++;
		}
	}
	return(count);
}

int stemmerPorter::contains_vowel ( char *word )
{
	register int i;
	for ( i=0 ; i < strlen(word) ; i++ )
		if ( i > 0 ) {
			if ( vowel(word[i],word[i-1]) == TRUE )
				return(TRUE);
		}
		else {	if ( vowel(word[0],'a') == TRUE )
				return(TRUE);
		}
	return(FALSE);
}

char * stemmerPorter::spanish_stemming (char word[])
{ 
int len = strlen (word)-1;
if (len > 3) {  
   removeSpanishAccent(word);
   if ((word[len]=='s') && (word[len-1]=='e') && (word[len-2]=='s') && (word[len-3]=='e')) {
         /*  corteses -> cortés  */
         word[len-1]='\0';
         return(word);
      }
   if ((word[len]=='s') && (word[len-1]=='e') && (word[len-2]=='c')) {
         word[len-2]='z';        /*  dos veces -> una vez  */
         word[len-1]='\0';
         return(word);
      }
   if (word[len]=='s') {  /*  ending with -os, -as  or -es */
      if (word[len-1]=='o' || word[len-1]=='a' || word[len-1]=='e' ) {
         word[len-1]='\0';  /*  remove -os, -as  or -es */
         return (word);
         }
      }
   if (word[len]=='o') {   /*  ending with  -o  */
      word[len]='\0';  
      return(word);
      }
   if (word[len]=='a') {   /*  ending with  -a  */
      word[len]='\0';  
      return(word);
      }
   if (word[len]=='e') {   /*  ending with  -e  */
      word[len]='\0';  
      return(word);
      }
   } /* end if (len > 3) */
return(word);         
}


char * stemmerPorter::removeSpanishAccent (char word[])
{ 
int len = strlen (word)-1;
int i;

   for(i=len; i>=0; i--) {
      if ((word[i]=='à') || (word[i]=='á') || (word[i]=='â') || (word[i]=='ä')) {
         word[i] = 'a';
         }
      if ((word[i]=='ò') || (word[i]=='ó') || (word[i]=='ô') || (word[i]=='ö')) {
         word[i] = 'o';
         }
      if ((word[i]=='è') || (word[i]=='é') || (word[i]=='ê') || (word[i]=='ë')) {
         word[i] = 'e';
         }
      if ((word[i]=='ù') || (word[i]=='ú') || (word[i]=='û') || (word[i]=='ü')) {
         word[i] = 'u';
         }
      if ((word[i]=='ì') || (word[i]=='í') || (word[i]=='î') || (word[i]=='ï')) {
         word[i] = 'i';
         }
      }
   return(word);
}
// ***********************************FIN ESPANOL


void stemmerPorter::stemmer(string  & cad, const int& numero)
  {
//A  char cadena[1000];

	if(cad.size() >= GtamCadena) {
		delete [] cadena;
		GtamCadena = cad.size() + 1;
		cadena = new char [GtamCadena];
	}

  strcpy(cadena, cad.c_str());

  switch(numero){
  case 1: //espanol
          cad = spanish_stemming(cadena);
     break;
  case 2: //ingleis
           strip_affixes(cadena);
//           cout << "STEMMER " << numero << ": pal: " << cad << " stem: " << cadena << endl;
	       cad = cadena;
     break;
  default:
           break;
   }
}

void stemmerPorter::stemmer(string  & cad, const int& numero, string & cadF)
{
	//A  char cadena[1000];

	if(cad.size() >= GtamCadena) {
		delete [] cadena;
		GtamCadena = cad.size() + 1;
		cadena = new char [GtamCadena];
	}

	strcpy(cadena, cad.c_str());

	switch(numero){
	case 1: //espanol
		cadF = spanish_stemming(cadena);
		break;
	case 2: //ingleis
		strip_affixes(cadena);
//		cout << "STEMMER " << numero << ": pal: " << cad << " stem: " << cadena << endl;
		cadF = cadena;
		break;
	default:
		cadF=cadena;
		break;
	}
}

void stemmerPorter::stemmer(char* & cad, const int& numero) {
	switch(numero){
	case 1: //espanol
		//      cad = spanish_stemming(cad);
		spanish_stemming(cad);
		break;
	case 2: //ingleis
		strip_affixes(cad);
		//           cout << "STEMMER " << numero << ": pal: " << cad << " stem: " << cadena << endl;
		//	       cad = cadena;
		break;
	default:
		break;
	}
}
          
void stemmerPorter::stemmer(char*  & cad, const int& numero, char*& cadF)
{
	if(cadF) {
		delete [] cadF;
	}
	cadF = new char[strlen(cad) + 1];
	strcpy(cadF, cad);
	stemmer(cadF, numero);
}
          
 
