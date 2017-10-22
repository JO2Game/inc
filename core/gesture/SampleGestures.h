#ifndef _SampleGesturesIncluded_
#define _SampleGesturesIncluded_

#include "core/gesture/GeometricRecognizerTypes.h"
#include "utils/JOMacro.h"

NS_JOFW_BEGIN
// TODO: read from a file. This approach is just ugly
//--- Make it a struct so that everything defaults to public
struct JO_DLL SampleGestures
{
    Path2D getGestureArrow();

    Path2D getGestureCaret();

    Path2D getGestureCheckMark();

    Path2D getGestureCircle();

    Path2D getGestureDelete();

    Path2D getGestureDiamond();

    Path2D getGestureLeftCurlyBrace();

    Path2D getGestureLeftSquareBracket();

    Path2D getGestureLeftToRightLine();

    Path2D getGestureLineDownDiagonal();

    Path2D getGesturePigtail();

    Path2D getGestureQuestionMark();

    Path2D getGestureRectangle();

    Path2D getGestureRightSquareBracket();

    Path2D getGestureRightCurlyBrace();

    Path2D getGestureRightToLeftLine();

    Path2D getGestureRightToLeftLine2();

    Path2D getGestureRightToLeftSlashDown();

    Path2D getGestureSpiral();

    Path2D getGestureStar();

    Path2D getGestureTriangle();

    Path2D getGestureV();

    Path2D getGestureX();

};

NS_JOFW_END

#endif