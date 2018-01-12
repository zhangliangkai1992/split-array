#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;
const int N = 1000;
const int M = 32;
const int NUMMAX = 100000;
double sum = 0.0;
void printSet(vector<int> a)
{
    for (auto i = a.begin(); i != a.end(); ++i) {
	std::cout << *i << "\t";
    }
    std::cout << "" << std::endl;
}
void splitArray(int* array, vector<int>* s)
{
    int realSum[M];
    int currentSetIndex = 0;
    memset(realSum, 0, M * sizeof(int));
    bool flag = true;
    int i;
    for (i = N - 1; i >= 0 ; --i) {
	if(realSum[currentSetIndex] + array[i] <= sum) {
	    s[currentSetIndex].push_back(array[i]);
	    realSum[currentSetIndex] += array[i];
	    if(flag) {
		if(currentSetIndex == M-1) {
		    flag = false;
		} else
		    ++currentSetIndex;
	    } else {
		if(currentSetIndex == 0) {
		    flag = true;
		} else
		    --currentSetIndex;
	    }
	} else {
	    break;
	}
    }
    std::cout << "currentSetIndex = " << currentSetIndex << "\ti = " << i << "\tcurrentVal = " << array[i]<< std::endl;

    int totalElement = 0;
    for(int j = 0; j <= i; j++) {
	s[currentSetIndex].push_back(array[j]);
	realSum[currentSetIndex] += array[j];
	currentSetIndex = (currentSetIndex + 1) % M;
    }

    for (int i = 0; i < M; ++i) {
	std::cout << "realSum = " << realSum[i] << std::endl;
	std::cout << "set size = " << s[i].size() << std::endl;
	totalElement += s[i].size();

    }
    std::cout << "N = " << N << "\ttotalElement = " << totalElement << std::endl;

}
int main(int argc, char **argv)
{
    int array[N];
    sum = 0;
    srand((unsigned)(time(0)));
    for (int i = 0; i < N; ++i) {
	array[i] = rand() % NUMMAX;
	//	array[i] = i;
	sum += array[i];
    }
    sort(array, array+N);
    std::cout << "100 element:" << std::endl;

    for(int i = 0; i < 100; i++) {
	//	std::cout << array[i] << "\t";
    }
    std::cout << std::endl;
    std::cout << "min-max = " << array[0] << "\t" << array[N-1] << std::endl;

    sum /= M;
    std::cout << "sum = " << sum << std::endl;

    vector<int> ss[M];
    splitArray(array, ss);
    for (int i = 0; i < M; ++i) {
	std::cout << "set #" << i << "\t";
	printSet(ss[i]);
    }
    return 0;
}
