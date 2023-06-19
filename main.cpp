//============================================================================
// Name        : main.cpp
// Author      : Joey Wheeler
// Version     : 1.0
// Description : This is my project 2 assignment.
//============================================================================

#include <iostream>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

struct Course {
    string code;
    string title;
    list<string> prerequisites;
};

list<Course> courseList;

//============================================================================
// Main
//============================================================================

int main() {
    string filePath = "courselist.csv";

    int choice = 0;
    while (choice != 4) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Courselist" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            try {
                csv::Parser parser(filePath, csv::DataType::eFILE);

                // Access and process the parsed data
                unsigned int rowCount = parser.rowCount();
                unsigned int columnCount = parser.columnCount();

                for (unsigned int row = 0; row < rowCount; ++row) {
                    Course course;
                    course.code = parser[row][0];
                    course.title = parser[row][1];

                    // Check if there are prerequisites listed in the row
                    if (columnCount > 2) {
                        for (unsigned int col = 2; col < columnCount; ++col) {
                            std::string prerequisite = parser[row][col];
                            course.prerequisites.push_back(prerequisite);
                        }
                    }

                    courseList.push_back(course);               // Add the Course object to the linked list
                }

            } catch (const csv::Error& e) {
                cerr << "Error: " << e.what() << endl;
            }

            break;

        case 2:
            if (courseList.empty()) {
                cout << "Course list is empty. Please load data structure first." << endl;
            } else {
                cout << "Course List:" << endl;
                for (const Course& course : courseList) {
                    cout << "Code: " << course.code << endl;
                    cout << "Title: " << course.title << endl;
                    cout << "Prerequisites: ";
                    if (course.prerequisites.empty()) {
                        cout << "None";
                    } else {
                        for (const string& prerequisite : course.prerequisites) {
                            cout << prerequisite << " ";
                        }
                    }
                    cout << endl << "---------------------" << endl;
                }
            }

            break;

        case 3:
            if (courseList.empty()) {
                cout << "Course list is empty. Please load data structure first." << endl;
            } else {
                string courseCode;
                cout << "Enter the course code: ";
                cin >> courseCode;

                bool courseFound = false;
                for (const Course& course : courseList) {
                    if (course.code == courseCode) {
                        cout << "Code: " << course.code << endl;
                        cout << "Title: " << course.title << endl;
                        cout << "Prerequisites: ";
                        if (course.prerequisites.empty()) {
                            cout << "None";
                        } else {
                            for (const string& prerequisite : course.prerequisites) {
                                cout << prerequisite << " ";
                            }
                        }
                        cout << endl;
                        courseFound = true;
                        break;
                    }
                }

                if (!courseFound) {
                    cout << "Course not found." << endl;
                }
            }
            break;

    }

    cout << "Good bye." << endl;

	return 0;
    }
}
