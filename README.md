# Obits Table Generation
An automated way to generate the html table for our Obituary page. This program reads from any .csv file.
## Prep
Due to the presence of commas in table data that consists of names and hometowns, please change the delimiter of your .csv file from a comma to a semicolon. You can find a tutorial at https://www.spreadsheetweb.com/how-to-change-csv-delimiter-in-excel/.

Lines 15 and 18 of main.cpp contain the information needed by the user.
Place the columns needed from the .csv file on line 15. Make sure they are placed in the order that you want them to appear in the generated table.
```
vector<string> COLUMNS_TO_READ {"Full Name (w/ birth name)", "Degree", "Preferred Graduation Date", "Hometown", "Obituary Link"};
```
Enter the path to the .csv file on line 18.
```
fs::path PATH_TO_CSV_FILE = "Obits.csv";
```
## Run
Compile the program with `g++ -Wall -Werror -std=c++2a -g *.cpp`. Run the program with `./a.out`.
## Results
The program will generate the file `table.html` within your current directory. This file will contain the html rows needed for the table.
