#ifndef __JORECT_H__
#define __JORECT_H__

#include <algorithm>
#include <math.h>

#include "utils/JOMacro.h"
#include "datastruct/JOPoint.h"
#include "datastruct/JOSize.h"

NS_JOFW_BEGIN

class JO_DLL JORect
{
public:
	/**Low left point of JORect.*/
	JOPoint origin;
	/**Width and height of the JORect.*/
	JOSize  size;

public:

	JORect();
	JORect(float x, float y, float width, float height);
	JORect(const JORect& other);

	JORect& operator= (const JORect& other);

	void setRect(float x, float y, float width, float height);
	float getMinX() const; /// return the leftmost x-value of current JORect
	float getMidX() const; /// return the midpoint x-value of current JORect
	float getMaxX() const; /// return the rightmost x-value of current JORect
	float getMinY() const; /// return the bottommost y-value of current JORect
	float getMidY() const; /// return the midpoint y-value of current JORect
	float getMaxY() const; /// return the topmost y-value of current JORect
	
	bool equals(const JORect& rect) const;
	
	bool containsPoint(const JOPoint& point) const;
	bool intersectsJORect(const JORect& rect) const;	
	bool intersectsCircle(const JOPoint& center, float radius) const;	
	JORect unionWithJORect(const JORect& rect) const;
	
	void merge(const JORect& rect);
	
	static const JORect ZERO;
};

NS_JOFW_END

#endif //__JORECT_H__

