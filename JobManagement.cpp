#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include <ctime>
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

using namespace std;

#ifdef _WIN32
void clearConsole() {
    system("cls");
}
#else
void clearConsole() {
    system("clear");
}
#endif

void showCurrentTime() {
    time_t now = time(nullptr);
    tm* ptm = localtime(&now);

    // Get current date and time
    int year = 1900 + ptm->tm_year;
    int month = 1 + ptm->tm_mon;
    int day = ptm->tm_mday;
    int hour = ptm->tm_hour;
    int min = ptm->tm_min;
    int sec = ptm->tm_sec;

    // Create a formatted string
    cout << setw(52) << ANSI_COLOR_CYAN << setfill('0') << setw(4) << year << "-"
              << setw(2) << month << "-"
              << setw(2) << day << " "
              << setw(2) << hour << ":"
              << setw(2) << min << ":"
              << setw(2) << sec << ANSI_COLOR_RESET << endl;
}

class Job{
public:
    int jobId;
    string title;
    string description;
    double salary;
    int companyId;
    string status; // "open" or "closed"

    Job(int id, string t, string d, double s,int c , string st)
        : jobId(id), title(t), description(d), salary(s), companyId(c), status(st) {}
};



class Company {
public:
    int companyId;
    string name;
    string industry;
    string location;
    vector<int> jobs;

    Company(int id, string n, string i, string l, const vector<int>& j)
        : companyId(id), name(n), industry(i), location(l), jobs(j) {}
};

class Applicant {
public:
    int applicantId;
    string name;
    string contactInfo;
    vector<int> appliedJobs; // Store job IDs

    Applicant(int id, string n, string c, const vector<int>& jobs)
        : applicantId(id), name(n), contactInfo(c), appliedJobs(jobs) {}
};

class JobManagementSystem {
private:
    //Auto - Increment
    int nextJobId = 1;
    int nextApplicantId = 1;
    int nextCompanyId = 1;

    //Saving to File
    void saveJobsToFile();
    void saveCompaniesToFile();
    void saveApplicantsToFile();

    //Loading all files when program starts
    void loadJobsFromFile();
    void loadApplicantsFromFile();
    void loadCompaniesFromFile();


    //Holding all data during runtime
    vector<Job> jobs;
    vector<Company> companies;
    vector<Applicant> applicants;



public:
    JobManagementSystem() {
        loadJobsFromFile();
        loadApplicantsFromFile();
        loadCompaniesFromFile();
    }

    void listJobs();

    //Login Menu -> Company & Applicant
    void companyLogin();
    void applicantLogin();
    void companyMenu(int companyId);
    void applicantMenu(int applicantId);

    //Company Features
    void addJobForCompany(int companyId);
    void editJobForCompany(int companyId);
    void deleteJobForCompany(int companyId);
    void listJobsForCompany(int companyId);
    void viewApplicantsForJob(int companyId);
    void editCompanyInfo(int companyId);
    //void viewAllApplicantsUnderCompany(int companyId); //implement

    //Applicant Features
    void applyForJob(int applicantId);
    void cancelApplication(int applicantId);
    void listAppliedJobs(int applicantId);
    void listAllJobs();
    void editApplicantInfo(int applicantId);

    // Admin Features
    void adminLogin();
    void adminMenu();
    void addCompany();
    void addApplicant();
    void listCompanies();
    void listApplicants();
};

void JobManagementSystem::editApplicantInfo(int applicantId){
    for (auto& applicant : applicants) {
        if (applicant.applicantId == applicantId) {
            int editChoice;
            cout << "\nEditing Company ID: " << applicantId << "\n";
            cout << "1. Edit Name\n";
            cout << "2. Edit Contact Info(EMAIL) \n";
            cout << "0. Cancel\n";
            cout << "Enter your choice: ";
            cin >> editChoice;
            cin.ignore();  // Clear the input buffer

            switch (editChoice) {
                case 1: {
                    cout << "Enter new Name: ";
                    string Name;
                    getline(cin, Name);
                    applicant.name = Name;
                    break;
                }
                case 2: {
                    cout << "Enter new Contact Info(EMAIL): ";
                    string newcontactInfo;
                    getline(cin, newcontactInfo);
                    applicant.contactInfo = newcontactInfo;
                    break;
                }
                case 0:
                    cout << "Edit cancelled.\n";
                    return;
                default:
                    cout << "Invalid choice. Edit cancelled.\n";
                    return;
            }

            // Save changes to the file
            saveApplicantsToFile();
            cout << "Company updated successfully!\n";
            return;
        }
    }
}
void JobManagementSystem::editCompanyInfo (int companyId){
    for (auto& company : companies) {
        if (company.companyId == companyId) {
            int editChoice;
            cout << "\nEditing Company ID: " << companyId << "\n";
            cout << "1. Edit Name\n";
            cout << "2. Edit Industry\n";
            cout << "3. Edit Location\n";
            cout << "0. Cancel\n";
            cout << "Enter your choice: ";
            cin >> editChoice;
            cin.ignore();  // Clear the input buffer

            switch (editChoice) {
                case 1: {
                    cout << "Enter new Name: ";
                    string Name;
                    getline(cin, Name);
                    company.name = Name;
                    break;
                }
                case 2: {
                    cout << "Enter new Industry: ";
                    string newIndustry;
                    getline(cin, newIndustry);
                    company.industry = newIndustry;
                    break;
                }
                case 3: {
                    cout << "Enter new Location: ";
                    string newLocation;
                    getline(cin, newLocation);
                    company.location = newLocation;
                    break;
                }
                case 0:
                    cout << "Edit cancelled.\n";
                    return;
                default:
                    cout << "Invalid choice. Edit cancelled.\n";
                    return;
            }

            // Save changes to the file
            saveCompaniesToFile();
            cout << "Company updated successfully!\n";
            return;
        }
    }
}
void JobManagementSystem::saveJobsToFile() {
    ofstream outFile("jobs.txt");
    if (outFile.is_open()) {
        for (const auto& job : jobs) {
            outFile << job.jobId << ","
                    << job.title << ","
                    << job.description << ","
                    << job.salary << ","
                    << job.companyId << ","
                    << job.status << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for writing: jobs.txt\n";
    }
}

void JobManagementSystem::saveCompaniesToFile() {
    ofstream outFile("companies.txt");
    if (outFile.is_open()) {
        for (const auto& company : companies) {
            outFile << company.companyId << ","
                    << company.name << ","
                    << company.industry << ","
                    << company.location << ",";

            for (size_t i = 0; i < company.jobs.size(); ++i) {
                outFile << company.jobs[i]; // Directly write job ID
                if (i < company.jobs.size() - 1) {
                    outFile << ";";
                }
            }

            outFile << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for writing: companies.txt\n";
    }
}

void JobManagementSystem::saveApplicantsToFile() {
    ofstream outFile("applicants.txt");
    if (outFile.is_open()) {
        for (const auto& applicant : applicants) {
            outFile << applicant.applicantId << ","
                    << applicant.name << ","
                    << applicant.contactInfo << ",";

            for (size_t i = 0; i < applicant.appliedJobs.size(); ++i) {
                outFile << applicant.appliedJobs[i];
                if (i < applicant.appliedJobs.size() - 1) {
                    outFile << ";";
                }
            }

            outFile << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for writing: applicants.txt\n";
    }
}


void JobManagementSystem::loadJobsFromFile() {
    ifstream inFile("jobs.txt");
    if (inFile.is_open()) {
        jobs.clear();
        string line;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> jobData;

            while (getline(ss, item, ',')) {
                jobData.push_back(item);
            }

            if (jobData.size() == 6) {
                int jobId = stoi(jobData[0]);
                string title = jobData[1];
                string description = jobData[2];
                double salary = stod(jobData[3]);
                int companyId = stoi(jobData[4]);
                string status = jobData[5];

                jobs.emplace_back(jobId, title, description, salary, companyId, status);

                if (jobId >= nextJobId) {
                    nextJobId = jobId + 1;
                }
            }
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading: " << "jobs.txt" << "\n";
    }
}

void JobManagementSystem::loadApplicantsFromFile() {
    ifstream inFile("applicants.txt");
    if (inFile.is_open()) {
        applicants.clear();
        string line;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> applicantData;

            while (getline(ss, item, ',')) {
                applicantData.push_back(item);
            }

            if (applicantData.size() >= 4) {
                int applicantId = stoi(applicantData[0]);
                string name = applicantData[1];
                string contactInfo = applicantData[2];

                vector<int> appliedJobs;
                stringstream jobStream(applicantData[3]);
                string jobId;

                while (getline(jobStream, jobId, ';')) {
                    appliedJobs.push_back(stoi(jobId));
                }

                applicants.emplace_back(applicantId, name, contactInfo, appliedJobs);

                if (applicantId >= nextApplicantId) {
                    nextApplicantId = applicantId + 1;
                }
            }
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading: applicants.txt\n";
    }
}


void JobManagementSystem::loadCompaniesFromFile() {
    ifstream inFile("companies.txt");
    if (inFile.is_open()) {
        companies.clear();
        string line;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> companyData;

            while (getline(ss, item, ',')) {
                companyData.push_back(item);
            }

            if (companyData.size() >= 4) {
                int companyId = stoi(companyData[0]);
                string name = companyData[1];
                string industry = companyData[2];
                string location = companyData[3];

                vector<int> jobIds;
                if (companyData.size() == 5) {
                    stringstream jobStream(companyData[4]);
                    string jobId;

                    while (getline(jobStream, jobId, ';')) {
                        jobIds.push_back(stoi(jobId));
                    }
                }

                companies.emplace_back(companyId, name, industry, location, jobIds);

                if (companyId >= nextCompanyId) {
                    nextCompanyId = companyId + 1;
                }
            }
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading: companies.txt\n";
    }
}

void JobManagementSystem::companyLogin() {
    string companyName;
    int companyId;
    cout << "Enter Company ID: ";
    cin >> companyId;
    cout << "Enter Password: "; //company_name is the password
    cin.ignore();
    getline(cin, companyName);

    bool found = false;
    for (const auto& company : companies) {
        if (company.companyId == companyId && company.name == companyName) {
            found = true;
            companyMenu(companyId);
            break;
        }
    }

    if (!found) {
        cout << "Invalid Company ID or Name.\n";
    }
}

void JobManagementSystem::applicantLogin() {
    string applicantName;
    int applicantId;
    cout << "Enter Applicant ID: ";
    cin >> applicantId;
    cout << "Enter Password: "; //Applicant's Name is the password
    cin.ignore();
    getline(cin, applicantName);

    bool found = false;
    for (const auto& applicant : applicants) {
        if (applicant.applicantId == applicantId && applicant.name == applicantName) {
            found = true;
            applicantMenu(applicantId);
            break;
        }
    }

    if (!found) {
        cout << "Invalid Applicant ID or Name.\n";
    }
}

void JobManagementSystem::companyMenu(int companyId) {
    int choice;
    do {

        for (const auto& company : companies){
            if(companyId == company.companyId){
                cout << "\n" << company.name << " ---> ID: " << company.companyId << endl;
            }
        }
        cout << "Company Menu\n";
        cout << "1. Add Job\n";
        cout << "2. Edit Job\n";
        cout << "3. Delete Job\n";
        cout << "4. List All Jobs\n";
        cout << "5. View Applicants for a Job\n";
        cout << "6. Edit Info\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addJobForCompany(companyId);
                break;
            case 2:
                editJobForCompany(companyId);
                break;
            case 3:
                deleteJobForCompany(companyId);
                break;
            case 4:
                listJobsForCompany(companyId);
                break;
            case 5:
                viewApplicantsForJob(companyId);
                break;
            case 6:
                editCompanyInfo(companyId);
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void JobManagementSystem::applicantMenu(int applicantId) {
    int choice;
    do {
            for (const auto& applicant : applicants){
            if(applicantId == applicant.applicantId){
                cout << "\n" << applicant.name << " ---> ID: " << applicant.applicantId << endl;
            }
        }
        cout << "Applicant Menu\n";
        cout << "1. View All Jobs\n";
        cout << "2. Apply for a Job\n";
        cout << "3. List Applied Jobs\n";
        cout << "4. Cancel Application\n";
        cout << "5. Edit Info\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listAllJobs();
                break;
            case 2:
                applyForJob(applicantId);
                break;
            case 3:
                listAppliedJobs(applicantId);
                break;
            case 4:
                cancelApplication(applicantId);
                break;
            case 5:
                editApplicantInfo(applicantId);
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}
void JobManagementSystem::addJobForCompany(int companyId) {
    string title, description, status;
    double salary;

    cout << "Enter Job Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Job Description: ";
    getline(cin, description);
    cout << "Enter Job Salary: ";
    cin >> salary;
    cout << "Enter Job Status (open/closed): ";
    cin.ignore();
    getline(cin, status);

    Job newJob(nextJobId++, title, description, salary, companyId, status);
    jobs.push_back(newJob);

    // Update the company's job list
    for (auto& company : companies) {
        if (company.companyId == companyId) {
            company.jobs.push_back(newJob.jobId);
            break;
        }
    }

    // Save changes to the file
    saveJobsToFile();
    saveCompaniesToFile();

    cout << "Job added successfully!\n";
}

void JobManagementSystem::editJobForCompany(int companyId) {
    int jobId;
    cout << "Enter Job ID to Edit: ";
    cin >> jobId;

    // Find the job
    bool jobFound = false;
    for (auto& job : jobs) {
        if (job.jobId == jobId && job.companyId == companyId) {
            jobFound = true;
            int editChoice;
            cout << "\nEditing Job ID: " << jobId << "\n";
            cout << "1. Edit Title\n";
            cout << "2. Edit Description\n";
            cout << "3. Edit Salary\n";
            cout << "4. Edit Status\n";
            cout << "0. Cancel\n";
            cout << "Enter your choice: ";
            cin >> editChoice;
            cin.ignore();  // Clear the input buffer

            switch (editChoice) {
                case 1: {
                    cout << "Enter new Title: ";
                    string newTitle;
                    getline(cin, newTitle);
                    job.title = newTitle;
                    break;
                }
                case 2: {
                    cout << "Enter new Description: ";
                    string newDescription;
                    getline(cin, newDescription);
                    job.description = newDescription;
                    break;
                }
                case 3: {
                    cout << "Enter new Salary: ";
                    double newSalary;
                    cin >> newSalary;
                    job.salary = newSalary;
                    break;
                }
                case 4: {
                    cout << "Enter new Status (open/closed): ";
                    string newStatus;
                    getline(cin, newStatus);
                    job.status = newStatus;
                    break;
                }
                case 0:
                    cout << "Edit cancelled.\n";
                    return;
                default:
                    cout << "Invalid choice. Edit cancelled.\n";
                    return;
            }

            // Save changes to the file
            saveJobsToFile();
            cout << "Job updated successfully!\n";
            return;
        }
    }

    if (!jobFound) {
        cout << "Job ID not found for this company.\n";
    }
}

void JobManagementSystem::deleteJobForCompany(int companyId) {
    int jobId;
    cout << "Enter Job ID to Delete: ";
    cin >> jobId;

    // Find and remove the job
    auto jobIt = jobs.begin();
    bool jobFound = false;
    for (; jobIt != jobs.end(); ++jobIt) {
        if (jobIt->jobId == jobId && jobIt->companyId == companyId) {
            jobFound = true;
            break;
        }
    }

    if (jobFound) {
        jobs.erase(jobIt);

        // Remove the job from the company's job list
        for (auto& company : companies) {
            if (company.companyId == companyId) {
                auto it = find(company.jobs.begin(), company.jobs.end(), jobId);
                if (it != company.jobs.end()) {
                    company.jobs.erase(it);
                }
                break;
            }
        }

        // Remove the job from applicants' applied jobs
        for (auto& applicant : applicants) {
            auto it = find(applicant.appliedJobs.begin(), applicant.appliedJobs.end(), jobId);
            if (it != applicant.appliedJobs.end()) {
                applicant.appliedJobs.erase(it);
            }
        }

        // Save changes to the files
        saveJobsToFile();
        saveCompaniesToFile();
        saveApplicantsToFile();

        cout << "Job deleted successfully!\n";
    } else {
        cout << "Job ID not found for this company.\n";
    }
}

void JobManagementSystem::listJobsForCompany(int companyId) {
    //clearConsole();
    cout << "Listing Jobs for Company ID: " << companyId << "\n";
    bool jobsFound = false;

    for (const auto& job : jobs) {
        if (job.companyId == companyId) {
            jobsFound = true;
            cout << "Job ID: " << job.jobId << "\n"
                 << "Title: " << job.title << "\n"
                 << "Description: " << job.description << "\n"
                 << "Salary: $" << job.salary << "\n"
                 << "Status: " << job.status << "\n"
                 << "------------------------------\n";
        }
    }

    if (!jobsFound) {
        cout << "No jobs found for this company.\n";
    }
}

void JobManagementSystem::viewApplicantsForJob(int companyId) {
    //clearConsole();
    int jobId;
    cout << "Enter Job ID to View Applicants: ";
    cin >> jobId;

    // Find the job to ensure it belongs to the company
    bool jobFound = false;
    for (const auto& job : jobs) {
        if (job.jobId == jobId && job.companyId == companyId) {
            jobFound = true;
            break;
        }
    }

    if (jobFound) {
        cout << "\nApplicants for Job ID: " << jobId << "\n\n";
        bool applicantsFound = false;

        for (const auto& applicant : applicants) {
            for (const auto& appliedJobId : applicant.appliedJobs) {
                if (appliedJobId == jobId) {
                    applicantsFound = true;
                    cout << "Applicant ID: " << applicant.applicantId << "\n"
                         << "Name: " << applicant.name << "\n"
                         << "Contact Info: " << applicant.contactInfo << "\n"
                         << "------------------------------\n";
                }
            }
        }

        if (!applicantsFound) {
        cout << "No applicants found for this job.\n";
        }
    } else {
        cout << "Job ID not found for this company.\n";
    }
}

void JobManagementSystem::listAllJobs() {
    //clearConsole();
    cout << "\nListing All Jobs:\n\n";
    for (const auto& job : jobs) {
        cout << "Job ID: " << job.jobId << "\n"
             << "Title: " << job.title << "\n"
             << "Description: " << job.description << "\n"
             << "Salary: $" << job.salary << "\n"
             << "Company ID: " << job.companyId << "\n"
             << "Status: " << job.status << "\n"
             << "------------------------------\n";
    }
}

void JobManagementSystem::listAppliedJobs(int applicantId) {
    cout << "\nListing Applied Jobs for Applicant ID " << applicantId << ":\n\n";
    for (const auto& applicant : applicants) {
        if (applicant.applicantId == applicantId) {
            for (const auto& jobId : applicant.appliedJobs) {
                for (const auto& job : jobs) {
                    if (job.jobId == jobId) {
                        cout << "Job ID: " << job.jobId << "\n"
                             << "Title: " << job.title << "\n"
                             << "Description: " << job.description << "\n"
                             << "Salary: $" << job.salary << "\n"
                             << "Status: " << job.status << "\n"
                             << "------------------------------\n";
                    }
                }
            }
            return;
        }
    }

    cout << "Applicant not found.\n";
}


void JobManagementSystem::cancelApplication(int applicantId) {
    int jobId;
    cout << "Enter Job ID to Cancel Application: ";
    cin >> jobId;

    for (auto& applicant : applicants) {
        if (applicant.applicantId == applicantId) {
            auto jobIt = find(applicant.appliedJobs.begin(), applicant.appliedJobs.end(), jobId);
            if (jobIt != applicant.appliedJobs.end()) {
                applicant.appliedJobs.erase(jobIt);
                saveApplicantsToFile();
                cout << "Successfully canceled application for Job ID " << jobId << ".\n";
            } else {
                cout << "You have not applied for this job.\n";
            }
            return;
        }
    }

    cout << "Applicant not found.\n";
}

void JobManagementSystem::applyForJob(int applicantId) {
    int jobId;
    cout << "Enter Job ID to Apply: ";
    cin >> jobId;

    bool jobFound = false;
    for (const auto& job : jobs) {
        if (job.jobId == jobId && job.status == "open") {
            jobFound = true;
            break;
        }
    }

    if (!jobFound) {
        cout << "Job not found or is not open for applications.\n";
        return;
    }

    for (auto& applicant : applicants) {
        if (applicant.applicantId == applicantId) {
            if (find(applicant.appliedJobs.begin(), applicant.appliedJobs.end(), jobId) == applicant.appliedJobs.end()) {
                applicant.appliedJobs.push_back(jobId);
                saveApplicantsToFile();
                cout << "Successfully applied for Job ID " << jobId << ".\n";
            } else {
                cout << "You have already applied for this job.\n";
            }
            return;
        }
    }

    cout << "Applicant not found.\n";
}

void JobManagementSystem::adminLogin() {
    string adminUsername, adminPassword;

    cout << "Enter Admin Username: ";
    cin.ignore();
    getline(cin, adminUsername);
    cout << "Enter Admin Password: ";
    getline(cin, adminPassword);

    // For simplicity, using hardcoded admin credentials
    if (adminUsername == "admin" && adminPassword == "password") {
        adminMenu();
    } else {
        cout << "Invalid Admin Credentials.\n";
    }
}

void JobManagementSystem::adminMenu() {
    int choice;
    do {
        cout << "\nAdmin Menu\n";
        cout << "1. Add Company\n";
        cout << "2. Add Applicant\n";
        cout << "3. List Companies\n";
        cout << "4. List Applicants\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addCompany();
                break;
            case 2:
                addApplicant();
                break;
            case 3:
                listCompanies();
                break;
            case 4:
                listApplicants();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void JobManagementSystem::addCompany() {
    string name, industry, location;

    cout << "Enter Company Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Industry: ";
    getline(cin, industry);
    cout << "Enter Location: ";
    getline(cin, location);

    Company newCompany(nextCompanyId++, name, industry, location, {});
    companies.push_back(newCompany);

    // Save changes to the file
    saveCompaniesToFile();

    cout << "Company added successfully!\n";
}

void JobManagementSystem::addApplicant() {
    string name, contactInfo;

    cout << "Enter Applicant Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Contact Info: ";
    getline(cin, contactInfo);

    Applicant newApplicant(nextApplicantId++, name, contactInfo, {});
    applicants.push_back(newApplicant);

    // Save changes to the file
    saveApplicantsToFile();

    cout << "Applicant added successfully!\n";
}

void JobManagementSystem::listApplicants() {
    clearConsole();
    cout << "\nListing All Applicants:\n\n";
    for (const auto& applicant : applicants) {
        cout << "Applicant ID: " << applicant.applicantId << "\n"
             << "Name: " << applicant.name << "\n"
             << "Contact Info: " << applicant.contactInfo << "\n"
             << "Applied Jobs: ";
        for (const auto& jobId : applicant.appliedJobs) {
            cout << jobId << " ";
        }
        cout << "\n------------------------------\n";
    }
}

void JobManagementSystem::listCompanies() {
    clearConsole();
    cout << "\nListing All Companies:\n\n";
    for (const auto& company : companies) {
        cout << "Company ID: " << company.companyId << "\n"
             << "Name: " << company.name << "\n"
             << "Industry: " << company.industry << "\n"
             << "Location: " << company.location << "\n"
             << "Jobs: ";
        for (const auto& jobId : company.jobs) {
            cout << jobId << " ";
        }
        cout << "\n------------------------------\n";
    }
}

void quote() {
    srand(time(NULL));
    int x = rand() % 10;
    switch (x) {
    case 0:
        std::cout << ANSI_COLOR_BLUE << "Success is not final, failure is not fatal, it is the courage to continue that counts. \n-Winston Churchill" << ANSI_COLOR_RESET << std::endl;
        break;
    case 1:
        std::cout << ANSI_COLOR_BLUE << "Play by the rules, but be ferocious.\n-Phil Knight" << ANSI_COLOR_RESET << std::endl;
        break;
    case 2:
        std::cout << ANSI_COLOR_BLUE << "Business opportunities are like buses, there's always another one coming.\n-Richard Branson" << ANSI_COLOR_RESET << std::endl;
        break;
    case 3:
        std::cout << ANSI_COLOR_BLUE << "Every problem is a gift—without problems we would not grow.\n-Anthony Robbins" << ANSI_COLOR_RESET << std::endl;
        break;
    case 4:
        std::cout << ANSI_COLOR_BLUE << "You only have to do a few things right in your life so long as you don't do too many things wrong.\n-Warren Buffett" << ANSI_COLOR_RESET << std::endl;
        break;
    case 5:
        std::cout << ANSI_COLOR_BLUE << "Success usually comes to those who are too busy to be looking for it.\n-Henry David Thoreau" << ANSI_COLOR_RESET << std::endl;
        break;
    case 6:
        std::cout << ANSI_COLOR_BLUE << "And the day came when the risk to remain tight in a bud was more painful than the risk it took to blossom.\n-Anaïs Nin" << ANSI_COLOR_RESET << std::endl;
        break;
    case 7:
        std::cout << ANSI_COLOR_BLUE << "There's no shortage of remarkable ideas, what's missing is the will to execute them.\n-Seth Godin" << ANSI_COLOR_RESET << std::endl;
        break;
    case 8:
        std::cout << ANSI_COLOR_BLUE << "I owe my success to having listened respectfully to the very best advice, and then going away and doing the exact opposite.\n-G.K.Chesterton" << ANSI_COLOR_RESET << std::endl;
        break;
    case 9:
        std::cout << ANSI_COLOR_BLUE << "I don't know the word 'quit'. Either I never did, or I have abolished it.\n-Susan Butcher" << ANSI_COLOR_RESET << std::endl;
        break;
    }
}

int main() {
    JobManagementSystem system;
    int mainChoice;

    do {
        cout << endl;
        showCurrentTime();
        cout << "\n";
        //cout << setw(100) << setfill('*') << "" << endl;
        cout << setw(45) << setfill(' ') << ANSI_COLOR_RED << "Welcome to the Job Management System\n" << ANSI_COLOR_RESET <<endl;
        //cout << setw(100) << setfill('*') << "" << endl;
        cout << "Quote of the day: ";
        quote();
        cout << endl;
        cout << "1. Company Login\n";
        cout << "2. Applicant Login\n";
        cout << "3. Admin Login\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                system.companyLogin();
                break;
            case 2:
                system.applicantLogin();
                break;
            case 3:
                system.adminLogin();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (mainChoice != 0);

    return 0;
}
