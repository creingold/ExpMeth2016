/*
Craig Reingold
2/18/16
Autotune

This program will do the following:
	- take in .csv file with data from the variable energy source?
	- if not above, take in a .dat file
	- TSpectrum to find the peaks
	- Fit the quadratic background around the peaks
	- Fit the gaussians with quadratic background accounted for
	- Plot TGraphErrors with Energy against Channel
	- Fit a calibration curve to the TGraph, and then output the results of the curve
*/
