#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;
const int N = 30;
const int M = 3 ;
const int MAX = 100;
typedef int DataType;
double average;
struct PartInfo {
    static int count;
    DataType val;
    int number;
    int rank;
    PartInfo(DataType v)
    {
	val = v;
	number = count;
	++count;
	rank = -1;
    }
};
int PartInfo::count = 0;
bool compare(PartInfo a, PartInfo b)
{
    return a.val < b.val;
}
/**
 * part n elements into m parts with balance
 * input array[N]
 * output result[N]
 */
void splitArray(vector<PartInfo>& input, int* result)
{
    int index = 0;
    int currentVectorIndex = 0;
    DataType partSum[M];
    vector<DataType> subPart[M];
    memset(partSum, 0, sizeof(DataType) * M);
    bool flag = true;
    for(index = N - 1; index >= 0; index--) {
	if(partSum[currentVectorIndex] + input[index].val <= average) {
	    input[index].rank = currentVectorIndex;
	    partSum[currentVectorIndex] += input[index].val;
	    subPart[currentVectorIndex].push_back(input[index].val);
	    if(flag) {
		if(currentVectorIndex == M - 1)
		    flag =false;
		else
		    ++currentVectorIndex;
	    } else {
		if(currentVectorIndex == 0)
		    flag = true;
		else
		    --currentVectorIndex;
	    }
	} else {
	    break;
	}
    }
    for(int i = 0; i <= index; i++) {
	input[i].rank = currentVectorIndex;
	partSum[currentVectorIndex] += input[i].val;
	subPart[currentVectorIndex].push_back(input[i].val);
	currentVectorIndex = (currentVectorIndex + 1) % M;
    }
    int totalSum = 0;
    for(int i = 0; i < M; i++) {
	totalSum += subPart[i].size();
	std::cout << "#" << i << "\tpartSum = " << partSum[i] << std::endl;
	std::cout << "subPart\t";
	for (auto it = subPart[i].begin(); it != subPart[i].end(); ++it) {
	    std::cout << *it << "\t";
	}
	std::cout << "" << std::endl;

    }
    for(int i = 0; i < N; i++) {
	result[input[i].number] = input[i].rank;
    }
    std::cout << "result : N = " << N << "\ttotalSum = " << totalSum << std::endl;
    for(int i = 0; i < N; i++) {
	std::cout << result[i] << " ";
    }
    std::cout << "" << std::endl;

}

int main(int argc, char **argv)
{
    vector<PartInfo> parts;
    average = 0;
    std::cout << "datas : " << std::endl;

    for(int i = 0; i < N; i++) {
	DataType data = rand() % MAX;
	//DataType data = i + 1;
	//DataType data = 200;
	std::cout << data << " ";
	parts.push_back(PartInfo(data));
	average += data;
    }
    //    parts[10].val = 540;
    std::cout << "" << std::endl;

    average /= M;
    std::cout << "average = " << average << std::endl;

    sort(parts.begin(), parts.end(), compare);
    std::cout << "min-max = " << parts[0].val << "\t" << parts[N-1].val << std::endl;

    int result[N];
    splitArray(parts, result);
    return 0;
}
