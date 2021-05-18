클라우드 컴퓨팅 모델

IasS
PaaS
--
AWS 시작할때
1. 컨텐트 전송
2. 스토리지
3. 메시징
--
이렇게 시작했음


1. Global Infra

1). Region (AWS 도시)
2). Availability Zone / AZ(가용 영역)
 -> AZ 가 데이터 센터는 아님(1:1 매핑아님). 가용 영역은 추상적인 데이터 센터 개념
 -> AZ 가 최소 2개 이상이 있어야 Region이 구성됨 ( 적어도 이중화는 해야하기 때문)
    : 현재 서울에는 AZ가 4개임.


3). Edge Location (Availability Zone과 직접적인 연관은 없음)
-> Region은 전 세계에 25개인데, Edge location은 전세계 200여개임(별도의 시설물).
일반적인 이름은 보통 CDN 이라고 부름 ( 빠르게 내려줘야 하는 데이터를 보관/ 응답 속도가 빨라야 하는 경우)
CDN: cloud front
DNS: R53

공격이나 보안 같은 서비스(DDOS 방어 서비스 :shield), WAF

--
2. 비관리형 서비스와 관리형 서비스

비관리형(고객 관리형): customer managed -> on premise 와 비슷함. - (MySQL 같은 것을 설치해서. customer 가 관리하므로)
관리형 : managed (RDS 를 사용)

=> MySQL을 사용해서 데이터를 CRUD 결과는 같음.

--
3. 마이크로 서비스
EC2 			-> ECS				 -> Lambda
(가상 머신) 	(작업/컨데이너)			함수 ( 실행환경만 제공 , 파이썬 런타임, node )


4. AWS 리전 선택하는 기준
1) 데이터 거버넌스 법적 요구 사항 ( 고객 정보를 국외로 보내지 않음)
2) 고객에 대한 접근성(지연시간)
3) 리전내에서 사용 가능한 서비스 ( 특정 서비스가 서울 리전에 없다면? , 가장 가까운 호주, 싱가폴 리젼을 사용 . 특정한
서비스가 전세계에 동시에 배포되지 않음)
4) 비용 ( 리젼별로 다름)
   예) t2.micro EC2를 사용한다고 해도 리젼별로 금액이 다름
   
   
   
* EC2는 엄격히 말해 서버라고 부르지 말고 인스턴스라고 불러야 함.
인스턴스 타입의 종류는 정말 많음


4. ELB (elastic load balancer)
세가지가 있음
1) classic load balancer : 이걸 추천함 (L4, L7 모두 포함)
2) Network lb: osi layer 의 4계층을 담당 (TCP UDP)
3) Application lb : osi layer 의 7 계층을 담당( HTTP/TLS)

 -> 1)은 모두를  포함하고 2), 3)은 필요 목적에 따라 사용 
 
 sticky session : 고정 세션
 auto scaling 이 발생하면 기존에 문제되던 세션에 붙어 있던 사람들은 해결이 안됨
 신규로 유입되는 사람들은 새로 할당된 리소스에 할당됨
 -> 아직 이해를 못하겠음.
 ELB의 로그 밸랜서가 라운드 로빈으로 트래픽을 분배하지 않고 사용자의 쿠키 세션을 기준으로 트래픽을 분배함
고정 세션의 대안 -> 분산 캐시
 
 
 5. EC2 Auto scaling
 1) 수동 조정
 2) 예약된 조정 ( 특정 시점에 조정함. 예를 들어 특정 시간에 사용자가 몰릴것 같으면 스케일링을 시작)
 3) 동적 조정 ( cpu 상태를 보고서 조정함. 그런데 이렇게 되면 서비스가 멈출수도 있고 스케일링 되었을때 
 장애가 끝났을수도있음)
 
 
 6. AWS 사용 방법
 1) AWS Management Console
 2) CLI
 3) SDK
 ==> 무엇을 사용하더라도 API 를 사용 (http request를 하게됨) // 직접 postman 으로 해도 되지만
     위를 사용하면 인증 관련을 추상화한 것임 . 그래서 CLI 나 SDK를 사용하는 것임
	 

	 

 7. 관리도구
 x-ray
 
 cloud watch : AWS 리소스 상태를 모니터링함 -> 예) EC2의 cpu 사용량을 모니터링 함. 
				모니터링의 대상이 리소스임. 
				*두눈을 뜨고 바라보는 것
 cloud trail : 발자국을 따라가서 보는것 처럼. 
               AWS의 API를 모니터링 함:  예) 누가 로그인 하다가 실패했음. 누가 로그인해서 EC2를 실행했다. 이런ㄱ것
			   
8. 서비스 통합
ELB			   
Cloud watch : CPU 상태를 모니터링. 특정 상황이 되면 auto scaling 한테 알려줌. 
EC2 auto scaling 이 LB한테 auto scaling 했으니 새로운 요청은 routing 해라. 라고 알려줌. 
 
 9. IAM
 공동 책임 모델(shared responsibity model)
 - AWS와 사용자 각자 책임을 지게 되어 있음
 
 IAM 
 User: 여러개의 정책을 할당할수 있음
      - IAM user ID/PW
	  - A key, S key  (.aws 폴더 내에 credential 에 들어 있음)
	  ㅁ
	  
 Group:
 Role: role을 switch 해서 권한을 계속 변경할 수 있음. (모자를 쓰는 순간 기존 role을 덮어 쓰게 됨)
 Policy : 권한 부여 . JSON으로 정의 (~ALLOW(permission), ~DENY) - 여러개 permission의 집합
 특별히 allow, deny 가 없으면 deny 이며 allow 와 deny 가 동시에 있으면 역시 deny 됨
 그룹의 정책은 상속받아서 유지가 됨. 새로운 그룹에 속하면 기존 그룹의 정책은 계속 포함됨
 -> role 은 상복 받지 않게 되고 user의 기존 권한을  덮어 씌우게 됨. 
 -> group 과 role의 정책이 다름. 
 -> role은 권한을 임시 권한 할당할 때 씌임 ( AWS의 최소 권한 부여 정책을 따름)
 
 role의 특수성 -> user(alice)가 모자를 쓸 수 있다 라는 가정
 role -> user 
      -> aws resource(ec2/lambda)
      => 사람과 리소스에 모두 할당 가능
	  
	  
 AWS에서는 root 계정을 사용하는 경우가 없음


Amazon 리소스에서 s3는 globally unique 해야 함 (리전정보나 계정 정보를 포함하지 않음)

IAM 사용자 계정은 항상 필요한가?
IAM의 AWS의 방화벽과 같은 역할 ( 모든 API 요청은 IAM의 허락을 받음)

보안자격 증명: 액세스 키
.aws/credentials
해서는 안될일 : root 계정, 코드에 aws자격 증명 삽입 (github 같은데 올리는것), 
해야 할일 : 자격증명 사용,

우선 순위 순서
1) 코드에 지정되어 있음
2)


10. S3
s3의 namespace 은 bucket 임.
bucket의 이름은 globally unique 해야함.
용량 제한은 없음
bucket 내에서 object 의 이름은 unique 해야함.
=> 그 이유는 URL을 따야 하기 때문임.

1) Create (upload) PUT
 a) 5 테라까지
 b) multi-part 업로드 가능
 c) SSE (서버 사이드 인크립션 가능)
     - Azmaon S3 관리형 키
	 - 사용자 관리
	 - 하나 더 있는데 못 적음 
2) Read(download) GET
 a) download
 b) byte-range
 c) sql query (csv, parquet 형식) 
 d) key list만 가지고 올 수 있음
 /image/cat.jpg
 /image/dog.jpg
  -> 디렉토리는
 실제 디렉토리는 아니고 그냥 리소스 이름임. (prefix 의 관점임). 클릭하면 폴더 처럼 보이지만 실제 폴더는 아님
 e) presigend URL : 임시로 접근 가능한 주소 ( object를 업로드하면 url 이  생성되는데, 이 url에 미리 권한이 있는 사람이
    sign을 해놓는 것임. (예를 들어 일정 시간 10초 만 사용 가능한 URL. 대신 누구나 접근할수 있는 URL 이 생성됨)

3) Update (AWS에서는 update 는 존재하지 않음).  // 그냥 덮어 쓰는 것임
4) Delete 
  object를 삭제하는 경우
  versioning 을 활성화 할 수 있음. (대신 비용이 들어감) - 삭제했다고 삭제된게 아님
  한번 삭제하면 정말 삭제됨. (두군데에 복사되어 백업되어 있다고 해도 한번 삭제하면 영구 삭제됨)  
 
11. S3의 Region
버킷 이름은 전역적으로 고유해야 함.
cross-region enable 하지 않는 이상 default 는 특정 region 에만 종속됨


12. S3 ACL
s3의 접근 권한을 관리하는 방법 
1) ACL (account)
2) bucket polity
3) IAM
  => 세가지 방법이 있는데 그중에 제일 좋은 방법은 없음 
4) access point ( 새로 나온 기능. 용도별로 url 을 별도로 생성
5) presigend url : 임시 접근 url - 권한이 없는 사람에게 임시로 권한을 열어주기 때문에 접근 권한을 관리하는 방법임

13. s3 가격
1) 데이터 크기
2) 요청횟수 . get 21 + delete 1 + post + 1 => 전체 더해서 한달 단위로. 보통 1000건에 5원?	
3) Data transfer 비용이 발생 - 전송 비용은 별도 5TB 짜리를 10번 다운로드 받으면 50T 받은 것 같은 비용

리전내 bucket 에서 cloud front로 배포하는 것은 비용 발생하지 않음. 
bucket 에서 다른 리전으로 배포하는 것은 비용 발생
bucket 에서 같으 리전으로 복사시 비용 면제 

14. s3 데이터 무결성 체크
GET/PUT 작업데 대해 MD5 checksum 확인
 
