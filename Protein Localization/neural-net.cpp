#include "neural-net.h"
#include "protein.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void TrainingData::getTopology(vector<unsigned> &topology)
{
	string line;
	string label;

	getline(m_trainingDataFile, line);
	stringstream ss(line);
	ss >> label;
	if (this->isEof() || label.compare("topology:") != 0)
	{
		abort();
	}

	while (!ss.eof())
	{
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}
	return;
}

TrainingData::TrainingData(const string filename)
{
	m_trainingDataFile.open(filename.c_str());
}

unsigned TrainingData::getNextInputs(vector<double> &inputVals)
{
	inputVals.clear();

	string line;
	getline(m_trainingDataFile, line);
	stringstream ss(line);

	string label;
	ss >> label;
	if (label.compare("in:") == 0)
	{
		double oneValue;
		while (ss >> oneValue)
		{
			inputVals.push_back(oneValue);
		}
	}

	return inputVals.size();
}

void TrainingData::getFileAttributes(vector<vector<double>> &inputTestVals, vector<vector<double>> &inputTrainVals, vector<vector<double>> &outputTestVals, vector<vector<double>> &outputTrainVals, int trainPercentage)
{
	inputTestVals.clear();
	inputTrainVals.clear();
	outputTestVals.clear();
	outputTrainVals.clear();

	int random;

	while (!m_trainingDataFile.eof())
	{
		random = rand() % 100;

		string line_in;
		getline(m_trainingDataFile, line_in);
		stringstream ss_in(line_in);

		string label_in;
		ss_in >> label_in;

		if (label_in.compare("in:") == 0)
		{
			vector<double> oneIn;
			double inValue;

			while (ss_in >> inValue)
			{
				oneIn.push_back(inValue);
			}

			string line_out;
			getline(m_trainingDataFile, line_out);
			stringstream ss_out(line_out);

			string label_out;
			ss_out >> label_out;

			if (label_out.compare("out:") == 0)
			{
				vector<double> oneOut;
				string outValue;

				while (ss_out >> outValue)
				{
					vector<double> ValueVec = translateNN(outValue);
					oneOut = ValueVec;
				}

				if (random < (100 - trainPercentage))
				{
					inputTestVals.push_back(oneIn);
					outputTestVals.push_back(oneOut);
				}
				else
				{
					inputTrainVals.push_back(oneIn);
					outputTrainVals.push_back(oneOut);
				}
			}
		}
	}
}

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputVals)
{
	targetOutputVals.clear();

	string line;
	getline(m_trainingDataFile, line);
	stringstream ss(line);

	string label;
	ss >> label;
	if (label.compare("out:") == 0)
	{
		string oneValue;
		// double oneValueVal;
		while (ss >> oneValue)
		{
			vector<double> ValueVec = translateNN(oneValue);
			targetOutputVals = ValueVec;
		}
	}

	return targetOutputVals.size();
}

// ****************** class Neuron ******************

void Neuron::updateInputWeights(Layer &prevLayer)
{
	// The weights to be updated are in the Connection container
	// in the nuerons in the preceding layer

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight =
			// Individual input, magnified by the gradient and train rate:
			eta * neuron.getOutputVal() * m_gradient
			// Also add momentum = a fraction of the previous delta weight
			+ alpha * oldDeltaWeight;
		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}
double Neuron::sumDOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_inputVal); // NOT m_outputVal
}

void Neuron::calcOutputGradients(double targetVals)
{
	double delta = targetVals - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_inputVal); // NOT m_outputVal
}

double Neuron::eta = 0.25;  // overall net learning rate
double Neuron::alpha = 0.1; // momentum, multiplier of last deltaWeight, [0.0..n]

// void Neuron::calcHiddenGradients(const Layer &nextLayer)
// {
// 	double dow = sumDOW(nextLayer);
// 	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
// }
// void Neuron::calcOutputGradients(double targetVals)
// {
// 	double delta = targetVals - m_outputVal;
// 	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
// }

double Neuron::transferFunction(double x)
{
	// tanh - output range [-1.0..1.0]
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	// tanh derivative
	return 1.0 - tanh(x) * tanh(x);
}

// double Neuron::transferFunctionDerivative(double x)
// {
// 	// tanh derivative
// 	return 1.0 - x * x;
// }

void Neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].getOutputVal() *
			   prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_inputVal = sum;
	m_outputVal = Neuron::transferFunction(sum);
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (unsigned c = 0; c < numOutputs; ++c)
	{
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;
}
// ****************** class Net ******************
double Net::m_recentAverageSmoothingFactor = 100.0; // Number of training samples to average over

void Net::getResults(vector<double> &resultVals) const
{
	resultVals.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n)
	{
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}
}

void Net::backProp(const std::vector<double> &targetVals)
{
	// Calculate overal net error (RMS of output neuron errors)

	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1; // get average error squared
	m_error = sqrt(m_error);		   // RMS

	// Implement a recent average measurement:

	m_recentAverageError =
		(m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);
	// Calculate output layer gradients

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}
	// Calculate gradients on hidden layers

	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	// For all layers from outputs to first hidden layer,
	// update connection weights

	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].updateInputWeights(prevLayer);
		}
	}
}

void Net::feedForward(const vector<double> &inputVals)
{
	// Check the num of inputVals euqal to neuronnum expect bias
	// assert(inputVals.size() == m_layers[0].size() - 1);

	// Assign {latch} the input values into the input neurons
	for (unsigned i = 0; i < inputVals.size(); ++i)
	{
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	// Forward propagate
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
	{
		Layer &prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
		{
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}
Net::Net(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());
		// numOutputs of layer[i] is the numInputs of layer[i+1]
		// numOutputs of last layer is 0
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		// We have made a new Layer, now fill it ith neurons, and
		// add a bias neuron to the layer:
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			// cout << "Mad a Neuron!" << endl;
		}

		// Force the bias node's output value to 1.0. It's the last neuron created above
		m_layers.back().back().setOutputVal(1.0);
	}
}

void showVectorVals(string label, vector<double> &v)
{
	cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}

	cout << endl;
}

void showTargetVals(string label, int index)
{
	cout << " | " << de_translate(index) << endl;
}

void trainNeuralNetwork(TrainingData *trainData, Net myNet, vector<unsigned> topology)
{
	vector<vector<double>> inputTrainVals, inputTestVals, outputTrainVals, outputTestVals;
	vector<double> resultVals;
	int trainingPass = 0;
	int correct = 0;
	int trainPercentage;

	unsigned short correctPred[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned short sumReal[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned short sumPred[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	cout << "Insert train percentage: ";
	cin >> trainPercentage;

	(*trainData).getFileAttributes(inputTestVals, inputTrainVals, outputTestVals, outputTrainVals, trainPercentage);
	(*trainData).m_trainingDataFile.close();
	(*trainData).m_trainingDataFile.open("training_yeast.txt");

	int i, epochs;

	cout << "\nInsert the number of epochs:";
	cin >> epochs;

	cout << endl;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (i = 0; i < epochs; i++)
	{
		while (trainingPass < outputTrainVals.size())
		{
			// Get new input data and feed it forward:
			// showVectorVals("Inputs :", inputVals[trainingPass]);
			myNet.feedForward(inputTrainVals[trainingPass]);

			// Collect the net's actual results:
			myNet.getResults(resultVals);

			int maxRes_i = distance(resultVals.begin(), max_element(resultVals.begin(), resultVals.end()));
			sumPred[maxRes_i]++;
			// showVectorVals("Output:", resultVals);
			// showTargetVals("Output String:", maxRes_i);

			// Train the net what the outputs should have been:
			int maxTarget_i = distance(outputTrainVals[trainingPass].begin(), max_element(outputTrainVals[trainingPass].begin(), outputTrainVals[trainingPass].end()));
			sumReal[maxTarget_i]++;
			// showVectorVals("Target:", targetVals[trainingPass]);
			// showTargetVals("Target String:", maxTarget_i);

			if (maxRes_i == maxTarget_i)
			{
				correctPred[maxRes_i]++;
				correct++;
			}

			myNet.backProp(outputTrainVals[trainingPass]);

			trainingPass++;
		}

		cout << "Epoch: " << (i + 1) << " | "
			 << "Accuracy: " << ((float)correct / (float)trainingPass) * 100.0 << "%\n\n";

		trainingPass = 0;
		correct = 0;
	}

	trainingPass = 0;
	correct = 0;

	while (trainingPass < outputTestVals.size())
	{
		// Get new input data and feed it forward:
		// showVectorVals("Inputs :", inputVals[trainingPass]);
		myNet.feedForward(inputTestVals[trainingPass]);

		// Collect the net's actual results:
		myNet.getResults(resultVals);

		int maxRes_i = distance(resultVals.begin(), max_element(resultVals.begin(), resultVals.end()));
		sumPred[maxRes_i]++;
		// showVectorVals("Output:", resultVals);
		// showTargetVals("Output String:", maxRes_i);

		// Train the net what the outputs should have been:
		int maxTarget_i = distance(outputTestVals[trainingPass].begin(), max_element(outputTestVals[trainingPass].begin(), outputTestVals[trainingPass].end()));
		sumReal[maxTarget_i]++;
		// showVectorVals("Target:", targetVals[trainingPass]);
		// showTargetVals("Target String:", maxTarget_i);

		if (maxRes_i == maxTarget_i)
		{
			correctPred[maxRes_i]++;
			correct++;
		}

		myNet.backProp(outputTestVals[trainingPass]);
		trainingPass++;
	}

	cout << "\nTest: " << " | "
		 << "Accuracy: " << ((float)correct / (float)trainingPass) * 100.0 << "%\n\n";

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "\nDuration: " << (float)duration / 1000000 << " seconds.\n";

	// showStats(correctPred, sumReal, sumPred, trainingPass - i);
}