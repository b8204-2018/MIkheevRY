#include <iostream>
#include "string.h"
#include "vector"
#include <fstream>
#include "math.h"

using namespace std;

class SolverTasks {
public:
    virtual int* calculateTask(int *variables) = 0;
};

class Reader{
public:
    string returnExercise(string nameFile) const {
        string exercise;
        ifstream yourFile;
        yourFile.open(nameFile, ios_base::in);
        if (!yourFile.is_open())
            throw invalid_argument(nameFile);
            int format(0);
            yourFile >> format;
            yourFile >> exercise;
            yourFile.close();
       
        return exercise;
    }

    int discoverFormatTaskInFile(string nameFile) const {
        int format(0);
        ifstream yourFile;
        yourFile.open(nameFile, ios_base::in);
        if (!yourFile.is_open())
            throw invalid_argument(nameFile);
            yourFile >> format;
            yourFile.close();
        return format;
    }
};

class Writer {
private:
    string nameFile;
public:
    Writer(string file){
        nameFile = file;
    }

    void writeSolverOnTheScreen(int *answer, string nameFile) {
        cout << "Решение из файла: \"" << nameFile << "\"" << endl;
        for (int i = 1; i <= answer[0]; i++) {
            cout << "Ответ " << i << " :  " << answer[i] << endl;
        }
        cout << endl;
    }

    void writeSolverOnTheFile(int *answer, string numbFile) {
        ofstream outputFile;
        ifstream outputFileForCheck;
        string str;
        outputFile.open(nameFile, ios_base::app);
        outputFileForCheck.open(nameFile, ios_base::in);
        if (outputFileForCheck.is_open()) {
            outputFile << "Решение из файла: \"" << numbFile << "\"" << endl;
            for(int i = 1; i <= answer[0]; i++) {
                outputFile << "Ответ " << i << " :  " << answer[i] << endl;
            }
            outputFile << endl;
        }
        outputFile.close();
        outputFileForCheck.close();
    }

    void setFile(string nameFile){
        this->nameFile = nameFile;
    }
};

class DirectoreSolutions {
private:
    vector<SolverTasks*> AllSolverTask;
public:
    void addSolutionTask(SolverTasks &SolverTask) {
        AllSolverTask.push_back(&SolverTask);
    }

    SolverTasks* returnSolverTask(int howReturnSolverTask) const {
        return AllSolverTask[howReturnSolverTask - 1];
    }
};

class Parser {                                    // Ну да у KillReal'а, а кому сейчас легко? (Я разобрался как это работает).
    int isNum(char symbol) const {
        if (symbol >= 48 && symbol <= 57) {
            return -(48 - symbol);
        }
        return -1;
    }
public:
    int *takeVariabels(string exercize) const {
        int *vars = new int[5];
        int count = 0, i = 0;
        while (exercize[i] != '\0') {
            if (isNum(exercize[i]) == -1) {
                if ((exercize[i] == 'x') && (exercize[i + 1] == '2'))
                    i++;
                i++;
            }
            else {
                int temp = 0;
                int j = i;
                for (j; isNum(exercize[j]) != -1; j++) {
                    temp = temp * 10 + isNum(exercize[j]);
                }
                if (i > 0) {
                    if (exercize[i - 1] == '-') {
                        temp = -temp;
                    }
                }
                vars[count] = temp;
                count++;
                i = j;
            }
        }
        return vars;
    }
};

class Calculator {
private:
    SolverTasks *CurrentSolver;
public:
    Calculator(SolverTasks &Solver){
        CurrentSolver = &Solver;
    }

    void setSolverTask(const DirectoreSolutions &DirectoreSolution, int howSolveTask) {
        CurrentSolver = DirectoreSolution.returnSolverTask(howSolveTask);
    }

    int* calculateTask(const DirectoreSolutions &DirectoreSolutions, const Reader &Reader, const Parser &Parser, string nameFile) {
        return CurrentSolver->calculateTask(Parser.takeVariabels(Reader.returnExercise(nameFile)));
    }
};

class TaskSolver1 : public SolverTasks {
public:
    int* calculateTask(int *variables) override  {
        int* answer = new int[3];
        answer[0] = 2;
        if ((variables[1] * variables[1] - 4 * variables[0] * variables[2]) >= 0) {
            answer[1] = (-1 * variables[1] + sqrt(variables[1] * variables[1] - 4 * variables[0] * variables[2])) / (2 * variables[0]);
            answer[2] = (-1 * variables[1] - sqrt(variables[1] * variables[1] - 4 * variables[0] * variables[2])) / (2 * variables[0]);
        }
        return answer;
    }
};

class TaskSolver2 : public SolverTasks {
public:
    int* calculateTask(int *variables) override {
        int* answer = new int[2];
        answer[0] = 1;
        answer[1] = (variables[0] + variables[1]);
        return answer;
    }
};

class TaskSolver3 : public SolverTasks {
public:
    int* calculateTask(int *variables) override {
        int* answer = new int[2];
        answer[0] = 1;
        answer[1] = (variables[0] - variables[1]);
        return answer;
    }
};

class TaskSolver4 : public SolverTasks {
public:
    int* calculateTask(int *variables) override {
        int* answer = new int[2];
        answer[0] = 1;
        answer[1] = (variables[0] * variables[1]);
        return answer;
    }
};

class TaskSolver5 : public SolverTasks {
public:
    int* calculateTask(int *variables) override {
        int* answer = new int[2];
        answer[0] = 1;
        answer[1] = (variables[0] / variables[1]);
        return answer;
    }
};


int main() {
    Reader Reader;
    Writer Writer("out.txt");
    Parser Parser;
    DirectoreSolutions DirectoreSolutions;

    TaskSolver1 SolverTask1;
    TaskSolver2 SolverTask2;
    TaskSolver3 SolverTask3;
    TaskSolver4 SolverTask4;
    TaskSolver5 SolverTask5;

    DirectoreSolutions.addSolutionTask(SolverTask1);
    DirectoreSolutions.addSolutionTask(SolverTask2);
    DirectoreSolutions.addSolutionTask(SolverTask3);
    DirectoreSolutions.addSolutionTask(SolverTask4);
    DirectoreSolutions.addSolutionTask(SolverTask5);

    Calculator Calculator(*DirectoreSolutions.returnSolverTask(1));

    int amountFiles = 5;

    string *allFiles;
    allFiles = new string[amountFiles];
    allFiles[0] = ("exer1.txt");
    allFiles[1] = ("exer2.txt");
    allFiles[2] = ("exer3.txt");
    allFiles[3] = ("exer4.txt");
    allFiles[4] = ("exer5.txt");

    for (int i = 0; i < amountFiles; i++) {
        Calculator.setSolverTask(DirectoreSolutions, Reader.discoverFormatTaskInFile(allFiles[i]));
        Writer.writeSolverOnTheFile(Calculator.calculateTask(DirectoreSolutions, Reader, Parser, allFiles[i]), allFiles[i]);
        Writer.writeSolverOnTheScreen(Calculator.calculateTask(DirectoreSolutions, Reader, Parser, allFiles[i]), allFiles[i]);
    }

    return 0;
}