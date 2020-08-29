# LBEngine

LBEngine는  C++ Boost.Asio 소켓을 이용하여 개발한 게임 서버 엔진입니다. C++17을 이용했고, 비동기 멀티쓰레드 구조로 작동합니다. 현재는 Windows만 지원합니다. 

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/480aabb761ba4735a2763dd6dc816467)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=light8reeze/LBEngine&amp;utm_campaign=Badge_Grade)

## Feature

게임서버 개발에 쉽게 사용이 가능합니다.
비동기 방식의 IO
멀티쓰레드 지원

## Environment

Support Windows OS Only
Visual Studio 2017 or later
boost Lib 1.70

## How To Use

### GameObject

 `CGameObject`는 서버 접속하는 유저에게 할당되는 기본 오브젝트입니다. 사용자는 해당 클래스를 상속받아서 클래스를 구현하여 게임에 필요한 정보를 저장하고 플레이어 로직을 구현합니다.



### Config

 `CConfig`클래스는 서버 구동에 필요한 정보를 저장하는 클래스입니다. 사용자는 서버 설정을 `CConfig`클래스에서 설정합니다. 또한 Application에서 추가로 설정 정보가 필요한 경우 `CConfig`클래스를 상속받아 확장합니다.



### GameServer

 `CGameServer`는 게임서버의 메인 로직 클래스입니다. 템플릿 인자는 사용자가 구현한 `CGameObject`클래스를 넣습니다. 사용자는 Game Server Application 구현시 해당 클래스를 상속받아서 구현합니다. 사용자가 구현 가능한 함수는 3개가 있습니다.

- `Initialize()` : `Initialize()`함수는 서버의 초기화를 담당하는 함수입니다. 사용자는 해당 함수 구현시 `__super::Initialize()` 함수를 먼저 호출 후 Application에 필요한 초기화 로직을 작성합니다.
- `LazyInitialize()` : `LazyInitialize()` 함수는 초기화 단계 이후 서버 실행 전 마지막으로 필요한 정보를 초기화 하는 함수입니다. 사용자는 해당 함수 구현시 `__super::Initialize()` 함수를 먼저 호출 후 Application에 필요한 마지막 초기화 로직을 작성합니다.
- `Close()` : `Close()` 함수는 서버가 종료되기전에 자원 해제 등의 정리를 담당하는 함수입니다. 사용자는 해당 함수 구현시 Application에 필요한 정리 로직을 작성 후 `__super::Close()` 함수를 호출합니다.

  `CGameServer`클래스 구현 후 사용자는 `main` 함수에서 해당 클래스를 생성하고 `SetConfig`,  `Initialize`,  `LazyInitialize`,  `Run`,  `Close` 함수를 순서대로 호출합니다.



### Packet Handler

 패킷 처리 이벤트 등록은 `CTcpHandler`클래스를 통해 등록합니다. 패킷 처리 함수는  `std::function<ErrCode(CPacketHeader*, Size, SharedObject<CGameObject>&)>` 형식으로 사용합니다. 위와 같은 형식으로 함수, 람다를 구현하고 `CTcpHandler::Register`함수를 사용하여 패킷 번호와 함께 추가합니다. 패킷 형식은 `	CPacketHeader`클래스를 상속받은 형식으로 사용합니다.



### Example

 기본 사용 예제는 [Test Server](TestServer/)프로젝트를 참고하시기 바랍니다.



## Document

[Project Reference](Doc/Project-Reference.md)
[Project Todo List](Doc/Project-Todo.md)



## License

Copyright © 2019-2020 [light8reeze](http://www.github.com/light8reeze).

