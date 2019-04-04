LBEngine Project Convention
================================

1.etc
-------------------------

-윈도우를 타겟으로 만들지만 추후에 리눅스 포팅을 대비하여 플랫폼 독립적인 코드를 작성한다.

2.CPP
-------------------------

-템플릿 인자는 T를 붙이고, 일반 타입은 자유롭게 사용, 클래스 타입은 C를 사용한다.
-enum은 E를 붙이고 내부 값은 e를 붙인다
-템플릿 이외에는 inline는 이용하지 않는다. 컴파일러의 최적화를 이용한다.
(단 디버그모드에선 최적화를 사용하지 않는다.)

참고자료
-------------------------

L1: [C++11 하이퍼 쓰레딩](https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/)
L2: [프로세서 스케쥴링 이론](http://colomy.tistory.com/120)
L3: [윈도우10 쓰레드 분배](http://www.hwbattle.com/bbs/board.php?bo_table=news&wr_id=70307)
L4: [doxygen 매뉴얼](https://rinovation.tistory.com/77)
L5: [SRWLock 구현](https://megayuchi.com/2017/06/25/srwlock-%EB%B9%A0%EB%A5%B8-%EC%84%B1%EB%8A%A5%EC%9D%98-%EB%B9%84%EA%B2%B0/)
