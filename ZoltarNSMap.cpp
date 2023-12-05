#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <limits>

using namespace std;

struct JobData {
    string areaTitle;
    string primState;
    string naics;
    string naicsTitle;
    string occTitle;
    string totEmp;
    string hMean;
    string aMean;
    string aPct10;
    string aPct25;
    string aMedian;
    string aPct75;
    string aPct90;
};

string IndustryTranslator(string industry){
    if (industry == "1")
        return industry = "11";
    else if (industry == "2")
        return industry = "21";
    else if (industry == "3")
        return industry = "22";
    else if (industry == "4")
        return industry = "23";
    else if (industry == "5")
        return industry = "31";
    else if (industry == "6")
        return industry = "32";
    else if (industry == "7")
        return industry = "33";
    else if (industry == "8")
        return industry = "42";
    else if (industry == "9")
        return industry = "44";
    else if (industry == "10")
        return industry = "45";
    else if (industry == "11")
        return industry = "48";
    else if (industry == "12")
        return industry = "49";
    else if (industry == "13")
        return industry = "51";
    else if (industry == "14")
        return industry = "52";
    else if (industry == "15")
        return industry = "53";
    else if (industry == "16")
        return industry = "54";
    else if (industry == "17")
        return industry = "55";
    else if (industry == "18")
        return industry = "56";
    else if (industry == "19")
        return industry = "61";
    else if (industry == "20")
        return industry = "62";
    else
        return industry = "0";
    }


void inCSV(const string& filename, map<string, string>& jobMap, string industry, string state) {
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens[4].substr(0, 2) == industry && tokens[3] == state){
            if (tokens.size() >= 27) {
                JobData job;
                job.occTitle = tokens[9];
                job.aMean = tokens[17];
                jobMap.insert(make_pair(job.occTitle, job.aMean)); 
            }
        }
    }
}


void NameAndSalary(map<string, string>& jobMap){
    vector<string> name, salary;
    for (auto it = jobMap.begin(); it != jobMap.end(); ++it) {
        name.push_back(it->first);
        salary.push_back(it->second);
        cout << "Name of the position: " << it->first << ", Average annual salary: " << it->second << endl; 
    }

}
int main() {
    map<string, string> jobMap;

    int minSalary, maxSalary;
    string industry, state;

    cout << "Enter Industry (1-20): ";
    cin >> industry;

    industry = IndustryTranslator(industry); 

    cout << "Enter State (e.g., FL, KY, WA): ";
    cin >> state;

    //cout << "Enter Minimum Salary: ";
    //cin >> minSalary;

    //cout << "Enter Maximum Salary: ";
    //cin >> maxSalary;
    
    inCSV("2022LaborData.csv", jobMap, industry, state);
    NameAndSalary(jobMap);

    return 0;
}