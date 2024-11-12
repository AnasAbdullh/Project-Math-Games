#include <iostream>
#include <cstdlib>
using namespace std;
enum enGameLevelChoice
{
	Easy = 1,
	Med = 2,
	Hard = 3,
	Mix = 4
};
enum enOperationType
{
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	mix = 5
};
struct stQuestionsInfo
{
	short RoundNumber = 0;
	short ArrayTwoNumber[2] ;
	enGameLevelChoice PlayChoiceLevel ;
	enOperationType OpType;
	string PrintRightsOrWrong;
	short StorageResult;
	string PassOrFailed;
	
};
struct stRustleGame
{
	string PassOrField;
	short NumberOfQuotations = 0;
	string QuestionsLevel;
	string OperationType;
	short NumberOfRights;
	short numberOfWrong;

};
void PrintRightsOfWrong(bool Answer , stQuestionsInfo PrintAnswer)
{
	if (Answer)
	{
		cout << "Answer is Rights :-) " << endl;
	}
	else
	{
		cout << "Answer is Wrong " << endl;
		cout << "The Rights Answer is : " << PrintAnswer.StorageResult << endl;
	}
}
string PrintOpType(enOperationType OpType)
{
	string ArrAnswer[4] = { "+" , "-" , "x" , "/"};
	return ArrAnswer[OpType - 1];
}
string PrintChoice(enGameLevelChoice Choice)
{
	string ArrAnswer[4] = { "Easy" , "Med" , "Hard" , "Mix" };
	return ArrAnswer[Choice - 1];
}
string Operation(enOperationType Op)
{
	string ArrAnswer[5] = { "Add" , "Sub" , "Mul" , "Div" , "Mix"};
	return ArrAnswer[Op - 1];
}

short QuestionsNumberWants()
{
	short Answer = 0;
	
		cout << "How Many Questions do you want to Answer ?";
		cin >> Answer;
		return Answer;
}
enGameLevelChoice ReadQuestionsLevel()
{
	short Level;
	do
	{
	cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?";
	cin >> Level;

	} while (Level < 1 || Level > 4);
	return static_cast<enGameLevelChoice>(Level);
}
enOperationType TypeQuestions()
{
	short Type;
	do
	{
	cout << "Enter Operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?";
	cin >> Type;

	} while (Type < 1 || Type > 5);
	return static_cast<enOperationType>(Type);
}
void SetWinnerScreenColor(bool Answer)
{
	switch (Answer)
	{
	case true:
		system("color 2F");
		break;
	default:
		system("color 4F");
		cout << "\a";
		break;
	}
}
short RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}
enOperationType caseMix(stQuestionsInfo& OpType)
{
	enOperationType Mixes = static_cast<enOperationType>(RandomNumber(1, 4));

	switch (Mixes)
	{
	case Add:
		OpType.StorageResult = OpType.ArrayTwoNumber[0] + OpType.ArrayTwoNumber[1];
		return Add;
		break ;
	case Sub:
		OpType.StorageResult = OpType.ArrayTwoNumber[0] - OpType.ArrayTwoNumber[1];
		return Sub;
		break;
	case Mul:
		OpType.StorageResult = OpType.ArrayTwoNumber[0] * OpType.ArrayTwoNumber[1];
		return Mul;
		break;
	case Div:
		OpType.StorageResult = OpType.ArrayTwoNumber[0] / OpType.ArrayTwoNumber[1];
		return Div;
		break;
	}
}
short FillNumbersomeLevel(enGameLevelChoice Level)
{
	short level;
	switch (Level)
	{
	case Easy:
		return level = RandomNumber(1, 30);
		break;
	case Med:
		return level = RandomNumber(30, 60);
		break;
	case Hard:
		return level = RandomNumber(60,100);
		break;
	case Mix:
		return level = RandomNumber(1, 100);
		break;
	}
}

enOperationType SelectOpType(stQuestionsInfo &OpType)
{
	switch (OpType.OpType)
	{
	case Add:
	  OpType.StorageResult = OpType.ArrayTwoNumber[0] + OpType.ArrayTwoNumber[1];
	  return Add;
    	break;
	case Sub :
		OpType.StorageResult = OpType.ArrayTwoNumber[0] - OpType.ArrayTwoNumber[1];
		return Sub;
		break;
	case Mul :
		OpType.StorageResult = OpType.ArrayTwoNumber[0] * OpType.ArrayTwoNumber[1];
		return Mul;
	    break;
	case Div :
		OpType.StorageResult = OpType.ArrayTwoNumber[0] / OpType.ArrayTwoNumber[1];
		return Div;
		break;
	case mix :
		return caseMix(OpType);
		break;
	}
}
   
bool CheckResult(stQuestionsInfo result)
{
	short readInput;
	cin >> readInput;
	cout << "\n";
	if (readInput == result.StorageResult)
	{
		return true;
	}
	return false;
		
}
void PrintQuestions(stQuestionsInfo ShowQuestions)
{
	cout << ShowQuestions.ArrayTwoNumber[0] << endl;
	cout << ShowQuestions.ArrayTwoNumber[1] << " " << PrintOpType(SelectOpType(ShowQuestions)) << endl;;
	cout << "_______________" << endl;
}

void FillArray(stQuestionsInfo &Numbers)
{
	for (size_t i = 0; i < 2; i++)
	{
		Numbers.ArrayTwoNumber[i] = FillNumbersomeLevel(Numbers.PlayChoiceLevel);
	}
}
string PrintPassOrFailed(short NumberPass , short NumberFailed)
{
	if (NumberPass > NumberFailed)
	{
		return "Pass  :-)";
	}
	else
		return "Failed :-(";
}
bool returnTrueetc(string Pass)
{
	if (Pass == "Pass  :-)")
	{
		return true;
	}
	else {
		return false;
	}
}

stRustleGame fillResultGame(short NumbersRights , short NumberWrong , short NumberQuestion , enGameLevelChoice Choice , enOperationType Type )
{
	stRustleGame Fill;
	Fill.PassOrField = PrintPassOrFailed(NumbersRights, NumberWrong);
	Fill.NumberOfQuotations = NumberQuestion;
	Fill.QuestionsLevel = PrintChoice(Choice);
	Fill.OperationType = Operation(Type);
	Fill.NumberOfRights = NumbersRights;
	Fill.numberOfWrong = NumberWrong;
	return Fill;
}

stRustleGame PlayGame(short HowManyQuestions)
{
	short NumberRights{}, NumberWrong{};
	bool TrueOrFalse;
	    stQuestionsInfo Question;
    	Question.PlayChoiceLevel = ReadQuestionsLevel();
	    Question.OpType = TypeQuestions();
	for ( short QuestionsRound = 1; QuestionsRound <= HowManyQuestions; QuestionsRound++)
	{
		cout << "Questions [" << QuestionsRound << "/" << HowManyQuestions << "]" << "\n\n";
		Question.RoundNumber = QuestionsRound;
		FillArray(Question);
		PrintQuestions(Question);
		SelectOpType(Question);
        TrueOrFalse	= (CheckResult(Question));
		SetWinnerScreenColor(TrueOrFalse);
		PrintRightsOfWrong(TrueOrFalse , Question);

		if (TrueOrFalse == true)
		{
			NumberRights++;
		}
		else
		{
			NumberWrong++;
		}
	}
	return fillResultGame(NumberRights, NumberWrong, HowManyQuestions,Question.PlayChoiceLevel, Question.OpType);
}
void PrintResultFinally(stRustleGame Result)
{
	cout << "_________________________________" << endl;
	cout << "Finally result is " << Result.PassOrField << endl;
	cout << "_________________________________" << endl;
	cout << endl;
	cout << "Number Of Questions : " << Result.NumberOfQuotations << endl;
	cout << "Question Level : " << Result.QuestionsLevel << endl;
	cout << "OpType : " << Result.OperationType << endl;
	cout << "Number Of Rights Answer : " << Result.NumberOfRights << endl;
	cout << "Number Of Wrong Answer : " << Result.numberOfWrong << endl;
	bool  Color = returnTrueetc(Result.PassOrField);
	SetWinnerScreenColor(Color);
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stRustleGame GameResult = PlayGame(QuestionsNumberWants());
		PrintResultFinally(GameResult);
		cout  << "Do you want Play Again Y/N ? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}