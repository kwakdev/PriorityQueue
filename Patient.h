#pragma once
#include "Ailment.h" 
#include "LinkedList.h" 
#include "PriorityQueue.h"
#include <string>
//evan kwak 1052443
class Patient {
public:
    std::string name_;

    LinkedList<Ailment> ailments_;
public:
    // Default constructor
    Patient() : name_(""), ailments_() {}

    // Parameterized constructor
    Patient(const std::string& name) : name_(name), ailments_() {} // Initialize ailments_ in the constructor

    std::string get_name() const { return name_; }

    // Method to add an ailment to the patient
    void add_ailment(const Ailment& ailment) {
        ailments_.push_back(ailment);
    }

    // Getter method to access the list of ailments
    const LinkedList<Ailment>& get_ailments()const {
        return ailments_;
    }

    // Method to calculate the patient's score
    int get_score() const {
        int score = 0;
        const LinkedList<Ailment>::Node* ailment = ailments_.begin();

        while (ailment != nullptr) {
            int severity = ailment->data.get_severity();
            int timeCriticality = ailment->data.get_time_sensitivity();
            int contagiousness = ailment->data.get_contagiousness();

            // Calculate the score for this ailment
            int ailmentScore = (severity * timeCriticality) + contagiousness;

            // Add the ailment's score to the patient's total score
            score += ailmentScore;

            ailment = ailment->next;
        }

        return score;
    }
    // Overloaded equality operator for comparing patients based on their names
    bool operator==(const Patient& other) const {
        return name_ == other.name_;
    }

    // Custom comparison function to determine if one patient has a lower priority than another
    bool is_less_than(const Patient& other) const {
        return get_score() < other.get_score();
    }
};
