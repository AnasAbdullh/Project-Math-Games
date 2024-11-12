#include <iostream>
#include <cstdlib>

using namespace std;
enum enLevelQuestions {
    Easy = 1,
    Med = 2,
    Hard = 3,
    Mix = 4
};

enum enTypeQuestions {
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    OpMix = 5
};

struct stQuestions {
    int Number[3] = { 0, 0 };           // تهيئة الأرقام
    short NumberOfQuestions = 0;
    enLevelQuestions LevelQuestions = Easy;   // تهيئة إلى مستوى "Easy" كقيمة افتراضية
    enTypeQuestions OpType = Add;             // تهيئة إلى العملية "Add" كقيمة افتراضية
    int correctRights = 0;
    int AnswerPlayer = 0;
    bool PassOrFeild = false;

    // مُنشئ لتهيئة القيم بشكل افتراضي
    stQuestions() : NumberOfQuestions(0), LevelQuestions(Easy), OpType(Add), correctRights(0), AnswerPlayer(0), PassOrFeild(false) {
        Number[0] = 0;
        Number[1] = 0;
    }
};

struct stQuiz {
    stQuestions Questions[100];           // مصفوفة الأسئلة
    short NumberOfQuestions = 0;
    enLevelQuestions LevelQuestions = Easy;   // تهيئة إلى مستوى "Easy" كقيمة افتراضية
    enTypeQuestions OpType = Add;             // تهيئة إلى العملية "Add" كقيمة افتراضية
    int AnswerRights = 0;
    int AnswerWrong = 0;
    bool finallyResult = true;

    // مُنشئ لتهيئة القيم بشكل افتراضي
    stQuiz() : NumberOfQuestions(0), LevelQuestions(Easy), OpType(Add), AnswerRights(0), AnswerWrong(0), finallyResult(true) {}
};

string GetOpTypeSymbol(enTypeQuestions OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mul:
        return "x";
    case Div:
        return "/";
    default:
        return "Mix";
    }
}
short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}
short HowManyQuestions()
{
    short NumberQuestion;
    cout << "How Many Questions want ?";
    cin >> NumberQuestion;
    return NumberQuestion;
}
int SimpleCalculator(int Number1, int Number2, enTypeQuestions OpType)
{
    if (OpType == Div) {
        if (Number2 == 0) {
            cout << "Cannot divide by zero. Setting answer to 0 by default." << endl;
            return 0;
        }
        return Number1 / Number2;
    }
    switch (OpType) {
    case Add: return Number1 + Number2;
    case Sub: return Number1 - Number2;
    case Mul: return Number1 * Number2;
    default: return 0;
    }
}
string GetQuestionLevelText(enLevelQuestions QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
}
enLevelQuestions AskQuestionsLevel()
{
    short Level;
    do
    {

        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?";
        cin >> Level;
    } while (Level < 1 || Level > 4);

    return static_cast<enLevelQuestions>(Level);
}
enTypeQuestions TypeQuestions()
{
    short Type;
    do
    {
        cout << "Enter Operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?";
        cin >> Type;

    } while (Type < 1 || Type > 5);
    return static_cast<enTypeQuestions>(Type);
}
int AnswerPlay() {
    int Answer;
    while (!(cin >> Answer)) {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return Answer;
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); // turn screen to Green
    else
    {
        system("color 4F"); // turn screen to Red
        cout << "\a";
    }
}
int ComplexCalculator(int Number1, int Number2, int Number3, enTypeQuestions OpType1, enTypeQuestions OpType2) {
    int result = SimpleCalculator(Number1, Number2, OpType1);
    return SimpleCalculator(result, Number3, OpType2);
}

stQuestions GenerateQuestionsAsk(enLevelQuestions LevelQuestions, enTypeQuestions TypeQuestions)
{
    stQuestions Questions;

    // إذا كان مستوى السؤال Mix، نختار مستوى عشوائي
    if (LevelQuestions == Mix)
    {
        LevelQuestions = static_cast<enLevelQuestions>(RandomNumber(1, 3));
    }

    // إذا كان نوع السؤال OpMix، نختار عملية عشوائية
    if (TypeQuestions == OpMix)
    {
        TypeQuestions = static_cast<enTypeQuestions>(RandomNumber(1, 4));
    }

    Questions.OpType = TypeQuestions;

    // توليد الأرقام حسب مستوى الصعوبة
    switch (LevelQuestions)
    {
    case Easy:
        Questions.Number[0] = RandomNumber(1, 30);
        Questions.Number[1] = RandomNumber(1, 30);

        // في حالة Mix، نستخدم ComplexCalculator
        if (Questions.OpType == OpMix)
        {
            Questions.Number[2] = RandomNumber(1, 30);  // الرقم الثالث في حالة Mix
            enTypeQuestions OpType1 = static_cast<enTypeQuestions>(RandomNumber(1, 4));
            enTypeQuestions OpType2 = static_cast<enTypeQuestions>(RandomNumber(1, 4));

            Questions.correctRights = ComplexCalculator(Questions.Number[0], Questions.Number[1], Questions.Number[2], OpType1, OpType2);
        }
        else
        {
            Questions.correctRights = SimpleCalculator(Questions.Number[0], Questions.Number[1], TypeQuestions);
        }
        return Questions;

    case Med:
        Questions.Number[0] = RandomNumber(30, 60);
        Questions.Number[1] = RandomNumber(30, 60);

        if (Questions.OpType == OpMix)
        {
            Questions.Number[2] = RandomNumber(30, 60);
            enTypeQuestions OpType1 = static_cast<enTypeQuestions>(RandomNumber(1, 4));
            enTypeQuestions OpType2 = static_cast<enTypeQuestions>(RandomNumber(1, 4));

            Questions.correctRights = ComplexCalculator(Questions.Number[0], Questions.Number[1], Questions.Number[2], OpType1, OpType2);
        }
        else
        {
            Questions.correctRights = SimpleCalculator(Questions.Number[0], Questions.Number[1], TypeQuestions);
        }
        return Questions;

    case Hard:
        Questions.Number[0] = RandomNumber(60, 100);
        Questions.Number[1] = RandomNumber(60, 100);

        if (Questions.OpType == OpMix)
        {
            Questions.Number[2] = RandomNumber(60, 100);
            enTypeQuestions OpType1 = static_cast<enTypeQuestions>(RandomNumber(1, 4));
            enTypeQuestions OpType2 = static_cast<enTypeQuestions>(RandomNumber(1, 4));

            Questions.correctRights = ComplexCalculator(Questions.Number[0], Questions.Number[1], Questions.Number[2], OpType1, OpType2);
        }
        else
        {
            Questions.correctRights = SimpleCalculator(Questions.Number[0], Questions.Number[1], TypeQuestions);
        }
        return Questions;
    }

    return Questions;
}

void GenerateQuestions(stQuiz& Quiz)
{
    for (size_t i = 0; i < Quiz.NumberOfQuestions; i++)
    {
        Quiz.Questions[i] = GenerateQuestionsAsk(Quiz.LevelQuestions, Quiz.OpType);
    }
}
void PrintQuestions(stQuiz Quiz, short Round)
{
    cout << "\n";
    cout << "Questions [" << Round + 1 << "/" << Quiz.NumberOfQuestions << endl;
    cout << "\n\n";
    cout << Quiz.Questions[Round].Number[0];
    cout << "\n"
        << Quiz.Questions[Round].Number[1] << GetOpTypeSymbol(Quiz.Questions[Round].OpType) << endl;
    cout << "________________" << endl;
}
void CorrectTheQuestionAnswer(stQuiz &Questions, short NumberQuestions)
{
    if (Questions.Questions[NumberQuestions].AnswerPlayer != Questions.Questions[NumberQuestions].correctRights)
    {
        Questions.Questions[NumberQuestions].PassOrFeild = false;
        Questions.AnswerWrong++;
        cout << "Wrong Answer :-( \n";
        cout << "The right answer is: ";
        cout << Questions.Questions[NumberQuestions].correctRights;
        cout << "\n";
    }
    else
    {
        Questions.Questions[NumberQuestions].PassOrFeild = true;
        Questions.AnswerRights++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Questions.Questions[NumberQuestions].PassOrFeild);
}
void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{

    Quiz.NumberOfQuestions = Quiz.NumberOfQuestions;
    for (short NumberQuestions = 0; NumberQuestions < Quiz.NumberOfQuestions; NumberQuestions++)
    {
        PrintQuestions(Quiz, NumberQuestions);
        Quiz.Questions[NumberQuestions].AnswerPlayer = AnswerPlay();
        CorrectTheQuestionAnswer(Quiz, NumberQuestions);
    }
    Quiz.finallyResult = (Quiz.AnswerRights >= Quiz.AnswerWrong);
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "PASS :-)";
    else
        return "Fail :-(";
}
void PrintResultQuestions(stQuiz Quiz)
{
    cout << "================ Final Results ================\n";
    cout << "Number of Questions: " << Quiz.NumberOfQuestions << endl;
    cout << "Questions Level   : " << GetQuestionLevelText(Quiz.LevelQuestions) << endl;
    cout << "Operation Type    : " << GetOpTypeSymbol(Quiz.OpType) << endl;
    cout << "Correct Answers   : " << Quiz.AnswerRights << endl;
    cout << "Incorrect Answers : " << Quiz.AnswerWrong << endl;
    cout << "Final Result      : " << GetFinalResultsText(Quiz.finallyResult) << endl;
    cout << "================================================\n";

}
void ShowInstructions() {
    cout << "Welcome to the Math Quiz Game!" << endl;
    cout << "Choose the difficulty and type of operation, then answer each question." << endl;
    cout << "Good luck!" << endl;
}


void PlayMathGame()
{
    stQuiz Quiz;
    ShowInstructions();
    Quiz.NumberOfQuestions = HowManyQuestions();
    Quiz.LevelQuestions = AskQuestionsLevel();
    Quiz.OpType = TypeQuestions();
    GenerateQuestions(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintResultQuestions(Quiz);
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
        PlayMathGame();
        cout << endl
            << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
    // Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}