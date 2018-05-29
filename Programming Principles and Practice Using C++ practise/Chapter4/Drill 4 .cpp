#include "std_lib_facilities.h"
double convertToMeter(double d,string c)
{
	if (c == "cm")
		return d / 100;
	if (c == "in")
		return d * 2.54 / 100;
	if (c == "ft")
		return d * 12 * 2.54 / 100;
	if (c == "m")
		return d;		
	simple_error("wrong unit!");
}
int main()
{
	vector<double> nums;
	double d;
	double sum = 0;
	string unit;
	double max;
	double min;
	if (cin >> d>>unit)
	{
		sum=max = min = convertToMeter(d,unit);
		nums.push_back(sum);
		cout << d<<unit << ":the smallest so far and the largest so far\n";
	}
	while (cin >> d>>unit)
	{
		double value = convertToMeter(d, unit);
		nums.push_back(value);
		if(value<min)
		{
			min = value;
		}
		if (value >max)
		{
			max = value;
		}
		cout << d<<unit;
		if (value == min)
		{
			cout << " ths smallest so far";
		}
		if (value == max) {
			cout << " the largest so far";
		}
		cout << '\n';
	}
	
	sort(nums);
	for (int i=nums.size()-1;i>-1;i--)
	{
		cout << nums[i] << '\t';
	}
	cout << endl;
	cout << "min: " << min << "m" << ",max: " << max << "m" << ",sum: " << "m\n";
}