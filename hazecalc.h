// hazecalc.h
// Here we provide functions to calculate the haze using NEA Haze tables.
#include <map>
#include <string>
#include <vector>

using namespace std;

class HazeCalc
{
	public:
		HazeCalc();
		void take(const string& key, float value);
		float getAndReset();
	private: 
		float currentPSI;

		static const map<string, const vector<float>> NEA_HAZE_TABLE;
		static const vector<float> NEA_HAZE_TABLE_PSI;
};
