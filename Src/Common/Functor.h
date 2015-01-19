#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

class Widget;

class Functor_Base
{
	public:
		virtual void operator()(Widget* pWidget) = 0;
};

template<typename Owner>
class Functor : public Functor_Base
{
	public:
		typedef void (Owner::*Function)(Widget*);

	public:
		Functor(Owner* pOwner, Function pFunction)
			: m_pOwner(pOwner)
			, m_pFunction(pFunction)
		{}

		void operator()(Widget* pWidget) { (m_pOwner->*m_pFunction)(pWidget); }

	private:
		Owner* m_pOwner;
		union
		{
			Function m_pFunction;
			char buff[16];
		};
};


#endif //__FUNCTOR_H__
