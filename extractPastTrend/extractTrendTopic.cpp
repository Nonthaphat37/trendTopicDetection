#include <bits/stdc++.h>

using namespace std;

// string curdir = "/Users/nonthaphat/Research/SeniorProject/new/extractPastTrend/";
// string csvpath = "/Users/nonthaphat/Research/SeniorProject/new/extractData/testAlgor/output/";

string curdir = "extractPastTrend/";
string csvpath = "output/";

string trendfile = "main.txt";
string logfile = "varnishncsa.log-";

// string datepath[] = {"1-2-2017-1700", "1-3-2017-0400", "1-4-2017-0000", "13-2-2017-0000", "14-2-2017-0000", "14-3-2017-0300", "15-2-2017-1800", "16-2-2017-1200", "16-3-2017-0200", "17-2-2017-0400", "17-3-2017-0200", "18-2-2017-0000", "19-3-2017-0000", "2-3-2017-1300", "2-4-2017-0100", "21-3-2017-0000", "22-3-2017-0200", "23-3-2017-0000", "24-3-2017-0100", "26-2-2017-0000", "26-3-2017-0100", "28-3-2017-0100", "3-3-2017-0200", "3-4-2017-0000", "30-3-2017-0000", "31-1-2017-2359", "31-3-2017-0200", "4-3-2017-0000", "4-4-2017-0000", "5-3-2017-0000", "5-4-2017-0000", "6-3-2017-0100", "6-4-2017-0000", "7-2-2017-1500", "7-4-2017-0000", "8-4-2017-0000",};
string datepath[] = {"10-4-2017-0000", "13-4-2017-0000", "16-4-2017-0000", "19-4-2017-0000", "3-4-2017-0000", "6-4-2017-0000", "9-4-2017-0000", "11-4-2017-0000", "14-4-2017-0000", "17-4-2017-0000", "2-4-2017-0100", "4-4-2017-0000", "7-4-2017-0000", "12-4-2017-0000", "15-4-2017-0000", "18-4-2017-0000", "20-4-2017-0000", "5-4-2017-0000", "8-4-2017-0000"};

string outputTrendPath = "InputTrend/";
string outputNoTrendPath = "InputNotrend/";
int outputTrend = 1;
int outputNoTrend = 1;

map<int, bool> trendTopic;
string sentence;

const int MAX_interval = 720;
map<int, int> freqTrend[MAX_interval+1];
map<int, int> freqNoTrend[MAX_interval+1];
set<int> getedTrendTopic;
set<int> getedNoTrendTopic;

map<int, bool> randomNum;

int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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

matchString MS;

int main(){
	srand(time(NULL));
	for(int i=0;i<sizeof(datepath)/sizeof(*datepath);i++){
		trendTopic.clear();
		for(int i=0;i<MAX_interval;i++) freqTrend[i].clear();
		for(int i=0;i<MAX_interval;i++) freqNoTrend[i].clear();
		getedTrendTopic.clear();
		getedNoTrendTopic.clear();

		randomNum.clear();
		for(int i=0;i<2500;i++) randomNum[rand()%100000000 + 1] = 1;

		string path = curdir+datepath[i]+"/"+trendfile;
		cout << ":path " << path << endl;
		
		ifstream ifile(path);
		if(ifile.is_open()){
			while(ifile.good()){
				getline(ifile, sentence);
				trendTopic[atoi(sentence.c_str())] = 1;
			}
			ifile.close();
		}
		else cout << "cannot open file1" << endl;

		// extract name log file
		vector<string> tmp = MS.getSplitString(datepath[i], '-');

		// string day = tmp[0];
		int iday = atoi(tmp[0].c_str());
		int imonth = atoi(tmp[1].c_str());
		iday--;
		if(iday == 0){
			imonth--;
			iday = maxday[imonth];
		}

		cout << "day month::: : " << iday << " " << imonth << " " << tmp[0] << endl;

		string day = to_string(iday);
		string month = to_string(imonth);
		string year = tmp[2];

		if(day.size() == 1) day = "0"+day;
		if(month.size() == 1) month = "0"+month;

		path = csvpath + logfile + year+month+day + ".csv";

		cout << path << endl;

		ifstream ifile2(path);

		int beginTime = 0;
		bool setTime = 0;

		if(ifile2.is_open()){
			int cnt = 0;
			while(ifile2.good()){
				getline(ifile2, sentence);
				if(sentence.size() < 10) continue;
				cnt++;
				if(cnt == 1) continue;
				vector<string> tmp = MS.getSplitString(sentence, ',');

				if(!setTime){
					beginTime = atoi(tmp[2].c_str());
					setTime = 1;
				}

				string getTopic = tmp[tmp.size()-2];
				if(getTopic.length() != 8) continue;
				int numTopic = atoi(getTopic.c_str());
				int curTime = atoi(tmp[2].c_str());
				int interval = (curTime-beginTime)/120;

				if(trendTopic.count(numTopic) == 0){
					if(getedNoTrendTopic.count(numTopic) == 0){
						if(randomNum.count(cnt) > 0){
							cout << numTopic << " " << interval << endl;
							getedNoTrendTopic.insert(numTopic);
							freqNoTrend[interval][numTopic]++;
						}
					}
					else{
						freqNoTrend[interval][numTopic]++;
					}
				}
				else{
					getedTrendTopic.insert(numTopic);
					freqTrend[interval][numTopic]++;
				}
			}
			ifile2.close();

			cout << "success" << endl;

			cout << "ok : " << path << " -> " << getedTrendTopic.size() << " - " << getedNoTrendTopic.size() << endl;

			for(auto x:getedNoTrendTopic){
				ofstream outfile( (outputNoTrendPath+to_string(outputNoTrend)+".txt").c_str(), std::ofstream::binary);
				for(int i=0;i<720;i++){
					int tmpFreq = 0;
					if(freqNoTrend[i].count(x)) tmpFreq = freqNoTrend[i][x];
					string writeString = to_string(i) + " " + to_string(tmpFreq) + "\n";
					outfile.write (writeString.c_str(), writeString.length());
				}
				outputNoTrend++;
				outfile.close();
			}
			for(auto x:getedTrendTopic){
				ofstream outfile( (outputTrendPath+to_string(outputTrend)+".txt").c_str(), std::ofstream::binary);
				for(int i=0;i<720;i++){
					int tmpFreq = 0;
					if(freqTrend[i].count(x)) tmpFreq = freqTrend[i][x];
					string writeString = to_string(i) + " " + to_string(tmpFreq) + "\n";
					outfile.write (writeString.c_str(), writeString.length());
				}
				outputTrend++;
				outfile.close();
			}
		}
		else cout << "cannot open file2" << endl;

	}
}