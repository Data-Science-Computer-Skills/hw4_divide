// suyonghua

#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>     /* atoi */
using namespace std;

vector<double> maxSumSeqInMid(vector<double>vec, vector<double> res_left, vector<double> res_right, int mid){
    vector<double> res_mid(3);
    int left_start = res_left.at(0), left_end = res_left.at(1), right_end = res_right.at(1);
    double mid_sum = res_left.at(2);
    for(int i = left_end+1; i <= mid+1; i++){
        mid_sum += vec.at(i);
    }
    double new_sum = mid_sum;
    int start = left_start, end = mid + 1;
    for(int j = mid+2; j <= right_end; j++){
        new_sum += vec.at(j);
        if(new_sum > mid_sum){
            end = j;
            mid_sum = new_sum;
        }
    }
    res_mid.at(0) = start;
    res_mid.at(1) = end;
    res_mid.at(2) = mid_sum;
    return res_mid;
}

vector<double> maxSumSeq(vector<double> vec, int low, int high){
    vector<double> res(3);
    if(low == high){
        res.at(0) = low;
        res.at(1) = high;
        res.at(2) = vec[low];
        return res;
    }

    int mid = (low + high) / 2;
    vector<double> res_left(3), res_right(3), res_mid(3);
    res_left = maxSumSeq(vec, low, mid);
    res_right = maxSumSeq(vec, mid + 1, high);
    if(res_right.at(2) > res_left.at(2))
        res = res_right;
    else
        res = res_left;

    res_mid = maxSumSeqInMid(vec, res_left, res_right, mid);
    if(res_mid.at(2) > res.at(2))
        res = res_mid;

    return res;
}

int main(int argc, char *argv[]){
    int seedN,sizeN;
    std::default_random_engine generator;

    sizeN = atoi(argv[1]); // convert string to int
    seedN = atoi(argv[2]);

    vector<double> vd(sizeN);
    generator.seed(seedN);

    std::uniform_real_distribution<double> distUniform(-100,100);

    size_t i;
    for(i = 0; i < sizeN; i++)
        vd.at(i) = distUniform(generator);

    cout << "The original array is:" << std::endl;
    for(i=0; i<sizeN;i++)
        cout << vd.at(i) << " ";
    cout << std::endl;

    // implement your own function
    vector<double> result = maxSumSeq(vd, 0, sizeN-1);
    int left, right;
    left = result.at(0);
    right = result.at(1);

    cout << "The consecutive subarray with maximum summation is:" << std::endl;
    for(i = left; i <=right; i++)
        cout << vd.at(i) << " ";
    cout << std::endl;
    cout << "Their summation is:" << result.at(2) << std::endl;

    return 0;
}

