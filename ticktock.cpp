#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef struct
{
	std::string question;
	std::vector<std::string> answers;
	int correct;
	bool asked;
} question_t;

std::vector<question_t> loadQuestions()
{
	std::vector<question_t> out = {};
	std::vector<std::string> filestr = {"q_default_1", "q_default_2"};
	int qcounter = 1;
	for (std::string filename : filestr)
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
	/*
	for (int i = 0; i < size; i++)
	{
		std::cout << questions[i].question << std::endl;
	}
	*/
}