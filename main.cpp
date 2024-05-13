#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<string> readPasswordsFromFile(const string& filename) {
    ifstream file(filename);
    vector<string> passwords;
    string password;
    while (getline(file, password)) {
        passwords.push_back(password);
    }
    return passwords;
}

int countNumericPasswords(const vector<string>& passwords) {
    int count = 0;
    for (const string& password : passwords) {
        if (all_of(password.begin(), password.end(), ::isdigit)) {
            count++;
        }
    }
    return count;
}

vector<string> findDuplicatePasswords(const vector<string>& passwords) {
    unordered_set<string> seen;
    vector<string> duplicates;
    for (const string& password : passwords) {
        if (seen.count(password)) {
            duplicates.push_back(password);
        } else {
            seen.insert(password);
        }
    }
    sort(duplicates.begin(), duplicates.end());
    duplicates.erase(unique(duplicates.begin(), duplicates.end()), duplicates.end());
    return duplicates;
}

int countUsersWithConsecutiveChars(const vector<string>& passwords) {
    int count = 0;
    for (const string& password : passwords) {
        for (size_t i = 0; i <= password.size() - 4; ++i) {
            if (isascii(password[i]) && isascii(password[i+1]) && isascii(password[i+2]) && isascii(password[i+3])) {
                count++;
                break;
            }
        }
    }
    return count;
}

int countValidPasswords(const vector<string>& passwords) {
    int count = 0;
    for (const string& password : passwords) {
        bool hasDigit = any_of(password.begin(), password.end(), ::isdigit);
        bool hasLowercase = any_of(password.begin(), password.end(), ::islower);
        bool hasUppercase = any_of(password.begin(), password.end(), ::isupper);
        if (hasDigit && hasLowercase && hasUppercase) {
            count++;
        }
    }
    return count;
}

int main() {
    const vector<string> passwords = readPasswordsFromFile("hasla.txt");

    int result1 = countNumericPasswords(passwords);
    vector<string> result2 = findDuplicatePasswords(passwords);
    int result3 = countUsersWithConsecutiveChars(passwords);
    int result4 = countValidPasswords(passwords);


    ofstream outputFile("wyniki_hasla.txt");
    if (outputFile.is_open()) {
        outputFile << "74.1. " << result1 << endl;
        outputFile << "74.2. ";
        for (const string& password : result2) {
            outputFile << password << endl;
        }
        outputFile << "74.3. " << result3 << endl;
        outputFile << "74.4. " << result4 << endl;
        outputFile.close();
        cout << "Wyniki zostały zapisane do pliku wyniki_hasla.txt" << endl;
    } else {
        cout << "Błąd przy zapisie do pliku wyniki_hasla.txt" << endl;
    }

    return 0;
}
