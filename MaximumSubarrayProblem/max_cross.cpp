#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
  int num;
  vector<double> array;
  
  cout << "How many numbers: ";
  cin >> num;
  
  for (int i = 0; i < num; i++) {
    double tmp;
    cin >> tmp;
    array.push_back(tmp);
  }
  
  vector<double> maxAux;
  vector<double> minAux;
  
  maxAux.push_back(array[0]);
  minAux.push_back(array[0]);

  double max = maxAux[0];
  for (int i = 1; i < num; i++) {
    if (array[i] > 0) {
      double tmpMax = maxAux[i-1]*array[i];
      if (tmpMax  > array[i]) {
	maxAux.push_back(tmpMax);
      } else {
	maxAux.push_back(array[i]);
      }

      double tmpMin = minAux[i-1]*array[i];
      if (tmpMin < array[i]) {
	minAux.push_back(tmpMin);
      } else {
	minAux.push_back(array[i]);
      }
    }
    else {
      double tmpMax = minAux[i-1]*array[i];
      if (tmpMax > array[i]) {
	maxAux.push_back(tmpMax);
      } else {
	maxAux.push_back(array[i]);
      }

      double tmpMin = maxAux[i-1]*array[i];
      if (tmpMin < array[i]) {
	minAux.push_back(tmpMin);
      } else {
	minAux.push_back(array[i]);
      }
    }

    if (max < maxAux[i]) {
      max = maxAux[i];
    }
  }

  cout << "The maximum cross subarray is: " << max << endl;
  return 0;
}

