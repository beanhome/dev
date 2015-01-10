#ifndef __GENGINE_H__
#define __GENGINE_H__

#include "Utils.h"
#include "CanvasBase.h"
#include "ImageResource.h"
#include "FontResource.h"

class Resource;
class Canvas;
class EventManager;
class Event;
class GAppBase;

typedef map<uint32, Resource*> ResourceMap;
typedef pair<uint32, Resource*> ResourcePair;

class Event;

class GEngine : public CanvasBase
{
	public:
		GEngine(uint16 width, uint16 height, uint16 depth, const char* rootpath);
		GEngine(GAppBase* pApp, uint16 width, uint16 height, uint16 depth, const char* rootpath);
		virtual ~GEngine();

		GEngine*						GetGEngine() { return this; }
		const GEngine*					GetGEngine() const { return this; }

		virtual void					Clear() = 0;
		virtual void					Flip() = 0;

		virtual void					PurgeResource();

		const EventManager*				GetEventManager() const { return m_pEventManager; }
		void							UpdateEvent();

		virtual void					Resize(uint16 w, uint16 h) = 0;

		virtual bool					PollEvent(Event* pEvent) = 0;
		virtual const Event&			WaitEvent(Event* pEvent) = 0;

		virtual sint32					GetMouseX() const;
		virtual sint32					GetMouseY() const;

		const char*						GetRootPath() const { return m_sRootPath; }

		template<typename T>
		T* const						GetResource(const typename T::Desc& oDesc) const;

		virtual ImageResource* const	GetImageResource(const ImageResource::Desc& oDesc) const = 0;
		virtual FontResource* const		GetFontResource(const FontResource::Desc& oDesc) const = 0;

		bool							AddResource(uint32 crc, Resource* pRes);
		bool							RemResource(uint32 crc);
		bool							RemResource(Resource* pRes);

		virtual void					ClampClear() const = 0;
		virtual void					ClampRect(sint32 x, sint32 y, uint16 w, uint16 h) const = 0;
		virtual void					ClampRect(const ClampingRect& rect) const { ClampRect(rect.x, rect.y, rect.w, rect.h); }
		void							ClampCanvas(const Canvas& canvas) const;
		virtual ClampingRect			GetClampingRect() const { return ClampingRect(0, 0, GetWidth(), GetHeight()); }

		virtual Event*					CreateEvent() const = 0;
		void							ReceiveEvent(Event* pEvent);

	protected:
		template<typename T>
		T*								CreateResource(uint32 crc, const typename T::Desc& oDesc);

		template<typename T>
		uint32							ComputeResourceCRC32(const typename T::Desc& oDesc);

	protected:
		uint16							m_iDepth;
		const char*						m_sRootPath;

	private:
		GAppBase*						m_pApp;

		ResourceMap						m_aResources;
		EventManager*					m_pEventManager;
};

template<typename T>
T* const GEngine::GetResource(const typename T::Desc& oDesc) const
{
	uint32 crc = T::ComputeCRC32(oDesc);

	ResourceMap::const_iterator iter = m_aResources.find(crc);

	return (iter == m_aResources.end() ? ((GEngine*)this)->CreateResource<T>(crc, oDesc) : (T*)iter->second);
}

template<typename T>
T* GEngine::CreateResource(uint32 crc, const typename T::Desc& oDesc)
{
	return new T(this, crc, oDesc);
}

template<typename T>
uint32 GEngine::ComputeResourceCRC32(const typename T::Desc& oDesc)
{
	return T::ComputeCRC32(oDesc);
}


#endif // __GENGINE_H__

