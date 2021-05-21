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

비관리형(고객 관리형): customer managed -> on premise 와 비슷함. - (MySQL 같은 것을 설치해서. customer 가 세심하게 관리하므로)
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
	  
 Group: role을 할당할 수 없는 대상임.
 Role: role을 switch 해서 권한을 계속 변경할 수 있음. (모자를 쓰는 순간 기존 role을 덮어 쓰게 됨)
 Policy : 권한 부여 . JSON으로 정의 (~ALLOW(permission), ~DENY) - 여러개 permission의 집합
 특별히 allow, deny 가 없으면 deny 이며 allow 와 deny 가 동시에 있으면 역시 deny 됨
 그룹의 정책은 상속받아서 유지가 됨. 새로운 그룹에 속하면 기존 그룹의 정책은 계속 포함됨
 -> role 은 상속 받지 않게 되고 user의 기존 권한을  덮어 씌우게 됨. 
 -> group 과 role의 정책이 다름. 
 -> role은 권한을 임시 권한 할당할 때 씌임 ( AWS의 최소 권한 부여 정책을 따름)
 
 role의 특수성 -> user(alice)가 모자를 쓸 수 있다 라는 가정 (임시로 권한을 부여하는 역할)
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
2) 환경 변수에 지정
3) .aws 내에
[ec2-user@ip-10-0-10-220 .aws]$ cat config
[default]
region = ap-northeast-2
[ec2-user@ip-10-0-10-220 .aws]$ cat credentials
[default]
aws_access_key_id=AKIA4EXBI6KYSOUVO36S
aws_secret_access_key=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
[ec2-user@ip-10-0-10-220 .aws]$
4) ec2 설정에서


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
 
 
 --
 2일차
 
1. 다이나모 DB (DDB)
 NoSQL 인데 몽고DB와도 좀 다름
 다이나모 DB의 가장 큰 단위는 테이블임.
 파티션 키(필수) 가 가장 중요함. -> hash key 임
        정렬 키(sort key, 선택 사항)
		    속성(attribute)
			    항목(item)

 * primaray key는 SQL에서 중복이 안됨
 
 파티션 키는 중복이 있을 수 있음. (파티션 키 + 정렬 키) 를 조합해서 해시를 만듬
 
 
 CAP 이론 : consistency(일관성), availablity(가용성), Parting tolerence
            분산 환경에서 고려해야 하는 것이 있는데 CAP 인데, 그중에 하나는 포기 해야함.
			CA, CP, AP . 이렇게 하나는 포기해야 함.
			CP: 항상 최신값을 응답 해야함 그렇지 못하면 에러를 발생하면
			AP: 옛날값 응답이라도 응답. (어쨌든 읽어야햠)
			
			
글로벌 테이블 : 한 리전의 다이나모 DB와 다른 리전의 다이나모 DB가 싱크를 이루고 있음
(스트림은 24시간 보관)

읽기 일관성 수준 (아래 두가지 지원)
: 최종 일관성
  강력한 일관성

읽기 용량 단위: RCU 4K

쓰기 용량 단위: WCU 1K

DDB : serverless ( 서버리스가 람다는 아님, 서버리서는 관리, 설정 같은 작업을 사용자가 하지 않는다는 접근으로 봐야함)

1) RCU / WCU : 기준 성능
강력  1 RCU (4K당 1RCU)
최종 : 0.5 RCU (예를 들어 7K 읽어야 하면 4K + 3K : 전체 1 RCU 사용)

default 방식은 기본인 provisioned 방식임. ( 기본 설정한 요청 보다 더 요청이 들어오면 에러 발생함) . 계속 에러 발생하면 onDemand 방식으로 변경을 고려해야함.

LSI (local)             | GSI (global)
------------------------------------------------
동일한 P key 			|	다른 P key
테이블 성능 도일한 성능 | 할당된	테이블 성능 할당을 다르게
테이블 생성시에만 생성 가능 | 생성 후 인텍싱 가능한



1. 서버리스 
2. seondary index 제공 가능
3. 글로벌 테이블 제공
    3-1: 다이나모 DB stream 이란 기능이 있어야 글로벌 테이블 제공
	
	
글로벌 테이블이란
: 리전과 다름 없이 한 리전에 업에이트한 결과가 다른 리전에 싱크를 맞춤.
: 이 기능을 활성화 하기 위해서 다이나모 DB 스트림 기능을 사용함.  ( 24 시간)

API는 제어 작업과 데이터 작업(CRUD) 가 서로 분리되어 있음

항목 업데이트할 때는 UpdateItem 과 PutItem과 구분을 해야 함. Update는 변경한 것만 저장되도 PutItem은 변경한 것 외에는 삭제함.

배치 아이템 : 중간에 에러나도 끝까지는 진행함. 다만 에러 는 발생하고 에러 발생한 아이템을 리턴함.
트랜잭선 아이템: 중간에 에러나면 중간에 끝남.






서버리스 컴퓨팅

람다는 실행 환경임. invoke 기능이 없으면 람다는 동작하지 않음 ( standalone 이 없음. 즉 누군가 불러주지 않으면 동작하지 않는다)
람다도 DDB와 마찬가지로 성능을 지정해 줘야 함
( 성능은 아래와 관련 있는데, memory 만 결정하면 cpu와 network t-put 은 알아서 결정됨. 최소 128MB -> 10G 까지 설정 가능함)
cpu, memory, network t-put

저장공간: 영구적인 저장공간이 없음 /tmp 에 저장되는게 보통 512MB ( 상태를 저장하지 않음 stateless)
           람다의 로그는 cloudwatch의 logs 에 저장됨 ( 보통 cloudtrail 에 저장되지만, 서버리스라서 이렇게 됨)

handler(event, context)
-> main 함수의 시작
   event : 로직을 처리, 호출/이벤트 관련 data. 
   context 가 없이도 로직을 구현할 수 있음 - 람다의 실행 context(id/timeout)
   
   람다의 가장 큰  네임스페이스는 function 임. 
   


		   
람다의 실행 모델
동기식				| 		비동기식			| 스트림 기반
API Gateway			|	SNS, S3					| DynamoDB, Kinesis

람다의 실행시간에는 제약이 발생 (최대 15분). 그렇지 않으면 계속 비용 발생
cron 처럼 정기적으로 부르게 되는게 AWS Gateway 로 invoke 하는 경우임.




API Gateway

1) 추상화된 API 서버 : 모든 로직을 가지고 있지 않음 , 실제 서버가 존재하지 않음. 
2) 외부 노출 포인트 ( 그래서 보안 요구 사항 필요, DDOS 예방 및 엣지 로케이션)
=> API 프론트 엔드 설정
3) API Gateway 는 람다와 통합하지 않아도 사용 사능 
   -> API Gateway는 ec2 api,on-premise 의 api 호출 가능, 


Amazon CloudFront <-> Amazon Gateway <-> AWS Lambda <-> Amazon DynamoDB
					|-> API Gate응답 캐시
					
API Gateway 에 동일한 요청이 자주 들어오면 API Gateway 응답 캐시에 저장해 둬서 굳이 DB 조회까지 않도록 함.



AWS Step Functions 로 솔루션 개발
람다의 함수가 많아지고 복잡해 지면서 함수 간 호출되는 관계를 지정함
ASL -> Amazon States Language 라고 부름


--
vpc 10.0.0.0/16
으로 접근하기 위해서 NACL을 통과해야 함. ( 보통은 열려 있음)
ec2에 접근할 때 접근 통제를 할때 security group 임. 





---

동기식 프로세스

Amazon simple queue service 
1) 표준 대기열 ( 최대한 FIFO 로 동작하지만 순서 보장 안됨.
                 한번 들어왔는데 여러번 처리될 수 있음
				 하지만 최대 처리량(무한에 가까움) 제공
				 FIFO를 조금 포기하더라도 성능이 좋은 Queue
				 )
2) FIFO 대기열

SQS의 가장 큰 namespace 는 queue 임. 

message를 put 함 
1) queue 정보(내가 누가한테 보내는지 URL)
2) message 내용 ( 전체 메시지의 크기가 256KB 이하여야 함)


message get 할때
(consumer 가 long polling, short polling 하면서 메시지를 가져가야 함)
1) queue 정보(URL)
2) 메시지 수신 Max
3) 대기 시간 1초 ( queue에 메시지를 기다리는 시간이며, 1초를 기다렸다가 queue에 담긴 메시지만 가져옴)
4) visiability timeout ( 가시성 제한 시간) 
-> 메시지를 가져가고 나면 메시지가 삭제 되는 것이 아님 (삭제는 아니고 안보이게 하는 것임)
-> 다만 가시성 시간 제한 만큼은 메시지가 보이지 않도록 함.
   ( 만약 메시지를 가져가도 정상 처리 못하면 다시 시도해야 하기 때문에 )
-> 메시지를 가져와서 잘 처리했으면 "DEL" 요청을 해서 메시지를 Queue에서 삭제할 수 있도록 요청함.
   다만 삭제할 때는 message id 기준으로 삭제하면 안되고, 수신 핸들(receipt handle) 을 기준으로 삭제해야 함
   
Dead-letter queues : 내가 처리 못한 메시지를 넣는 queue 

특징:
1) auto scaling trigger 가능 ( queue에 처리 못한 메시지가 많이 쌓여 있다고 하면)
2) fanout/filter 미지원 ( 대신 SNS에서 지원)



SNS
---


A 라는 메시지(topic)가 있으면 이것을 모든 등록자에게 전달 가능 : Fanout 이라는 기능
SQS 와 다르게 polling 방식은 없고 push 방식만 가능. Fanout 할때 filter 기능을 제공





screct manager 			|   system manager (parameter store)
--------------------------------------------------------
비밀 번호 저장			|	키 (value) 
암호화					| 	default 는 평문 저장, 옵션으로 암호화 가능함
정기적 교체				| 	cloud formation, aws 에서 system magager를 호출함.
						|   -> 이 과정에서 versioning 을 처리함



STS
(security token service)
STS 와 IAM이 같은 것은 아니지만, IAM이 STS를 사용하는 것임
1) SAML
2) OpenD connect
3) Cognito -> 무엇을 할수있는지 나타냄 ( 약간 end-user 에게 제공한다는 느낌)


aws cognito-idp sign-up --client-id 62g4n1qlbnqdqu0l83i5liruo0 --username student --password student


Pool Id ap-northeast-2_cT3TWe9WO
Pool ARN arn:aws:cognito-idp:ap-northeast-2:833726965819:userpool/ap-northeast-2_cT3TWe9WO
62g4n1qlbnqdqu0l83i5liruo0


aws cognito-idp sign-up --client-id 62g4n1qlbnqdqu0l83i5liruo0 --username student --password student

aws cognito-idp admin-confirm-sign-up --user-pool-id ap-northeast-2_cT3TWe9WO --username student

invoke url : https://2h06xhsnya.execute-api.ap-northeast-2.amazonaws.com/prod



