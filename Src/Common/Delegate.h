#ifndef __DELEGATE_H__
#define __DELEGATE_H__

class DelegateInstanceBase
{
	public:
		virtual void Exec() = 0;
};


template<typename TClass>
class DelegateInstance : public DelegateInstanceBase
{
	public:
		typedef  void (TClass::*TFunc)();

	public:
		DelegateInstance(TClass* pObj, TFunc pFunction)
			: m_pObj(pObj)
			, m_pFunction(pFunction)
		{
		}

		virtual void Exec() override
		{
			if (m_pObj && m_pFunction)
				(m_pObj->*m_pFunction)();
		}

	private:
		TClass* m_pObj;
		TFunc m_pFunction;
};

class Delegate
{
	public:
		Delegate()
			: m_pInstance(nullptr)
		{
		}

		~Delegate()
		{
			if (m_pInstance != nullptr)
				delete m_pInstance;
		}

		template<typename TClass>
		void Bind(TClass* pObj, typename DelegateInstance<TClass>::TFunc pFunction)
		{
			m_pInstance = new DelegateInstance<TClass>(pObj, pFunction);
		}

		void Exec()
		{
			if (m_pInstance)
				m_pInstance->Exec();
		}

	private:
		DelegateInstanceBase* m_pInstance;
};

#endif //__DELEGATE_H__
