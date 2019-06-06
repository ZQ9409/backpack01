// backpack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;
/*
背包算法   f(i,j) = max( (f(i-1,j-Wi) + Pi) ;  f(i-1,j))
其中f(i,j) 代表背包容量为j，可放的物品共有i个时，能达到的价值最大值，Wi代表编号为i的物品的重量，Pi代表i物品的价值
(f(i-1,j-Wi) + Pi)    代表先放i物品后，还能放下的物品最大价值  此时需要保证i物品能放进背包
f(i-1,j)              代表不放i物品时能放下的物品最大值。
pig
2019.6.5
after  vivo failed
*/


void print_val(vector< vector<int> > re)
{
	int n = re.size();
	int m = re[0].size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << "re[" << i << "][" << j << "] = " << re[i][j] << "  ";
		}
		cout << endl;
	}
}



int main()
{
	//物品的重量
	vector<int> weight = { 4,5,6,2,2 };  //C++ 98不允许这种初始化方式
	//物品的价值
	vector<int> value = { 6,4,5,3,6 };
	//f(i,j)的存储容器
	vector< vector<int> > result;
	//包含几件物品可选的f(x,j)
	vector<int> result1;
	//j在此处代表的是可选择的物品的数量
	for (int j = 0; j < value.size(); j++)
	{
		//i代表背包容量
		for (int i = 0; i < 11; i++)
		{
			if (j == 0)
			{
				if (weight[0] <= i)
					result1.push_back(value[0]);
				else
					result1.push_back(0);
			}
			else
			{
				//need1 代表必须先放最后一个物品，再放其他物品的value值
				//noneed1 代表不放最后一个物品，再放其他物品的value值
				int need1 = 0, noneed1 = 0;

				//计算必须先放最后一个物品，再放其他物品的value值   计算f(i-1,j-wi) + Pi
				//能放下最后的物品用以下公式  （f(i-1,j-wi) + Pi）  计算;不能放下时need1的计算与后面noneed1的计算公式相同，故不在重复计算
				if (weight[j] <= i)
				{	//f(i-1,j-wi) + Pi
					//判断剩余的容量能放下的最大的物品value
					if (i - weight[j] <= 0)
						need1 = value[j];
					else
						need1 = value[j] + result[j - 1][i - weight[j]];
				}
				//代表不放最后一个物品，再放其他物品的value值
				//f(i-1,j)
				noneed1 = result[j - 1][i];
				int max = need1 > noneed1 ? need1 : noneed1;
				result1.push_back(max);
			}
		}
		result.push_back(result1);
		result1.clear();
	}
	print_val(result);
	return 0;
}




