#ifndef manageString_H
#define manageString_H

class matchString{

private: 
	int prefixString[1000];
	const int SZPOST = 8;

public:
	matchString(){

	}

	void getPrefixString(string T){
		int i=1, j=0;
		while(i<T.length()){
			if(T[i] == T[j]) prefixString[i++] = (++j);
			else if(j != 0) j = prefixString[j-1];
			else prefixString[i++] = 0;
		}
	}

	int getMatchString(string S, string T){
		int i=0, j=0;
		getPrefixString(T);
		
		while(i<S.length()){
			if(S[i] == T[j]){
				i++, j++;
				if(j == T.length()) return i-T.length();
			}
			else if(j != 0) j = prefixString[j-1];
			else i++;
		}
		return -1;
	}

	string getPrefixSpace(string S){
		int i=0;
		string T="";
		while(i<S.length()){
			if(S[i] == ' ') return T;
			T += S[i];
			i++;
		}
		return "";
	}

	string getPrefixBracket(string S, char open, char close){
		int i=0;
		string T = "";
		bool begin = 0;
		while(i<S.length()){
		if(S[i] == open) begin = 1;
			else if(S[i] == close) return T;
			else if(begin) T += S[i];
			i++;
		}
		return "";
	}

	string getTopicString(string S){
		string posts = "";
		int idx = getMatchString(S, "topic/");
		if(idx == -1) return "";
		idx+=6;
		while(idx<S.length()){
			if('0' <= S[idx] && S[idx] <= '9') posts += S[idx];
			else break;
			idx++;
		}
		if(posts.length() == SZPOST && posts[0] == '3') return posts;
		return "";
	}

	vector<string> getSplitString(string S, char p){
		vector<string> res;
		string tmp = "";

		int last = 0;
		for(int i=0;i<S.length();i++){
			if(S[i] == p){
				tmp = S.substr(last, i-last);
				res.push_back(tmp);
				last = i+1;
			}
		}
		tmp = S.substr(last, S.length()-last);
		res.push_back(tmp);
		return res;
	}
};

class robustDate{
// d = day, mo = month, y = year, h = hour, mi = minute, s = second
// ex. 04/Apr/2017:23:59:59, d/mo/y:h:mi:s

private:
	string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int days[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}; // feb -> 28 days
	map<string, int> changetoSec;

public:
	robustDate(){
		changetoSec["s"] = 1;
		changetoSec["mi"] = 60;
		changetoSec["h"] = 3600;
		changetoSec["d"] = 86400;
		changetoSec["y"] = 0; // not ready to use
		for(int i=0;i<12;i++) changetoSec[months[i]] = days[i]*changetoSec["d"]; // calculate seconds each months
	}
	
	long long getSecond(string Date, string format){
		int l1=Date.length(), l2=format.length();
		int i=0, j=0;

		long long sec = 0;

		long long a, b, c, d, e;

		while(i<l1){
			if('a' <= format[j] && format[j] <= 'z'){
				if(format[j] == 'm'){
					if(format[j+1] == 'o'){
						string mt = Date.substr(i, 3);
						sec += changetoSec[mt];
						i+=3;
					}
					else{
						int tot = 0;
						while(i<l1 && '0'<=Date[i] && Date[i]<='9') tot = 10*tot + Date[i]-'0', i++;
						sec += tot*changetoSec["mi"];
					}
					j+=2;
				}
				else{
					string tp = format.substr(j, 1);
					int tot = 0;
					while(i<l1 && '0'<=Date[i] && Date[i]<='9') tot = 10*tot + Date[i]-'0', i++;
					if(tp == "d") tot--;
					sec += tot*changetoSec[tp];
					j++;
				}
			}
			else i++, j++;
		}
		return sec;
	}
};

#endif