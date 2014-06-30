/*
 * Kartya.cpp
 *
 *  Created on: 2012.05.15.
 *      Author: medwe
 */

#include "Kartya.h"


Kartya::Kartya() {
	if(sta_szam>13){ ResetSta_szam(); sta_szin++; }
	szam=sta_szam++;
	szin=sta_szin;
	allapot=pakliban;
	setNev();
}

Kartya::Kartya(int ujszam, int ujszin){
	szam=ujszam;
	szin=ujszin;
	allapot=pakliban;
	nev="";
}

int Kartya::getSzam() const{
	return szam;
}

void Kartya::setSzam(int ujszam){
	szam=ujszam;
}

int Kartya::getSzin() const{
	return szin;
}

void Kartya::setSzin(int ujszin){
	szin=ujszin;
}

void Kartya::ResetSta_szam(){
	sta_szam=1;
}

void Kartya::ResetSta_szin(){
	sta_szin=1;
}

int Kartya::getAllapot() const {
	return allapot;
}

void Kartya::setAllapot(int ujallapot){
	allapot=ujallapot;
}

void Kartya::setNev(){
	switch(szin){
	case 1: nev="o"; break;
	case 2: nev="p"; break;
	case 3: nev="k"; break;
	case 4: nev="t"; break;
	default: break;
	}
	if(szam<10 && szam>1){ nev+='0'+szam; }
	if(szam==1){ nev+='A'; }
	else{
		switch(szam){
		case 10: nev+="10"; break;
		case 11: nev+='J'; break;
		case 12: nev+='Q'; break;
		case 13: nev+='K'; break;
		default: break;
		}
	}
}

string Kartya::getNev() const{
	return nev;
}

Kartya::~Kartya() {
	ResetSta_szam();
	ResetSta_szin();
}

