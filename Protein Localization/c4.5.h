#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <cmath>

class MatrixCls
{
private:
    std::vector<std::vector<std::string>> Matrix;

public:
    MatrixCls(std::string Data_File);
    MatrixCls(){};
    ~MatrixCls(){};
    std::string Element(int i, int j);
    int SizeX();
    int SizeY();
    std::vector<std::string> GetVarKinds();
    std::vector<std::string> GetAttributes();
    std::vector<std::string> GetScores();
    int GetAttributeIndex(std::string The_Attribute);
    std::vector<std::string> GetAttributeValues(std::string The_Attribute);
    std::vector<std::string> GetUniqueAttributeValues(std::string The_Attribute);
    std::map<std::string, std::vector<std::string>> GetAttributeValuesScores(std::string The_Attribute);
    std::vector<std::string> SortAttributeValues(std::string The_Attribute);
    std::vector<std::string> SortScoreValues(std::string The_Attribute);
    std::vector<std::string> GetBisectNodes(std::string The_Attribute);
    std::map<std::string, std::vector<std::string>> GetAttributeBisectParts(std::string The_Attribute, std::string Bisect_Node);
    MatrixCls operator()(MatrixCls A_Matrix, std::string The_Attribute, std::string The_Value, std::string Bisect_Node = "");
    void Display();
};

class TreeCls
{
public:
    std::string Node;
    std::string Branch;
    std::vector<TreeCls *> Child;
    TreeCls();
    TreeCls *BuildTree(TreeCls *Tree, MatrixCls Remain_Matrix);
    void Display(int Depth = 0);
    std::string Temp_TestTree(std::vector<std::string> Kinds, std::vector<std::string> Attributes, std::vector<std::string> Value, std::vector<std::string> Score_Range);
    std::vector<std::string> TestTree(MatrixCls Data_Matrix);
};

void DisplayVector(std::vector<std::string> The_Vector);
double GainRatio(MatrixCls Remain_Matrix, std::string The_Attribute, std::string Bisect_Node = "");
double ComputeAttributeEntropyGain(MatrixCls Remain_Matrix, std::string The_Attribute, std::string Bisect_Node);
double ComputeAttributeEntropy(MatrixCls Remain_Matrix, std::string The_Attribute);
double ComputeScoreEntropy(std::vector<std::string> Scores);
std::string FrequentValues(std::vector<std::string> A_String);
std::vector<std::string> UniqueValues(std::vector<std::string> A_String);

