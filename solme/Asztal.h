/*
 * Asztal.h
 *
 *  Created on: 2012.05.15.
 *      Author: medwe
 */

#ifndef ASZTAL_H_
#define ASZTAL_H_
#include "Pakli.h"
#include "Kartya.h"
#include <fstream>



class Asztal {
private:
	int pakli_num;
	int pi;
	int pi_t;
	int tmp_pi;
	int jatek_tipus;
	Pakli* P;
	Kartya*** JT;
	Kartya*** ASZOK;
	int* JT_ALLAPOT;
	int* ASZ_ALLAPOT;

public:
	Asztal();
	Asztal(Pakli&);
	virtual ~Asztal();

	void clear();
	void leosztas();
	Kartya* huzas();

	int get_JT_ALLAPOT(int) const;
	int get_ASZ_ALLAPOT(int) const;
	string getKartyaNev(char, int i=0, int j=0);
	int getKartyaSzin(char, int i=0, int j=0);

	bool lerak(int);					//paklibol oszlopba
	bool lerak(int,int);				//aszbol oszlopba
	bool felrak(int, int);				//oszlopbol aszra; paklibol aszra
	bool atrak(int, int, int ki=0);				//oszlopbol oszlopba
	bool atrak_cs(int, int, int);		//csoportos oszlopbol oszlopba

	bool GameOver();

	void ResetStat();
	void IncAllGame();
	void IncNyertGame();

	void SetGameType();
	void SaveGameType(int);
	int getGameType() const;

	int Sor(int);

};

#endif /* ASZTAL_H_ */
