#ifndef __JO_LASER_H__
#define __JO_LASER_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "ui/JOSprite.h"

NS_JOFW_BEGIN

class JOHalfLaser;

class JO_DLL JOLaser :public Node
{
	JO_CLS_MPOOL_DECLARE(JOLaser);
public:
	JOLaser();
	virtual ~JOLaser();
	static JOLaser* create(const string &Laser, const string &mask, const string &mask2, const string &noise, const string &noise2);
	bool init(const string &Laser, const string &mask, const string &mask2, const string &noise, const string &noise2);
	void setStart(const Point&start);
	void setEnd(const Point&end);

protected:
	void _layout();
private:
	JOHalfLaser*m_halfLaser1;
	JOHalfLaser*m_halfLaser2;
	JOHalfLaser*m_slimHalfLaser1;
	JOHalfLaser*m_slimHalfLaser2;
	Point m_start;
	Point m_end;
};

class JOHalfLaser :public JOSprite{
public:
	JOHalfLaser();
	virtual~JOHalfLaser();
	static JOHalfLaser* create(const string &Laser, const string &mask, const string &mask2, const string &noise, const string &noise2);
	bool init(const string &Laser, const string &mask, const string &mask2, const string &noise, const string &noise2);

	void setBlendFunc(GLenum src, GLenum dst);
	void updateStartAndEnd();
	void setStart(const Point&start);
	void setEnd(const Point&end);

	void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
	void update(float dt);
	void setPorN(float value){ m_PorN = value; }
	void onPassUnifoAndBindTex(const Mat4 &transform, uint32_t flags);

	ens::CGLProgramWithUnifos*m_program;
	Texture2D*m_maskTex;
	Texture2D*m_maskTex2;
	Texture2D*m_noiseTex;
	Texture2D*m_noiseTex2;
	float m_highlight;
	float m_time;
	float m_PorN;
	CCPoint m_start;
	CCPoint m_end;
	float m_kLightColor;
	float m_kGlowColor;
	float m_noiseScale;

	CustomCommand _customCommand;
	CustomCommand _passUnifoAndBindTexCommand;
};



NS_JOFW_END

#endif //__JO_LASER_H__