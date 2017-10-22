//
//  Created by James on 15/3/12.
//  Copyright (c) 2015???dream. All rights reserved.
//

#ifndef __JOFRAMEWORK_ENTER_H__
#define __JOFRAMEWORK_ENTER_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

NS_JOFW_BEGIN

class JO_DLL JOFWEnter : public JOSingleton < JOFWEnter >
{
public:
	JOFWEnter();
	virtual ~JOFWEnter();

public:
	void init();
	void tick(float dt);
	
private:
	void _regPoolVO();
};

NS_JOFW_END

#endif // !__JOFRAMEWORK_ENTER_H__