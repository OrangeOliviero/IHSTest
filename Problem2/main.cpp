#include <iostream>
#include <string>
#include <vector>

#include "ArrayTransformer.h"


using namespace std;

enum class Operation
{
  none,
  sum,
  product,
  delta,
};

void printUsage();
void printArray(int array[], size_t size);
template<template<typename...> class Container, typename Type>
void printArray(Container<Type>);
Operation getOperation(const string& operation);

int main(int argc, const char* argv[])
{
  Operation operation = Operation::none;

  int idx = 1;
  while (idx < argc) {
    string arg = argv[idx++];
    if (arg == "-o") {
      if (idx == argc) {
        cerr << "Error: Expected an argument to -o" << endl;
        return 2;
      }

      arg = argv[idx++];
      operation = getOperation(arg);
      if (operation == Operation::none) {
        cerr << "Error: Invalid operation (" << arg << ")" << endl;
        printUsage();
        return 2;
      }
      continue;
    }

    // No expected switches were handled, treat remainder as array value
    break;
  }

  int(*transformOperation)(int, int, const int*) = nullptr;
  switch (operation) {
  case Operation::none:
    cerr << "Error: No operation specified" << endl;
    printUsage();
    return 2;

  case Operation::sum:
    transformOperation = sumPrev<int>;
    break;

  case Operation::product:
    transformOperation = mulPrev<int>;
    break;

  case Operation::delta:
    transformOperation = deltaPrev<int>;
    break;
  }


  int numValues = argc - idx + 1;
  if (numValues <= 0) {
    cerr << "Error: No array values specified" << endl;
    printUsage();
    return 2;
  }

  vector<int> array;
  for (idx = 0; idx < numValues; ++idx) {
    string arg = argv[argc - numValues + idx];
    try {
      array.push_back(stoi(arg));
    } catch (invalid_argument& exc) {
      cerr << "Error reading array value " << arg << " (" << exc.what() << ")" << endl;
      return 2;
    }
  }

  cout << "Original array:    ";
  printArray(array);

  transformArray(array, transformOperation);

  cout << "Transformed array: ";
  printArray(array);
}

void printUsage()
{
  cout << "Usage: ArrayTransformExample -o <operation> <array values>" << endl;
  cout << "  Acceptable operations are:" << endl;
  cout << "    sum   : array[i] = sum of it and all previous values" << endl;
  cout << "    prod  : array[i] = product of it and all previous values" << endl;
  cout << "    delta : array[i] = the delta between it and the previous value" << endl;
  cout << "  Values are space-delimeted and assumed to be integers." << endl;
}

void printArray(int array[], size_t size)
{
  for (size_t idx = 0; idx < size; ++idx) {
    if (idx > 0) {
      cout << ", ";
    }
    cout << array[idx];
  }
  cout << endl;
}

template<template<typename...> class Container, typename Type>
void printArray(Container<Type> values)
{
  bool printComma = false;
  for (const auto& value : values) {
    if (printComma) {
      cout << ", ";
    }
    cout << value;
    printComma = true;
  }
  cout << endl;
}

Operation getOperation(const string& operation)
{
  if (operation == "sum") {
    return Operation::sum;
  }
  if (operation == "prod") {
    return Operation::product;
  }
  if (operation == "delta") {
    return Operation::delta;
  }

  return Operation::none;
}
