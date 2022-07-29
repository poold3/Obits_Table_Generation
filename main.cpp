#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<set>
#include<map>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

//Enter the columns of the CSV to be put in the table here.
//Enter the columns in the order that you want them to appear in the table.
vector<string> COLUMNS_TO_READ {"Full Name (w/ birth name)", "Degree", "Preferred Graduation Date", "Hometown", "Obituary Link"};

//Enter the path to the CSV file from the current directory here
fs::path PATH_TO_CSV_FILE = "Summer.csv";

int main() {

    //Verify that PATH_TO_CSV_FILE is a valid path
    if (fs::exists(PATH_TO_CSV_FILE) == false) {
        cout << PATH_TO_CSV_FILE << " is not a valid path to an existing file!" << endl;
        return 0;
    }
    //Verify that PATH_TO_CSV_FILE is a .csv file
    if (PATH_TO_CSV_FILE.extension() != ".csv") {
        cout << PATH_TO_CSV_FILE << " is not a .csv file!" << endl;
        return 0;
    }

    ifstream inFile;
    inFile.open(PATH_TO_CSV_FILE);
    if (!inFile.is_open()) {
        cout << "Could not open csv file!" << endl;
        return 0;
    }

    //Get the positions of the needed columns stored in a map
    set<string> columnsToRead;
    for (string column: COLUMNS_TO_READ) {
        columnsToRead.insert(column);
    }
    string csvColumns, csvColumn;
    getline(inFile, csvColumns);
    stringstream ss(csvColumns);

    map<string,int> columnsAndPositions;
    int columnPosition = 0;
    while (getline(ss, csvColumn, ';')) {
        if (columnsToRead.find(csvColumn) != columnsToRead.end()) {
            columnsAndPositions.insert(pair<string,int>(csvColumn, columnPosition));
        }
        ++columnPosition;
    }

    //Go through each line of the csv file and build out the table using ofstream
    ofstream outFile;
    outFile.open("table.html");
    if (!outFile.is_open()) {
        cout << "Could not open table.html!" << endl;
        return 0;
    }
    while (getline(inFile, csvColumns)) {
        outFile << "<tr>" << endl;
        stringstream ss(csvColumns);
        vector<string> rowResults;
        while (getline(ss, csvColumn, ';')) {
            rowResults.push_back(csvColumn);
        }
        for (string column: COLUMNS_TO_READ) {
            string value = rowResults.at(columnsAndPositions.at(column));
            outFile << "<td>";
            //If the value begins with "http", the value is a link. Probably the obituary link.
            if (value.substr(0, 4) == "http") {
                outFile << "<a href=\"" << value << "\">" << value << "</a>";
            }
            else {
                outFile << value;
            }
            outFile << "</td>" << endl;
        }
        outFile << "</tr>" << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}