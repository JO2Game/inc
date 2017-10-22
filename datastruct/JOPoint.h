#ifndef __JOPOINT_H__
#define __JOPOINT_H__

#include <algorithm>
#include <math.h>

#include "utils/JOMacro.h"
NS_JOFW_BEGIN
/**
* Defines a 2-element floating point vector.
*/
class JO_DLL JOPoint
{	
public:
	float x;
	float y;

	~JOPoint();
	JOPoint();	
	JOPoint(float xx, float yy);	
	JOPoint(const float* array);
	JOPoint(const JOPoint& copy);
	/**
	* Constructs a vector that describes the direction between the specified points.
	*
	* @param p1 The first point.
	* @param p2 The second point.
	*/
	JOPoint(const JOPoint& p1, const JOPoint& p2);

	
	inline bool isZero() const{ return x == 0.0f && y == 0.0f; };
	inline bool isOne() const{ return x == 1.0f && y == 1.0f; };
	inline void add(const JOPoint& v){
		x += v.x;
		y += v.y;
	};

	static float angle(const JOPoint& v1, const JOPoint& v2);
	static void add(const JOPoint& v1, const JOPoint& v2, JOPoint* dst);
	/**
	根据点v 返回一个限制在min\max之内的点
	*/
	static JOPoint clamp(const JOPoint& v, const JOPoint& min, const JOPoint& max);

	
	
	/**
	将点限制在min\max之内
	*/
	void clamp(const JOPoint& min, const JOPoint& max);

	float distance(const JOPoint& v) const;

	/**
	还没开平方根的distance值
	*/
	inline float distanceSquared(const JOPoint& v) const{
		float dx = v.x - x;
		float dy = v.y - y;
		return (dx * dx + dy * dy);
	};

	/**
	点乘
	*/
	inline float dot(const JOPoint& v) const{ return (x * v.x + y * v.y); };
	static float dot(const JOPoint& v1, const JOPoint& v2);

	/**
	距离原点的长度
	*/
	float length() const;
	inline float lengthSquared() const{ return (x * x + y * y); };

	/**
	相反数
	*/
	inline void negate(){
		x = -x;
		y = -y;
	};

	/**
	归一化，处理后，x、y都小于1
	*/
	void normalize();	
	JOPoint getNormalized() const;

	/**
	x,y都时乘以系数scalar
	*/
	inline void scale(float scalar){
		x *= scalar;
		y *= scalar;
	};
	inline void scale(const JOPoint& scale){
		x *= scale.x;
		y *= scale.y;
	};

	/**
	* Rotates this vector by angle (specified in radians) around the given point.
	*
	* @param point The point to rotate around.
	* @param angle The angle to rotate by (in radians).
	*/
	void rotate(const JOPoint& point, float angle);


	inline void set(float xx, float yy){
		this->x = xx;
		this->y = yy;
	};
	void set(const float* array);
	inline void set(const JOPoint& v){
		this->x = v.x;
		this->y = v.y;
	};
	inline void set(const JOPoint& p1, const JOPoint& p2){
		x = p2.x - p1.x;
		y = p2.y - p1.y;
	};
	inline void setZero(){ x = y = 0.0f; };

	/**
	减
	*/
	inline void subtract(const JOPoint& v){
		x -= v.x;
		y -= v.y;
	};
	static void subtract(const JOPoint& v1, const JOPoint& v2, JOPoint* dst);

	/**
	点靠向target的过程，通过逝去时间和响应时间影响
	* Updates this vector towards the given target using a smoothing function.
	* The given response time determines the amount of smoothing (lag). A longer
	* response time yields a smoother result and more lag. To force this vector to
	* follow the target closely, provide a response time that is very small relative
	* to the given elapsed time.
	*
	* @param target target value.
	* @param elapsedTime elapsed time between calls.
	* @param responseTime response time (in the same units as elapsedTime).
	*/
	inline void smooth(const JOPoint& target, float elapsedTime, float responseTime){
		if (elapsedTime > 0)
		{
			*this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
		}
	};

	
	inline const JOPoint operator+(const JOPoint& v) const{
		JOPoint result(*this);
		result.add(v);
		return result;
	};
	inline JOPoint& operator+=(const JOPoint& v){
		add(v);
		return *this;
	};
	inline const JOPoint operator-(const JOPoint& v) const{
		JOPoint result(*this);
		result.subtract(v);
		return result;
	};
	inline JOPoint& operator-=(const JOPoint& v){
		subtract(v);
		return *this;
	};
	inline const JOPoint operator-() const{
		JOPoint result(*this);
		result.negate();
		return result;
	};
	inline const JOPoint operator*(float s) const{
		JOPoint result(*this);
		result.scale(s);
		return result;
	};
	inline JOPoint& operator*=(float s){
		scale(s);
		return *this;
	};
	
	inline const JOPoint operator/(float s) const{
		return JOPoint(this->x / s, this->y / s);
	};

	inline bool operator<(const JOPoint& v) const{
		if (x == v.x){
			return y < v.y;
		}
		return x < v.x;
	};
	inline bool operator>(const JOPoint& v) const{
		if (x == v.x){
			return y > v.y;
		}
		return x > v.x;
	};
	inline bool operator==(const JOPoint& v) const{ return x == v.x && y == v.y; };
	inline bool operator!=(const JOPoint& v) const{ return x != v.x || y != v.y; };

	
public:	
	
	bool equals(const JOPoint& target) const;

	/*
	在误差variance范围内，是否相等
	*/
	bool fuzzyEquals(const JOPoint& target, float variance) const;


	/** @returns the angle in radians between this vector and the x axis
	*/
	inline float getAngle() const {
		return atan2f(y, x);
	};

	/** @returns the angle in radians between two vector directions
	*/
	float getAngle(const JOPoint& other) const;

	/** Calculates cross product of two points.
	*/
	inline float cross(const JOPoint& other) const {
		return x*other.y - y*other.x;
	};

	/** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
	*/
	inline JOPoint getPerp() const {
		return JOPoint(-y, x);
	};
	/** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
	*/
	inline JOPoint getRPerp() const {
		return JOPoint(y, -x);
	};

	/** Calculates midpoint between two points.
	*/
	inline JOPoint getMidpoint(const JOPoint& other) const
	{
		return JOPoint((x + other.x) / 2.0f, (y + other.y) / 2.0f);
	}

	/** Clamp a point between from and to.
	*/
	JOPoint getClampPoint(const JOPoint& min_inclusive, const JOPoint& max_inclusive) const;

	/** Run a math operation function on each point component
	* absf, fllorf, ceilf, roundf
	* any function that has the signature: float func(float);
	* For example: let's try to take the floor of x,y
	* p.compOp(floorf);
	@since v3.0
	* @js NA
	* @lua NA
	*/
	inline JOPoint compOp(std::function<float(float)> function) const
	{
		return JOPoint(function(x), function(y));
	}

	

	/** Calculates the projection of this over other.
	*/
	inline JOPoint project(const JOPoint& other) const {
		return other * (dot(other) / other.dot(other));
	};

	/** Complex multiplication of two points ("rotates" two points).
	@return JOPoint vector with an angle of this.getAngle() + other.getAngle(),
	and a length of this.getLength() * other.getLength().
	*/
	inline JOPoint rotate(const JOPoint& other) const {
		return JOPoint(x*other.x - y*other.y, x*other.y + y*other.x);
	};

	/** Unrotates two points.
	@return JOPoint vector with an angle of this.getAngle() - other.getAngle(),
	and a length of this.getLength() * other.getLength().
	*/
	inline JOPoint unrotate(const JOPoint& other) const {
		return JOPoint(x*other.x + y*other.y, y*other.x - x*other.y);
	};

	/** Linear Interpolation between two points a and b
	@returns
	alpha == 0 ? a
	alpha == 1 ? b
	otherwise a value between a..b
	*/
	inline JOPoint lerp(const JOPoint& other, float alpha) const {
		return *this * (1.f - alpha) + other * alpha;
	};

	/** Rotates a point counter clockwise by the angle around a pivot
	@param pivot is the pivot, naturally
	@param angle is the angle of rotation ccw in radians
	@returns the rotated point
	*/
	JOPoint rotateByAngle(const JOPoint& pivot, float angle) const;

	
	static inline JOPoint forAngle(const float a)
	{
		return JOPoint(cosf(a), sinf(a));
	}

	/** A general line-line intersection test
	@param A   the startpoint for the first line L1 = (A - B)
	@param B   the endpoint for the first line L1 = (A - B)
	@param C   the startpoint for the second line L2 = (C - D)
	@param D   the endpoint for the second line L2 = (C - D)
	@param S   the range for a hitpoint in L1 (p = A + S*(B - A))
	@param T   the range for a hitpoint in L2 (p = C + T*(D - C))
	@returns   whether these two lines interects.

	Note that to truly test intersection for segments we have to make
	sure that S & T lie within [0..1] and for rays, make sure S & T > 0
	the hit point is        C + T * (D - C);
	the hit point also is   A + S * (B - A);
	*/
	static bool isLineIntersect(const JOPoint& A, const JOPoint& B,
		const JOPoint& C, const JOPoint& D,
		float *S = nullptr, float *T = nullptr);

	/**
	returns true if Line A-B overlap with segment C-D	
	*/
	static bool isLineOverlap(const JOPoint& A, const JOPoint& B,
		const JOPoint& C, const JOPoint& D);

	/**
	returns true if Line A-B parallel with segment C-D	
	*/
	static bool isLineParallel(const JOPoint& A, const JOPoint& B,
		const JOPoint& C, const JOPoint& D);

	/**
	returns true if Segment A-B overlap with segment C-D	
	*/
	static bool isSegmentOverlap(const JOPoint& A, const JOPoint& B,
		const JOPoint& C, const JOPoint& D,
		JOPoint* S = nullptr, JOPoint* E = nullptr);

	/**
	returns true if Segment A-B intersects with segment C-D	
	*/
	static bool isSegmentIntersect(const JOPoint& A, const JOPoint& B, const JOPoint& C, const JOPoint& D);

	/**
	returns the intersection point of line A-B, C-D	
	*/
	static JOPoint getIntersectPoint(const JOPoint& A, const JOPoint& B, const JOPoint& C, const JOPoint& D);

	/** equals to JOPoint(0,0) */
	static const JOPoint ZERO;
	/** equals to JOPoint(1,1) */
	static const JOPoint ONE;
	/** equals to JOPoint(1,0) */
	static const JOPoint UNIT_X;
	/** equals to JOPoint(0,1) */
	static const JOPoint UNIT_Y;
	/** equals to JOPoint(0.5, 0.5) */
	static const JOPoint ANCHOR_MIDDLE;
	/** equals to JOPoint(0, 0) */
	static const JOPoint ANCHOR_BOTTOM_LEFT;
	/** equals to JOPoint(0, 1) */
	static const JOPoint ANCHOR_TOP_LEFT;
	/** equals to JOPoint(1, 0) */
	static const JOPoint ANCHOR_BOTTOM_RIGHT;
	/** equals to JOPoint(1, 1) */
	static const JOPoint ANCHOR_TOP_RIGHT;
	/** equals to JOPoint(1, 0.5) */
	static const JOPoint ANCHOR_MIDDLE_RIGHT;
	/** equals to JOPoint(0, 0.5) */
	static const JOPoint ANCHOR_MIDDLE_LEFT;
	/** equals to JOPoint(0.5, 1) */
	static const JOPoint ANCHOR_MIDDLE_TOP;
	/** equals to JOPoint(0.5, 0) */
	static const JOPoint ANCHOR_MIDDLE_BOTTOM;
};

NS_JOFW_END

#endif //__JOPOINT_H__

