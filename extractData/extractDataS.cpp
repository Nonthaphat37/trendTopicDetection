#include <bits/stdc++.h>

using namespace std;

#define MAXL 1000
#define SZPOST 8

string sentence;

string outdir = "output/";
// string outfiles[] = {"varnishncsa.log-20170128", "varnishncsa.log-20170129", "varnishncsa.log-20170130", "varnishncsa.log-20170131", "varnishncsa.log-20170201", "varnishncsa.log-20170202", "varnishncsa.log-20170203", "varnishncsa.log-20170204", "varnishncsa.log-20170205", "varnishncsa.log-20170206", "varnishncsa.log-20170207", "varnishncsa.log-20170208", "varnishncsa.log-20170209", "varnishncsa.log-20170210", "varnishncsa.log-20170211", "varnishncsa.log-20170212", "varnishncsa.log-20170213", "varnishncsa.log-20170214", "varnishncsa.log-20170215", "varnishncsa.log-20170216", "varnishncsa.log-20170217", "varnishncsa.log-20170218", "varnishncsa.log-20170219", "varnishncsa.log-20170220", "varnishncsa.log-20170221", "varnishncsa.log-20170222", "varnishncsa.log-20170223", "varnishncsa.log-20170224", "varnishncsa.log-20170225", "varnishncsa.log-20170226", "varnishncsa.log-20170227", "varnishncsa.log-20170228", "varnishncsa.log-20170301", "varnishncsa.log-20170302", "varnishncsa.log-20170303", "varnishncsa.log-20170304", "varnishncsa.log-20170305", "varnishncsa.log-20170306", "varnishncsa.log-20170307", "varnishncsa.log-20170308", "varnishncsa.log-20170309", "varnishncsa.log-20170310", "varnishncsa.log-20170311", "varnishncsa.log-20170312", "varnishncsa.log-20170313", "varnishncsa.log-20170314", "varnishncsa.log-20170315", "varnishncsa.log-20170316", "varnishncsa.log-20170317", "varnishncsa.log-20170318", "varnishncsa.log-20170319", "varnishncsa.log-20170320", "varnishncsa.log-20170321", "varnishncsa.log-20170322", "varnishncsa.log-20170323", "varnishncsa.log-20170324", "varnishncsa.log-20170325", "varnishncsa.log-20170326", "varnishncsa.log-20170327", "varnishncsa.log-20170328", "varnishncsa.log-20170329", "varnishncsa.log-20170330", "varnishncsa.log-20170331", "varnishncsa.log-20170401", "varnishncsa.log-20170402", "varnishncsa.log-20170403", "varnishncsa.log-20170404", "varnishncsa.log-20170405", "varnishncsa.log-20170406", "varnishncsa.log-20170407", "varnishncsa.log-20170408", "varnishncsa.log-20170409", "varnishncsa.log-20170410", "varnishncsa.log-20170411", "varnishncsa.log-20170412"};

string header = "IP-Address,Date,Seconds,GetURL,FromURL,GetTopic,FromTopic\n";

// string indir = "";
string infiles1 = "111";
string infiles2 = "222";

string logdir = "00_pts_project/pt_weblog/";
// string filelog[] = {"varnishncsa.log-20170128.gz", "varnishncsa.log-20170129.gz", "varnishncsa.log-20170130.gz", "varnishncsa.log-20170131.gz", "varnishncsa.log-20170201.gz", "varnishncsa.log-20170202.gz", "varnishncsa.log-20170203.gz", "varnishncsa.log-20170204.gz", "varnishncsa.log-20170205.gz", "varnishncsa.log-20170206.gz", "varnishncsa.log-20170207.gz", "varnishncsa.log-20170208.gz", "varnishncsa.log-20170209.gz", "varnishncsa.log-20170210.gz", "varnishncsa.log-20170211.gz", "varnishncsa.log-20170212.gz", "varnishncsa.log-20170213.gz", "varnishncsa.log-20170214.gz", "varnishncsa.log-20170215.gz", "varnishncsa.log-20170216.gz", "varnishncsa.log-20170217.gz", "varnishncsa.log-20170218.gz", "varnishncsa.log-20170219.gz", "varnishncsa.log-20170220.gz", "varnishncsa.log-20170221.gz", "varnishncsa.log-20170222.gz", "varnishncsa.log-20170223.gz", "varnishncsa.log-20170224.gz", "varnishncsa.log-20170225.gz", "varnishncsa.log-20170226.gz", "varnishncsa.log-20170227.gz", "varnishncsa.log-20170228.gz", "varnishncsa.log-20170301.gz", "varnishncsa.log-20170302.gz", "varnishncsa.log-20170303.gz", "varnishncsa.log-20170304.gz", "varnishncsa.log-20170305.gz", "varnishncsa.log-20170306.gz", "varnishncsa.log-20170307.gz", "varnishncsa.log-20170308.gz", "varnishncsa.log-20170309.gz", "varnishncsa.log-20170310.gz", "varnishncsa.log-20170311.gz", "varnishncsa.log-20170312.gz", "varnishncsa.log-20170313.gz", "varnishncsa.log-20170314.gz", "varnishncsa.log-20170315.gz", "varnishncsa.log-20170316.gz", "varnishncsa.log-20170317.gz", "varnishncsa.log-20170318.gz", "varnishncsa.log-20170319.gz", "varnishncsa.log-20170320.gz", "varnishncsa.log-20170321.gz", "varnishncsa.log-20170322.gz", "varnishncsa.log-20170323.gz", "varnishncsa.log-20170324.gz", "varnishncsa.log-20170325.gz", "varnishncsa.log-20170326.gz", "varnishncsa.log-20170327.gz", "varnishncsa.log-20170328.gz", "varnishncsa.log-20170329.gz", "varnishncsa.log-20170330.gz", "varnishncsa.log-20170331.gz", "varnishncsa.log-20170401.gz", "varnishncsa.log-20170402.gz", "varnishncsa.log-20170403.gz", "varnishncsa.log-20170404.gz", "varnishncsa.log-20170405.gz", "varnishncsa.log-20170406.gz", "varnishncsa.log-20170407.gz", "varnishncsa.log-20170408.gz", "varnishncsa.log-20170409.gz", "varnishncsa.log-20170410.gz", "varnishncsa.log-20170411.gz", "varnishncsa.log-20170412.gz", "varnishncsa.log-20170413.gz"};

// string startTimes[] = {"28/Jan/2017:00:00:00", "29/Jan/2017:00:00:00", "30/Jan/2017:00:00:00", "31/Jan/2017:00:00:00", "01/Feb/2017:00:00:00", "02/Feb/2017:00:00:00", "03/Feb/2017:00:00:00", "04/Feb/2017:00:00:00", "05/Feb/2017:00:00:00", "06/Feb/2017:00:00:00", "07/Feb/2017:00:00:00", "08/Feb/2017:00:00:00", "09/Feb/2017:00:00:00", "10/Feb/2017:00:00:00", "11/Feb/2017:00:00:00", "12/Feb/2017:00:00:00", "13/Feb/2017:00:00:00", "14/Feb/2017:00:00:00", "15/Feb/2017:00:00:00", "16/Feb/2017:00:00:00", "17/Feb/2017:00:00:00", "18/Feb/2017:00:00:00", "19/Feb/2017:00:00:00", "20/Feb/2017:00:00:00", "21/Feb/2017:00:00:00", "22/Feb/2017:00:00:00", "23/Feb/2017:00:00:00", "24/Feb/2017:00:00:00", "25/Feb/2017:00:00:00", "26/Feb/2017:00:00:00", "27/Feb/2017:00:00:00", "28/Feb/2017:00:00:00", "01/Mar/2017:00:00:00", "02/Mar/2017:00:00:00", "03/Mar/2017:00:00:00", "04/Mar/2017:00:00:00", "05/Mar/2017:00:00:00", "06/Mar/2017:00:00:00", "07/Mar/2017:00:00:00", "08/Mar/2017:00:00:00", "09/Mar/2017:00:00:00", "10/Mar/2017:00:00:00", "11/Mar/2017:00:00:00", "12/Mar/2017:00:00:00", "13/Mar/2017:00:00:00", "14/Mar/2017:00:00:00", "15/Mar/2017:00:00:00", "16/Mar/2017:00:00:00", "17/Mar/2017:00:00:00", "18/Mar/2017:00:00:00", "19/Mar/2017:00:00:00", "20/Mar/2017:00:00:00", "21/Mar/2017:00:00:00", "22/Mar/2017:00:00:00", "23/Mar/2017:00:00:00", "24/Mar/2017:00:00:00", "25/Mar/2017:00:00:00", "26/Mar/2017:00:00:00", "27/Mar/2017:00:00:00", "28/Mar/2017:00:00:00", "29/Mar/2017:00:00:00", "30/Mar/2017:00:00:00", "31/Mar/2017:00:00:00", "01/Apr/2017:00:00:00", "02/Apr/2017:00:00:00", "03/Apr/2017:00:00:00", "04/Apr/2017:00:00:00", "05/Apr/2017:00:00:00", "06/Apr/2017:00:00:00", "07/Apr/2017:00:00:00", "08/Apr/2017:00:00:00", "09/Apr/2017:00:00:00", "10/Apr/2017:00:00:00", "11/Apr/2017:00:00:00", "12/Apr/2017:00:00:00"};
// string endTimes[] = {"28/Jan/2017:23:59:59", "29/Jan/2017:23:59:59", "30/Jan/2017:23:59:59", "31/Jan/2017:23:59:59", "01/Feb/2017:23:59:59", "02/Feb/2017:23:59:59", "03/Feb/2017:23:59:59", "04/Feb/2017:23:59:59", "05/Feb/2017:23:59:59", "06/Feb/2017:23:59:59", "07/Feb/2017:23:59:59", "08/Feb/2017:23:59:59", "09/Feb/2017:23:59:59", "10/Feb/2017:23:59:59", "11/Feb/2017:23:59:59", "12/Feb/2017:23:59:59", "13/Feb/2017:23:59:59", "14/Feb/2017:23:59:59", "15/Feb/2017:23:59:59", "16/Feb/2017:23:59:59", "17/Feb/2017:23:59:59", "18/Feb/2017:23:59:59", "19/Feb/2017:23:59:59", "20/Feb/2017:23:59:59", "21/Feb/2017:23:59:59", "22/Feb/2017:23:59:59", "23/Feb/2017:23:59:59", "24/Feb/2017:23:59:59", "25/Feb/2017:23:59:59", "26/Feb/2017:23:59:59", "27/Feb/2017:23:59:59", "28/Feb/2017:23:59:59", "01/Mar/2017:23:59:59", "02/Mar/2017:23:59:59", "03/Mar/2017:23:59:59", "04/Mar/2017:23:59:59", "05/Mar/2017:23:59:59", "06/Mar/2017:23:59:59", "07/Mar/2017:23:59:59", "08/Mar/2017:23:59:59", "09/Mar/2017:23:59:59", "10/Mar/2017:23:59:59", "11/Mar/2017:23:59:59", "12/Mar/2017:23:59:59", "13/Mar/2017:23:59:59", "14/Mar/2017:23:59:59", "15/Mar/2017:23:59:59", "16/Mar/2017:23:59:59", "17/Mar/2017:23:59:59", "18/Mar/2017:23:59:59", "19/Mar/2017:23:59:59", "20/Mar/2017:23:59:59", "21/Mar/2017:23:59:59", "22/Mar/2017:23:59:59", "23/Mar/2017:23:59:59", "24/Mar/2017:23:59:59", "25/Mar/2017:23:59:59", "26/Mar/2017:23:59:59", "27/Mar/2017:23:59:59", "28/Mar/2017:23:59:59", "29/Mar/2017:23:59:59", "30/Mar/2017:23:59:59", "31/Mar/2017:23:59:59", "01/Apr/2017:23:59:59", "02/Apr/2017:23:59:59", "03/Apr/2017:23:59:59", "04/Apr/2017:23:59:59", "05/Apr/2017:23:59:59", "06/Apr/2017:23:59:59", "07/Apr/2017:23:59:59", "08/Apr/2017:23:59:59", "09/Apr/2017:23:59:59", "10/Apr/2017:23:59:59", "11/Apr/2017:23:59:59", "12/Apr/2017:23:59:59"};

string outfiles[] = {"varnishncsa.log-20170302", "varnishncsa.log-20170303", "varnishncsa.log-20170304", "varnishncsa.log-20170305", "varnishncsa.log-20170306", "varnishncsa.log-20170307", "varnishncsa.log-20170308", "varnishncsa.log-20170309", "varnishncsa.log-20170310", "varnishncsa.log-20170311", "varnishncsa.log-20170312", "varnishncsa.log-20170313", "varnishncsa.log-20170314", "varnishncsa.log-20170315", "varnishncsa.log-20170316", "varnishncsa.log-20170317", "varnishncsa.log-20170318", "varnishncsa.log-20170319", "varnishncsa.log-20170320", "varnishncsa.log-20170321", "varnishncsa.log-20170322", "varnishncsa.log-20170323", "varnishncsa.log-20170324", "varnishncsa.log-20170325", "varnishncsa.log-20170326", "varnishncsa.log-20170327", "varnishncsa.log-20170328", "varnishncsa.log-20170329", "varnishncsa.log-20170330", "varnishncsa.log-20170331", "varnishncsa.log-20170401", "varnishncsa.log-20170402", "varnishncsa.log-20170403", "varnishncsa.log-20170404", "varnishncsa.log-20170405", "varnishncsa.log-20170406", "varnishncsa.log-20170407", "varnishncsa.log-20170408", "varnishncsa.log-20170409", "varnishncsa.log-20170410", "varnishncsa.log-20170411", "varnishncsa.log-20170412"};
string filelog[] = {"varnishncsa.log-20170302.gz", "varnishncsa.log-20170303.gz", "varnishncsa.log-20170304.gz", "varnishncsa.log-20170305.gz", "varnishncsa.log-20170306.gz", "varnishncsa.log-20170307.gz", "varnishncsa.log-20170308.gz", "varnishncsa.log-20170309.gz", "varnishncsa.log-20170310.gz", "varnishncsa.log-20170311.gz", "varnishncsa.log-20170312.gz", "varnishncsa.log-20170313.gz", "varnishncsa.log-20170314.gz", "varnishncsa.log-20170315.gz", "varnishncsa.log-20170316.gz", "varnishncsa.log-20170317.gz", "varnishncsa.log-20170318.gz", "varnishncsa.log-20170319.gz", "varnishncsa.log-20170320.gz", "varnishncsa.log-20170321.gz", "varnishncsa.log-20170322.gz", "varnishncsa.log-20170323.gz", "varnishncsa.log-20170324.gz", "varnishncsa.log-20170325.gz", "varnishncsa.log-20170326.gz", "varnishncsa.log-20170327.gz", "varnishncsa.log-20170328.gz", "varnishncsa.log-20170329.gz", "varnishncsa.log-20170330.gz", "varnishncsa.log-20170331.gz", "varnishncsa.log-20170401.gz", "varnishncsa.log-20170402.gz", "varnishncsa.log-20170403.gz", "varnishncsa.log-20170404.gz", "varnishncsa.log-20170405.gz", "varnishncsa.log-20170406.gz", "varnishncsa.log-20170407.gz", "varnishncsa.log-20170408.gz", "varnishncsa.log-20170409.gz", "varnishncsa.log-20170410.gz", "varnishncsa.log-20170411.gz", "varnishncsa.log-20170412.gz", "varnishncsa.log-20170413.gz"};

string startTimes[] = {"02/Mar/2017:00:00:00", "03/Mar/2017:00:00:00", "04/Mar/2017:00:00:00", "05/Mar/2017:00:00:00", "06/Mar/2017:00:00:00", "07/Mar/2017:00:00:00", "08/Mar/2017:00:00:00", "09/Mar/2017:00:00:00", "10/Mar/2017:00:00:00", "11/Mar/2017:00:00:00", "12/Mar/2017:00:00:00", "13/Mar/2017:00:00:00", "14/Mar/2017:00:00:00", "15/Mar/2017:00:00:00", "16/Mar/2017:00:00:00", "17/Mar/2017:00:00:00", "18/Mar/2017:00:00:00", "19/Mar/2017:00:00:00", "20/Mar/2017:00:00:00", "21/Mar/2017:00:00:00", "22/Mar/2017:00:00:00", "23/Mar/2017:00:00:00", "24/Mar/2017:00:00:00", "25/Mar/2017:00:00:00", "26/Mar/2017:00:00:00", "27/Mar/2017:00:00:00", "28/Mar/2017:00:00:00", "29/Mar/2017:00:00:00", "30/Mar/2017:00:00:00", "31/Mar/2017:00:00:00", "01/Apr/2017:00:00:00", "02/Apr/2017:00:00:00", "03/Apr/2017:00:00:00", "04/Apr/2017:00:00:00", "05/Apr/2017:00:00:00", "06/Apr/2017:00:00:00", "07/Apr/2017:00:00:00", "08/Apr/2017:00:00:00", "09/Apr/2017:00:00:00", "10/Apr/2017:00:00:00", "11/Apr/2017:00:00:00", "12/Apr/2017:00:00:00"};
string endTimes[] = {"02/Mar/2017:23:59:59", "03/Mar/2017:23:59:59", "04/Mar/2017:23:59:59", "05/Mar/2017:23:59:59", "06/Mar/2017:23:59:59", "07/Mar/2017:23:59:59", "08/Mar/2017:23:59:59", "09/Mar/2017:23:59:59", "10/Mar/2017:23:59:59", "11/Mar/2017:23:59:59", "12/Mar/2017:23:59:59", "13/Mar/2017:23:59:59", "14/Mar/2017:23:59:59", "15/Mar/2017:23:59:59", "16/Mar/2017:23:59:59", "17/Mar/2017:23:59:59", "18/Mar/2017:23:59:59", "19/Mar/2017:23:59:59", "20/Mar/2017:23:59:59", "21/Mar/2017:23:59:59", "22/Mar/2017:23:59:59", "23/Mar/2017:23:59:59", "24/Mar/2017:23:59:59", "25/Mar/2017:23:59:59", "26/Mar/2017:23:59:59", "27/Mar/2017:23:59:59", "28/Mar/2017:23:59:59", "29/Mar/2017:23:59:59", "30/Mar/2017:23:59:59", "31/Mar/2017:23:59:59", "01/Apr/2017:23:59:59", "02/Apr/2017:23:59:59", "03/Apr/2017:23:59:59", "04/Apr/2017:23:59:59", "05/Apr/2017:23:59:59", "06/Apr/2017:23:59:59", "07/Apr/2017:23:59:59", "08/Apr/2017:23:59:59", "09/Apr/2017:23:59:59", "10/Apr/2017:23:59:59", "11/Apr/2017:23:59:59", "12/Apr/2017:23:59:59"};


class matchString{

private: 
	int prefixString[MAXL];

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
};

class manageDate{
// d = day, mo = month, y = year, h = hour, mi = minute, s = second
// ex. 04/Apr/2017:23:59:59, d/mo/y:h:mi:s

private:
	string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int days[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}; // feb -> 28 days
	map<string, int> changetoSec;

public:
	manageDate(){
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

	// 0 : Date1 = Date2
	// 1 : Date1 > Date2
	// 2 : Date1 < Date2
	int compareDate(string Date1, string Date2, string format){
		long long sec1 = getSecond(Date1, format);
		long long sec2 = getSecond(Date2, format);

		if(sec1 == sec2) return 0;
		else if(sec1 > sec2) return 1;
		return 2;
	}
};

matchString getMatch;
manageDate robustDate;

bool extractData(string sentence, ostream& ostream, int time_id){
	string IP_Addr, Date, url[2], topic[2];
	string writeFile = "";

	int idx[2];
	long long sec;

	IP_Addr = getMatch.getPrefixSpace(sentence);
	Date = getMatch.getPrefixSpace(getMatch.getPrefixBracket(sentence, '[', ']'));

	for(int i=0;i<2;i++){
		idx[i] = getMatch.getMatchString(sentence, "http");
		if(idx[i] == -1) continue;
		topic[i] = getMatch.getPrefixSpace(sentence.substr(idx[i]));
		if(topic[i].back() == '\"') topic[i].pop_back();
		if(topic[i].back() == '?') topic[i].pop_back();
		url[i] = getMatch.getTopicString(topic[i]);
		sentence = sentence.substr(idx[i]+1);
	}
	sec = robustDate.getSecond(Date, "d/mo/y:h:mi:s");

	if(robustDate.compareDate(Date, startTimes[time_id], "d/mo/y:h:mi:s") == 2) return 0;  // Date < startTimes .[]  :search continue
	else if(robustDate.compareDate(Date, endTimes[time_id], "d/mo/y:h:mi:s") == 1) return 1; // Date > endTimes  []. :search break

	writeFile = IP_Addr + ",";
	writeFile += Date + ",";
	writeFile += to_string(sec) + ",";

	for(int i=0;i<2;i++){
		if(idx[i] != -1) writeFile += topic[i] + ",";
		else writeFile += ",";
	}

	if(idx[0] != -1) writeFile += url[0] + ",";
	else writeFile += ",";
	if(idx[1] != -1) writeFile += url[1];
	writeFile += "\n";

  	ostream.write (writeFile.c_str(), writeFile.length());

  	return 0;
}

bool stream_reader(istream& istream, ostream& ostream, int time_id){
	getline(istream, sentence);
	return extractData(sentence, ostream, time_id);
}

void read(string infile1, string infile2, string outfile, int time_id){
	// extract
	string command = "gunzip -c " + infile1 + " > " + "111";
	system(command.c_str());
	command = "gunzip -c " + infile2 + " > " + "222";
	system(command.c_str());

	cout << infile1 << " " << infile2 << endl;

	int cnt = 0;
	ifstream ifile1(infiles1);
	ifstream ifile2(infiles2);
	if(ifile1.is_open() && ifile2.is_open()){
		ofstream ofile(outfile, ofstream::binary);
		ofile.write(header.c_str(), header.length());

		bool ok = 0;
		while(ifile1.good() && !ok) ok = stream_reader(ifile1, ofile, time_id);
		ok = 0;
		while(ifile2.good() && !ok) ok = stream_reader(ifile2, ofile, time_id);
		ifile1.close();
		ifile2.close();
  		ofile.close();
	}
	else cout << "Cannot access file" << endl;

	// remove
	command = "rm 111";
	system(command.c_str());
	command = "rm 222";
	system(command.c_str());
}

int main(int argc, char* argv[]){
	for(int i=0;i<(sizeof(filelog)/sizeof(*filelog))-1;i++) read(logdir+filelog[i], logdir+filelog[i+1], outdir+outfiles[i]+".csv", i);
}
	