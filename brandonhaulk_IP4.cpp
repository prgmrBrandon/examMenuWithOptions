#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// super class
class Question{
		public:
		    //gets the question
				string getQuestion(){
						return question;
        }
				//gets the point value of the question
        virtual int getValue(){
              return value;
         }
 
				// gets the type of question
        virtual string getQuestionType(){
						return questiontype;
        }

        virtual void setQuestion(string answer, int value){

        }

        virtual void setNewQuestion(string answer, int value) {

        }

        virtual void printOptions(){

        }

        virtual string getAnswer(){
						return answer;
        }

	private:
			string question,  answer;
			int value;
			string questiontype;
};

 // class for true and false questions
class QuestionTF: public Question{
		public:
			void setQuestion(string theQuestion, int pointValue){
					string theAnswer;
           questiontype = "TF";
           question = theQuestion;
           value = pointValue;
           options = "true/false";
                            
           //get the answer from the file
           getline(cin,theAnswer);
           answer = theAnswer;
			}

      void setNewQuestion(string theQuestion, int pointValue) {
					string theAnswer;
					questiontype = "TF";
					question = theQuestion;
					value = pointValue;
					options = "true/false";

           //get the answer from user
           cout<<"Enter answer true/false\n";
           getline(cin,theAnswer);
           answer = theAnswer;
      }

			//gets the point value of the question 
      int getValue(){
          return value;
      }
        
      // gets the type of question
      string getQuestionType(){
					return questiontype;
      }

			//prints the options for that question
      void printOptions(){
					cout<<question<<endl;
          cout<<answer<<endl;
      }
 
			//outputs the answer for that question
      string getAnswer(){
          return answer;
      }

	private:
			string question, questiontype;
      string answer;
      string options;
      int value;
};

//class for multiple choice
class QuestionMC: public Question{
		public:
				void setQuestion(string theQuestion, int pointValue) {
						string line;
            questiontype = "MC";
            getline(cin,line);
            numberOfOptions = atoi(line.c_str());
            cout<<numberOfOptions<<endl;
            question = theQuestion;
						value = pointValue;
                             
						//get the individual choice lines and load to options array
            for (int count = 0; count<numberOfOptions;count++){
								getline(cin,line);
                options[count] = line;
						}
                             
                             //get the answer from the file and load into answer
                             getline(cin, line);
                             answer = line;
              }

        void setNewQuestion(string theQuestion, int pointValue) {
						string line;
            questiontype = "MC";
                             
						//get the number of choices from the user
            cout<<"Enter the number of choices:  ";
            getline(cin,line);
            numberOfOptions = atoi(line.c_str());

            question = theQuestion;
            value = pointValue;

            //get the individual choice lines and load to options array
            for (int count = 0; count<numberOfOptions;count++){
								cout<<"\nEnter next option:  ";
                getline(cin,line);
								options[count] = line;
            }
                             
            //get the answer from the user and load into answer
						cout<<"\nEnter Answer:  ";
            getline(cin, line);
            answer = line;
        }

				// prints the questions, options, and answer
        void printOptions() {
						//char first = 'A';
            cout<<question<<endl;
        
            for(int count = 0; count<numberOfOptions;count++){
								cout<<options[count]<<"\n";
            }
            cout<< answer << "\n";
        }

				//gets the point value of the question
        int getValue() {
						return value;
        }

				// gets the type of question
        string getQuestionType() {
						return questiontype;
				}

				// prints the answer
        string getAnswer() {
						return answer;
        }

		private:
        int numberOfOptions;
        string question, answer;
        string options[6];
        string questiontype;
				int value;
};

class Exam{
		public:
				int loadExam(){
				//ifstream infile;
				//string examName = exam;
				ifstream infile("exam.txt");
				streambuf *cinbuf = cin.rdbuf();       //save old buf
				cin.rdbuf(infile.rdbuf());             //redirect std::cin to infile.txt!
				string line, theQuestion, questiontype, theAnswer;
				int  questionvalue;

				//get the number of questions from the first line in the file
        getline(cin,line);
        numquestions = atoi(line.c_str());
         
         for(int count = 0; count<numquestions;count++){
						getline(cin,line);
            //get the next line with the question type and the value of the question
            int npos = line.size();
            int prev_pos = 0;
						int pos = 0;
						
            while( line[pos]!=' ')
								pos++;
						questiontype = line.substr(prev_pos, pos-prev_pos);
						prev_pos = ++pos;
						questionvalue = atoi(line.substr(prev_pos, npos-prev_pos).c_str()); // Last word
                //process a true/false question
								if (questiontype == "TF") {
										myQuestions[count] = new QuestionTF;
                    getline(cin,theQuestion);
                    myQuestions[count]->setQuestion(theQuestion,questionvalue);
                }

                //process a multiple choice question
								if (questiontype =="MC") {
										myQuestions[count] =new QuestionMC;
                    getline(cin,theQuestion);
                    myQuestions[count]->setQuestion(theQuestion,questionvalue);
               }
					}

					cin.rdbuf(cinbuf);   //restore cin to standard input
					return numquestions;
				}
				

				void displayExamQuestions(int numquestions) {
						string qtype;
						//print out the questions that have been processed
            for(int count = 0; count<numquestions;count++) {
								qtype=myQuestions[count]->getQuestionType();
                cout<<qtype<<" "<<myQuestions[count]->getValue()<<"\n";
                myQuestions[count]->printOptions();
                cout<<"\n";
						}

				}
				
		private:
				Question *myQuestions[10];
				int numquestions;
};

int displayMenu();  //function prototype



int main() {
		Exam myExam;
        int numquestions, choice;
				string examName = "exam.txt";

        while((choice = displayMenu())!=3)
						switch(choice) {
								case 1: numquestions = myExam.loadExam();
										break;
                case 2: myExam.displayExamQuestions(numquestions);
                    break;

                default: cout<<"Invalid choice.  Try again.\n";
            }

            getchar();
            return 0;
}

int displayMenu() {
		int choice;
				cout<< "Enter your choice for this Exam."<<endl;
				cout<< "1.  Load Exam "<<endl;
				cout<< "2.  Display Exam "<<endl;
				cout<< "3.  Quit"<<endl;
				cin>>choice;
		return choice;

}
