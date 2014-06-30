/*
 * Kartya.h
 *
 *  Created on: 2012.05.15.
 *      Author: medwe
 */



#ifndef KARTYA_H_
#define KARTYA_H_

#include "macro.h"
#include <iostream>
using namespace std;

class Kartya {
private:
	int szam;
	int szin;
	static int sta_szam;
	static int sta_szin;
	int allapot;
	string nev;
public:
	Kartya();
	Kartya(int, int);

	int getSzam() const;
	void setSzam(int);
	int getSzin() const;
	void setSzin(int);

	static void ResetSta_szam();
	static void ResetSta_szin();

	int getAllapot() const;
	void setAllapot(int);

	void setNev();
	string getNev() const;

	virtual ~Kartya();
};

#endif /* KARTYA_H_ */
