#pragma once
#define  Assert( _exp ) ((void)0)
class __declspec(align(16))VectorAligned : public Vector
{
public:
	VectorAligned& operator=(const Vector &vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		w	= 0.f;
		return *this;
	}
	float w;
};
struct Ray_t
{
	VectorAligned  m_Start;    // starting point, centered within the extents
	VectorAligned  m_Delta;    // direction + length of the ray
	VectorAligned  m_StartOffset;    // Add this to m_Start to get the actual ray start
	VectorAligned  m_Extents;    // Describes an axis aligned box extruded along a ray
	//const matrix3x4_t *m_pWorldAxisTransform;
	bool    m_IsRay;    // are the extents zero?
	bool    m_IsSwept;    // is delta != 0?

	void Init(Vector& vecStart, Vector& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;
		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}


private:
};
struct csurface_t
{
    const char *name;
    short surfaceProps;
    unsigned short flags;
};

struct cplane_t
{
    Vector normal;
    float dist;
    byte type;
    byte signbits;
    byte pad[2];
};
struct trace_t
{
	Vector start;
	Vector end;
	cplane_t plane;
	float fraction;
	int contents;
	WORD dispFlags;
	bool allsolid;
	bool startSolid;
	float fractionLeftSolid;
	csurface_t surface;
	int hitGroup;
	short physicsBone;
	CBaseEntity* m_pEnt;
	int hitbox;
};
enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};
class ITraceFilter
{
public:
	virtual bool			ShouldHitEntity(void* pEntity, int mask) = 0;
	virtual TraceType_t            GetTraceType() const = 0;
};


class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip1);
	}

	TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip1;
};

class CTrace
{
public:
	void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter* filter, trace_t *trace)
	{
		typedef void(__thiscall* fn)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		VMT.getvfunc<fn>(this, 5)(this, ray, fMask, filter, trace);
	}
};
