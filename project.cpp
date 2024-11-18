#include <bits/stdc++.h>
#include <windows.h> // For Sleep() and system() functions
using namespace std;

class Display {
public:
    // Function to display the introduction screen
    static void intro() {
        cout << endl << endl << endl << endl << "\t\t\t\t\t"; Sleep(900);
        cout << "\n\t\t\t    |||||||||| ||||       |||||||||| |||||||||| |||||||||| |||||||||| |||||||||| |||||     ||| "; Sleep(200);
        cout << "\n\t\t\t    ||||       ||||       ||||       |||||||||| |||||||||| |||||||||| |||||||||| ||||||    ||| "; Sleep(200);
        cout << "\n\t\t\t    |||||||    ||||       |||||||    ||||          ||||       ||||    |||    ||| ||| |||   ||| "; Sleep(200);
        cout << "\n\t\t\t    |||||||    ||||       |||||||    ||||          ||||       ||||    |||    ||| |||  |||  ||| "; Sleep(200);
        cout << "\n\t\t\t    ||||       |||||||||| ||||       ||||||||||    ||||    |||||||||| |||||||||| |||   ||| ||| "; Sleep(200);
        cout << "\n\t\t\t    |||||||||| |||||||||| |||||||||| ||||||||||   ||||||   |||||||||| |||||||||| |||    |||||| "; Sleep(200);
        cout << endl << endl << endl << endl << endl << "\t\t\t\t\t\t\t"; Sleep(1000);
        cout << "\n\n\t\t\t\tProject Prepared by:"; Sleep(400);
        cout << "\n\n\t\t\t\t--------------------"; Sleep(500);
        cout << "\n\n\t\t\t\t  ABHAY     BT23CSE020      "; Sleep(1000);
        cout << "\n\n\t\t\t\t  GAURAV     BT23CSE0      "; Sleep(1000);
        cout << "\n\n\t\t\t\t  AYUSH     BT23CSE056      "; Sleep(1000);
        cout << "\n\n\t\t\t\t  AMAN      BT23CSE058      "; Sleep(1000);
        cout << "\n\n\t\t\t  Guided By - Dr. Vasundhara Rathod Mam     ";
        Sleep(3500);
        system("cls");
    }
    // Function to display the winner announcement
    static void winner() {
        cout << endl << endl << endl << endl << "\t\t\t\t\t"; Sleep(900);
        cout << "\n\t\t\t\t\t    |||       ||| |||||||||| |||||     ||| |||||     ||| |||||||||| |||||||||| "; Sleep(200);
        cout << "\n\t\t\t\t\t    |||       ||| |||||||||| ||||||    ||| ||||||    ||| ||||       |||    ||| "; Sleep(200);
        cout << "\n\t\t\t\t\t    |||   |   |||    ||||    ||| |||   ||| ||| |||   ||| |||||||    |||||||||| "; Sleep(200);
        cout << "\n\t\t\t\t\t    |||  |||  |||    ||||    |||  |||  ||| |||  |||  ||| |||||||    ||||||||   "; Sleep(200);
        cout << "\n\t\t\t\t\t    ||| || || ||| |||||||||| |||   ||| ||| |||   ||| ||| ||||       ||| |||||  "; Sleep(200);
        cout << "\n\t\t\t\t\t    |||||   ||||| |||||||||| |||    |||||| |||    |||||| |||||||||| |||  ||||| "; Sleep(200);
    }
};
class User {
protected:
    int user_id;
    string name;
    string password;

public:
    User(int id = 0, const string& n = "", const string& pass = "") 
        : user_id(id), name(n), password(pass) {}

    int getID() const { return user_id; }
    string getName() const { return name; }
    bool verifyPassword(const string& inputPass) const { return inputPass == password; }

    virtual void saveToFile(ofstream& file) const {
        file << user_id << " " << name << " " << password << "\n";
    }

    virtual void loadFromFile(ifstream& file) {
        file >> user_id >> name >> password;
    }

    friend ifstream& operator>>(ifstream& file, User& user) {
        file >> user.user_id >> user.name >> user.password;
        return file;
    }
};

class Admin : public User {
public:
    Admin(int id = 0, const string& name = "", const string& pass = "") : User(id, name, pass) {}
    void saveToFile(ofstream& file) const override {
        User::saveToFile(file);
    }
    void loadFromFile(ifstream& file) override {
        User::loadFromFile(file);
    }
    friend ifstream& operator>>(ifstream& file, Admin& admin) {
        file >> static_cast<User&>(admin);
        return file;
    }
};
class Voter : public User {
private:
    bool hasVoted;

public:
    Voter(int id, const string& name, const string& pass, bool voted = false)
        : User(id, name, pass), hasVoted(voted) {}
    bool getHasVoted() const { return hasVoted; }
    void markAsVoted() { hasVoted = true; }
    void saveToFile(ofstream& file) const override {
        User::saveToFile(file);
        file << hasVoted << "\n";
    }
    void loadFromFile(ifstream& file) override {
        User::loadFromFile(file);
        file >> hasVoted;
    }
    // Overload >> operator for Voter class
    friend ifstream& operator>>(ifstream& file, Voter& voter) {
        file >> static_cast<User&>(voter);  // Read base class part first
        file >> voter.hasVoted;
        return file;
    }
};
class Candidate {
private:
    int candidate_id;
    string name;
    string party;
    string symbol;
    int voteCount;

public:
    Candidate(int id, const string& n, const string& p, const string& s, int votes = 0)
        : candidate_id(id), name(n), party(p), symbol(s), voteCount(votes) {}

    int getID() const { return candidate_id; }
    string getName() const { return name; }
    string getParty() const { return party; }
    string getSymbol() const { return symbol; }
    int getVoteCount() const { return voteCount; }
    void incrementVoteCount() { voteCount++; }
    void saveToFile(ofstream& file) const {
        file << candidate_id << " " << name << " " << party << " " << symbol << " " << voteCount << "\n";
    }
    void loadFromFile(ifstream& file) {
        file >> candidate_id >> name >> party >> symbol >> voteCount;
    }
    // Overload >> operator for Candidate class
    friend ifstream& operator>>(ifstream& file, Candidate& candidate) {
        file >> candidate.candidate_id >> candidate.name >> candidate.party >> candidate.symbol >> candidate.voteCount;
        return file;
    }
};
class Election {
private:
    vector<Candidate> candidates;
    unordered_map<int, int> votes;

public:
vector<Candidate> getCandidates() {
        return candidates;
    }
void addCandidate(int id, const string& name, const string& party, const string& symbol) {
    // Check if the candidate already exists
    for (const auto& candidate : candidates) {
        if (candidate.getID() == id) {
            cout << "Candidate with ID " << id << " already exists.\n";
            return;
        }
    }
    // If no duplicate found, add new candidate
    candidates.emplace_back(id, name, party, symbol);
    cout << "Candidate " << name << " added successfully.\n";
}
    bool castVote(int voterID, int candidateID) {
        if (votes.find(voterID) != votes.end()) {
            cout << "Voter " << voterID << " has already voted.\n";
            return false;
        }
        for (auto& candidate : candidates) {
            if (candidate.getID() == candidateID) {
                candidate.incrementVoteCount();
                votes[voterID] = candidateID;
                return true;
            }
        }
        cout << "Invalid Candidate ID.\n";
        return false;
    }
    void displayResults() const {
        cout << "Election Results:\n";
        for (const auto& candidate : candidates) {
            cout << "Candidate: " << candidate.getName() 
                 << ", Party: " << candidate.getParty() 
                 << ", Symbol: " << candidate.getSymbol() 
                 << ", Votes: " << candidate.getVoteCount() << "\n";
        }
    }
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (const auto& candidate : candidates) {
            candidate.saveToFile(file);
        }
    }
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "No previous election data found.\n";
            return;
        }
        Candidate temp(0, "", "", "");
        while (file >> temp) {
            candidates.push_back(temp);
        }
    }
};
class ElectionManagementSystem {
private:
    vector<Voter> voters;
    vector<Admin> admins;
    Election election;
    bool isAdminLoggedIn = false;
    bool isVoterLoggedIn = false;
    int currentVoterID=-1;
public:
    void registerVoter(int id, const string& name, const string& pass) {
        // Register voter only if a voter is logged in
        if (!isVoterLoggedIn) {
            cout << "You must be logged in as a voter to add another voter.\n";
            return;
        }

        for (const auto& voter : voters) {
            if (voter.getID() == id) {
                cout << "Voter with ID " << id << " already exists.\n";
                return;
            }
        }
        voters.emplace_back(id, name, pass);
    }
    void registerAdmin(int id, const string& name, const string& pass) {
        for (const auto& admin : admins) {
            if (admin.getID() == id) {
                cout << "Admin with ID " << id << " already exists.\n";
                return;
            }
        }
        admins.emplace_back(id, name, pass);
    }
    bool loginUser(int id, const string& pass, bool isAdmin) {
    if (isAdmin) {
        for (const auto& admin : admins) {
            if (admin.getID() == id && admin.verifyPassword(pass)) {
                isAdminLoggedIn = true;
                isVoterLoggedIn = false;
                return true;
            }
        }
    } else {
        for (auto& voter : voters) {  // Use reference to modify voters
            if (voter.getID() == id && voter.verifyPassword(pass)) {
                isVoterLoggedIn = true;
                isAdminLoggedIn = false;
                currentVoterID = voter.getID(); // Set the currentVoterID here
                return true;
            }
        }
    }
    cout << "Invalid ID or Password.\n";
    return false;
}
bool castVote(int candidateID) {
    if (!isVoterLoggedIn) {
        cout << "You must be logged in as a voter to cast a vote.\n";
        return false;
    }
    // use currentVoterID to check if this voter has already voted
    for (auto& voter : voters) {
        if (voter.getID() == currentVoterID) {
            if (voter.getHasVoted()) {
                cout << "Voter " << currentVoterID << " has already voted.\n";
                return false;
            }

            // Find the candidate and cast the vote
            bool voteSuccess = election.castVote(currentVoterID, candidateID);
            if (voteSuccess) {
                voter.markAsVoted();  // Mark voter as having voted
                return true;
            }
            break;
        }
    }
    cout << "Voter ID not found.\n";
    return false;
}
    void showResults() const {
        election.displayResults();
        Display::winner();
    }
    void addCandidate(int id, const string& name, const string& party, const string& symbol) {
        if (!isAdminLoggedIn) {
            cout << "You must be logged in as an admin to add a candidate.\n";
            return;
        }
        election.addCandidate(id, name, party, symbol);
    }
    void saveData() const {
        ofstream voterFile("voters.txt");
        for (const auto& voter : voters) {
            voter.saveToFile(voterFile);
        }

        ofstream adminFile("admins.txt");
        for (const auto& admin : admins) {
            admin.saveToFile(adminFile);
        }

        election.saveToFile("election.txt");
    }
    void loadData() {
    ifstream voterFile("voters.txt");
    if (voterFile) {
        Voter tempVoter(0, "", "");
        while (voterFile >> tempVoter) {
            voters.push_back(tempVoter);
        }
        voterFile.close();
    } else {
        cout << "Voters file not found or could not be opened.\n";
    }
    ifstream adminFile("admins.txt");
    bool adminFound = false;
    if (adminFile) {
        Admin tempAdmin(0, "", "");
        while (adminFile >> tempAdmin) {
            admins.push_back(tempAdmin);
            adminFound = true;
        }
        adminFile.close();
    } else {
        cout << "Admins file not found or could not be opened.\n";
    }
    // Initial admin setup if no admin data exists
    if (!adminFound) {
        cout << "No admin accounts found. Creating an initial admin account.\n";
        int initialAdminID;
        string initialAdminName, initialAdminPassword;

        cout << "Enter Initial Admin ID: ";
        cin >> initialAdminID;
        cout << "Enter Initial Admin Name: ";
        cin >> initialAdminName;
        cout << "Enter Initial Admin Password: ";
        cin >> initialAdminPassword;

        Admin initialAdmin(initialAdminID, initialAdminName, initialAdminPassword);
        admins.push_back(initialAdmin);

        // Save the initial admin to the admin file
        ofstream adminFile("admins.txt", ios::app);
        if (adminFile) {
            initialAdmin.saveToFile(adminFile);
            cout << "Initial admin account successfully created and saved.\n";
        } else {
            cout << "Error saving initial admin data to file.\n";
        }
    }
    election.loadFromFile("election.txt");

    // Initial voter setup if no voters exist
    if (voters.empty()) {
        cout << "No voters found. Creating an initial voter account.\n";
        int initialVoterID;
        string initialVoterName, initialVoterPassword;

        cout << "Enter Initial Voter ID: ";
        cin >> initialVoterID;
        cout << "Enter Initial Voter Name: ";
        cin >> initialVoterName;
        cout << "Enter Initial Voter Password: ";
        cin >> initialVoterPassword;

        Voter initialVoter(initialVoterID, initialVoterName, initialVoterPassword);
        voters.push_back(initialVoter);

        // Save the initial voter to the voter file
        ofstream voterFile("voters.txt", ios::app);
        if (voterFile) {
            initialVoter.saveToFile(voterFile);
            cout << "Initial voter account successfully created and saved.\n";
        } else {
            cout << "Error saving initial voter data to file.\n";
        }
    } 

    // Initial candidate setup if no candidates exist
    if (election.getCandidates().empty()) {
        cout << "No candidates found. Creating an initial candidate account.\n";
        int initialCandidateID;
        string initialCandidateName, initialCandidateParty, initialCandidateSymbol;

        cout << "Enter Initial Candidate ID: ";
        cin >> initialCandidateID;
        cout << "Enter Initial Candidate Name: ";
        cin >> initialCandidateName;
        cout << "Enter Initial Candidate Party: ";
        cin >> initialCandidateParty;
        cout << "Enter Initial Candidate Symbol: ";
        cin >> initialCandidateSymbol;

        Candidate initialCandidate(initialCandidateID, initialCandidateName, initialCandidateParty, initialCandidateSymbol);
        election.addCandidate(initialCandidateID, initialCandidateName, initialCandidateParty, initialCandidateSymbol);

        // Save the initial candidate to the election file
        ofstream electionFile("election.txt", ios::app);
        if (electionFile) {
            initialCandidate.saveToFile(electionFile);
            cout << "Initial candidate account successfully created and saved.\n";
        } else {
            cout << "Error saving initial candidate data to file.\n";
        }
    }
}

    void displayMenu() {
        cout << "\n===== Election Management System =====\n";
        cout << "1. Login as Admin\n";
        cout << "2. Login as Voter\n";
        cout << "3. Add Candidate (Admin only)\n";
        cout << "4. Cast Vote (Voter only)\n";
        cout << "5. View Results\n";
        cout << "6. Save & Exit\n";
        cout << "Enter choice: ";
    }
void run() {
    Display::intro();
    loadData();
    bool running = true;
    bool isAdminLoggedIn = false;
    bool isVoterLoggedIn = false;
    
    while (running) {
        displayMenu();
        int choice;
        cin >> choice;
        int id;
        string pass;
        string name, party, symbol;  // Declare these variables outside the switch to make them accessible to all cases
        
        switch (choice) {
            case 1: // Admin login
                cout << "Enter Admin ID and Password: ";
                cin >> id >> pass;
                if (loginUser(id, pass, true)) {
                    isAdminLoggedIn = true;
                    cout << "Admin login successful.\n";
                    bool addingCandidates = true;
                    while (addingCandidates) {
                        cout << "Enter Candidate Details to Add:\n";
                        int candidateID;
                        cout << "Candidate ID: ";
                        cin >> candidateID;
                        cout << "Name: ";
                        cin >> name;
                        cout << "Party: ";
                        cin >> party;
                        cout << "Symbol: ";
                        cin >> symbol;
                        addCandidate(candidateID, name, party, symbol);

                        // Ask if the admin wants to add another candidate
                        char addMore;
                        cout << "Do you want to add another candidate? (y/n): ";
                        cin >> addMore;
                        if (addMore != 'y' && addMore != 'Y') {
                            addingCandidates = false;
                        }
                    }
                }
                break;
            case 2: // Voter login
                cout << "Enter Voter ID and Password: ";
                cin >> id >> pass;
                if (loginUser(id, pass, false)) {
                    isVoterLoggedIn = true;
                    cout << "Voter login successful.\n";
                    int candidateID;
                    cout << "Enter Candidate ID to vote for: ";
                    cin >> candidateID;
                    if (!castVote(candidateID)) {
                        cout << "Voting failed.\n";
                    }
                }
                break;
            case 3: // Add Candidate (Admin Only)
                if (!isAdminLoggedIn) {
                    cout << "You must be logged in as an admin to add a candidate.\n";
                    break;
                }
                cout << "Enter Candidate Details to Add:\n";
                int candidateID;
                cout << "Candidate ID: ";
                cin >> candidateID;
                cout << "Name: ";
                cin >> name;
                cout << "Party: ";
                cin >> party;
                cout << "Symbol: ";
                cin >> symbol;
                addCandidate(candidateID, name, party, symbol);
                break;
            case 4: // Cast Vote (Voter Only)
                if (!isVoterLoggedIn) {
                    cout << "You must be logged in as a voter to cast a vote.\n";
                    break;
                }
                int candidateIDToVote;
                cout << "Enter Candidate ID to vote for: ";
                cin >> candidateIDToVote;
                if (!castVote(candidateIDToVote)) {
                    cout << "Voting failed.\n";
                }
                break;
            case 5: // View Results
                showResults();
                break;
            case 6: // Save and Exit
                saveData();
                running = false;
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
};
int main() {
    ElectionManagementSystem system;
    system.run();
    return 0;
}