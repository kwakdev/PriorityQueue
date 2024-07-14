#pragma once
//evan kwak 1052443

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// Class representing an Ailment
class Ailment
{
private:
    std::string name_;
    int severity_;
    int time_sensitivity_;
    int contagiousness_;

public:
    // Default constructor
    Ailment() : name_(""), severity_(0), time_sensitivity_(0), contagiousness_(0) { }

    // Constructor with only name
    Ailment(const std::string& name) : name_(name) {}

    // Constructor with all parameters
    Ailment(const std::string& name, int severity, int time_sensitivity, int contagiousness)
        : name_(name), severity_(severity), time_sensitivity_(time_sensitivity), contagiousness_(contagiousness) {}

    // Getter for the name
    std::string get_name() const { return name_; }

    // Getter for the severity
    int get_severity() const { return severity_; }

    // Getter for the time sensitivity
    int get_time_sensitivity() const { return time_sensitivity_; }

    // Getter for the contagiousness
    int get_contagiousness() const { return contagiousness_; }

    // Overloaded equality operator
    bool operator==(const Ailment& other) const {
        // Compare the relevant members for equality
        return (name_ == other.name_ && severity_ == other.severity_
            && time_sensitivity_ == other.time_sensitivity_ && contagiousness_ == other.contagiousness_);
    }
};
