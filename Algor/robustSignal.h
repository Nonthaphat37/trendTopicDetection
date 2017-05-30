#ifndef robustSignal_H
#define robustSignal_H

class robustSignal{

private:
	
public:
	vector<double> extractPN(vector<pair<double, double> > data){
		vector<double> P;
		for(int i=0;i<data.size();i++) P.push_back(data[i].second);
		return P;
	}

	vector<double> extractPBN(vector<double> P){
		vector<double> Pb;
		double b = 0;
		for(int i=0;i<P.size();i++) b += P[i];
		if(b == 0) b = 1;
		for(int i=0;i<P.size();i++) Pb.push_back(P[i]/b);
		return Pb;
	}

	vector<double> extractPBSN(vector<double> Pb, double alpha){
		vector<double> Pbs;
		for(int i=1;i<Pb.size();i++) Pbs.push_back( pow(abs(Pb[i]-Pb[i-1]), alpha) );
		return Pbs;
	}

	vector<double> extractPBSCN(vector<double> Pbs, int Ns){
		vector<double> Pbsc;
		int n = Pbs.size();
		int wz = Ns; // window size

		double sum = 0;
		for(int i=0;i<n;i++){
			if(i < wz-1) sum += Pbs[i];
			else{
				sum += Pbs[i];
				Pbsc.push_back(sum);
				sum -= Pbs[i-wz+1];
			}
		}
		return Pbsc;
	}

	vector<double> extractPBSCLN(vector<double> Pbsc){
		vector<double> Pbscl;
		for(int i=0;i<Pbsc.size();i++) Pbscl.push_back(log(Pbsc[i]==0.0?1.0:Pbsc[i]));

		for(int i=1;i<Pbscl.size();i++) if(Pbscl[i] == 0.0 || Pbscl[i] != Pbscl[i]) Pbscl[i] = Pbscl[i-1];
		for(int i=Pbscl.size()-2;i>=0;i--) if(Pbscl[i] == 0.0 || Pbscl[i] != Pbscl[i]) Pbscl[i] = Pbscl[i+1];

		return Pbscl;
	}

	vector<double> run(vector<pair<double, double> > data, double alpha, int Ns){
	 	vector<double> P = extractPN(data); // get p[n]
	 	vector<double> Pb = extractPBN(P); // get pb[n]
	 	vector<double> Pbs = extractPBSN(Pb, alpha); // get Pbs[n]
	 	vector<double> Pbsc = extractPBSCN(Pbs, Ns); // get Pbsc[n]
	 	// return Pbsc;
	 	vector<double> Pbscl = extractPBSCLN(Pbsc); // get Pbsc[n]
	 	return Pbscl;
	} 
};

#endif