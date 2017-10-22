#ifndef __JOSIZE_H__
#define __JOSIZE_H__

#include <algorithm>
#include <math.h>

#include "datastruct/JOPoint.h"
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JO_DLL JOSize
{
public:
	/**Width Height of the JOSize.*/
	float width;	
	float height;

public:
	/**
	@{
	Constructor.
	@param width Width of the Size.
	@param height Height of the Size.
	@param other Copy constructor.
	@param point Conversion from a point.
	*/
	JOSize();
	JOSize(float width, float height);
	JOSize(const JOSize& other);
	explicit JOSize(const JOPoint& point);
		
	JOSize& operator= (const JOSize& other);
	JOSize& operator= (const JOPoint& point);
	JOSize operator+(const JOSize& right) const;
	JOSize operator-(const JOSize& right) const;
	JOSize operator*(float a) const;
	JOSize operator/(float a) const;

	void setSize(float width, float height);
	bool equals(const JOSize& target) const;

	static const JOSize ZERO;
};

NS_JOFW_END

#endif //__JOSIZE_H__
