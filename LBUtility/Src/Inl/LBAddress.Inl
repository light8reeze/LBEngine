namespace LBNet
{
	template <EIPVersion IPType>
	CIPAddress<IPType>::CIPAddress() : __mAddress(), __mIPStr()
	{
		if (IPType == EIPVersion::eIPv4)
			__mIPStr.reserve(static_cast<size_t>(eSzIPv4Str));
		else
			__mIPStr.reserve(static_cast<size_t>(eSzIPv6Str));

		SetIpAddress();
	}

	template <EIPVersion IPType>
	CIPAddress<IPType>::CIPAddress(const char* pIPStr) : CIPAddress()
	{
		if (SetIpAddress(pIPStr) != 0)
		{
			//@todo : 에러처리 추가할것
		}
	}

	template <EIPVersion IPType>
	CIPAddress<IPType>::CIPAddress(const std::string& pIPStr) : CIPAddress()
	{
		if (SetIpAddress(pIPStr) != 0)
		{
			//@todo : 에러처리 추가할것
		}
	}

	template <EIPVersion IPType>
	CIPAddress<IPType>::CIPAddress(const CIPAddress<IPType>& pIPAddr) : CIPAddress()
	{
		(*this) = pIPAddr;
	}

	template <EIPVersion IPType>
	CIPAddress<IPType>::CIPAddress(const CIPAddress<IPType>&& pIPAddr) : CIPAddress()
	{
		(*this) = pIPAddr;
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	bool CIPAddress<IPType>::operator==(const CIPAddress<IPType2>& pRvalue)
	{
		return __mAddress == pRvalue.GetAddress();
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	bool CIPAddress<IPType>::operator!=(const CIPAddress<IPType2>& pRvalue)
	{
		return !(__mAddress == pRvalue.GetAddress());
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	bool CIPAddress<IPType>::operator<(const CIPAddress<IPType2>& pRvalue)
	{
		return __mAddress < pRvalue.GetAddress();
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	bool CIPAddress<IPType>::operator>(const CIPAddress<IPType2>& pRvalue)
	{
		return __mAddress > pRvalue.GetAddress();
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	bool CIPAddress<IPType>::operator<=(const CIPAddress<IPType2>& pRvalue)
	{
		return __mAddress <= pRvalue.GetAddress();
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	bool CIPAddress<IPType>::operator>=(const CIPAddress<IPType2>& pRvalue)
	{
		return __mAddress >= pRvalue.GetAddress();
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	CIPAddress<IPType>& CIPAddress<IPType>::operator=(const CIPAddress<IPType2>& pRvalue)
	{
		CIPAddress<IPType> aConvertedIP = ConvertTo<IPType>(pRvalue);
		SetIpAddress(aConvertedIP.GetAddressStr());

		return (*this);
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	CIPAddress<IPType>& CIPAddress<IPType>::operator=(const CIPAddress<IPType2>&& pRvalue)
	{
		CIPAddress<IPType> aConvertedIP = ConvertTo<IPType>(pRvalue);
		__mAddress	= std::move(aConvertedIP.GetAddress());
		__mIPStr	= std::move(aConvertedIP.GetAddressStr());

		return (*this);
	}

	template <>
	ErrCode CIPAddress<EIPVersion::eIPv4>::SetIpAddress()
	{
		__mAddress = asio::ip::address_v4::any();
		return 0;
	}

	template <>
	ErrCode CIPAddress<EIPVersion::eIPv6>::SetIpAddress()
	{
		__mAddress = asio::ip::address_v6::any();
		return 0;
	}

	template <EIPVersion IPType>
	ErrCode CIPAddress<IPType>::SetIpAddress(const char* pIPStr)
	{
		boost::system::error_code aErrorCode;
		__mAddress.from_string(pIPStr, aErrorCode);
		__mIPStr = pIPStr;

		return aErrorCode.value();
	}

	template <EIPVersion IPType>
	ErrCode CIPAddress<IPType>::SetIpAddress(const std::string& pIPStr)
	{
		LB_ASSERT(pIPStr.size() > __mIPStr.size(), "Invalid Arguments");

		boost::system::error_code aErrorCode;
		__mAddress.from_string(pIPStr, aErrorCode);
		__mIPStr = pIPStr;

		return aErrorCode.value();
	}

	template <EIPVersion IPType>
	const std::string& CIPAddress<IPType>::GetAddressStr() const
	{
		return __mIPStr;
	}

	template <EIPVersion IPType>
	const asio::ip::address& CIPAddress<IPType>::GetAddress() const
	{
		return __mAddress;
	}

	template <>
	CIPAddress<EIPVersion::eIPv4> CIPAddress<EIPVersion::eIPv4>::ToVersion4()
	{
		LB_ASSERT(__mAddress.is_v4() == true, "Invalid Addr!");
		return (*this);
	}

	template <>
	CIPAddress<EIPVersion::eIPv4> CIPAddress<EIPVersion::eIPv6>::ToVersion4()
	{
		LB_ASSERT(__mAddress.is_v4() == true, "Invalid Addr!");
		CIPAddress<EIPVersion::eIPv4> aIP4;
		asio::ip::address aAddress = __mAddress.to_v4();

		if (aIP4.SetIpAddress(aAddress.to_string()) != 0)
		{
			//@todo : 에러처리 추가할것
		}

		return aIP4;
	}

	template <>
	CIPAddress<EIPVersion::eIPv6> CIPAddress<EIPVersion::eIPv4>::ToVersion6()
	{
		LB_ASSERT(__mAddress.is_v6() == true, "Invalid Addr!");
		CIPAddress<EIPVersion::eIPv6> aIP6;
		asio::ip::address aAddress = __mAddress.to_v6();

		if (aIP6.SetIpAddress(aAddress.to_string()) != 0)
		{
			//@todo : 에러처리 추가할것
		}

		return aIP6;
	}

	template <>
	CIPAddress<EIPVersion::eIPv6> CIPAddress<EIPVersion::eIPv6>::ToVersion6()
	{
		LB_ASSERT(__mAddress.is_v6() == true, "Invalid Addr!");

		return (*this);
	}

	template <EIPVersion IPType>
	template <EIPVersion IPType2>
	CIPAddress<IPType2> CIPAddress<IPType>::ConvertTo()
	{
		return (IPType2 == EIPVersion::eIPv4) ? ToVersion4() : ToVersion6();
	}
}