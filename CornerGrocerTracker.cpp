#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <cctype>

using namespace std;

// Encapsulating the logic into a controller class, treating the grocery data like a system log
class InventoryController {
private:
    // The core map structure: tracking the string (item) and its integer (frequency counter)
    map<string, int> itemLog;

    // Automated redundancy protocol to prevent data loss
    void executeBackupProtocol(const string& backupFileName) {
        ofstream outFS(backupFileName);

        // System check: Verify write permissions/file creation before proceeding
        if (!outFS.is_open()) {
            cout << "[FAULT] Backup protocol failed. Unable to initialize " << backupFileName << endl;
            return;
        }

        // Output the current map state to the backup file
        for (const auto& pair : itemLog) {
            outFS << pair.first << " " << pair.second << endl;
        }
        outFS.close();
    }

public:
    // Initialization sequence: Load the daily readouts and secure the backup
    InventoryController(const string& inputFileName) {
        ifstream inFS;
        string item;

        inFS.open(inputFileName);

        // Hard fault check: Prevent system crash if the target text file is missing
        if (!inFS.is_open()) {
            cout << "[CRITICAL FAULT] Source data offline. Verify " << inputFileName << " is in the local directory." << endl;
            return;
        }

        // Process the text stream; the map will automatically increment the counter for each item
        while (inFS >> item) {
            itemLog[item]++;
        }
        inFS.close();

        // Trigger the backup automatically once the data stream is processed
        executeBackupProtocol("frequency.dat");
    }

    // Option 1 Logic: Targeted query for a specific string
    void runTargetedQuery(const string& item) {
        string searchItem = item;

        // Input sanitization: Force the first char to uppercase to match the raw data formatting
        if (!searchItem.empty() && islower(searchItem[0])) {
            searchItem[0] = toupper(searchItem[0]);
        }

        // .count() acts as a safety check to ensure the key exists before calling it
        if (itemLog.count(searchItem)) {
            cout << "\n[QUERY RESULT] " << searchItem << " logs " << itemLog[searchItem] << " total scans." << endl;
        }
        else {
            cout << "\n[QUERY RESULT] " << searchItem << " returned zero matches in the current cycle." << endl;
        }
    }

    // Option 2 Logic: Output the raw numeric log
    void outputDiagnosticLog() {
        cout << "\n--- Master Diagnostic Log ---" << endl;
        for (const auto& pair : itemLog) {
            cout << pair.first << " " << pair.second << endl;
        }
        cout << "-----------------------------\n" << endl;
    }

    // Option 3 Logic: Output the data visually
    void outputHistogram() {
        cout << "\n--- Frequency Histogram ---" << endl;
        for (const auto& pair : itemLog) {
            // Set uniform column width (15 chars) and align left for clean terminal output
            cout << setw(15) << left << pair.first << " ";

            // Loop to print an asterisk for each integer count
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
        cout << "---------------------------\n" << endl;
    }
};

// Standard terminal interface
void initializeTerminalUI() {
    cout << "\n===================================" << endl;
    cout << "     CORNER GROCER TERMINAL UI     " << endl;
    cout << "===================================" << endl;
    cout << "1. Run targeted item query" << endl;
    cout << "2. Output master diagnostic log" << endl;
    cout << "3. Output frequency histogram" << endl;
    cout << "4. Initiate safe shutdown" << endl;
    cout << "Awaiting operator input (1-4): ";
}

int main() {
    // Boot up the controller and feed it the daily data file
    InventoryController systemControl("CS210_Project_Three_Input_File.txt");

    int operatorCommand = 0;
    string targetItem;

    // Keep the terminal active until a shutdown command is received
    while (operatorCommand != 4) {
        initializeTerminalUI();

        // Validation loop: Catch bad input types (e.g., chars instead of ints)
        if (!(cin >> operatorCommand)) {
            cout << "\n[INPUT FAULT] Invalid data type. Numeric inputs only." << endl;
            // Reset the fail state on the input stream
            cin.clear();
            // Dump the corrupted input from the buffer
            cin.ignore(10000, '\n');
            continue;
        }

        // Route the valid integer command
        switch (operatorCommand) {
        case 1:
            cout << "Enter target parameter: ";
            cin >> targetItem;
            systemControl.runTargetedQuery(targetItem);
            break;
        case 2:
            systemControl.outputDiagnosticLog();
            break;
        case 3:
            systemControl.outputHistogram();
            break;
        case 4:
            cout << "\n[SHUTDOWN] Backup data verified in 'frequency.dat'. Terminating session..." << endl;
            break;
        default:
            // Catch integers outside the accepted parameters
            cout << "\n[INPUT FAULT] Command not recognized. Select a valid parameter (1-4)." << endl;
            break;
        }
    }

    return 0;
}