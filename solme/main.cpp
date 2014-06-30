/*
 * main.cpp
 *
 *  Created on: 2012.05.15.
 *      Author: medwe
 */


#include "Kartya.h"
#include "Pakli.h"
#include "Asztal.h"
#include "UI.h"
#include <windows.h>


int Kartya::sta_szam=1;
int Kartya::sta_szin=1;



void Play(UI& u, Asztal& a, Pakli& p){
	string c="", /*funkcio*/  b="", /*honnan*/  d="", /*hova*/ e="" /*mennyit*/;

	a.IncAllGame();
	p.kever();
	a.leosztas();
	u.refresh(a);
	u.PrintTable();
	while(c!="0"){
		c="", b="", d="", e="";
		u.refresh(a);
		u.PrintTable();
		cin>>c;
		switch(c[0]){
			case '1': a.huzas(); break;																			    	//huz a paklibol
			case '2': cin>>d; a.lerak(d[0]-48); break;																	//lerak a paklibol az asztalra
			case '3': cin>>b; cin>>d; a.felrak(b[0]-48,d[0]-48); break;													//felrak a verembe (paklibol v asztalrol)
			case '4': cin>>b; cin>>d; a.atrak(b[0]-48,d[0]-48); break;													//oszlop kozott pakol
			case '5': cin>>b; cin>>d; cin>>e; if(e.length()<2){ a.atrak(b[0]-48,d[0]-48,e[0]-48); }						//csoportos atrakas
												else if(e.length()==2){ a.atrak_cs(b[0]-48,d[0]-48,(e[1]-48)+10); }
												break;
			case '6': cin>>b; cin>>d; a.lerak(b[0]-48,d[0]-48); break;													//verembol asztalra rak
			case '0': u.PrintConfirm(); while(b[0]-48>1 || b==""){ cin>>b; } if(b[0]-48==1){ break; } else if(b[0]-48==0){ c=""; } break;			//kilep
			default: break;
		}
		if(a.GameOver()){ c="0"; a.IncNyertGame(); u.PrintWin(); cin>>b; }
	}
	a.clear();
	u.clearA();
}

void Stat(UI &u, Asztal& a){
	char e='1', g='1';
	u.PrintStat();
	while(g!='0'){
		cin>>g;
		if(g=='1'){
			u.PrintConfirmStatDelete();
			cin>>e;
			if(e=='1'){
				a.ResetStat();
				u.PrintStat();
			}
			else if(e=='0'){ u.PrintStat(); }
		}
	}
}

void Set(UI &u, Asztal& a){
	char e='1';
	u.PrintSettings(a);
	while(e!='0'){
		cin>>e;
		a.SaveGameType(e-48); a.SetGameType();
		u.PrintSettings(a);
	}
}

void MainFunc(){
	UI u;
	Pakli p;
	Asztal a(p);

	bool exit=false;
	char f='1', g='1';
	while(exit==false){
		f='1', g='3';
		u.PrintMainScreen();
		cin>>f;
		if(f>='0' && f<'6'){
			switch(f){
			case '1': Play(u, a, p);  break;
			case '2': Stat(u, a); break;
			case '3': Set(u, a); break;
			case '4': system("help.txt"); break;
			case '5': u.PrintAbout(); while(g!='0'){ cin>>g; } break;
			case '0': u.PrintConfirm(); while(g>'1'){ cin>>g; } if(g=='1'){ exit=true; } else if(g=='0'){ exit=false; } break;
			default: break;
			}
		}
	}
}


int main(){


	MainFunc();


	return 0;
}
