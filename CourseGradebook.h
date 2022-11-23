#ifndef COURSEGRADEBOOK_H
#define COURSEGRADEBOOK_H

#include <algorithm>
#include "Gradebook.h"

class CourseGradebook : public Gradebook {
protected:
   // Your code here
std::unordered_map<std::string, std::unordered_map<int,double>*> assignmentMap;


public:
virtual ~CourseGradebook() {
    // Your code here, if needed
    for (auto& pair: assignmentMap) {
        delete pair.second;
    }
}

std::unordered_map<int, double> GetAssignmentScores(
    std::string assignmentName) override {
    // Your code here (remove placeholder line below)
    if (0 == assignmentMap.count(assignmentName)) {
        return std::unordered_map<int,double>();
    }
    return *assignmentMap[assignmentName];
}

double GetScore(std::string assignmentName, int studentID) override {
    // Your code here (remove placeholder line below)
    if (0 == assignmentMap.count(assignmentName)) {
            return NAN;
    }
    
    std::unordered_map<int, double>& assignment = *assignmentMap[assignmentName];
    
    if(assignment.count(studentID) > 0) {
        return assignment[studentID];
    }
    return NAN;
}

std::vector<std::string> GetSortedAssignmentNames() override {
    // Your code here (remove placeholder line below)
    std::vector<std::string> names;
    for (auto& pair : assignmentMap) {
        names.push_back(pair.first);
    }
    
    std::sort(names.begin(), names.end());
    return names;
    
}

// GetSortedStudentIDs() returns a vector with all distinct student IDs,
// sorted in ascending order.
std::vector<int> GetSortedStudentIDs() override {
    // Your code here (remove placeholder line below)
    using namespace std;
    
    vector<int> result;
    std::unordered_map<int, bool> distinctIDs;
    
    for (auto& pair: assignmentMap) {
        std::unordered_map<int, double>* tempMap = assignmentMap[pair.first];
        for (auto& idScorePair : *tempMap) {
        if ( 0 == distinctIDs.count(idScorePair.first)) {
            distinctIDs[idScorePair.first] = true;
            result.push_back(idScorePair.first);
        }
        }
    }
    
    std::sort(result.begin(), result.end());
    return result;
    
}

// GetStudentScores() gets all scores that exist in the gradebook for the
// student whose ID equals the studentID parameter. Scores are returned as
// an unordered_map that maps an assignment name to the student's
// corresponding score for that assignment.
std::unordered_map<std::string, double> GetStudentScores(
    int studentID) override {
    // Your code here (remove placeholder line below)
    std::unordered_map<std::string, double> result;
    
    for (auto& pair: assignmentMap) {
        std::unordered_map<int, double>* tempMap = assignmentMap[pair.first];
        
        if(pair.second->count(studentID) > 0) {
        result[pair.first] = (*tempMap)[studentID];
        }
    }
    return result;
}

void SetScore(std::string assignmentName, int studentID, double score) override {
    // Your code here
    if ( 0 == assignmentMap.count(assignmentName)) {
        assignmentMap[assignmentName] = new std::unordered_map<int, double>();
    }
    
    std::unordered_map<int,double>* map = assignmentMap[assignmentName];
    
    (*map)[studentID] = score;
}
};

#endif