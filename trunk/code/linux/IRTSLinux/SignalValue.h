
/**
 * @file
 * Implements the SignalValue and AnnotValue struct's
 */
#ifndef SIGNALVALUE_H_
#define SIGNALVALUE_H_

/**
 * Structure for holding signal value.
 *
 */
struct SignalValue
{
	float value;
	float value2;
	int sample;
};

/**
 * Structure for hold annotation values.
 *
 */
struct AnnotValue
{
	float value;
	int   sample;
	char  type;

};



#endif /* SIGNALVALUE_H_ */

