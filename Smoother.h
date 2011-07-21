/*                                                      */
/* Smoother.h by T888 - T.888@gmx.com - github.com/T888 */
/*                                                      */

#ifndef SMOOTHER_H
#define SMOOTHER_H
#include "InlineTimer.h"
#include <list>

// ************************************************************************************
// Smoother class 
//    Provides a rolling average for a set of values.
//
// -- Template parameter type must support a zero initialization
//    e.g., "ItemType item (0);"
//
// -- Template parameter type must support the division operator/() for 
//    averaging values.
//
// ************************************************************************************
//
template <class Item>
class Smoother
{
	typedef std::list <Item> ItemList;

public:
	typedef void (*Callback)(Item);

	Smoother (unsigned samples, double sample_time = 0.0, Callback pfn = 0);
	void Update (Item item);
	Item GetAverage () const {return m_ravg;}
	void SetCallback (Callback pfn) {m_callback = pfn;}
	~Smoother ();

protected:
	ItemList m_list;
	unsigned m_samples;
	double   m_time;
	Callback m_callback;
	Item     m_ravg;
};


// _______________________________________________________________
//
// Initialization constructor
// -- samples: the maximum size of the smoother list.
// -- sample_time: time between recalculating average (and calling
//    the callback function).
// _______________________________________________________________
//
template <class Item> inline
Smoother <Item>::Smoother (unsigned samples, double sample_time, Callback pfn)
	: m_samples (samples), m_time (sample_time)
	, m_callback (pfn), m_ravg (0) {}


// _______________________________________________________________
//
// Destructor
//
// _______________________________________________________________
//
template <class Item> inline
Smoother <Item>::~Smoother () {}


// _______________________________________________________________
//
// Update
//    Adds a value to the list and performs an average
//    if applicable.
//
// _______________________________________________________________
//
template <class Item>
void Smoother <Item>::Update (Item item)
{
	// Record delta time.
	//
	static InlineTimer timer;
	timer.Mark ();

	// Push list value and pop if long enough.
	//
	m_list.push_back (item);
	if (m_list.size () > m_samples)
		m_list.pop_front ();

	// If the sample time has elapsed, process the list. If the
	// sample time is zero this block always executes. It also
	// executes if the list is size one (first call).
	//
	if (timer.GetLastDelta () >= m_time || m_list.size () == 1)
	{
		timer.Reset ();

		Item total (0);
		std::for_each (m_list.begin (), m_list.end (), [&](Item i) {
			total += i;
		});
		m_ravg = total / m_list.size ();
		if (m_callback != 0) m_callback (m_ravg);
	}
}


#endif // SMOOTHER_H