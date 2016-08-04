// I will explain step by step how this program works
// Anything starting with // is a comment
/* As is anything in between these. These can span many lines */

// Includes - They define the commands we'll be using
#include <iostream> // General output & more
#include <fstream> // File manipulation (Input & output)
#include <string> // Strings. AKA Words EG: "Hello"
#include <vector> // Vectors. Like arrays (list of items), but you can add things to this list. 
// You cannot do this with arrays (you set how big an array is, and it will never change)

typedef struct 
// A struc(ture) is a collection of data under one name
// See below for typedef explaination
{
	std::string question; // Makes a string variable called question
	// std:: allows your computer to know where to find this command. This case, string is in the STANDARD library.
	std::vector<std::string> answers; // Makes a vector (list) of strings in a variable called answers.
	int correct; // Makes a variable called correct that is an int (AKA whole number)
	bool asked; // Makes a boolean variable called asked. Only two values allowed; True or false
} question_t; // typedef allows you to make a datatype (much like string or int) with a name of your choosing.
// In this case, we are making a type called question_t is a mirror of sorts for the structure we just made.

std::vector<question_t> loadQuestions()
/*
When you think, you can think in any language, but when you talk you have to speak the language that the person you're talking to speaks
Just like this, you can "think" however you want but it has to make sense to the computer. We tell the computer how we're going to answer (with what data)
by specifying what datatype we will return (speak) after we think. In this case, we are returning a vector of question_ts.
The function (thought) is called loadQuestions, and can called by the computer to calculate and return data.
Keep in mind, this function is ONLY run when called
*/ 
{
	std::vector<question_t> out = {}; // Creates a vector of question_t called out. We intialize it (create it and fill the data with) empty (data)
	// To clarify, the VECTOR is created empty, not the data inside of it (which is question_t)
	std::vector<std::string> filestr = {"q_default_1", "q_default_2"}; // Vector of strings called filestr that has two entries (strings) inside.
	int qcounter = 1; // Integer called qcounter that equals one
	for (std::string filename : filestr) // Called a for each loop, this takes that data inside of filestr, and loops through it for every entry inside
	// And places the entires of such as a variable (only valid during that loop iteration) called filename
	{
		question_t question; // Makes a question_t (remember, a collection of data under one name) called question

		std::fstream onefile (filename, std::ios::in); // Opens the file `filename` for the computer to read (only read) from.
		// You make changes on onefile, as that is the variable that reflects the file you are modifying.
		std::getline(onefile, question.question); // Getline grabs the information from a line in onefile (starting at the top, and moving one down every time you use it)
		// and puts it into a string variable. This string variable is question inside of the question_t structure we just created called question
		int acounter = 1; // Sets the int acounter to 1
		while (onefile.good()) // While there is valid data in onefile, loop through each line
		{
			std::string answer; // Makes a string called answer
			std::getline(onefile, answer); // Get the next line in onefile, assign that data to answer
			
			if (answer[0] == '>') // If the first character (letter) of answer is a carrot ('>'), do this:
			{
				question.correct = acounter; // Set variable correct inside of question to equal the value inside of acounter
				answer.erase(0, 1); // Erase the carrot
			}

			question.answers.push_back(answer); // Push value of answer to vector answers inside of question
			acounter++; //Add one to acounter. This is to keep track of which option the correct answer is of
		}
		out.push_back(question); // Adds question_t to vector out
	}
	return out; // returns (speaks) vector out to use
	// Move to begining of main() function for further explaination
}

bool askQ(question_t &question)
/*
Sometimes, you need something to think ABOUT. The items inside of the paranthesis () are what the computer will be thinking about
When you call the function, the arguments (what the computer thinks about) act like normal variables inside of the function
The & means that the function can modify the variable just like you could if you were inside of main(). If you didn't have this reference (&),
it would only make changes inside of THIS function, and nothing else. This essentially allows the thought (function) to modify the speach (variable) like you would if you were talking

In this case, we are passing through a reference to a question_t that will internally be called question
*/
{
	question.asked = true; // Sets variable asked inside of question (which is question_t, remember) to true, so you know what you have seen
	static int nth = 1; // Sets a variable nth to 1. Static means that this data can NOT be changed elsewhere in the program
	int useransw, nthA = 1; // Makes two ints called useransw (blank) and  nthA (equal to 1)
	std::cout << "Question " << nth << ": " << question.question << std::endl; // Outputs nth (question number) and question.question (the string question inside of question)
	for (std::string answer : question.answers) // For each item in question.answers, run once and make equal to answer
	{
		std::cout << nthA << ") " << answer << std::endl; // Outputs nthA (option number) and answer (option)
		nthA++; // Adds one to nthA
	}
	std::cin >> useransw; // Gets user input and saves to variable useransw
	nth++; // Iterates nth
	return (question.correct == useransw); // If question.correct = useransw, return true - else return false
}

int main() // main() is the function that the computer calls when you run the program from your computer
{
	int score = 0; // Creates int variable score and makes it equal to 0 
	std::vector<question_t> questions = loadQuestions(); //Makes a vector of question_t called questions and have it equal the output of the function loadQuestions() (that we made before)
	for (question_t question : questions) // Like the for each above; This runs for each entry in questions and assigns that entry to question for that single iteration
	{
		// See begining of function askQ for explaination of what the following will do
		if (askQ(question)) // If askQ outputs true, then run this code. This passes through question as an argument to askQ
		{
			std::cout << "Congrats, you got it correct" << std::endl; // Congratulates the user
			score++; // Adds one to the score
		}
		else // Otherwise, run this code
		{
			std::cout << "Sorry fam, not correct" << std::endl; // Lets the user know they didn't answer correctly
		}
	}
	int size = questions.size(); // Makes variable size equal to how many entries there are in questions
	std::cout << "You are done! Your score is: " << score << " out of " << size << std::endl; // Lets the user know their score and how many questions there were
	
	return 0; // And that's the end! Congrats! You did it!
}
