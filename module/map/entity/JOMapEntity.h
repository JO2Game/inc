#ifndef __JOMAP_ENTITY_H__
#define __JOMAP_ENTITY_H__

#include "cocos2d.h"
USING_NS_CC;

#include "datastruct/JOPoint.h"
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JO_DLL JOMapEntity : public Node
{
public:	
	JOMapEntity();
	virtual ~JOMapEntity();

	inline const long long getId(){ return entityId; };
	inline void setId(long long id){ entityId = id; };

public:
	enum { TOP, LEFT, LEFT_BOTTOM, BOTTOM, RIGHT_BOTTOM, RIGHT};
	void setDirectionWithPoints(JOPoint &sPoint, JOPoint &ePoint);
	void setDirection(short type);


protected:
	long long entityId;
};

NS_JOFW_END

#endif	//__JOMAP_ENTITY_H__
