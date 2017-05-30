#ifndef classifyClass_H
#define classifyClass_H

class classifyClass{

private:

public:
	double Dist(vector<double> s, vector<double> t, int lo, int hi){
		double D = 0;
		for(int i=lo;i<=hi;i++) D += pow(s[i]-t[i-lo], 2);
		return D;
	}

	double ProbClass(vector<double> dist, double grammar){
		double P = 0;
		for(int i=0;i<dist.size();i++) P += exp(-grammar*dist[i]);
		return P;
	}	

	double DistToReference(vector<double> s, vector<double> r){
		int No = s.size();
		int Nr = r.size();

		double MinDist = INF;

		for(int i=Nr-1;i<No;i++) MinDist = min(MinDist, Dist(s, r, i-Nr+1, i));
		return MinDist;
	}

	bool runAlgorithm(vector<double> Observation, vector<vector<double> > Rp, vector<vector<double> > Rn, double zeta, double grammar){
		vector<double> posDist;
		vector<double> negDist;

		for(int i=0;i<Rp.size();i++) posDist.push_back(DistToReference(Observation, Rp[i]));
		for(int i=0;i<Rn.size();i++) negDist.push_back(DistToReference(Observation, Rn[i]));

		double posScore = ProbClass(posDist, grammar);
		double negScore = ProbClass(negDist, grammar);
		if(negScore == 0.0) negScore = 0.00001;
		// cout << "neh : " << negScore << endl;
		double R = posScore/negScore;
		cout << "R : " << R <<  " 1: " << posScore << " 2: " << negScore << " " << Rp.size() << " " << Rn.size() << endl;
		if(R > zeta) return 1;
		else return 0;
	}
};

#endif