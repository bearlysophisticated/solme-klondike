/*
 * Asztal->cpp
 *
 *  Created on: 2012->05->15->
 *      Author: medwe
 */

#include "Asztal.h"

Asztal::Asztal() {
	pakli_num=0;
	pi=0;
	pi_t=2;
	tmp_pi=-1;
	P=NULL;
	jatek_tipus=1;

	SetGameType();

	JT=new Kartya** [JT_MAG_MAX];
	for(int i=0; i<JT_MAG_MAX; i++){
		JT[i]=new Kartya* [JT_SZEL];
	}

	ASZOK=new Kartya** [NUM_OF_COLCAR];
	for(int i=0; i<NUM_OF_COLCAR; i++){
		ASZOK[i]=new Kartya* [NUM_OF_ACE];
	}

	for(int i=0; i<NUM_OF_COLCAR; i++){
		for(int j=0; j<NUM_OF_ACE; j++){
			ASZOK[i][j]=NULL;
		}
	}

	for(int i=0; i<JT_MAG_MAX; i++){
		for(int j=0; j<JT_SZEL; j++){
			JT[i][j]=NULL;
		}
	}

	JT_ALLAPOT=new int [JT_SZEL];
	for(int i=0; i<JT_SZEL; i++){ JT_ALLAPOT[i]=JT_SZEL-i; }

	ASZ_ALLAPOT=new int [NUM_OF_ACE];
	for(int i=0; i<NUM_OF_ACE; i++){ ASZ_ALLAPOT[i]=0; }
}

Asztal::Asztal(Pakli& p) {
	pakli_num=NUM_OF_CAR;
	pi=-1;
	pi_t=-1;
	tmp_pi=-1;
	P=&p;
	jatek_tipus=1;

	SetGameType();

	JT=new Kartya** [JT_MAG_MAX];
	for(int i=0; i<JT_MAG_MAX; i++){
		JT[i]=new Kartya* [JT_SZEL];
	}

	ASZOK=new Kartya** [NUM_OF_COLCAR];
	for(int i=0; i<NUM_OF_COLCAR; i++){
		ASZOK[i]=new Kartya* [NUM_OF_ACE];
	}

	for(int i=0; i<NUM_OF_COLCAR; i++){
		for(int j=0; j<NUM_OF_ACE; j++){
			ASZOK[i][j]=NULL;
		}
	}

	for(int i=0; i<JT_MAG_MAX; i++){
		for(int j=0; j<JT_SZEL; j++){
			JT[i][j]=NULL;
		}
	}

	JT_ALLAPOT=new int [JT_SZEL];
	for(int i=0; i<JT_SZEL; i++){ JT_ALLAPOT[i]=JT_SZEL-i; }

	ASZ_ALLAPOT=new int [NUM_OF_ACE];
	for(int i=0; i<NUM_OF_ACE; i++){ ASZ_ALLAPOT[i]=0; }
}

void Asztal::clear(){
	for(int i=0; i<NUM_OF_CAR; i++){
		P->getKartya(i)->setAllapot(pakliban);
	}
	pakli_num=NUM_OF_CAR;

	for(int i=0; i<JT_MAG_MAX; i++){
		for(int j=0; j<JT_SZEL; j++){
			JT[i][j]=NULL;
		}
	}
	JT_ALLAPOT=new int [JT_SZEL];
	for(int i=0; i<JT_SZEL; i++){
		JT_ALLAPOT[i]=JT_SZEL-i;
	}

	for(int i=0; i<NUM_OF_COLCAR; i++){
		for(int j=0; j<NUM_OF_ACE; j++){
			ASZOK[i][j]=NULL;
		}
	}
	for(int i=0; i<NUM_OF_ACE; i++){
		ASZ_ALLAPOT[i]=0;
	}

	pi=-1;
	pi_t=-1;
	tmp_pi=-1;
}

void Asztal::SetGameType(){
	FILE* set_file;
	set_file=fopen("set.txt","r");
	if(set_file){
		fscanf(set_file, "%d", &jatek_tipus);
		if(jatek_tipus<1 || jatek_tipus>2){ jatek_tipus=1; }
		fclose(set_file);
	}
}

void Asztal::SaveGameType(int new_setting){
	FILE* set_file;
	set_file=fopen("set.txt","w");
	if(set_file){
		if(new_setting<3 && new_setting>0){
			fprintf(set_file, "%d", new_setting);
			fclose(set_file);
		}
	}
}

int Asztal::getGameType() const{
	return jatek_tipus;
}

void Asztal::leosztas(){
	int k=0;
	for(int i=0; i<JT_SZEL; i++){
		for(int j=0; j<JT_SZEL-i; j++){
			JT[i][j]=P->getKartya(k);
			JT[i][j]->setAllapot(kiosztott);
			P->getKartya(k++)->setAllapot(kiosztott);
		}
		JT[i][6-i]->setAllapot(felforditott);
		P->getKartya(k-1)->setAllapot(felforditott);
	}
	pakli_num=P->rendez();
}

Kartya* Asztal::huzas(){
	pakli_num=P->rendez();
	if(jatek_tipus==1){
		pi++;
		if(pi>=pakli_num){
			pi=-1;
		}
		if(pakli_num>0){
		return P->getKartya(pi);}
	}
	else if(jatek_tipus==2){
		pi_t+=3;
		if(pi_t>=pakli_num){
			if(pakli_num>=3){
				pi_t=-1;
			}
			else{
				pi_t=pakli_num-1;
			}
		}
		pi=pi_t;
		if(pakli_num>0){
		return P->getKartya(pi);}
	}
	return NULL;
}

int Asztal::get_JT_ALLAPOT(int index) const{
	return JT_ALLAPOT[index];
}

int Asztal::get_ASZ_ALLAPOT(int index) const{
	return ASZ_ALLAPOT[index];
}

string Asztal::getKartyaNev(char vezer, int i, int j){
	switch(vezer){
	case 'j': 	if(JT[i][j]){ if(JT[i][j]->getAllapot()!=felforditott){ return "[]";} else { return JT[i][j]->getNev(); } } break;
	case 'a': if(ASZOK[i][j]){ return ASZOK[i][j]->getNev(); } break;
	case 'p': if(pakli_num>0 && pi!=-1){ return P->getKartya(pi)->getNev(); } else if(pi==-1){ return "URES"; } else { return "URES"; } break;
	default: break;
	}
	return "   ";
}

int Asztal::getKartyaSzin(char vezer, int i, int j){
	switch(vezer){
	case 'j': 	if(JT[i][j]){ if(JT[i][j]->getAllapot()==felforditott){ return (JT[i][j]->getSzin()); } } break;
	case 'a': if(ASZOK[i][j]){ return ASZOK[i][j]->getSzin(); } break;
	case 'p': if(pakli_num>0 && pi!=-1){ return P->getKartya(pi)->getSzin(); } break;
	default: break;
	}
	return 0;
}

bool Asztal::lerak(int oszlop){			//paklibol oszlopba
	if(pi>=0){
		oszlop=7-oszlop;
		if(oszlop>=0 && oszlop<7){
			if(JT_ALLAPOT[oszlop]>0){
				if(JT[JT_ALLAPOT[oszlop]-1][oszlop]->getSzin()%2 != P->getKartya(pi)->getSzin()%2){
					if(JT[JT_ALLAPOT[oszlop]-1][oszlop]->getSzam() == P->getKartya(pi)->getSzam()+1){
						JT[JT_ALLAPOT[oszlop]][oszlop]=P->getKartya(pi);
						P->getKartya(pi)->setAllapot(felforditott);
						JT_ALLAPOT[oszlop]++;
						pakli_num=P->rendez();
						pi--;
						if(pi<-1){ pi=-1; }
						tmp_pi=pi;
						P->rendez();
						return true;
					}
				}
			}

			else if(P->getKartya(pi)->getSzam()==13){
				JT[JT_ALLAPOT[oszlop]][oszlop]=P->getKartya(pi);
				P->getKartya(pi)->setAllapot(felforditott);
				JT_ALLAPOT[oszlop]++;
				pakli_num=P->rendez();
				pi--;
				if(pi<-1){ pi=-1; }
				return true;
			}
		}
	}
	return false;
}

bool Asztal::lerak(int asz, int oszlop){		//aszrol oszlopba
	asz--, oszlop=7-oszlop;
	if(asz>=0 && asz<NUM_OF_ACE && oszlop>=0 && oszlop<JT_SZEL){
		if(ASZ_ALLAPOT[asz]>0){
			if(JT_ALLAPOT[oszlop]>0){
				if(ASZOK[ASZ_ALLAPOT[asz]-1][asz]->getSzin()%2 != JT[JT_ALLAPOT[oszlop]-1][oszlop]->getSzin()%2){
					if(ASZOK[ASZ_ALLAPOT[asz]-1][asz]->getSzam()+1 == JT[JT_ALLAPOT[oszlop]-1][oszlop]->getSzam()){
						JT[JT_ALLAPOT[oszlop]][oszlop]=ASZOK[ASZ_ALLAPOT[asz]-1][asz];
						ASZOK[ASZ_ALLAPOT[asz]-1][asz]=NULL;
						JT[JT_ALLAPOT[oszlop]][oszlop]->setAllapot(felforditott);
						JT_ALLAPOT[oszlop]++;
						ASZ_ALLAPOT[asz]--;
						return true;
					}
				}
			}
			else{
				if(ASZOK[ASZ_ALLAPOT[asz]-1][asz]->getSzam()==13){
					JT[JT_ALLAPOT[oszlop]][oszlop]=ASZOK[ASZ_ALLAPOT[asz]-1][asz];
					ASZOK[ASZ_ALLAPOT[asz]-1][asz]=NULL;
					JT[JT_ALLAPOT[oszlop]][oszlop]->setAllapot(felforditott);
					JT_ALLAPOT[oszlop]++;
					ASZ_ALLAPOT[asz]--;
				}
			}
		}
	}
	return false;
}

bool Asztal::felrak(int oszlop, int asz){
	asz--; oszlop=7-oszlop;
	if(oszlop>=0 && oszlop<7 && asz>=0 && asz<4){					//oszlopbol aszra
		if(JT_ALLAPOT[oszlop]>0){
			if(ASZ_ALLAPOT[asz]>0){
				if(ASZOK[ASZ_ALLAPOT[asz]-1][asz]->getSzin()==JT[JT_ALLAPOT[oszlop]-1][oszlop]->getSzin()){
					if(ASZOK[ASZ_ALLAPOT[asz]-1][asz]->getSzam()+1==JT[JT_ALLAPOT[oszlop]-1][oszlop]->getSzam()){
						ASZOK[ASZ_ALLAPOT[asz]][asz]=JT[JT_ALLAPOT[oszlop]-1][oszlop];
						ASZOK[ASZ_ALLAPOT[asz]][asz]->setAllapot(fekvo);
						if(JT_ALLAPOT[oszlop]>1){ JT[JT_ALLAPOT[oszlop]-2][oszlop]->setAllapot(felforditott); }
						JT[JT_ALLAPOT[oszlop]-1][oszlop]=NULL;
						JT_ALLAPOT[oszlop]--;
						ASZ_ALLAPOT[asz]++;
						return true;
					}
				}
			}
			else if(JT[JT_ALLAPOT[oszlop]-1][oszlop]->getSzam()==1){
				ASZOK[0][asz]=JT[JT_ALLAPOT[oszlop]-1][oszlop];
				ASZOK[0][asz]->setAllapot(fekvo);
				if(JT_ALLAPOT[oszlop]>1){ JT[JT_ALLAPOT[oszlop]-2][oszlop]->setAllapot(felforditott); }
				JT[JT_ALLAPOT[oszlop]-1][oszlop]=NULL;
				JT_ALLAPOT[oszlop]--;
				ASZ_ALLAPOT[asz]++;
				return true;
			}
		}
	}
	else if(asz>=0 && asz<4 && pi>-1){							//paklibol aszra
		oszlop=0;
		if(ASZ_ALLAPOT[asz]>0){
			if(ASZOK[ASZ_ALLAPOT[asz]-1][asz]->getSzin()==P->getKartya(pi)->getSzin()){
				if(ASZOK[ASZ_ALLAPOT[asz]-1][asz]->getSzam()+1==P->getKartya(pi)->getSzam()){
					ASZOK[ASZ_ALLAPOT[asz]][asz]=P->getKartya(pi);
					ASZOK[ASZ_ALLAPOT[asz]][asz]->setAllapot(fekvo);
					P->getKartya(pi)->setAllapot(fekvo);
					ASZ_ALLAPOT[asz]++;
					pi--; if(pi<-1){ pi=-1; }
					return true;
				}
			}
		}
		else if(P->getKartya(pi)->getSzam()==1){
			ASZOK[0][asz]=P->getKartya(pi);
			ASZOK[0][asz]->setAllapot(fekvo);
			P->getKartya(pi)->setAllapot(fekvo);
			ASZ_ALLAPOT[asz]++;
			pi--; if(pi<-1){ pi=-1; }
			return true;
		}
	}
	return false;
}

bool Asztal::atrak(int honnan_oszlop, int hova_oszlop, int ki){			//oszlopbol oszlopba
	honnan_oszlop=7-honnan_oszlop; hova_oszlop=7-hova_oszlop;
	if(honnan_oszlop>=0 && honnan_oszlop<7 && hova_oszlop>=0 && hova_oszlop<7){
		if(JT_ALLAPOT[honnan_oszlop]>0){
			if(JT_ALLAPOT[hova_oszlop]>0){
				if(JT[JT_ALLAPOT[honnan_oszlop]-1][honnan_oszlop]->getSzin()%2 != JT[JT_ALLAPOT[hova_oszlop]-1][hova_oszlop]->getSzin()%2){
					if(JT[JT_ALLAPOT[honnan_oszlop]-1][honnan_oszlop]->getSzam()+1==JT[JT_ALLAPOT[hova_oszlop]-1][hova_oszlop]->getSzam()){
						JT[JT_ALLAPOT[hova_oszlop]][hova_oszlop]=JT[JT_ALLAPOT[honnan_oszlop]-1][honnan_oszlop];
						JT[JT_ALLAPOT[honnan_oszlop]-1][honnan_oszlop]=NULL;
						if(JT_ALLAPOT[honnan_oszlop]>1){ JT[JT_ALLAPOT[honnan_oszlop]-2][honnan_oszlop]->setAllapot(felforditott); }
						JT_ALLAPOT[honnan_oszlop]--;
						JT_ALLAPOT[hova_oszlop]++;
						return true;
					}
				}
			}
			else{
				if(JT[JT_ALLAPOT[honnan_oszlop]-1][honnan_oszlop]->getSzam()==13){
					JT[JT_ALLAPOT[hova_oszlop]][hova_oszlop]=JT[JT_ALLAPOT[honnan_oszlop]-1][honnan_oszlop];
					JT[JT_ALLAPOT[honnan_oszlop]-1][honnan_oszlop]=NULL;
					if(JT_ALLAPOT[honnan_oszlop]>1){ JT[JT_ALLAPOT[honnan_oszlop]-2][honnan_oszlop]->setAllapot(felforditott); }
					JT_ALLAPOT[honnan_oszlop]--;
					JT_ALLAPOT[hova_oszlop]++;
					return true;
				}
			}
		}
	}
	if(ki>0 && ki<=JT_ALLAPOT[honnan_oszlop] && Sor(honnan_oszlop)>=ki && honnan_oszlop>=0 && honnan_oszlop<7 && hova_oszlop>=0 && hova_oszlop<7){
		if(honnan_oszlop>=0 && honnan_oszlop<7 && hova_oszlop>=0 && hova_oszlop<7){
			if(JT_ALLAPOT[honnan_oszlop]>0){
				if(JT_ALLAPOT[hova_oszlop]>0){
					if(JT[JT_ALLAPOT[honnan_oszlop]-ki][honnan_oszlop]->getSzin()%2 != JT[JT_ALLAPOT[hova_oszlop]-1][hova_oszlop]->getSzin()%2){
						if(JT[JT_ALLAPOT[honnan_oszlop]-ki][honnan_oszlop]->getSzam()+1==JT[JT_ALLAPOT[hova_oszlop]-1][hova_oszlop]->getSzam()){
							for(int i=0; i<ki; i++){
								JT[JT_ALLAPOT[hova_oszlop]+i][hova_oszlop]=JT[(JT_ALLAPOT[honnan_oszlop]-ki)+i][honnan_oszlop];
							}
							if(JT_ALLAPOT[honnan_oszlop]>ki){ JT[JT_ALLAPOT[honnan_oszlop]-ki-1][honnan_oszlop]->setAllapot(felforditott); }
							JT_ALLAPOT[honnan_oszlop]-=ki;
							JT_ALLAPOT[hova_oszlop]+=ki;
							return true;
						}
					}
				}
				else{
					if(JT[JT_ALLAPOT[honnan_oszlop]-ki][honnan_oszlop]->getSzam()==13){
						for(int i=0; i<ki; i++){
							JT[JT_ALLAPOT[hova_oszlop]+i][hova_oszlop]=JT[(JT_ALLAPOT[honnan_oszlop]-ki)+i][honnan_oszlop];
						}
						if(JT_ALLAPOT[honnan_oszlop]>ki){ JT[JT_ALLAPOT[honnan_oszlop]-ki-1][honnan_oszlop]->setAllapot(felforditott); }
						JT_ALLAPOT[honnan_oszlop]-=ki;
						JT_ALLAPOT[hova_oszlop]+=ki;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Asztal::atrak_cs(int honnan_oszlop, int hova_oszlop, int ki){
	honnan_oszlop=7-honnan_oszlop; hova_oszlop=7-hova_oszlop;

	return false;
}

int Asztal::Sor(int oszlop){
	int hossz=1;
	for(int i=0; i<JT_ALLAPOT[oszlop]-1; i++){
		if(JT[JT_ALLAPOT[oszlop]-1-i][oszlop]->getAllapot()!=leforditott){
			if(JT[JT_ALLAPOT[oszlop]-1-i][oszlop]->getSzam()+1==JT[JT_ALLAPOT[oszlop]-2-i][oszlop]->getSzam()){
				hossz++;
			}
		}
	}
	return hossz;
}

bool Asztal::GameOver(){
	int go=0;
	for(int i=0; i<NUM_OF_ACE; i++){
		if(ASZ_ALLAPOT[i]>=13){ go++; }
	}
	if(go==4){ return true; }
	return false;
}

void Asztal::ResetStat(){
	FILE* stat_file;
	stat_file=fopen("stat.txt","w");
	fprintf(stat_file, "%d\n%d", 0, 0);
	fclose(stat_file);
}

void Asztal::IncAllGame(){
	FILE* stat_file;
	int a,b;
	stat_file=fopen("stat.txt", "r");
	fscanf(stat_file, "%d\n%d", &a, &b);
	fclose(stat_file);
	stat_file=fopen("stat.txt","w");
	fprintf(stat_file, "%d\n%d", a+1, b);
	fclose(stat_file);
}

void Asztal::IncNyertGame(){
	FILE* stat_file;
	int a,b;
	stat_file=fopen("stat.txt", "r");
	fscanf(stat_file, "%d\n%d", &a, &b);
	fclose(stat_file);
	stat_file=fopen("stat.txt","w");
	fprintf(stat_file, "%d\n%d", a, b+1);
	fclose(stat_file);
}

Asztal::~Asztal() {
	P=NULL;
	for(int i=0; i<JT_MAG_MAX; i++){
		delete [] JT[i];
	}
	delete [] JT;
	for(int i=0; i<NUM_OF_ACE; i++){
		delete [] ASZOK[i];
	}
	delete [] ASZOK;
	delete [] JT_ALLAPOT;
	delete [] ASZ_ALLAPOT;
}

