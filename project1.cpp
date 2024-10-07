#include <iostream>
#include <cmath>
#include <cstdlib>
#include "capacitor.h"

using namespace std;

void allocate_capacitor_arrays(Capacitor &cap, int num_steps)
{
	cap.time = (double*)malloc(num_steps * sizeof(double));
	cap.voltage = (double*)malloc(num_steps * sizeof(double));
	cap.current = (double*)malloc(num_steps * sizeof(double));
}

void free_capacitor_arrays(Capacitor &cap)
{
	free(cap.time);
	free(cap.voltage);
	free(cap.current);
}

void constant_current_supply(Capacitor &cap, double I, double dt, int num_steps)
{
	cap.voltage[0] = 0.0; 
	for(int t = 1; t < num_steps; ++t)
	{
		cap.time[t] = t *dt;
		cap.voltage[t] = cap.voltage[t-1] + (I *dt) / cap.C;
		if(t % 200 == 0)
		{
			cout << "Step: " << t << "Time: " << cap.time[t] << "Voltage: " << cap.voltage[t] << endl;
		}
	}
}

void constant_voltage_supply(Capacitor &cap, double V0, double R, double dt, int num_steps)
{
	cap.current[0] = V0/R;
	for(int t = 1; t < num_steps; ++t)
	{
		cap.time[t] = t *dt;
		cap.current[t] = cap.current[t-1] - (cap.current[t-1] * dt) / (R * cap.C);
		if(t % 200 == 0)
		{
			cout << "Step: " << t << "Time: " << cap.time[t] << "Current: " << cap.current[t] << endl;
		}
	}
}

int main()
{
	double dt = 1e-10;
	double final_time = 5e-6;
	int num_steps = (int)(final_time / dt);
	double R = 1000;
	double C = 100e-12;
	double I = 1e-2;
	double V0 = 10.0;

	Capacitor cap1;
	cap1.C = C;

	allocate_capacitor_arrays(cap1, num_steps);

	cout << "Constant Current Supply:\n";
	constant_current_supply(cap1, I, dt, num_steps);

	Capacitor cap2;
	cap2.C = C;
	allocate_capacitor_arrays(cap2, num_steps);

	cout << "\nConstant Voltage Supply:\n";
	constant_voltage_supply(cap2, V0, R, dt, num_steps);

	free_capacitor_arrays(cap1);
	free_capacitor_arrays(cap2);

	return 0;
}

