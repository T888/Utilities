/*                                                       */
/* Utilities.h by T888 - T.888@gmx.com - github.com/T888 */
/*                                                       */

#ifndef UTILS_H
#define UTILS_H

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
	#include <cmath>
	#undef _USE_MATH_DEFINES
#else
	#include <cmath>
#endif

#include <stdlib.h>
#include <ctime>

#ifndef FLOAT_TYPE
	#define FLOAT_TYPE_DEFINED
	#define FLOAT_TYPE double
#endif

#ifndef FLOAT_EPSILON
	#define FLOAT_EPSILON_DEFINED
	#define FLOAT_EPSILON 1.0E-6
#endif

namespace Common
{
	// Epsilon value for floating point equality testing
	//
	const FLOAT_TYPE Epsilon = (FLOAT_TYPE) FLOAT_EPSILON;

	// _________________________________________________
	//
	// Round
	// -- Rounds a floating point value to the nearest
	//    integer 
	// _________________________________________________
	//
	inline
	int Round (FLOAT_TYPE f) {
		return int ((f < 0.0) ? (f - 0.5) : (f + 0.5));
	}


	// _________________________________________________
	//
	// InsertSorted (models insertion sort)
	// -- Inserts an item in sorted order into 
	//    a std::vector <> or compatible container.
	// -- For inserting into an already sorted array,
	//    this function runs O(n) with expected n/2 
	//    time on random data.
	// _________________________________________________
	//
	template <class Item, class Container>
	void InsertSorted (Item item, Container& c)
	{
		// Add new item to back of container
		//
		c.push_back (item);

		// Rotate items from last to last-minus-one
		// until new item is in sorted order.
		//
		size_t j = c.size () - 1;
		while ((j > 0) && (c[j] < c[j-1])) {
			std::swap (c[j], c[j-1]); 
			--j; 
		}
	}


	// _________________________________________________
	//
	// Interpolate
	// -- Provides linear interpolation between 
	// _________________________________________________
	//
	template <class ItemType> inline
	ItemType Interpolate (ItemType v1, ItemType v2, FLOAT_TYPE t)
	{
		return v1 + t*(v2-v1);
		// equivalent to (1-p)*v1 + p*v2.
	}


	// _________________________________________________
	//
	// SmoothInterpolate
	// -- Provides cubic interpolation between values.
	// _________________________________________________
	//
	template <class ItemType> inline
	ItemType SmoothInterpolate (ItemType v1, ItemType v2, FLOAT_TYPE t)
	{
		FLOAT_TYPE p = t*t*(3-2*t); // 3t^2 - 2t^3 = t^2(3-2t)
		return Interpolate (v1, v2, p*(v2-v1)); //v1 + p*(v2-v1);
		// equivalent to (1-p)*v1 + p*v2.
	}


	// _________________________________________________
	//
	// CosInterpolate
	// -- Provides sinusoidal interpolation between values.
	// _________________________________________________
	//
	template <class ItemType> inline
	ItemType CosInterpolate (ItemType v1, ItemType v2, FLOAT_TYPE t)
	{
		FLOAT_TYPE p = (1.0 - cos (t * M_PI)) * 0.5;
		return Interpolate (v1, v2, p*(v2-v1)); //v1 + p*(v2-v1);
		// equivalent to (1-p)*v1 + p*v2.
	}


	// _________________________________________________
	//
	// WrapEuler
	// -- Returns values in the range [-180, 180].
	// _________________________________________________
	//
	inline
	FLOAT_TYPE WrapEuler (FLOAT_TYPE angle, bool radians = true)
	{
		FLOAT_TYPE alpha = (radians == true) ? (float) M_PI : 180.f;
		if (angle < -alpha) angle = angle + 2*alpha;
		if (angle >  alpha) angle = angle - 2*alpha;
		return angle;
	}


	// _________________________________________________
	//
	// Clamp
	// -- Clips the bounds of a value, [min, max].
	// _________________________________________________
	//
	template <class ItemType> inline
	ItemType Clamp (ItemType val, ItemType min, ItemType max)
	{
		if (val < min) val = min;
		if (val > max) val = max;
		return val;
	}


	// _________________________________________________
	//
	// Wrap
	// -- Wraps values from min->max and max->min.
	// _________________________________________________
	//
	template <class ItemType> inline
	ItemType Wrap (ItemType val, ItemType min, ItemType max)
	{
		while (val < min) val += (max-min);
		while (val > max) val -= (max-min);
		return val;
	}


	// _________________________________________________
	//
	// Min
	// -- Returns the minimum of two values.
	// _________________________________________________
	//
	template <class ItemType> inline
	ItemType Min (ItemType val1, ItemType val2)
	{
		return val1 < val2 ? val1 : val2;
	}


	// _________________________________________________
	//
	// Max
	// -- Returns maximum of two values.
	// _________________________________________________
	//
	template <class ItemType> inline
	ItemType Max (ItemType val1, ItemType val2)
	{
		return val1 > val2 ? val1 : val2;
	}


}


namespace Random
{
	// _________________________________________________
	// 
	// InitRNG : initialize the random number generator
	// -- seed=0 randomizes rng starting point
	// -- seed=1 reinitializes the rng
	// -- seed=[2,n] passes directly to srand()
	// _________________________________________________
	//
	inline void InitRNG (unsigned seed = 0)
	{ 
		// seed is randomized
		if (seed == 0)
			srand ((unsigned) time (0));

		// Reinitializes rng (see lib documentation)
		else if (seed = 1)
			srand (1);

		// seed is fixed
		else
			srand (seed);
	}


	// _________________________________________________
	//
	// RandInt
	// -- Generate a random integer, [0, size)
	// _________________________________________________
	//
	inline int RandInt (int size)
	{ 
		if (size == 0)
			return 0;
		else 
			return rand () % size;
	}


	// _________________________________________________
	//
	// RandInt
	// -- Generate a random integer, [min, max]
	// _________________________________________________
	//
	inline int RandInt (int min, int max)
	{
		if (min == max)
			return min;
		else
			return min + RandInt (max - min + 1);
	}


	// _________________________________________________
	//
	// RandFloat
	// -- Generate a random float, [0, 1)
	// _________________________________________________
	//
	inline FLOAT_TYPE RandFloat ()
	{
		return rand () / (float) (RAND_MAX + 1);
	}


	// _________________________________________________
	//
	// RandFloatN
	// -- Generate a random float, (-1, 1)
	// _________________________________________________
	//
	inline FLOAT_TYPE RandFloatN ()
	{
		return 2 * RandFloat () - 1;
	}


	// _________________________________________________
	//
	// TrueOrFalse
	// -- 50/50 function, {true, false}
	// _________________________________________________
	//
	inline bool TrueOrFalse ()
	{
		return RandFloat () < 0.5;
	}


	// _________________________________________________
	//
	// HeadsOrTails
	// -- 50/50 function, {true, false}
	// _________________________________________________
	//
	inline bool HeadsOrTails ()
	{
		return TrueOrFalse ();
	}


	// _________________________________________________
	//
	// PosOrNeg
	// -- returns {-1, 1}
	// _________________________________________________
	//
	inline int PosOrNeg ()
	{
		return (TrueOrFalse ()) ? (1) : (-1);
	}


	// _________________________________________________
	//
	// DiceRoll
	// -- Return an integer, [1, sides]
	// _________________________________________________
	//
	inline unsigned DiceRoll (unsigned sides)
	{
		return RandInt (1, sides);
	}
}


#ifdef FLOAT_TYPE_DEFINED
	#undef FLOAT_TYPE
	#undef FLOAT_TYPE_DIFINED
#endif


#ifdef FLOAT_EPSILON_DEFINED
	#undef FLOAT_EPSILON
	#undef FLOAT_EPSILON_DIFINED
#endif

#endif // UTILS_H