#pragma once
#include <vector>

using namespace std;

vector<int> generateRandomArray(int n, int max_value);
vector<int> generateRandomArray(int n);
vector<int> inputArrayFromUser();
void printArray(const vector<int>& arr);
bool isSorted(const vector<int>& arr);