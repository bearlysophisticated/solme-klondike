/*
 * Pakli.h
 *
 *  Created on: 2012.05.15.
 *      Author: medwe
 */

#ifndef PAKLI_H_
#define PAKLI_H_
#include "Kartya.h"
#include "time.h"
#include "stdlib.h"


class Pakli {
	Kartya** PAKLI;
public:
	Pakli();

	Kartya* getKartya(int) const;
	Kartya* getKartya(int, int) const;

	void kever();
	int rendez();

	virtual ~Pakli();
};

#endif /* PAKLI_H_ */
