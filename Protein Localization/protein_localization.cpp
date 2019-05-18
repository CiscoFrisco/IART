#include "protein.h"
#include "c4.5.h"
#include "neural-net.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    int method;

    do
    {
        displayMenu();

        cin >> method;

        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        switch (method)
        {
        case 1:
            runKNN();
            break;
        case 2:
            runC45();
            break;
        case 3:
            runNeuralNetwork();
            break;
        default:
            break;
        }

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(t2 - t1).count();

        cout << "\nDuration: " << (float)duration / 1000000 << " seconds.\n";

    } while (method != 0);

    return 0;
}

void displayMenu()
{
    cout << "\n=====Protein Localization=====\n\n";
    cout << "Choose your Method:\n";
    cout << "1. K Nearest Neighbours\n2.C4.5\n3.Neural Network\n";
}

void runKNN()
{
    vector<Protein> train;
    vector<Protein> test;

    readTrainFile(&train, &test);
    k_nearest_evaluate(train, test);

    cout << "TRAIN: " << train.size() << " | "
         << "TEST: " << test.size() << endl;
}

void runC45()
{
    MatrixCls Matrix("yeast.dat");
    cout << Matrix.SizeY() << endl
         << endl;
    TreeCls *Tree;
    Tree = Tree->BuildTree(NULL, Matrix);
    Tree->Display();
    vector<string> Test_Scores = Tree->TestTree(Matrix);
    DisplayVector(Test_Scores);
}

void runNeuralNetwork()
{
    TrainingData trainData("training_yeast.txt");
    vector<unsigned> topology;

    trainData.getTopology(topology);
    Net myNet(topology);

    trainNeuralNetwork(&trainData, myNet, topology);
}

void showStats(unsigned short correctPred[], unsigned short sumReal[], unsigned short sumPred[], unsigned short test)
{

    for (int i = 0; i < 10; ++i)
    {
        int vp = correctPred[i];
        int fn = sumReal[i] - correctPred[i];
        int fp = sumPred[i] - correctPred[i];
        int vn = test - sumReal[i] - sumPred[i] + correctPred[i];

        cout << "Class: " << de_translate(i);
        cout << " VP: " << vp << " FN: " << fn << " FP: " << fp << " VN: " << vn;
        cout << " Accuracy: " << (float)(vp + vn) / (vp + fn + fp + vn);
        cout << " Precision: " << (float)vp / (vp + fp);
        cout << " F-measure: " << (2.0 * vp) / ((2.0 * vp) + fn + fp);

        cout << endl;
    }
}

unsigned short translate(std::string resultName)
{
    if (resultName == "CYT")
        return 0;
    else if (resultName == "NUC")
        return 1;
    else if (resultName == "MIT")
        return 2;
    else if (resultName == "ME3")
        return 3;
    else if (resultName == "ME2")
        return 4;
    else if (resultName == "ME1")
        return 5;
    else if (resultName == "EXC")
        return 6;
    else if (resultName == "VAC")
        return 7;
    else if (resultName == "POX")
        return 8;
    else if (resultName == "ERL")
        return 9;
}

std::vector<double> translateNN(std::string resultName)
{
    if (resultName == "CYT")
        return {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    else if (resultName == "NUC")
        return {0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    else if (resultName == "MIT")
        return {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    else if (resultName == "ME3")
        return {0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
    else if (resultName == "ME2")
        return {0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    else if (resultName == "ME1")
        return {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    else if (resultName == "EXC")
        return {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
    else if (resultName == "VAC")
        return {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    else if (resultName == "POX")
        return {0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
    else if (resultName == "ERL")
        return {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
}

std::string de_translate(unsigned short res)
{
    switch (res)
    {
    case 0:
        return "CYT";
    case 1:
        return "NUC";
    case 2:
        return "MIT";
    case 3:
        return "ME3";
    case 4:
        return "ME2";
    case 5:
        return "ME1";
    case 6:
        return "EXC";
    case 7:
        return "VAC";
    case 8:
        return "POX";
    case 9:
        return "ERL";
    }

    return "";
}