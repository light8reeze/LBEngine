/**
	@file	LBAddeess.h
	@brief	LBUtility의 IP 주소 관련 헤더(2019-05-11 폐기)
	@date	2019-05-04
	@auther Light8reeze(light8reeze@gmail.com)
*/
#if(0)
#pragma once
#include "LBUtility.h"
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/system_error.hpp>

namespace LBNet
{
	using namespace boost;
	
	/**
		@brief	IP 주소 버전
	*/
	enum class EIPVersion
	{
		eIPv4,
		eIPv6
	};

	/**
		@brief	IP 주소 스트링 글자수
	*/
	constexpr Size eSzIPv4Str = 15 + 1;
	constexpr Size eSzIPv6Str = 39 + 1;
	
	/**
		@brief			CIPAddress 클래스
		@details		네트워크 통신에서 사용되는 IP주소 클래스
		@param IPType	IP버전
		@date			2019-05-04
		@auther			Light8reeze(light8reeze@gmail.com)
		@todo			SetIPAddress관련 에러처리 추가
	*/
	template <EIPVersion IPType = EIPVersion::eIPv4>
	class CIPAddress
	{
	public:
		CIPAddress();
		CIPAddress(const char* pIPStr);
		CIPAddress(const std::string& pIPStr);
		CIPAddress(const CIPAddress<IPType>& pIPAddr);
		CIPAddress(const CIPAddress<IPType>&& pIPAddr);
		~CIPAddress() = default;

		template <EIPVersion IPType2>
		bool operator==(const CIPAddress<IPType2>& pRvalue);
		template <EIPVersion IPType2>
		bool operator!=(const CIPAddress<IPType2>& pRvalue);
		template <EIPVersion IPType2>
		bool operator<(const CIPAddress<IPType2>& pRvalue);
		template <EIPVersion IPType2>
		bool operator>(const CIPAddress<IPType2>& pRvalue);
		template <EIPVersion IPType2>
		bool operator<=(const CIPAddress<IPType2>& pRvalue);
		template <EIPVersion IPType2>
		bool operator>=(const CIPAddress<IPType2>& pRvalue);
		template <EIPVersion IPType2>
		CIPAddress<IPType>& operator=(const CIPAddress<IPType2>& pRvalue);
		template <EIPVersion IPType2>
		CIPAddress<IPType>& operator=(const CIPAddress<IPType2>&& pRvalue);

		ErrCode SetIpAddress();
		ErrCode SetIpAddress(const char* pIPStr);
		ErrCode SetIpAddress(const std::string& pIPStr);

		const std::string&			GetAddressStr() const;
		const asio::ip::address&	GetAddress() const;

		CIPAddress<EIPVersion::eIPv4> ToVersion4();
		CIPAddress<EIPVersion::eIPv6> ToVersion6();

		template <EIPVersion IPType2>
		CIPAddress<IPType2> ConvertTo();

	private:
		asio::ip::address	__mAddress;
		std::string			__mIPStr;
	};

	using CIPAddress4 = CIPAddress<EIPVersion::eIPv4>;
	using CIPAddress6 = CIPAddress<EIPVersion::eIPv6>;
}

template<typename Elem, typename Traits, LBNet::EIPVersion IPType>
	std::basic_ostream< Elem, Traits >& operator<<(
		std::basic_ostream< Elem, Traits > & os,
		const LBNet::CIPAddress<IPType>& addr)
{
	return os.operator<<(addr.GetAddress());
}

#include "LBAddress.Inl"
#endif