#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include "SortAlgorithms.cpp"

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

string IndustryTranslator(string industry) {
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

void inCSV(const string& filename, map<string, int>& jobMap, string industry, string state) {
    ifstream file(filename);
    string line;
    vector<string> tokens;
    vector<string> name, salary;
    JobData job;

    if (!file){
        cout << "File not found" << endl;
        return;
    }

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        while (getline(ss, token, '\n')) {
            tokens.push_back(token);
        }

        cout << tokens[1].substr(0, 2) << endl;
        cout << industry << endl;
        cout << tokens[0] << endl;
        cout << state << endl;
            if (tokens[1].substr(0, 2) == industry && tokens[0] == state) {
                JobData job;
                job.occTitle = tokens[2];
                job.aMean = tokens[3];
                cout << job.occTitle.size() << endl;  
                cout << job.aMean.size() << endl;
                cout << "Name of the position: " << job.occTitle << ", Average annual salary: " << job.aMean << endl;
                jobMap.insert(make_pair(job.occTitle, stoi(job.aMean)));
                tokens.clear();
        }
    }
}

void printResults(vector<Job>& results) {
    cout << "Top 10 Occupations by Salary:\n";

    // Print first 10 results
    for (int i = 0; i < 10; i++) {
        cout << results.at(i).jobTitle << ": $" << results.at(i).salary << "\n";
    }

    cout << "\nBottom 10 Occupations by Salary:\n";

    // Print last 10 results
    for (int i = results.size() - 1; i > results.size() - 11; i--) {
        cout << results.at(i).jobTitle << ": $" << results.at(i).salary << "\n";
    }
}

int main() {
    map<string, int> jobMap;
    vector<string> name, salary;

    int minSalary, maxSalary;
    string industry, state;

    cout << "Enter Industry (1-20): ";
    cin >> industry;

    industry = IndustryTranslator(industry); 

    cout << "Enter State (e.g., FL, KY, WA): ";
    cin >> state;

    inCSV("2022LaborData.csv", jobMap, industry, state);

    return 0;
}
