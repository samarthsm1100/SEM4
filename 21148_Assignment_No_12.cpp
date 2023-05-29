#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DirectAccessFile {
private:
    string filename;
    int recordSize;

public:
    DirectAccessFile(const string& filename, int recordSize) : filename(filename), recordSize(recordSize) {}

    void insertRecord(const string& recordData) {
        ofstream file(filename, ios::app);
        file << recordData << endl;
        file.close();
        cout << "Record inserted successfully." << endl;
    }

    void deleteRecord(int recordIndex) {
        ifstream inputFile(filename);
        ofstream outputFile(filename + ".temp");
        string record;
        int currentIndex = 0;

        while (getline(inputFile, record)) {
            if (currentIndex != recordIndex)
                outputFile << record << endl;
            currentIndex++;
        }

        inputFile.close();
        outputFile.close();
        remove(filename.c_str());
        rename((filename + ".temp").c_str(), filename.c_str());
        cout << "Record deleted successfully." << endl;
    }

    int getRecordCount() {
        ifstream file(filename);
        int count = 0;
        string record;

        while (getline(file, record))
            count++;

        file.close();
        return count;
    }
};

int main() {
    string filename = "data.txt";
    int recordSize = 100;
    DirectAccessFile file(filename, recordSize);

    int choice;
    string recordData;
    int recordIndex;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Insert record" << endl;
        cout << "2. Delete record" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the record data: ";
                cin.ignore();
                getline(cin, recordData);
                file.insertRecord(recordData);
                break;
            case 2:
                cout << "Enter the record index to delete: ";
                cin >> recordIndex;
                file.deleteRecord(recordIndex);
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    }
}
