/*
 * UI.h
 *
 *  Created on: 2012.05.17.
 *      Author: medwe
 */

#ifndef UI_H_
#define UI_H_

#include "Asztal.h"
#include <stdio.h>
#include <fstream>
#include <windows.h>

class UI {
	string ** ASZTAL;
	int ** COLOR;

	string blank;
	string tab;
	string hatlap;

	int max_m;

	HANDLE hConsole;
public:
	UI();
	virtual ~UI();

	void clearA();
	void refresh(Asztal&);

	int MaxM(Asztal&);

	void PrintTable();
	void PrintLogo();
	void PrintMainScreen();
	void PrintLegend();
	void PrintAbout();
	void PrintWin();
	void PrintStat();
	void PrintConfirm();
	void PrintConfirmStatDelete();
	void PrintSettings(Asztal& a);
};

#endif /* UI_H_ */
