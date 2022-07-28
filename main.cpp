#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<set>
#include<map>

using namespace std;

vector<string> COLUMNS_TO_READ {"Full Name (w/ birth name)", "Degree", "Preferred Graduation Date", "Hometown", "Obituary Link"};

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 2) {
        cout << "Incorrect number of command line arguments!" << endl;
        return 0;
    }
    string fileName = argv[1];

    ifstream inFile;
    inFile.open(fileName);
    if (!inFile.is_open()) {
        cout << "Could not open csv file!" << endl;
        return 0;
    }

    //Get the positions of the needed columns
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
            if (column == "Obituary Link" && value.substr(0, 4) == "http") {
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
    //outFile.close();




    return 0;
}