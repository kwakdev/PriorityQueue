#include <iostream>
#include <fstream>
#include <sstream>


#include "../Priority Queue/Patient.h"
//evan kwak 1052443

PriorityQueue<Patient> queue;

LinkedList<Patient> postqueue;

// Function to save patients to a CSV file
void savePatientsToCSV(const std::string& filePath, const PriorityQueue<Patient>& patientQueue) {
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open or create the file " << filePath << std::endl;
        return;
    }

    int position = 0;
    auto current = patientQueue.begin();

    while (current != nullptr) {
        const Patient& patient = current->data;

        // Write patient name to the file
        outputFile << patient.get_name() << ",";

        // Write each ailment's details to the file
        const LinkedList<Ailment>& ailments = patient.get_ailments();
        const LinkedList<Ailment>::Node* ailmentNode = ailments.begin();

        while (ailmentNode != nullptr) {
            const Ailment& ailment = ailmentNode->data;

            outputFile << ailment.get_name() << ","
                << ailment.get_severity() << ","
                << ailment.get_time_sensitivity() << ","
                << ailment.get_contagiousness();

            ailmentNode = ailmentNode->next;

            if (ailmentNode != nullptr) {
                outputFile << ",";
            }
        }

        outputFile << "\n";

        ++position;
        current = current->next;
    }

    outputFile.close();
}

// Function to load patients from a CSV file
void loadPatientsFromCSV(const std::string& filePath, PriorityQueue<Patient>& patientQueue) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file " << filePath << std::endl;
        return;
    }

    std::string csvLine;

    // Read each line from the CSV file
    while (std::getline(inputFile, csvLine)) {
        std::istringstream lineStream(csvLine);
        std::string token;

        // Get the patient's name from the CSV line
        std::getline(lineStream, token, ',');
        if (token.empty()) {
            std::cerr << "Error: Invalid CSV line - missing patient name." << std::endl;
            continue;
        }

        // Create a patient with the extracted name
        Patient patient(token);

        // Read ailment details from the CSV line and add them to the patient
        while (std::getline(lineStream, token, ',')) {
            int severity = std::stoi(token);

            if (!std::getline(lineStream, token, ',')) {
                break;
            }

            std::string ailmentName = token;

            if (!std::getline(lineStream, token, ',')) {
                std::cerr << "Error: Incomplete ailment details in CSV line." << std::endl;
                break;
            }

            int timeSensitivity = std::stoi(token);

            if (!std::getline(lineStream, token, ',')) {
                std::cerr << "Error: Incomplete ailment details in CSV line." << std::endl;
                break;
            }

            int contagiousness = std::stoi(token);

            // Create an Ailment object and add it to the patient
            Ailment ailment(ailmentName, severity, timeSensitivity, contagiousness);
            patient.add_ailment(ailment);
        }


        // Add the patient to the priority queue
        patientQueue.enqueue(patient);
    }
    std::cout << "CSV LOADED!" << std::endl;

    inputFile.close();
}

// Function to prompt the user for a CSV file path and load patients from it
void load() {
    std::string filePath = "./patients.csv";
    loadPatientsFromCSV(filePath, queue);
}

// Function to prompt the user for a CSV file path and save patients to it
void save() {
    std::string filePath = "./patients.csv";
    savePatientsToCSV(filePath, queue);
}

// Function to process the next patient in the queue
void processNextPatient(PriorityQueue<Patient>& patientQueue) {
    Patient nextPatient = queue.dequeue();
    std::cout << nextPatient.get_name() << " moved to patient room!" << std::endl;

    // Add the processed patient to the history linked list
    postqueue.push_front(nextPatient);

    if (!patientQueue.empty()) {
        const Patient& nextPatient = patientQueue.front();
        std::cout << "Next in queue: " << nextPatient.get_name() << " with priority score " << nextPatient.get_score() << std::endl;
    }
    else {
        std::cout << "No more patients in the queue." << std::endl;
    }
}

// Function to print the current patient queue
void printQueue(const PriorityQueue<Patient>& patientQueue) {
    if (patientQueue.empty()) {
        std::cout << "The queue is empty." << std::endl;
        return;
    }

    int position = 0;
    auto current = patientQueue.begin();

    while (current != nullptr) {
        const Patient& currentPatient = current->data;

        std::cout << position << " : ";
        std::cout << currentPatient.get_name() << " - " << currentPatient.get_score() << " - ";

        // Print each ailment's name in the patient's ailments
        const LinkedList<Ailment>& ailments = currentPatient.get_ailments();
        const LinkedList<Ailment>::Node* ailmentNode = ailments.begin();

        while (ailmentNode != nullptr) {
            const Ailment& currentAilment = ailmentNode->data;
            std::cout << currentAilment.get_name() << ", ";

            ailmentNode = ailmentNode->next;
        }

        std::cout << std::endl;

        ++position;
        current = current->next;
    }
}

// Function to print the history of processed patients
void printQueueHistory(const LinkedList<Patient>& patientQueue) {
    if (patientQueue.empty()) {
        std::cout << "The queue is empty." << std::endl;
        return;
    }

    std::cout << "History:" << std::endl;
    auto current = patientQueue.begin();

    while (current != nullptr) {
        const Patient& currentPatient = current->data;

        std::cout << currentPatient.get_name() << " - " << currentPatient.get_score() << " - ";

        // Print each ailment's name in the patient's ailments
        const LinkedList<Ailment>& ailments = currentPatient.get_ailments();
        const LinkedList<Ailment>::Node* ailmentNode = ailments.begin();

        while (ailmentNode != nullptr) {
            const Ailment& currentAilment = ailmentNode->data;
            std::cout << currentAilment.get_name() << ", ";

            ailmentNode = ailmentNode->next;
        }

        std::cout << std::endl;

        current = current->next;
    }
}

// Function to add a new user to the patient queue
void addUser() {
    std::string patientName;
    std::cout << "Enter patient's name: ";

    // Ignore any leftover characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read the patient's name
    std::getline(std::cin, patientName);

    // Create a Patient object with the entered name
    Patient patientClass(patientName);

    // Loop to add ailments to the patient
    do {
        std::string ailmentName;
        int severity, timeCriticality, contagiousness;

        // Prompt the user for ailment details
        std::cout << "Enter ailment name (press Enter to stop adding ailments): ";
        std::getline(std::cin, ailmentName);

        // Break the loop if the user presses Enter without entering an ailment name
        if (ailmentName.empty()) {
            break;
        }

        std::cout << "Enter severity: ";
        std::cin >> severity;

        std::cout << "Enter time criticality: ";
        std::cin >> timeCriticality;

        std::cout << "Enter contagiousness: ";
        std::cin >> contagiousness;

        // Ignore any leftover characters in the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Create an Ailment object and add it to the patient
        Ailment ailment(ailmentName, severity, timeCriticality, contagiousness);
        patientClass.add_ailment(ailment);

    } while (true);

    // Add the patient to the  priority queue
    queue.enqueue(patientClass);
}

int main(int argc, char* argv[]) {
    int choice;

    // Main menu loop
    do {
        // Display menu options
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cout << "Welcome to Evan's Medical Center" << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Please Make A Selection:" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "		1 - Add Patient" << std::endl;
        std::cout << "		2 - Process Next Patient In Queue" << std::endl;
        std::cout << "		3 - Display Queue" << std::endl;
        std::cout << "		4 - View Processed Patients History" << std::endl;
        std::cout << "		5 - Load Queue" << std::endl;
        std::cout << "		6 - Save Queue" << std::endl;
        std::cout << "		7 - Exit" << std::endl;
        // Prompt the user for their choice
        std::cin >> choice;

        // Process user choice
        switch (choice) {
        case 1:
            addUser();
            break;
        case 2:
            processNextPatient(queue);
            break;
        case 3:
            printQueue(queue);
            break;
        case 4:
            printQueueHistory(postqueue);
            break;
        case 5:
            load();
            break;
        case 6:
            save();
            break;
        case 7:
            std::cout << "Leaving Queue\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

