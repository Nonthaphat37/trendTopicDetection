#include <bits/stdc++.h>

using namespace std;

#include "manageString.h"
#include "robustSignal.h"
#include "segmentedLeastSquares.h"
#include "classifyClass.h"

// parameter
const double C = 10.0;
const double alpha = 4; // parameter : spike-based transformation
const int Ns = 110; // parameter : Nsmooth [10, 80, 115, 150]
const double zeta = 1.0;
const double grammar = 25;

// call class
segmentedLeastSquares SLS;
robustSignal RS;
matchString MS;
classifyClass CC;

// input
string pathInputPos = "trend/";
string pathInputNeg = "notrend/";
string inputPos[] = {"1.in", "2.in", "3.in", "4.in", "5.in"};
string inputNeg[] = {"1.in", "2.in", "3.in"};

string pathInputObsPos = "InputTrend/";
string pathInputObsNeg = "InputNotrend/";
string inputObs[] = {"1.in", "2.in", "3.in", "4.in", "5.in", "6.in"};

vector<vector<double> > posClass;
vector<vector<double> > negClass;
string sentence;

void buildPosClass(){
	string inputPos[1500];
	for(int i=1;i<=1441;i++) inputPos[i] = to_string(i)+".txt";
	// for(int i=0;i<(sizeof(inputPos)/sizeof(*inputPos));i++){
	for(int i=1;i<=1441;i++){
		vector<pair<double, double> > data;
		data.clear();
		ifstream ifile(pathInputPos+inputPos[i]);
		if(ifile.is_open()){
			double cnt = 0;
			while(ifile.good()){
				getline(ifile, sentence);
				if(sentence.size() == 0) continue;
				vector<string> ex = MS.getSplitString(sentence, ' ');
				data.push_back(make_pair(atof(ex[0].c_str()), atof(ex[1].c_str())));
				cnt += atof(ex[1].c_str());
			}
			ifile.close();
			cout << "cntPos : " << cnt << endl;
			vector<double> Pbscl = RS.run(data, alpha, Ns);
			auto interval = SLS.run(Pbscl, C, 1);
			vector<double> tmp;
			tmp.clear();
			for(int i=interval.first;i<=interval.second;i++) tmp.push_back(Pbscl[i]);
			posClass.push_back(tmp);
		}
	}
}

void buildNegClass(){
	string inputNeg[5000];
	for(int i=1;i<=4445;i++) inputNeg[i] = to_string(i)+".txt";
	// for(int i=0;i<(sizeof(inputNeg)/sizeof(*inputNeg));i++){

	srand (time(NULL));

	bool checkrand[5000] = {0};
	memset(checkrand, 0, sizeof(checkrand));
	vector<int> v;
	v.clear();

	for(int i=1;i<=550;i++){
		int rd = rand()%4445 + 1;
		while(checkrand[rd]) rd = rand()%4445 + 1;
		checkrand[rd] = 1;
		v.push_back(rd);
	}

	for(int i=0;i<v.size();i++){
		int val = v[i];
		vector<pair<double, double> > data;
		data.clear();
		ifstream ifile(pathInputNeg+inputNeg[val]);
		if(ifile.is_open()){
			double cnt = 0;
			while(ifile.good()){
				getline(ifile, sentence);
				if(sentence.size() == 0) continue;
				vector<string> ex = MS.getSplitString(sentence, ' ');
				data.push_back(make_pair(atof(ex[0].c_str()), atof(ex[1].c_str())));
				cnt += atof(ex[1].c_str());
			}
			ifile.close();
			cout << "cntNeg : " << cnt << endl;
			vector<double> Pbscl = RS.run(data, alpha, Ns);
			auto interval = SLS.run(Pbscl, C, 0);
			vector<double> tmp;
			tmp.clear();
			for(int i=interval.first;i<=interval.second;i++) tmp.push_back(Pbscl[i]);
			negClass.push_back(tmp);
		}
	}
}

void classifyClass(){
	string inputObs[7000];
	for(int i=1;i<=6000;i++) inputObs[i] = to_string(i)+".txt";
	// for(int i=0;i<(sizeof(inputObs)/sizeof(*inputObs));i++){

	int coPos = 0;
	int woPos = 0;

	int coNeg = 0;
	int woNeg = 0;


	for(int i=1;i<=550;i++){
		vector<pair<double, double> > data;
		data.clear();
		ifstream ifile(pathInputObsPos+inputObs[i]);
		if(ifile.is_open()){
			while(ifile.good()){	
				getline(ifile, sentence);
				if(sentence.size() == 0) continue;
				vector<string> ex = MS.getSplitString(sentence, ' ');
				data.push_back(make_pair(atof(ex[0].c_str()), atof(ex[1].c_str())));
			}
			ifile.close();
			vector<double> Pbscl = RS.run(data, alpha, Ns);
			cout << CC.runAlgorithm(Pbscl, posClass, negClass, zeta, grammar) << endl;

			if(CC.runAlgorithm(Pbscl, posClass, negClass, zeta, grammar) == 1) coPos++, cout << "correctPos" << " " << coPos << " " << woPos << endl;
			else woPos++;
		}
	}

	int detectTopic = 0;
	int cntMAX = 0;

	for(int i=1;i<=1682;i++){
		vector<pair<double, double> > data;
		data.clear();
		ifstream ifile("111.txt");
		int cnt = 0;
		if(ifile.is_open()){
			while(ifile.good()){
				getline(ifile, sentence);
				if(sentence.size() == 0) continue;
				vector<string> ex = MS.getSplitString(sentence, ' ');
				data.push_back(make_pair(atof(ex[0].c_str()), atof(ex[1].c_str())));
				cnt += atoi(ex[1].c_str());
			}
			ifile.close();
			vector<double> Pbscl = RS.run(data, alpha, Ns);

			cout << CC.runAlgorithm(Pbscl, posClass, negClass, zeta, grammar) << endl;

			if(CC.runAlgorithm(Pbscl, posClass, negClass, zeta, grammar) == 0) coNeg++, cout << "correctNeg" << " " << coNeg << " " << woNeg << endl;
			else woNeg++;
			for(int i=0;i<Pbscl.size();i++) cout << Pbscl[i] << endl;
			auto interval = SLS.run(Pbscl, C, 0);
			for(auto x:interval){
				cout << x.first.first << " " << x.first.second << " " << x.second.first << " " << x.second.second << endl;
			}
		}

		if(cnt > cntMAX){
			cntMAX = cnt;
			detectTopic = i;
		}
	}

	int co = coPos+coNeg;
	int wo = woPos+woNeg;

	cout << "result " << endl;
	cout << "ResultPos : " << coPos << " " << woPos << " percent " << (coPos/(double)(coPos+woPos))*100 << endl;
	cout << "ResultNeg : " << coNeg << " " << woNeg << " percent " << (coNeg/(double)(coNeg+woNeg))*100 << endl;
	cout << coPos+coNeg << " " << woPos+woNeg << " " << (co/(double)(co+wo))*100 << endl;

	cout << detectTopic << endl;
}

int main(){
	buildPosClass();
	buildNegClass();
	classifyClass();
}