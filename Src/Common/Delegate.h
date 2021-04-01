#ifndef __DELEGATE_H__
#define __DELEGATE_H__

#include <list>

template<typename TRet, typename... Args>
class DelegateInstanceBase
{
	public:
		virtual TRet Execute(Args...) = 0;

		virtual bool IsBoundTo(void* pObj) const { return false; }
};

template<typename TClass, typename TRet, typename... Args>
class MemberFunctionDelegateInstance : public DelegateInstanceBase<TRet, Args...>
{
	public:
		typedef  TRet (TClass::*TMemberFunction)(Args...);

	public:
		MemberFunctionDelegateInstance(TClass* pObj, TMemberFunction pFunction)
			: m_pObj(pObj)
			, m_pFunction(pFunction)
		{
		}

		virtual TRet Execute(Args... args) override
		{
			if (m_pObj && m_pFunction)
				return (m_pObj->*m_pFunction)(args...);

			return TRet();
		}

		virtual bool IsBoundTo(void* pObj) const override { return pObj == m_pObj; }

		TClass* GetObj() const { return m_pObj; }
		TMemberFunction GetFunction() const { return m_pFunction; }

	private:
		TClass* m_pObj;
		TMemberFunction m_pFunction;
};

template<typename TFunctor, typename TRet, typename... Args>
class FunctorDelegateInstance : public DelegateInstanceBase<TRet, Args...>
{
	public:
		FunctorDelegateInstance(TFunctor oFunctor)
			: m_oFunctor(oFunctor)
		{
		}

		virtual TRet Execute(Args... args) override
		{
			return m_oFunctor(args...);
		}

	private:
		TFunctor m_oFunctor;
};

template<typename TRet, typename... Args>
class RawFunctionDelegateInstance : public DelegateInstanceBase<TRet, Args...>
{
	public:
		typedef TRet (*FunctionPtr)(Args...);

	public:
		RawFunctionDelegateInstance(FunctionPtr pFunctionPtr)
			: m_pFunctionPtr(pFunctionPtr)
		{
		}

		virtual TRet Execute(Args... args) override
		{
			if (m_pFunctionPtr != nullptr)
				return m_pFunctionPtr(args...);

			return TRet();
		}

	private:
		FunctionPtr m_pFunctionPtr;
};

template<typename TRet = void, typename... Args>
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
		void BindMember(TClass* pObj, typename MemberFunctionDelegateInstance<TClass, TRet, Args...>::TMemberFunction pFunction)
		{
			if (m_pInstance != nullptr)
				delete m_pInstance;

			m_pInstance = new MemberFunctionDelegateInstance<TClass, TRet, Args...>(pObj, pFunction);
		}

		void BindRaw(typename RawFunctionDelegateInstance<TRet, Args...>::FunctionPtr pFunction)
		{
			if (m_pInstance != nullptr)
				delete m_pInstance;

			m_pInstance = new RawFunctionDelegateInstance<TRet, Args...>(pFunction);
		}

		template<typename TFunctor>
		void BindLambda(TFunctor pFunction)
		{
			if (m_pInstance != nullptr)
				delete m_pInstance;

			m_pInstance = new FunctorDelegateInstance<TFunctor, TRet, Args...>(pFunction);
		}

		void Unbind()
		{
			if (m_pInstance != nullptr)
			{
				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}

		TRet Execute(Args... args)
		{
			if (m_pInstance != nullptr)
				return m_pInstance->Execute(args...);

			return TRet();
		}

	private:
		DelegateInstanceBase<TRet, Args...>* m_pInstance;
};

template<typename... Args>
class MulticastDelegate
{

public:
	MulticastDelegate()
	{
	}

	~MulticastDelegate()
	{
		for (DelegateInstanceBase<void, Args...>* pInstance : m_aInstances)
			if (pInstance != nullptr)
				delete pInstance;
	}

	template<typename TClass>
	void AddMember(TClass* pObj, typename MemberFunctionDelegateInstance<TClass, void, Args...>::TMemberFunction pFunction)
	{
		DelegateInstanceBase<void, Args...>* pInstance = new MemberFunctionDelegateInstance<TClass, void, Args...>(pObj, pFunction);
		m_aInstances.push_back(pInstance);
	}

	template<typename TClass>
	void AddMemberUnique(TClass* pObj, typename MemberFunctionDelegateInstance<TClass, void, Args...>::TMemberFunction pFunction)
	{
		for (DelegateInstanceBase<void, Args...>*& pInstance : m_aInstances)
		{
			if (pInstance == nullptr)
				continue;

			if (!pInstance->IsBoundTo(pObj))
				continue;

			MemberFunctionDelegateInstance<TClass, void, Args...>* pMemberInstance = static_cast<MemberFunctionDelegateInstance<TClass, void, Args...>*>(pInstance);
			if (pMemberInstance != nullptr && pMemberInstance->GetObj() == pObj && pMemberInstance->GetFunction() == pFunction)
			{
				return;
			}
		}

		DelegateInstanceBase<void, Args...>* pInstance = new MemberFunctionDelegateInstance<TClass, void, Args...>(pObj, pFunction);
		m_aInstances.push_back(pInstance);
	}

	template<typename TClass>
	void RemoveMember(TClass* pObj, typename MemberFunctionDelegateInstance<TClass, void, Args...>::TMemberFunction pFunction)
	{
		if (pObj == nullptr || pFunction == nullptr)
			return;

		for (DelegateInstanceBase<void, Args...>*& pInstance : m_aInstances)
		{
			if (pInstance == nullptr)
				continue;

			if (pInstance->IsBoundTo(pObj))
			{
				MemberFunctionDelegateInstance<TClass, void, Args...>* pMemberInstance = static_cast<MemberFunctionDelegateInstance<TClass, void, Args...>*>(pInstance);
				if (pMemberInstance->GetFunction() == pFunction)
				{
					delete pMemberInstance;
					pInstance = nullptr;
				}
			}
		}

		m_aInstances.remove_if([pObj](DelegateInstanceBase<void, Args...>*& Entry) { return Entry == nullptr; });
	}

	template<typename TClass>
	void RemoveMemberAll(TClass* pObj)
	{
		if (pObj == nullptr)
			return;

		for (DelegateInstanceBase<void, Args...>*& pInstance : m_aInstances)
		{
			if (pInstance != nullptr && pInstance->IsBoundTo(pObj))
			{
				delete pInstance;
				pInstance = nullptr;
			}
		}

		m_aInstances.remove_if([pObj](DelegateInstanceBase<void, Args...>*& Entry) { return Entry == nullptr; });
	}

	void AddRaw(typename RawFunctionDelegateInstance<void, Args...>::FunctionPtr pFunction)
	{
		DelegateInstanceBase<void, Args...>* pInstance = new RawFunctionDelegateInstance<void, Args...>(pFunction);
		m_aInstances.push_back(pInstance);
	}

	template<typename TFunctor>
	void AddLambda(TFunctor pFunction)
	{
		DelegateInstanceBase<void, Args...>* pInstance = new FunctorDelegateInstance<TFunctor, void, Args...>(pFunction);
		m_aInstances.push_back(pInstance);
	}

	void Clear()
	{
		for (DelegateInstanceBase<void, Args...>* pInstance : m_aInstances)
			if (pInstance != nullptr)
				delete pInstance;

		m_aInstances.clear();
	}

	void Broadcast(Args... args)
	{
		for (DelegateInstanceBase<void, Args...>* pInstance : m_aInstances)
			if (pInstance != nullptr)
				pInstance->Execute(args...);
	}

private:
	std::list<DelegateInstanceBase<void, Args...>*> m_aInstances;
};

#endif //__DELEGATE_H__
