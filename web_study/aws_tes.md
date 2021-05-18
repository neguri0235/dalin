
ap-northeast-2 : 리전
가용 영역이 어디 있는지 알 수 없음

230개가 넘는 edge location에서 아래 서비스를 담당

Amazon Route 53 : DNS 서비스 임
Amazon CouldFront -> cache 기능 ( 지역에 가까운 곳에서 서비스 캐싱해놓음)
AWS WAF: 웹 방화벽 ( web app firewall)
AWS Shield : DDoS 방지


데이터 센서 그룹 : 가용 영역 (영문 ?)

각 가용 영역은 기본적으로 서로 격리되어 있지만, 한 리전의 가용 영역간에
지연 시간이 짧은 링크를 통해 연결되어 있음

----


Amazon EC2

가상 머신임
컴퓨팅 요구 사항의 변화에 따라 컴퓨팅 파워를 조정
실제로 사용한 용량 만큼만 지불
안정성 위해서 AWS 리전과 가용 영역에 걸처 배포
태그를 사용하여 Amazon EC2 리소스를 관리


--

아래 순서새로 인스턴스가 생성됨

AMI (amazon machine image, 붕어빵 틀임)
(Linux, Windows, 64/32 bit, x86/Arm)

-> Instance Type (t3a.large)을 고름
F : family
G : generation
I :
S : Size

-> Configure Instance ( 인스턴스 구성)

-> Add Storage (EBS - elastic block storeage/Instance Store)

-> Add Tags

-> configure security group (firewall)

-> key pair (public key, private key)

-> instance 생성됨


== > configure (web or was)

-> create Image (이미지 생성)

-> MyAMI (하나의 이미지로 만듬. 하나 만들지만 계속 수정하면서 인스턴스 만들고 이미지 만들고함)

이런 과정을 Market place에서 만들어진 것을 구입해도 됨 ( 이미 만들어진 AMI 가 비지니스 목적과 부합하면 그대로 구입하면 됨)
하니면 community AMI(public AMI)를 사용해도 됨

=> 그리고 나서 Launch Instance 하면 실행됨 ( 만약 변경이 필요하면 다시 configure 해서 이미지를 만들면 됨)


이렇게 instance 가 띄워지면 VPC 가 생성됨
사용 가능한 IP 주소의 범위 (CIDR 법으로 표현)


-------

EC2 패밀리
범용: 균형있는 워크 로드
컴퓨팅 최적화: 고성능 컴퓨팅, ..
메모리 최적화:
가속화된 컴퓨팅 : GPU
스코리지 최적화:


인스턴스는 EBS 에 스냅샷으로 백업되고 이는 S3에 저장됨
-> 이 과정은 하나의 리전에서 진행

인스턴스 메타데이터
-> 도움 데이터를 확인 가능
curl http://169.254.169.254/latest/meta-data


사용자 데이터 예) 아래 처럼 스크립트를 구성
yum -y install httpd]

아래와 같이 확인 가능
curl http://169.254.169.254/latest/user-data


---

Amazon VPC (virtual private cloud)

서브넷
VPC를 나누는 것을 의미.
VPC내에서 IPC 주소 범위를 정의함. ( 서브넷을 나눠서 사용)
EC2 인스턴스를 만들면 서브넷 내에 위치 시킴
인터넷에 연결되면 퍼플릭 서브넷. 인터넷에 연결되지 않으면 프라이빗 서브넷
(프라이빗이라도 NAT 게이트웨이을 통해서 외부 서비스-인터넷에 접속 가능)

VPC 보안
보안 그룹 (security group)
네트워크 ACL(액세스 제어 목록) : subnet
키페어 ( key pair, public pair)

awsstudent
701873589429
tdz6cRVQC?

----

인스턴스는 stop/atart 하게 되면 다른 호스트 PC에서 실행되게 됨
그래서 데이터가 Instance store 에 있으면 휘발성
EBS가 되면 비 휘발성 데이터


--
S3

s3는 객체 단위로 저장. 하나의 계정에 최대 100개 버킷.
객체 키는 버킷 내 객체의 고유한 식별자

버킷: globally unique 한 이름
http://버킷이름.s3.amazonaws.com/객체키/amazon.html

s3는 실제로는 폴더가 없음. 객체키가 prefix 역할을 함.

액세스 제어
버킷 정책 : 관계자외 출입 금지와 같은 역할
IAM 정책 : 사용자 마다 버킷의 액세스 여부를 할당

Amazon SDK를 통해 암호화 할 수 있음
s3는 lifecycle을 지원하고 있음 (객체 수명 주기. 사용하지 않는 파일은 저렴한 요금의
공간으로 이동 가능)

각각의 객체 하나가 원하는 스토리지 클래스로 이동됨(standard, glacier)

--------------------------------
EBS -> EC2가 사용하는 로컬 디스크
(Elastic Block Store)

저장된 데이터는 자동 저장. EBS는 S3에 붙였다, 떼었다 할 수 있음
스냅샷 백업 받기도 하고 복원하기도 하고.

범용 SSD(gp2) : 속도가 왔다 갔다 함.
프로비저닝된 IOPS: 정의된 iops 수준의 성능이 일정하게 됨.
처리량 최적화 HDD(st1) : 자주 액세스 하고 처리량 집약적인.

EBS는 빠른 데이테 액세스 필요, 암호화된 데이터 생성. 스냅샷 생성됨
IOPS를 동적으로 변경 가능

볼륨 데이터는 가용영역 내에서 백업이 계속 발생함.


-----------------------------
EC2 인스턴스 스토리지

지속성이 없음. 인스턴스가 중단, 종료되면 데이터가 날라감
EBS는 데이터가 영구적임


인스턴스 메타 데이터를 참조해서 프라이빗, 버블릿 IP주소를 찾음.


-----

AWS 책임 공유 모델

AWS STS (임시 보안 자격 증명)

액세스 키
보안 액세스 키

AWS IAM 은 사용자 그룹. 연동 사용자 같은 역할이지 OS에 대한 권한이 아님.

인증 (authentication)
권한 부여(authorization)

AWS CloudTrail계정 활동 모니터링 - > CCTV와 같은 역할

--

SQL : 수직적으로 확장해야 함. 스키마가 고정
NoSQL : 스키마를 동적으로 관리 할 수 있음.
쿼리가 제조사 마다 다름. GetItem,
노드를 수평적으로 확장할 수 있음

데이터 스토리지 고려 사항
- 하나로 모든 조건을 충족할 수 없음.
- 데이터 형식, 데이터 크기, 쿼리 빈도등을 고려하여 데이터 스토리지 고려 해야 함.

Amazon RDS
비용 효율적이고 조절 가능한 용량
여러 RDBMS를 선택해서 사용할 수 있음.
자동 백업 지원


Amazon DynamoDB
단순한 형태의 데이터를 저장
완전 관리형 NoSQL 데이터 베이스
- 프로비저닝 모드(사용자가 정의한 용량대로), / read capa. unit, write capa.unit 을
확인해서 최적의 값으로 설정
- 온디맨드 모드 방식으로 사용 가능

DB 인스턴스 : 기본 빌딩 블록 (Amazon RDS)
수동 스냅샷

쿼리 : 효율적인 방법
스캔 : 전체를 훑는 방식 (느림)



------------------------

Elastic Load Balancing

트래랙을 가용 영역에서 여러 EC2 인스턴스에 걸쳐 분산
비정상 Amazon EC2 인스턴스를 감지하기 위해 상태 확인 지원

ELB는 세가지 종류
CLB (class load balancer) - 예전에 쓰던 방식

--

Auto Scaling 그룹
비슷한 특성을 공유하는 EC2 인스턴스 모듬.
Auto scaling 그룹의 인스턴스는 인스턴스 확장 및 관리를 목적으로 한 논리적 그룹의

CloudWatch 경보를 사용하여 언제 확장할 지, 축소할지 정책 결정

오후 3:47: AWS 교육 및 자격증: https://aws.amazon.com/training/
AWS 자격증: https://aws.amazon.com/certification/
학습 경로: https://aws.amazon.com/training/learning-paths/
학습 퀘스트: https://amazon.qwiklabs.com/catalog?locale=en
https://amazon.qwiklabs.com/catalog?locale=en

lab-db.cc17lfndqj4d.ap-northeast-2.rds.amazonaws.com


https://aws.qwiklabs.com/classrooms/47580/labs/266061

LabELB-1368213964.ap-northeast-2.elb.amazonaws.com
