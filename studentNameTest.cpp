//This file gets a text file and steps through it asking for the user to input a yes or no to each file.
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

void quizLoop(int& studentNumber, int TOTAL_STUDENTS, string& name, char& userInput, bool userAffirmation[]){
	ifstream file("letourneauStudents.txt");
	
	file.seekg(0);
	for(int i = 0; i < (studentNumber-1); i++){
		getline(file, name, '\n');
	}
	
	while (studentNumber <= TOTAL_STUDENTS){
		//get the next name by reading until the end of the line
		getline(file, name, '\n');

		//prompt the user
		cout << name << setw(50-name.size()) << "Student Number:" << studentNumber << endl;
		cout << "Do you know this person? (y/n)\n";
		cin >> userInput;
		cout << endl;

		//process the user's answer
		if(userInput == 'y' || userInput == 'Y'){
			userAffirmation[studentNumber-1] = true;
		}
		else if(userInput == 'n' || userInput == 'N'){
			userAffirmation[studentNumber+1] = false;
		}
		else if(userInput == 'q' || userInput == 'Q'){
			if(studentNumber > 1){
				studentNumber--;
			}
				//reset getline pointer to beginning and loop until the previous student;
				file.seekg(0);
				for(int i = 0; i < (studentNumber-1); i++){
					getline(file, name, '\n');
				}
			continue;
		}
		else if(userInput == 's' || userInput == 'S'){
			break;
		}
		else{
			cout << "Please try a different character. (y = yes, n = no, s = save, q = previous question)\n\n";
			file.seekg(0);
			for(int i = 0; i < (studentNumber-1); i++){
				getline(file, name, '\n');
			}
			continue;
		}
			
		studentNumber++;
	}
}

void resetSave(int& studentNumber){
	ofstream file3("quizSave.txt");
	file3 << "0";
	file3.close();
	studentNumber = 1;
}

int main(){
    const int TOTAL_STUDENTS = 1119;
    ifstream file("letourneauStudents.txt");
	ifstream file3("quizSave.txt");
    string name;
    bool userAffirmation[TOTAL_STUDENTS];
    char userInput = 'a', ch;
    int studentNumber = 0;
    int count = 0;
    double percentage;
	
    // Check if the files are successfully opened
    if (!file.is_open()) {
        cout << "Error could not find the letourneauStudents file! (make sure the .txt file is in the same folder as the .exe";
        return 1;
    }
	if (!file3.is_open()) {
        cout << "Error could not find the quizSave file! (make sure the .txt file is in the same folder as the .exe";
        return 1;
    }
	
	//get stuff from save file
	file3 >> studentNumber;
	for(int i = 0; i < TOTAL_STUDENTS-1; i++){
		userAffirmation[i] = false;
	}
	//account for first index (next line char is there)
	for(int i = -1; i < studentNumber-2; i++){
		ch = file3.get();
		if(ch == 'y'){
		userAffirmation[i] = true;
		}
		else if(ch == 'n'){
		userAffirmation[i] = false;
		}
	}
	studentNumber++;
	
	if(studentNumber > 1){
		cout << "Would you like to continue your previous quiz? (y/n)\n";
		cin >> userInput;
	}
	
	if(userInput == 'y' || userInput == 'Y'){
        cout << "Great! Getting save... \n\n";
    }
    else if(userInput == 'n' || userInput == 'N'){
        for(int i = 0; i < TOTAL_STUDENTS-1; i++){
			userAffirmation[i] = false;
		}
		resetSave(studentNumber);
    }
	
	
	//beginning prompt (if first time)
	if(userInput == 'n' || userInput == 'a'){
		cout << "\nINSTRUCTIONS:\n";
		cout << "Welcome to my program! Type the letter 'Y' or 'N' for each question then hit enter.\n";
		cout << "If you miss input the previous name, type 'Q' and it will let you re-enter it.\n";
		cout << "If you want to finish the program later, type 'S' and it will save your progress.\n\n";
		cout << "Got it? (y/n)\n";
		cin >> userInput;
		cout << endl;
	}

	quizLoop(studentNumber, TOTAL_STUDENTS, name, userInput, userAffirmation);

    //print results
    for(int i = 1; i < studentNumber; i++){
        if(userAffirmation[i-1]){
            count++;
        }
    }

    cout << "You know " << count << " people at LeTourneau University.\n";
    percentage = (static_cast<double>(count) / (TOTAL_STUDENTS)) * 100;
    cout << "This is " << fixed << setprecision(3) << percentage << "%" << " of all the LeTourneau students!\n";

    if(count == (TOTAL_STUDENTS-1)){
        cout << ":0" << " YOU KNOW EVERYONE???\n\n";
    }
    else if(count <= 3){
        cout << "\n\nWelp, you know what Dr. Baas says, \"If you have one or no friends, YOU DIE! If you have three or more, YOU DIE! The perfect quantity of friends is two.\"\n\n";
    }
	if(count < TOTAL_STUDENTS || count > 0){
        cout << "Only " << (TOTAL_STUDENTS-count) << " more to go!\n\n";
    }
	
	//save game:
	ofstream file2("quizSave.txt");
	file2 << (studentNumber-1);
	file2 << endl;
	
	for(int i = 0; i < studentNumber-1; i++){
		if(userAffirmation[i] == true){
			file2.put('y');
		}
		else if(userAffirmation[i] == false){
			file2.put('n');
		}
	}
	
	file.close();
	file2.close();
	file3.close();
	
	if(studentNumber >= TOTAL_STUDENTS){
	resetSave(studentNumber);
	}
	
	cout << "When you are done, just close the window.";
	cin >> userInput;

    return 0;
}