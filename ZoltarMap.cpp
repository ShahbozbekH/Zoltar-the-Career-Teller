#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <limits>


struct JobData {
    std::string areaTitle;
    std::string primState;
    std::string naics;
    std::string naicsTitle;
    std::string occTitle;
    std::string totEmp;
    std::string hMean;
    std::string aMean;
    std::string aPct10;
    std::string aPct25;
    std::string aMedian;
    std::string aPct75;
    std::string aPct90;
};

void parseCSV(const std::string& filename, std::map<std::string, std::vector<JobData>>& jobMap) {
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 27) {
            JobData job;
            job.areaTitle = tokens[1];
            job.primState = tokens[3];
            job.naics = tokens[4].substr(0, 2); 
            job.naicsTitle = tokens[5];
            job.occTitle = tokens[9];
            job.totEmp = tokens[11];
            job.hMean = tokens[16];
            job.aMean = tokens[17];
            job.aPct10 = tokens[25];
            job.aPct25 = tokens[26];
            job.aMedian = tokens[27];
            job.aPct75 = tokens[28];
            job.aPct90 = tokens[29];

            jobMap[job.primState].push_back(job);
        }
    }
}

void searchJobs(const std::map<std::string, std::vector<JobData>>& jobMap,
                const std::string& industry, const std::string& state,
                int minSalary, int maxSalary) {
    const auto& jobs = jobMap.at(state);
    int jobsDisplayed = 0;

    for (const auto& job : jobs) {
        if (job.naics == industry &&
            std::stoi(job.aMean) >= minSalary &&
            std::stoi(job.aMean) <= maxSalary) {
            std::cout << "Name of the job: " << job.occTitle << "\n"
                      << "Location: " << job.areaTitle << "\n"
                      << "Industry: " << job.naicsTitle << "\n"
                      << "Average Hourly Salary: " << job.hMean << "\n"
                      << "Average Annual Salary: " << job.aMean << "\n"
                      << "Lowest Salaries: " << job.aPct10 << ", " << job.aPct25 << "\n"
                      << "Median Salaries: " << job.aMedian << "\n"
                      << "Highest Salaries: " << job.aPct75 << ", " << job.aPct90 << "\n\n";

            jobsDisplayed++;

            if (jobsDisplayed % 10 == 0) {
                std::cout << "Press Enter for the next 10 jobs (or type 'exit' to quit): ";
                std::string userInput;
                std::getline(std::cin, userInput);

                if (userInput == "exit") {
                    break;
                }
            }
        }
    }
}

int main() {
    std::map<std::string, std::vector<JobData>> jobMap;
    parseCSV("2022LaborData.csv", jobMap);

    int industryChoice, minSalary, maxSalary;
    std::string state;

    std::cout << "Enter Industry (1-20): ";
    std::cin >> industryChoice;

    std::string industry = (industryChoice < 10 ? "0" : "") + std::to_string(industryChoice);

    std::cout << "Enter State (e.g., FL, KY, WA): ";
    std::cin >> state;

    std::cout << "Enter Minimum Salary: ";
    std::cin >> minSalary;

    std::cout << "Enter Maximum Salary: ";
    std::cin >> maxSalary;

    searchJobs(jobMap, industry, state, minSalary, maxSalary);

    return 0;
}