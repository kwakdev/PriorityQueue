#pragma once 
#include "LinkedList.h"
//evan kwak 1052443

template <typename T>
class PriorityQueue {
private:
    LinkedList<T> list;

public:
    PriorityQueue() {}  // Default constructor

    // Returns a reference to the front element in the priority queue
    const T& front() const {
        if (list.empty()) {
            // Handle case when the priority queue is empty
        }
        return list.begin()->data;
    }

    // Enqueues an element based on its priority
    void enqueue(const T& patient) {
        if (list.empty()) {
            // If the list is empty, simply add the patient to the end
            list.push_back(patient);
        }
        else {
            auto current = list.begin();

            // Find the appropriate position based on priority
            while (current != nullptr && current->data.get_score() >= patient.get_score()) {
                current = current->next;
            }

            if (current == nullptr) {
                // If reached the end, add the patient to the end
                list.push_back(patient);
            }
            else if (current == list.begin()) {
                // If at the beginning, add the patient to the front
                list.push_front(patient);
            }
            else {
                // Insert the patient after the previous element
                auto previous = current->previous;
                list.insert_after(previous, patient);
            }
        }
    }

    // Dequeues the front element from the priority queue
    T dequeue() {
        if (list.empty()) {
            // Handle case when attempting to dequeue from an empty priority queue
            throw "";
        }
        return list.pop_front();
    }

    // Checks if the priority queue is empty
    bool empty() const {
        return list.empty();
    }

    // Returns an iterator to the beginning of the linked list
    typename LinkedList<T>::Node* begin() {
        return list.begin();
    }

    // Returns a const iterator to the beginning of the linked list
    const typename LinkedList<T>::Node* begin() const {
        return list.begin();
    }

    // Returns the number of elements in the priority queue
    size_t size() const {
        return list.size();
    }
};
