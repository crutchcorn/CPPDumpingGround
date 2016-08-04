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
*/ 
{
	std::vector<question_t> out = {}; // Creates a vector of question_t called out. We intialize it (create it and fill the data with) empty (data)
	// To clarify, the VECTOR is created empty, not the data inside of it (which is question_t)
	std::vector<std::string> filestr = {"q_default_1", "q_default_2"}; // Vector of strings called filestr that has two entries (strings) inside.
	int qcounter = 1; // Integer called qcounter that equals one
	for (std::string filename : filestr) // Called a for each loop, this takes that data inside of filestr, and loops through it for every entry inside
	// And places the entires of such as a variable (only valid during that loop iteration) called filename
	{
		question_t question;

		std::fstream onefile (filename, std::ios::in);
		std::getline(onefile, question.question);

		int acounter = 1;
		while (onefile.good())
		{
			std::string answer;
			std::getline(onefile, answer);

			if (answer[0] == '>')
			{
				question.correct = acounter;
				answer.erase(0, 1);
			}

			question.answers.push_back(answer);
			acounter++;
		}
		out.push_back(question);
	}
	return out;
}

bool askQ(question_t &question)
{
	question.asked = true;
	static int nth = 1;
	int useransw, nthA = 1;
	std::cout << "Question " << nth << ": " << question.question << std::endl;
	for (std::string answer : question.answers)
	{
		std::cout << nthA << ") " << answer << std::endl;
		nthA++;
	}
	std::cin >> useransw;
	nth++;
	return (question.correct == useransw);
}

int main()
{
	int score = 0;
	std::vector<question_t> questions = loadQuestions();
	for (question_t question : questions)
	{
		if (askQ(question))
		{
			std::cout << "Congrats, you got it correct" << std::endl;
			score++;
		}
		else
		{
			std::cout << "Sorry fam, not correct" << std::endl;
		}
	}
	int size = questions.size();
	std::cout << "You are done! Your score is: " << score << " out of " << size << std::endl;
}
