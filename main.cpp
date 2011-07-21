/*                                                    */
/* main.cpp by T888 - T.888@gmx.com - github.com/T888 */
/*                                                    */

#include "Utilities.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ios>
#include <vector>
#include <algorithm>

namespace {std::ofstream file ("output.txt");}

const double PI = 3.1415926535897932384626433832795;

//#define FILE_OUT
#ifdef FILE_OUT
	#define out file
#else
	#define out std::cout
#endif

int main ()
{
	out.precision (4);
	out << "\n";
	out << "Utilities" << "\n";
	out << "---------" << "\n\n";
	out << "-- Round (0.5) = " << Common::Round (0.5) << "\n";
	out << "-- Round (0.4) = " << Common::Round (0.4) << "\n";
	out << "-- Round (0.6) = " << Common::Round (0.6) << "\n";
	out << "\n";

	out << "-- Interpolate (0.0, 10.0, 0.0) = " << std::fixed << Common::Interpolate (0.0, 10.0, 0.0) << "\n";
	out << "-- Interpolate (0.0, 10.0, 0.3) = " << std::fixed << Common::Interpolate (0.0, 10.0, 0.3) << "\n";
	out << "-- Interpolate (0.0, 10.0, 0.5) = " << std::fixed << Common::Interpolate (0.0, 10.0, 0.5) << "\n";
	out << "-- Interpolate (0.0, 10.0, 0.7) = " << std::fixed << Common::Interpolate (0.0, 10.0, 0.7) << "\n";
	out << "-- Interpolate (0.0, 10.0, 1.0) = " << std::fixed << Common::Interpolate (0.0, 10.0, 1.0) << "\n";
	out << "\n";

	out << "-- SmoothInterpolate (0.0, 10.0, 0.0) = " << std::fixed << Common::SmoothInterpolate (0.0, 10.0, 0.0) << "\n";
	out << "-- SmoothInterpolate (0.0, 10.0, 0.3) = " << std::fixed << Common::SmoothInterpolate (0.0, 10.0, 0.3) << "\n";
	out << "-- SmoothInterpolate (0.0, 10.0, 0.5) = " << std::fixed << Common::SmoothInterpolate (0.0, 10.0, 0.5) << "\n";
	out << "-- SmoothInterpolate (0.0, 10.0, 0.7) = " << std::fixed << Common::SmoothInterpolate (0.0, 10.0, 0.7) << "\n";
	out << "-- SmoothInterpolate (0.0, 10.0, 1.0) = " << std::fixed << Common::SmoothInterpolate (0.0, 10.0, 1.0) << "\n";
	out << "\n";

	// -------------------------------------------------
	// InsertSorted
	//
	std::vector <char> chars (26);
	for (unsigned i = 0; i < chars.size (); ++i)
		chars[i] = 'a' + i;
	std::random_shuffle (chars.begin (), chars.end ());
	chars.resize (10);
	out << "-- std::vector <char> chars: ";
	for (unsigned i = 0; i < chars.size (); ++i) {
		out << chars[i] << " ";
	} out << "\n";
	std::vector <char> sorted;
	for (unsigned i = 0; i < chars.size (); ++i) {
		Common::InsertSorted (chars[i], sorted);
		out << "-- InsertSorted (), std::vector sorted = ";
		for (unsigned j = 0; j < sorted.size (); ++j) {
			out << sorted[j] << " ";
		}
		out << "\n";
	}

	out << std::endl << std::endl;
	return 0;
}