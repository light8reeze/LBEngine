/**
	@file	LBManagedObject.h
	@brief	LBServer의 관리되는 오브젝트 관련 헤더
	@date	2019-09-03
	@auther light8reeze(light8reeze@gmail.com)
*/
#pragma once
#include "LBServer.h"

namespace LBNet
{
	/**
		@brief		메모리 관리되는 오브젝트 클래스
		@details	레퍼런스 카운팅방식을 사용하여 오브젝트를 관리한다.
		@date		2019-09-03
		@auther		light8reeze(light8reeze@gmail.com)
	*/
	class LBS_EXPORT CManagedObject
	{
	public:
		enum class EState
		{
			eUsing,
			eReturnWait,
			eReturned,
		};

	private:
		using __RefCntType	= std::atomic<Size>;
		using __AtomicState	= std::atomic<EState>;

	public:
		template<typename TObject>
		using ManagedPtr = std::unique_ptr<TObject>;

	public:
		CManagedObject();
		virtual ~CManagedObject() = 0;

		bool				OnAccess();
		void				OnAccessEnd();
		ErrCode				SetReturn();
		EState				GetState();
		Size				GetRefCnt();

		template<typename TObject>
		static ManagedPtr<TObject> MakeManaged(TObject& pObject);

	protected:
		virtual ErrCode _OnDelete();

	private:
		__RefCntType	__mRefCnt;
		__AtomicState	__mObjState;
	};
}

#include "LBManagedObject.Inl"