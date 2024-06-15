#ifndef __XITOA_H_
#define __XITOA_H_

/** Converts an integer to another number base as a string.
 * 
 * This will convert an integer to other number bases and return a string. Specify the base, for example '16' for hex, '2' for binary.
 * No memory allocation is done, and no bounds checking is performed, so make sure the string you pass in is long enough.
 * 
 * @param[in] value The value to convert.
 * @param[in] result A pointer to a long enough string for the output.
 * @param[in] base The base to use
 * @return A pointer to result
 */
char* xitoa(int value, char* result, int base);

#endif