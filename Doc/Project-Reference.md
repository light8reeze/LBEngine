LBEngine Project Reference
================================

1.etc
-------------------------

-네트워크는 boost::asio 라이브러리를 기반으로 작성한다.(버전 1.70)  
-윈도우를 타겟으로 만들지만 추후에 리눅스 포팅을 대비하여 플랫폼 독립적인 코드를 작성한다.  

2.CPP
-------------------------

-템플릿 인자는 T를 붙이고, 일반 타입은 자유롭게 사용, 클래스 타입은 C를 사용한다.  
-클래스의 public는 m을 붙이고, protected는 _m, private는 __m을 붙인다.  
-enum은 E를 붙이고 내부 값은 e를 붙인다  
-지역변수는 a를 붙여 사용한다.  
-템플릿 이외에는 inline는 이용하지 않는다. 컴파일러의 최적화를 이용한다.  
(단 디버그모드에선 최적화를 사용하지 않는다.)  
-std::shared_ptr은 소유권 개념으로 사용한다. 같은 쓰레드 내에서는 복사를 하지 않는다.(이동, 레퍼런스로 전달)  
-DLL 라이브러리 사용시 static변수 사용에 유의한다.(상위, 하위 레이어 사이에서 한쪽에서만 생성하고 한쪽을 포인터, 레퍼런스로 사용한다.)  

Reference
-------------------------

L1: [C++11 하이퍼 쓰레딩](https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading)  
L2: [프로세서 스케쥴링 이론](http://colomy.tistory.com/120)  
L3: [윈도우10 쓰레드 분배](http://www.hwbattle.com/bbs/board.php?bo_table=news&wr_id=70307)  
L4: [doxygen 매뉴얼](https://rinovation.tistory.com/77)  
L5: [SRWLock 구현](https://megayuchi.com/2017/06/25/srwlock-%EB%B9%A0%EB%A5%B8-%EC%84%B1%EB%8A%A5%EC%9D%98-%EB%B9%84%EA%B2%B0)  
L6: [std::allocator<void> is deprecated in C++17](https://github.com/boostorg/beast/issues/1272)  
L7: [Warning C4251](https://mgun.tistory.com/508)  
L8: [[boost.asio] strand는 어떻게 동작하고 왜 사용해야 하는가?](http://blog.naver.com/PostView.nhn?blogId=njh0602&logNo=220715956896&parentCategoryNo=&categoryNo=&viewDate=&isShowPopularPosts=false&from=postView)  