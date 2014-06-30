/*
 * Pakli.cpp
 *
 *  Created on: 2012.05.15.
 *      Author: medwe
 */

#include "Pakli.h"

Pakli::Pakli() {
	PAKLI=new Kartya* [NUM_OF_CAR];
	for(int i=0; i<NUM_OF_CAR; i++){
		PAKLI[i]=new Kartya();
	}
}


Kartya* Pakli::getKartya(int index) const{
	return PAKLI[index];
}

Kartya* Pakli::getKartya(int szin, int szam) const{
	for(int i=0; i<NUM_OF_CAR; i++){
		if(PAKLI[i]->getSzin()==PAKLI[i]->getSzin() && PAKLI[i]->getSzam()==szam){
			return PAKLI[i];
		}
	}
	return NULL;
}

void Pakli::kever(){
	srand(time(NULL));
	int egyik;
	int masik;
	for(int i=0; i<NUM_OF_CAR*NUM_OF_CAR; i++){
		egyik=rand() % 52;
		do{
			masik=rand() % 52;
		}while(masik==egyik);
		Kartya* tmp;
		tmp=PAKLI[egyik];
		PAKLI[egyik]=PAKLI[masik];
		PAKLI[masik]=tmp;
	}
}

int Pakli::rendez(){
	Kartya* tmp;
	int p_n=0;
	for(int i=0; i<NUM_OF_CAR; i++){ if(PAKLI[i]->getAllapot()==pakliban){  p_n++; } }
	for(int k=0; k<NUM_OF_CAR-p_n; k++){
		for(int i=0; i<NUM_OF_CAR; i++){
			if(PAKLI[i]->getAllapot()!=pakliban){
				tmp=PAKLI[i];
				for(int j=i; j<NUM_OF_CAR-1; j++){
					PAKLI[j]=PAKLI[j+1];
				}
				PAKLI[NUM_OF_CAR-1]=tmp;
			}
		}
	}
	return p_n;
}

Pakli::~Pakli() {
	for(int i=0; i<NUM_OF_CAR; i++){
		delete PAKLI[i];
	}
	delete [] PAKLI;
}

