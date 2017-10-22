

#ifndef __JOASTAR_H__
#define __JOASTAR_H__

#include <deque>
#include <vector>
#include <cstdint>
#include <functional>

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "utils/JOBlockAllocator.h"
#include "datastruct/JOPoint.h"

NS_JOFW_BEGIN
/**
 * A-Star algorithm
 */
class JO_DLL JOAStar
{
public:
	struct Vec2
	{
		uint16_t x;
		uint16_t y;

		Vec2()
			: x(0)
			, y(0)
		{
		}

		Vec2(uint16_t _x, uint16_t _y)
			: x(_x)
			, y(_y)
		{
		}

		void set(uint16_t x, uint16_t y)
		{
			this->x = x;
			this->y = y;
		}

		bool operator== (const Vec2 &that) const
		{
			return x == that.x && y == that.y;
		}
	};

	typedef std::function<bool(const Vec2&)> QueryFunction;
	typedef std::function<int(const Vec2&)> GValFunction;
	typedef std::function<std::deque<JOPoint>()> ResultFunction;
	
private:
	/**
	 * 节点对象分配器
	 */
	class SamllObjectAllocator : public JOBlockAllocator, public JOSingleton< SamllObjectAllocator >
	{
		SamllObjectAllocator() = default;
		~SamllObjectAllocator() = default;
		friend class JOSingleton< SamllObjectAllocator >;
	};

	/**
	 * 路径节点状态
	 */
	enum NodeState
	{
		NOTEXIST,
		IN_OPENLIST,
		IN_CLOSELIST
	};

	/**
	 * 路径节点
	 */
	struct Node
	{
		uint16_t		g;
		uint16_t		h;
		Vec2			pos;
		NodeState		state;
		Node*			parent;		
		int f() const
		{
			return g + h;
		}

		inline Node(const Vec2 &pos)
			: g(0)
			, h(0)
			, pos(pos)
			, parent(nullptr)
			, state(NOTEXIST)
		{
		}

		void* operator new(std::size_t size)
		{
			return SamllObjectAllocator::Instance()->Allocate((int)size);
		}

		void operator delete(void* p) throw()
		{
			SamllObjectAllocator::Instance()->Free(p, sizeof(Node));
		}
	};

public:
	JOAStar();
	~JOAStar();
public:
    inline void setSize(uint16_t w, uint16_t h){
        width_ = w;
        height_ = h;
    }
    inline uint16_t getWidth(){ return width_; }
    inline uint16_t getHeight(){ return height_; }
    
    inline void setCanReachCall(const QueryFunction &_is_canreach){query_=_is_canreach;}
    inline void setGValCall(const GValFunction &_gValCall){gValQuery_=_gValCall;}
    inline void setAllowCorner(bool bAllow){bAllowCorner=bAllow;}
    inline bool isAllowCorner(){ return bAllowCorner; }
    
    void setResultCall(ResultFunction &resultCall);
    void setLuaResultCall(int luaHandle);
    
public:
	/*
	直走和斜走的消耗
	*/
	int stepValue() const;
	int obliqueValue() const;
	void setStepValue(int value);
	void setObliqueValue(int value);
    
	std::deque<JOPoint> search(const JOPoint &start_pos, const JOPoint &end_pos);

private:
	void clear();

private:
	void percolateUp(size_t hole);

	bool getNodeIndex(Node *node, size_t &index);

	uint16_t calculGValue(Node *parent_node, const Vec2 &current_pos);
	uint16_t calculHValue(const Vec2 &current_pos, const Vec2 &end_pos);

	bool hasNoodeInOpenList(const Vec2 &pos, Node *&out);
	bool hasNodeInCloseList(const Vec2 &pos);

	bool canreach(const Vec2 &pos);
	bool canreach(const Vec2 &current_pos, const Vec2 &target_pos);

	void findCanreachPos(const Vec2 &current_pos, std::vector<Vec2> &canreach_pos);

	void handleFoundNode(Node *current_node, Node *target_node);
	void handleNotFoundNode(Node *current_node, Node *target_node, const Vec2 &end_pos);

private:
	int						step_value_;
	int						oblique_value_;
    bool                    bAllowCorner;
	std::vector<Node *>		maps_;
	uint16_t				height_;
	uint16_t				width_;
	QueryFunction			query_;
    GValFunction			gValQuery_;
	std::vector<Node *>		open_list_;
};

NS_JOFW_END

#endif //__JOASTAR_H__
