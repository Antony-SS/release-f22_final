/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */

V2D file_to_V2D(const std::string & filename){
    // Your code here!
    V2D toReturn;

    std::string fileAsString = file_to_string(filename);

    // turning string into istringstream for getline processing
    std::istringstream fileStream;
    fileStream.str(fileAsString);

    std::vector<std::string> lines;

    for (std::string line; std::getline(fileStream, line);) {
        // for each line, split by comma and place array in the corresponding row
        std::vector<std::string> untrimmed;
        std::vector<std::string> toInsert;
        SplitString(line, ',', untrimmed);

        // iterate through comma split array and trim all white space
        for (std::string& word : untrimmed) {
            toInsert.push_back(Trim(word));
        }

        toReturn.push_back(toInsert);
    }

    return toReturn;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE

    // 2nd data structure actually could be an unordered set in both of these b/c we don't need a key value, only if we have seen it or not
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> studentSchedules;
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> courseRosters;

    for (auto studentSchedule : student) {
        std::string student = studentSchedule[0];
        std::unordered_map<std::string, bool> toInsert;
        for (unsigned i = 1; i < studentSchedule.size(); ++i) {
            toInsert.insert({studentSchedule.at(i), true});
        }
        studentSchedules.insert({student, toInsert});
    }

    for (auto courseRoster : cv) {
        std::string course = courseRoster[0];
        std::unordered_map<std::string, bool> toInsert;
        for (unsigned i = 1; i < courseRoster.size(); ++i) {
            toInsert.insert({courseRoster.at(i), true});
        }
        courseRosters.insert({course, toInsert});
    }

    V2D toReturn;
    for (auto courseRoster : cv) {
        std::vector<std::string> toInsert;
        std::string course = courseRoster[0];

        toInsert.push_back(course);
        
        for (unsigned i = 1; i < courseRoster.size(); ++i) {
            std::vector<std::string>::iterator it = courseRoster.begin();
            if (!(studentSchedules[courseRoster.at(i)][course] && courseRosters[course][courseRoster.at(i)])) {
                continue;
            } else {
                toInsert.push_back(courseRoster[i]);
            }
        }

        if (toInsert.size() <= 1) {
            // std::cout << "No students in course: " << courseRoster[0] << " so not adding!" << std::endl;
            continue;
        } else {
            toReturn.push_back(toInsert);
        }
    }

    return toReturn;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */

int** create2DArray(unsigned height, unsigned width)
    {
      int** array2D = 0;
      array2D = new int*[height];
    
      for (unsigned h = 0; h < height; h++)
      {
            array2D[h] = new int[width];
    
            for (unsigned w = 0; w < width; w++)
            {
              
                  array2D[h][w] = 0;
            }
      }
      return array2D;
}

int** constructGraph(const V2D& courses) {

    // construct 2D matrix for adj matrix of size n x n
    unsigned numOfCourses = courses.size();
    int** graph = create2DArray(numOfCourses, numOfCourses);

    // going to add edges to graph based on if they share a student, so must be able to tell which courses share students.  Using hash map.  Could be unordered set.
    std::unordered_map<std::string, std::unordered_map<std::string, bool>> courseRosters;

    for (auto courseRoster : courses) {
        std::string course = courseRoster[0];
        std::unordered_map<std::string, bool> toInsert;
        for (unsigned i = 1; i < courseRoster.size(); ++i) {
            toInsert.insert({courseRoster.at(i), true});
        }
        courseRosters.insert({course, toInsert});
    }

    for (unsigned i = 0; i < courses.size(); ++i) {
        std::string currentCourse = courses[i][0];
        for (unsigned j = 0; j < courses.size(); ++j) {
            if (j != i) {
                std::string otherCourse = courses[j][0];
                for (auto student : courses[i]) {
                    if (graph[i][j] != 1 && courseRosters[otherCourse][student]) {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    }
                }
            }
        }
    }

    unsigned i, j;
//     for(i = 0; i < numOfCourses; i++) {
//         for(j = 0; j < numOfCourses; j++) {
//             std::cout << graph[i][j] << " ";
//         }
//         std::cout << std::endl;
//    }

    return graph;

}

// taken from a stack overflow post - giving credit, this is a mundane thing


// call this at end of schedule
void delete2Darray(int**& array, unsigned height, unsigned width) {
     for (unsigned h = 0; h < height; h++) // loop variable wasn't declared
          {
            delete [] array[h];
          }
          delete [] array;
          array = nullptr;
}

std::vector<int> getAdj(int**& graph, unsigned graphSize, unsigned node) {
    std::vector<int> adjnodes;
    for (unsigned i = 0; i < graphSize; ++i) {
        if (i != node) {
            if (graph[node][i] == 1) {
                adjnodes.push_back(i);
            }
        }
    }

    return adjnodes;
}

V2D color(const V2D& courses, int** graph,  const std::vector<std::string>& timeslots, int start) {
    std::unordered_map<int, std::string> labels;
    V2D toReturn;

    for (unsigned i = 0; i < courses.size(); ++i) {
        unsigned trueIndex = (start + i) % courses.size();
        std::vector<int> adjNodes = getAdj(graph, courses.size(), trueIndex);
        std::unordered_map<std::string, bool> adjColors;

        for (int node : adjNodes) {
            auto search = labels.find(node);
            if (search != labels.end()) {
                std::string timeslot = search->second;
                adjColors.insert({timeslot, true});
            } 
        }

        for (auto timeslot : timeslots) {
            if (adjColors.find(timeslot) == adjColors.end()) {
                labels.insert({trueIndex, timeslot});
                break;
            } else if (timeslot == timeslots.at(timeslots.size() - 1)) {
                std::vector<std::string> notFound;
                notFound.push_back("-1");
                toReturn.push_back(notFound);
                return toReturn;
            }   
        }
    }

    for (auto timeslot : timeslots) {
        std::vector<std::string> toInsert;
        toInsert.push_back(timeslot);
        for (unsigned i = 0; i < courses.size(); ++i) {
            if (labels[i] == timeslot) {
                toInsert.push_back(courses[i][0]);
            }
        }

        toReturn.push_back(toInsert);
    }

    return toReturn;
}

V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    int ** graph = constructGraph(courses);
    
    V2D toReturn;

    unsigned int currentSize = 100000;
    for (unsigned i = 0; i < courses.size(); ++i) {
        V2D challenger = color(courses, graph, timeslots, i);
        if (challenger.size() < currentSize && challenger[0][0] != "-1") {
            toReturn = challenger;
            currentSize = challenger.size();
        }
    }

    if (currentSize == 100000) {
        std::vector<std::string> toInsert;
        toInsert.push_back("-1");
        toReturn.push_back(toInsert);
    }

    delete2Darray(graph, courses.size(), courses.size());

    // std::cout << std::endl;
    // std::cout << "Final Schedule" << std::endl;
    // for (unsigned i = 0; i < toReturn.size(); ++i) {
    //     for (unsigned j = 0; j < toReturn[i].size(); ++j) {
    //         std::cout << toReturn[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return toReturn;

}
