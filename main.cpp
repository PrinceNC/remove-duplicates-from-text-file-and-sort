#include <unordered_set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool wordSort(string &s1, string &s2) {
    return lexicographical_compare(
        begin(s1), end(s1),
        begin(s2), end(s2),
        [](const char& char1, const char& char2) {
            return tolower(char1) < tolower(char2);
        }
    );
}

int main(int argc, char **argv) {
    string fileName = "";
    
    // get file Name from arguments if available
    if (argc >= 2)
        fileName = argv[1];

    // prompt user for file name if not hardcoded or passed as launch argument
    if (fileName.length() == 0) {
        cout << "Enter file name: ";
        cin >> fileName;
    }

    // unordered set to store each line of the file
    unordered_set<string> lines;

    ifstream readFileStream(fileName);
    string textLine;

    // print error and return 1 if file specified cannot be opened
    if (!readFileStream.is_open()) {
        cerr << "Fatal Error: could not open " + fileName;
        return 1;
    }

    // read each line from file and insert into set
    cout << "Lines from file\n";
    while (getline(readFileStream, textLine)) {
        cout << textLine << " ";
        lines.insert(textLine);
    }

    readFileStream.close();

    cout << "\n\n\n";

    // create vector from set elements using iterators
    vector<string> v(lines.begin(), lines.end());

    // sort vector string elements in alphabetical order
    sort(v.begin(), v.end(), wordSort);

    vector<string>::iterator it;

    ofstream outFile("dedup" + fileName);
    
    // iterate over each element in vector and write to file
    cout << "Sorted lines\n";
    for (it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
        outFile << *it << "\n";
    }

    outFile.close();

    return 0;
}