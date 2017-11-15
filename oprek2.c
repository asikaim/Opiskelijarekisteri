#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

	char sukunimi[31];
	char etunimi[31];
	int opnro;
	int vuosi;

}Opiskelija_t;

void valikko(void);
void hakuvalikko(void);
int lueKokonaisluku(void);
void lisaaOpiskelija(void);
void selaa(void);
void etsi(void);
void tulostaOpiskelija(Opiskelija_t op);
Opiskelija_t lueOpiskelija(void);
void lueMerkkijono(char mjono[], int koko);
void lueRoskat(void);

int main(void){

	int loppu=0;
	int valinta;

	do{
		valikko();
		valinta = lueKokonaisluku();

		switch(valinta){
			case 1:
					lisaaOpiskelija();
				break;

			case 2:
					etsi();
				break;

			case 3:
					selaa();
				break;

			case 0: loppu=1;
				break;
		}

	}while(!loppu);

	return(0);
}

void lisaaOpiskelija(void){

	FILE * rekisteri = NULL;

	Opiskelija_t op;
	if((rekisteri=fopen("Opiskelijat.dat","a"))==NULL){
		printf("Virhe\n");
	}else{op = lueOpiskelija();
	fwrite(&op,sizeof(Opiskelija_t),1, rekisteri);
	fclose(rekisteri);
	}
}

Opiskelija_t lueOpiskelija(void){

	Opiskelija_t op;
	printf("\nAnna opiskelijan sukunimi \n");
	lueMerkkijono(op.sukunimi, 31);

	printf("Anna opiskelijan etunimi \n");
	lueMerkkijono(op.etunimi, 31);

	printf("Anna opiskelijanumero \n");
	op.opnro = lueKokonaisluku();

	printf("Anna kirjaitumisvuosi \n");
	op.vuosi = lueKokonaisluku();

	return op;
}

void etsi(void){

	int nrohaku = 0;
	char nimihaku[31];
	int hakuvalinta;
	int loytyi=0;

	FILE * rekisteri = NULL;
	Opiskelija_t op;

	hakuvalikko();	
	hakuvalinta = lueKokonaisluku();

	switch(hakuvalinta){	
		case 1:
				if((rekisteri = fopen("Opiskelijat.dat", "r"))==NULL){
					printf("Virhe");
				}else{
					printf("Anna haettavan opiskelijan sukunimi \n");
					lueMerkkijono(nimihaku, 31);
					fread(&op,sizeof(Opiskelija_t),1,rekisteri);

					while(!feof(rekisteri)){
						if(strcmp(nimihaku, op.sukunimi)==0){
							loytyi=1;
							tulostaOpiskelija(op);
						}
						fread(&op,sizeof(Opiskelija_t),1,rekisteri);
					}
					if(!loytyi){
						printf("Haulla ei löytynyt opiskelijaa.\n");
					}
					fclose(rekisteri);
				}
			break;
		case 2:
				if((rekisteri = fopen("Opiskelijat.dat", "r"))==NULL){
					printf("Virhe");
				}else{
					printf("Anna haettavan opiskelijan etunimi\n");
					lueMerkkijono(nimihaku, 31);
					fread(&op,sizeof(Opiskelija_t),1,rekisteri);

					while(!feof(rekisteri)){
						if(strcmp(nimihaku,op.etunimi)==0){
							loytyi=1;
							tulostaOpiskelija(op);
						}
						fread(&op,sizeof(Opiskelija_t),1,rekisteri);
					}
					if(!loytyi){
						printf("Haulla ei löytynyt opiskelijaa.\n");
					}
					fclose(rekisteri);
				}
			break;
		case 3:
			printf("Anna haettava opiskelijanumero\n");
			nrohaku = lueKokonaisluku();

				if((rekisteri = fopen("Opiskelijat.dat", "r"))==NULL){
					printf("Virhe");
				}else{
					printf("Anna haettava opiskelijanumero\n");
					nrohaku = lueKokonaisluku();
					fread(&op,sizeof(Opiskelija_t),1,rekisteri);

					while(!feof(rekisteri)){
						if(nrohaku == op.opnro){
							loytyi=1;
							tulostaOpiskelija(op);
						}
						fread(&op,sizeof(Opiskelija_t),1,rekisteri);
					}
					if(!loytyi)
						printf("Haulla ei löytynyt opiskelijaa.\n");
					fclose(rekisteri);
				}
			break;
		case 4:
				if((rekisteri = fopen("Opiskelijat.dat", "r"))==NULL){
					printf("Virhe");
				}else{
					printf("Anna haettavan opiskelijan aloitusvuosi\n");
					nrohaku = lueKokonaisluku();
					fread(&op,sizeof(Opiskelija_t),1,rekisteri);

					while(!feof(rekisteri)){
						if(nrohaku == op.vuosi){
							loytyi=1;
							tulostaOpiskelija(op);
						}
						fread(&op,sizeof(Opiskelija_t),1,rekisteri);
					}
					if(!loytyi)
						printf("Haulla ei löytynyt opiskelijaa.\n");
					fclose(rekisteri);
			break;
		}
	}
}

void selaa(void){

	FILE * rekisteri = NULL;
	Opiskelija_t op;
	if((rekisteri = fopen("Opiskelijat.dat", "r"))==NULL){
		printf("Virhe");
	}else{
		fread(&op,sizeof(Opiskelija_t),1,rekisteri);
		while(!feof(rekisteri)){
			tulostaOpiskelija(op);
			fread(&op,sizeof(Opiskelija_t),1,rekisteri);
		}
		fclose(rekisteri);
	}
}

void tulostaOpiskelija(Opiskelija_t op){

	printf("Sukunimi: %s\n", op.sukunimi);
	printf("Etunimi: %s\n", op.etunimi);
	printf("Opiskelijanumero: %d\n", op.opnro);
	printf("Aloitusvuosi: %d\n", op.vuosi);
	printf("\n");
}

void valikko(void){

	printf("\n1. Opiskelijan lisäys \n");
	printf("2. Haku \n");
	printf("3. Selaus \n");
	printf("0. Lopetus \n");
}

int lueKokonaisluku( void ){

	int luku;
	int result = 0;
	char merkki;

	while( (result=scanf("%d%c", &luku, &merkki) ) == 0 || ( result == 2 && merkki != '\n') ){
		printf("\nEt syottanyt kokonaislukua!\n");
		lueRoskat();
		printf("\nYrita uudelleen > ");
	}

	return luku;
}


void lueMerkkijono( char merkkijono[], int koko){
   
   fgets( merkkijono, koko, stdin );
   
   if( merkkijono[ strlen(merkkijono) -1 ] == '\n')
      merkkijono[ strlen(merkkijono) -1 ] = '\0';
   else
      lueRoskat();
   
}

void hakuvalikko(void){

	printf("\n1. Hae sukunimellä \n");
	printf("2. Hae etunimellä\n");
	printf("3. Hae opiskelijanumerolla\n");
	printf("4. Hae aloitusvuodella\n");
}

void lueRoskat(void){
   
   while( fgetc(stdin) != '\n');
   
}

