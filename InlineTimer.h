/*                                                         */
/* InlineTimer.h by T888 - T.888@gmx.com - github.com/T888 */
/*                                                         */

#ifndef INLINE_TIMER_H
#define INLINE_TIMER_H
#include <Windows.h>

// ************************************************************************************
// InlineTimer class : Performs high precision timing
// -- to start, construct a new instance or call Reset ()
// -- to stop, call Mark ()
// -- construct with a callback function argument if desired (*pfn)(double, void*)
// 
// ************************************************************************************
//
class InlineTimer
{
	typedef void (*Callback) (double, void*);

public:
	InlineTimer (Callback pfn = 0, void* context = 0);
	double Mark ();
	void Reset ();
	double GetLastDelta () const;
	void SetCallback (Callback pfn) {m_callback = pfn;}
	~InlineTimer (){}

protected:
	Callback  m_callback;
	__int64        m_start;
	__int64        m_freq;
	double         m_delta;
	void*          m_context;

private:
	InlineTimer (InlineTimer const&);
	InlineTimer& operator= (InlineTimer const&);
};


// _______________________________________________________________
//
// Initialization constructor
//
// _______________________________________________________________
//
inline
InlineTimer::InlineTimer (Callback pfn, void* context) 
	: m_callback (pfn)
	, m_start (0)
	, m_freq  (0)
	, m_delta (0.0)
	, m_context (context) {Reset ();}


// _______________________________________________________________
//
// Reset
//
// _______________________________________________________________
//
inline
void InlineTimer::Reset ()
{
	QueryPerformanceFrequency ((LARGE_INTEGER*)&m_freq);
	QueryPerformanceCounter ((LARGE_INTEGER*)&m_start);
}


// _______________________________________________________________
//
// Mark
//
// _______________________________________________________________
//
inline
double InlineTimer::Mark ()
{
	__int64 finish;
	QueryPerformanceCounter ((LARGE_INTEGER*)&finish);
	m_delta = (double) (finish - m_start) / m_freq;
	if (m_callback != 0)
		m_callback (m_delta, m_context);

	return m_delta;
}


// _______________________________________________________________
//
// GetLastDelta
//
// _______________________________________________________________
//
inline
double InlineTimer::GetLastDelta () const
{
	return m_delta;
}



#endif // INLINE_TIMER_H