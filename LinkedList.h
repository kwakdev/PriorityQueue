#pragma once
#pragma once

#include <exception> 
//evan kwak 1052443

template <typename T>
class LinkedList {
public:

    struct Node {
        Node* previous;
        Node* next;
        const T data;

        // Default constructor initializing pointers to nullptr and data to default value
        Node() : previous(nullptr), next(nullptr), data(T()) { }

        // Constructor initializing data with a provided item
        Node(const T& item) : previous(nullptr), next(nullptr), data(item) { }
    };

protected:
    Node* begin_;   // Pointer to the first node in the list
    Node* end_;     // Pointer to the last node in the list

public:
    // Default constructor initializing begin_ and end_ to nullptr
    LinkedList() : begin_(nullptr), end_(nullptr) {}

    // Getter for the beginning of the list (const version)
    const Node* begin() const { return begin_; }

    // Getter for the end of the list (const version)
    const Node* end() const { return end_; }

    // Getter for the beginning of the list (non-const version)
    Node* begin() { return begin_; }

    // Getter for the end of the list (non-const version)
    Node* end() { return end_; }

    // Function to add a new element to the front of the list
    void push_front(const T& item) {
        Node* node = new Node(item);

        if (begin_ != nullptr) {
            begin_->previous = node;
            node->next = begin_;
        }
        else {
            end_ = node;
        }

        begin_ = node;
    }

    // Function to add a new element to the back of the list
    void push_back(const T& item) {
        Node* node = new Node(item);

        if (begin_ == nullptr && end_ == nullptr) {
            begin_ = node;
            end_ = node;
        }
        else {
            node->previous = end_;
            end_->next = node;
            end_ = node;
        }
    }

    // Function to remove and return the element from the front of the list
    T pop_front() {
        Node* node = begin_;
        const T value = node->data;
        begin_ = node->next;

        if (begin_ != nullptr) {
            begin_->previous = nullptr;
        }

        delete node; // Release memory

        return value;
    }

    // Function to remove and return the element from the back of the list
    T pop_back() {
        Node* node = end_;
        const T value = node->data;
        end_ = node->previous;

        if (end_ != nullptr) {
            end_->next = nullptr;
        }

        delete node; // Release memory

        return value;
    }

    // Function to check if the list is empty
    bool empty() const {
        return begin_ == nullptr;
    }

    // Function to get the size of the list
    size_t size() const {
        size_t counter = 0;
        Node* node = begin_;

        while (node != nullptr) {
            ++counter;
            node = node->next;
        }

        return counter;
    }

    // Function to insert a new element after a given node
    void insert_after(Node* prevNode, const T& item) {
        if (prevNode == nullptr) {
            return;
        }

        Node* newNode = new Node(item);
        Node* nextNode = prevNode->next;

        newNode->previous = prevNode;
        newNode->next = nextNode;

        prevNode->next = newNode;

        if (nextNode != nullptr) {
            nextNode->previous = newNode;
        }
        else {
            end_ = newNode;
        }
    }
};
