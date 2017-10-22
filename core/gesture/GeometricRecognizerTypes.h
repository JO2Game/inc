#ifndef _GeometricRecognizerTypesIncluded_
#define _GeometricRecognizerTypesIncluded_

/*
* This code taken (and modified) from the javascript version of:
* The $1 Gesture Recognizer
*
*		Jacob O. Wobbrock
* 		The Information School
*		University of Washington
*		Mary Gates Hall, Box 352840
*		Seattle, WA 98195-2840
*		wobbrock@u.washington.edu
*
*		Andrew D. Wilson
*		Microsoft Research
*		One Microsoft Way
*		Redmond, WA 98052
*		awilson@microsoft.com
*
*		Yang Li
*		Department of Computer Science and Engineering
* 		University of Washington
*		The Allen Center, Box 352350
*		Seattle, WA 98195-2840
* 		yangli@cs.washington.edu
*/
#include <math.h>
#include <string>
#include <list>
#include <vector>
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JO_DLL Point2D
{
public:
	//--- Wobbrock used doubles for these, not ints
	//int x, y;
	double x, y;
	Point2D();	
	Point2D(double x, double y);
};

typedef std::vector<Point2D>  Path2D;
typedef Path2D::iterator Path2DIterator;

class JO_DLL Rectangle
{
public:
	double x, y, width, height;
	Rectangle(double x, double y, double width, double height);
};

class JO_DLL RecognitionResult
{
public:
	std::string name;
	double score;
	RecognitionResult(std::string name, double score);
};


class JO_DLL GestureTemplate
{
public:
	std::string name;
	Path2D points;	
	GestureTemplate(std::string name, Path2D points);
};
typedef std::vector<GestureTemplate> GestureTemplates;


class JO_DLL PathWriter
{
public:
	static bool writeToFile(
		Path2D path,
		const std::string fileName = "savedPath.txt",
		const std::string gestureName = "DefaultName");
};

NS_JOFW_END
#endif