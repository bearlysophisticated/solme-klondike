/*
 * UI.cpp
 *
 *  Created on: 2012.05.17.
 *      Author: medwe
 */

#include "UI.h"

UI::UI() {
	max_m=0;
	blank="   ";
	tab="\t";
	hatlap="[] ";
	ASZTAL=new string* [M];
	for(int i=0; i<M; i++){
		ASZTAL[i]=new string [SZ];
	}
	for(int i=0; i<M; i++){
		for(int j=0; j<SZ; j++){
			ASZTAL[i][j]=blank;
		}
	}

	COLOR=new int* [M];
	for(int i=0; i<M; i++){
		COLOR[i]=new int [SZ];
	}
	for(int i=0; i<M; i++){
		for(int j=0; j<SZ; j++){
			COLOR[i][j]=7;
		}
	}

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
}

void UI::clearA(){
	for(int i=0; i<M; i++){
		for(int j=0; j<SZ; j++){
			ASZTAL[i][j]=blank;
		}
	}
	for(int i=0; i<M; i++){
		for(int j=0; j<SZ; j++){
			COLOR[i][j]=7;
		}
	}
	max_m=0;
}

void UI::refresh(Asztal& a){
	for(int i=0; i<M; i++){
		for(int j=0; j<SZ; j++){
			ASZTAL[i][j]=blank;
		}
	}

	ASZTAL[0][0]="  "; ASZTAL[0][1]=" "; ASZTAL[0][2]="(0)";
	if(a.getKartyaNev(V_PAKLI)!="URES"){	ASZTAL[1][0]=hatlap; ASZTAL[1][1]=" "; COLOR[1][2]=a.getKartyaSzin(V_PAKLI); ASZTAL[1][2]=a.getKartyaNev(V_PAKLI);	}
	else{	ASZTAL[1][0]=hatlap; ASZTAL[1][1]=" "; ASZTAL[1][2]="[x]";	COLOR[1][2]=7; }

	for(int i=0; i<4; i++){
		ASZTAL[0][6+2*i]="(";
		ASZTAL[0][6+2*i]+='1'+i;
		ASZTAL[0][6+2*i]+=")";
	}
	if(a.get_ASZ_ALLAPOT(0)>0){ COLOR[1][6]=a.getKartyaSzin(V_ASZ, a.get_ASZ_ALLAPOT(0)-1, 0);  ASZTAL[1][6]=a.getKartyaNev(V_ASZ, a.get_ASZ_ALLAPOT(0)-1, 0); } else{ ASZTAL[1][6]=hatlap; }
	if(a.get_ASZ_ALLAPOT(1)>0){ COLOR[1][8]=a.getKartyaSzin(V_ASZ, a.get_ASZ_ALLAPOT(1)-1, 1);  ASZTAL[1][8]=a.getKartyaNev(V_ASZ, a.get_ASZ_ALLAPOT(1)-1, 1); } else{ ASZTAL[1][8]=hatlap; }
	if(a.get_ASZ_ALLAPOT(2)>0){ COLOR[1][10]=a.getKartyaSzin(V_ASZ, a.get_ASZ_ALLAPOT(2)-1, 2); ASZTAL[1][10]=a.getKartyaNev(V_ASZ, a.get_ASZ_ALLAPOT(2)-1, 2); } else{ ASZTAL[1][10]=hatlap; }
	if(a.get_ASZ_ALLAPOT(3)>0){ COLOR[1][12]=a.getKartyaSzin(V_ASZ, a.get_ASZ_ALLAPOT(3)-1, 3); ASZTAL[1][12]=a.getKartyaNev(V_ASZ, a.get_ASZ_ALLAPOT(3)-1, 3); } else{ ASZTAL[1][12]=hatlap; }

	int k=SZ-1;
	for(int j=0; j<7; j++){
		if(a.get_JT_ALLAPOT(j)>0){
			for(int i=0; i<a.get_JT_ALLAPOT(j); i++){
				ASZTAL[4+i][k]=a.getKartyaNev(V_JT,i,j);
				COLOR[4+i][k]=a.getKartyaSzin(V_JT,i,j);
				if(ASZTAL[4+i][k].length()==2){ ASZTAL[2+i][k]+=' '; }
			}
		}
		else{ ASZTAL[3][k]="| |"; }
		k-=2;
	}
	for(int i=2; i<M; i++){
		for(int j=1; j<SZ; j+=2){
			ASZTAL[i][j]="\t";
		}
	}
	k=0;
	for(int i=0; i<SZ; i+=2){
		ASZTAL[3][i]="(";
		ASZTAL[3][i]+='1'+k;
		ASZTAL[3][i]+=")";
		k++;
	}
	for(int i=0; i<3; i++){
		ASZTAL[1][3+i]="\t";
		ASZTAL[0][3+i]="\t";
	}
	max_m=MaxM(a)+4;
}

int UI::MaxM(Asztal& a){
	int max=a.get_JT_ALLAPOT(0);
	for(int i=1; i<7; i++){
		if(a.get_JT_ALLAPOT(i)>max){ max=a.get_JT_ALLAPOT(i); }
	}
	return max;
}

void UI::PrintTable(){
	PrintLogo();
	for(int i=0; i<max_m; i++){
		cout<<"\t\t";
		for(int j=0; j<SZ; j++){
			SetConsoleTextAttribute(hConsole, 7);
			if(COLOR[i][j]>0 && COLOR[i][j]<5){
				if(COLOR[i][j]==1 || COLOR[i][j]==3){ SetConsoleTextAttribute(hConsole, 12); }
				else if(COLOR[i][j]==2 || COLOR[i][j]==4){ SetConsoleTextAttribute(hConsole, 8); }
			}
			cout<<ASZTAL[i][j];
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout<<endl<<endl;
	}
	PrintLegend();
}

void UI::PrintLogo(){
	system("CLS");
	SetConsoleTextAttribute(hConsole, 2);
	cout<<"\n\n\t\t\t\t :::::::::::::\n";
	cout<<"\t\t\t\t ::: SolMe :::\n";
	cout<<"\t\t\t\t :::::::::::::\n\n\n\n";
	SetConsoleTextAttribute(hConsole, 7);
}

void UI::PrintAbout(){
	PrintLogo();
	cout<<"\t\t\t\tSolMe "<<V_NUM<<" Beta\n\n";
	cout<<"\t\t\t\t2012 mLab\n\n\n\n";
	cout<<"\t\t\t\t\t\tVissza a menube (0)\n";
}

void UI::PrintLegend(){
	cout<<"\n\n\n";
	cout<<"\t\t(1) Huz\n";
	cout<<"\t\t(2) Paklibol az asztalra tesz\n";
	cout<<"\t\t(3) Verembe tesz\n";
	cout<<"\t\t(4) Mozgatas az asztalon\n";
	cout<<"\t\t(5) Csoportos mozgatas az asztalon\n";
	cout<<"\t\t(6) Verembol az asztalra tesz\n";
	cout<<"\t\t(0) Kilepes a menube\n";
}

void UI::PrintMainScreen(){
	SetConsoleTitleA("SolMe");
	PrintLogo();
	cout<<"\t\t\t\t   START (1)\n\n";
	cout<<"\t\t\t\tStatisztika (2)\n";
	cout<<"\t\t\t\tBeallitasok (3)\n\n\n\n\n\n";
	cout<<"\t\tSugo (4)\n";
	cout<<"\t\tNevjegy (5)";
	cout<<"\t\t\t   Kilepes (0)\n";
}

void UI::PrintWin(){
	system("CLS");
	string** WIN;
	WIN=new string* [SZ];
	for(int i=0; i<SZ; i++){
		WIN[i]=new string [SZ-4];
		for(int j=0; j<SZ-4; j++){
			WIN[i][j]="*\t";
		}
	}
	WIN[SZ/2][(SZ-4)/2-1]="     NYER";
	WIN[SZ/2][(SZ-4)/2]="TEL!\t";
	WIN[SZ/2][(SZ-4)/2+1]="\t";
	cout<<"\n\n\n\n";
	for(int i=0; i<SZ; i++){
		cout<<"\t";
		for(int j=0; j<SZ-4; j++){
			if(WIN[i][j]!="*\t"){ SetConsoleTextAttribute(hConsole, 9); }
			cout<<WIN[i][j];
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout<<endl<<endl;
	}
}

void UI::PrintStat(){
	FILE* stat_file;
	stat_file=fopen("stat.txt","r");
	int a,b;
	double c=0;
	fscanf(stat_file, "%d\n%d", &a, &b);
	if(!(a==0 && b==0)){ c=((double)b/(double)a)*100; }
	PrintLogo();
	cout<<"\t\t\tOsszes jatszma:\t\t"<<a<<endl;
	cout<<"\t\t\tNyert jatszmak:\t\t"<<b<<endl;
	cout<<"\t\t\tVesztett jatszmak:\t"<<a-b<<endl;
	cout<<"\t\t\tNyeresi arany:\t\t";
	printf("%.2f%%\n", c);
	cout<<"\t\t\tVesztesi arany:\t\t";
	printf("%.2f%%\n", 100-c);
	cout<<"\n\n\n\n\n\tStatisztikak torlese (1)\t\t Vissza a menube (0)\n";
}

void UI::PrintConfirm(){
	PrintLogo();
	cout<<"\t\t\t   Tenyleg ki akarsz lepni?\n\n\n";
	cout<<"\t\t\t      Igen (1)\tNem(0)"<<endl;
}

void UI::PrintConfirmStatDelete(){
	PrintLogo();
	cout<<"\t\t   Tenyleg torolni akarod a statisztikakat?\n\n\n";
	cout<<"\t\t\t      Igen (1)\tNem(0)"<<endl;
}

void UI::PrintSettings(Asztal& a){
	PrintLogo();
	cout<<"\t\t\t\tNehezseg:\n\n";
	cout<<"\t\t\t["; if(a.getGameType()==1){ cout<<"X]\t"; } else{ cout<<" ]\t"; } cout<<"Egyesevel huz (1)\n";
	cout<<"\t\t\t["; if(a.getGameType()==2){ cout<<"X]\t"; } else{ cout<<" ]\t"; } cout<<"Harmasaval huz (2)\n";
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tVissza a menube (0)\n";
}

UI::~UI() {
	for(int i=0; i<M; i++){
		delete [] ASZTAL[i];
	}
	delete [] ASZTAL;
}

