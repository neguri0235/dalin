### 개요

* HTTPS 는 HTTP에 over secure socker layer를 합친 것임  

* HTTPS와 SSL이 같은 것은 아니고, HTTPS가 SSL 프로토콜 위에서 돌아가는 것임.

* SSL과 TLS는 서로 같은 것임. 네스케이프가 SSL을 만들었고, 표준화 기구인 IETF를 통해 TLS라는 이름으로 변경된 것이다. TLS 1.0은 SSL 3.0을 계승한 것임.

* SSL 인증서는 클라이언트와 서버간의 통신을 제 3자가 보증해주는 전자화된 문서이며, 클라이언트가 서버에 접속하면 곧바로 클라이언트에게 인증서를 전송한다. 그리고 클라이언트는 인증서가 신뢰할 수 있는 것인지 확인 후 다음 절차를 수행한다.

### 대칭키

암호화와 복호화에 하나의 키만을 사용하는 것을 __대칭키__ 암호화라고 한다. DES 가 대칭키 암호화이다.

``` bash
# 임의의 텍스트 파일을 하나 만듬
$ echo 'this is the plain text' > plain.text

# des3 방식으로 plain.text 를 암호화 함
$ openssl enc -e -des3 -in plain.text -out cipher.txt
enter des-ede3-cbc encryption password:
Verifying - enter des-ede3-cbc encryption password:
*** WARNING : deprecated key derivation used.
Using -iter or -pbkdf2 would be better.

# 암호화된 ciper.txt를 복호화 함
$ openssl enc -d -des3 -in cipher.txt -out decipher.txt

```

### 공개키

공개키로 암호화를 하고 비공개키를 이용하여 복화화를 한다. 암호화를 공개키를 이용하여 모든 사람이 암호화 할 수 있지만 복호화는 반드시 비공개키를 가진 사람만이 할 수 있다.  
  
인증의 관점으로도 볼 수 있는데, 공개키를 이용하여 암호화한 것을 비공개 키를 가진 사람이 복호화를 할 수 있는데, 여기에 대해 비공캐 키를 가진 사람이 암호화를 하여 전달하고 공개키를 가진 사람이 그 암호화된 문서를 복화화 가능하다면, 이 문서는 비공개키를 가진 사람으로 부터 전송된 것이라고 인정할 수 있다. 

https://minix.tistory.com/395


private key 생성

``` bash
$ openssl genrsa -out private.pem 1024
Generating RSA private key, 1024 bit long modulus (2 primes)
.........................+++++
....+++++
e is 65537 (0x010001)

```

private key를 이용하여 public key 생성
``` bash
$ openssl rsa -in private.pem -out public.pem -outform PEM -pubout
writing RSA key
```

암호화 하기
``` bash
$ openssl rsautl -encrypt -inkey public.pem -pubin -in file.txt -out file.ssl;
```

복호화하기
``` bash
$ openssl rsautl -decrypt -inkey private.pem -in file.ssl -out decrypt.txt
```



### 인증서
* 클라이언트가 접속한 서버가 신뢰할 수 있는 서버임을 보장.
* 서버에서 공개키를 사용자에게 인증서에 포함하여 전달.

#### CA
__CA__(Certificate authority) 혹은 __Root Certificate__이라고 부르는데 인증서를 관리하고 발행하는 기관을 말한다.

#### 인증서의 내용
* 인증서를 발급한 CA, 어떤 서비스에 사용할 수 있는지등 설명.
* 공개키가 들어가 있고, 공개키가 어떤 방식으로 암호화 되어 있는지 들어 있음.

추가로 CA 정보를 브라우저는 이미 알고 있고, 브라우저가 업데이트 될 때 새로운 CA 정보를 포함할 수 있다.

#### 인증서가 서비스를 보증하는 방법
1. 서버가 인증서를 웹 브라우저에 제공
2. 브라우저는 인증서에 포함된 CA가 브라우저에 있는 CA 리스트에 존재하는지 확인
3. 인증기관의 공개키를 브라우저는 가지고 있어, 공개키를 이용해서 인증서를 복호화함
4. 인증서는 비밀키로 암호화 되어 있으므로, 복호화하는 것은 해당 인증서를 복호화함으로서 해당 인증서는 비밀키를 통해서 암호화되었다고 확인함
5. 그런데 인증서안에도 공개키가 포함되어 있음.



### SSL의 동작 방법
클라이언트는 서버에게 자신의 공개키를 전송하고 , 서버도 클라이언트에게 자신의 공개키를 전송

* 실제 데이터: 대칭키를 이용하여 암호화
* 대칭키의 키: 공개키를 이용하여 암호화

컴퓨터와 네트워크가 통신할 때는 아래 3가지 단계로 처리
1. 악수(Handshake) : 서버와 클라이언트간 양쪽의 정보(암호화 기법등)를 파악
2. 전송
3. 세션 종료


#### Handshake

1. 클라이언트가 서버에 접속한다 (Client Hello)
> 클라이언트가 생성한 랜덤 데이터를 전달  
  클라이언트가 지원하는 암호화 방식을 전달  
  세션아이디(이미 SSL Handshake를 하였다면 리소스 절약을 위해서 기존 세션 재 활용)

2. Server Hello
> 서버에서 생성한 랜덤 데이터를 클라이언트에 전달  
  클라이언트가 전달한 암호화 방식 중 어떤 암호화 기법을 사용할 것인지를 선택해서 내려줌
  인증서를 전송

3. 클라이언트
  * 전달 받은 인증서가 CA에서 발급받은 것인지 확인  
  * 그리고 이미 가지고 있는 공개키를 이용하여 인증서를 복호화하고 성공하면 인증서를 믿을 수 있고 자신이 접속한 서버도 믿을 수 있는 서버로 판단 
  * 클라이언트는 인증서에 포함되어 있던 공개키를 획득
  * 클라이언트는 pre master secret 이라는 키를 생성하는데 pre master secret는 서버로 부터의 랜덤데이터 + 클라이언트의 랜덤 데이터를 조합한 것 
  * 세션 단계에서 데이터를 주고 받을때 데이터를 대칭키를 통해 암호화 하는데 이때 사용하는 키가 pre master secret임  
  * 클라이언트가 생성한 랜덤데이터를 서버로 전달해야 하는데, 이 랜덤 데이터도 암호화가 필요함. 그래서 인증서에 들어 있던 공개키를 이용하여 암호화하여 서버에 전송한다.  
  
4. 서버
> 클라이언트로 부터 전달 받은 pre master secret을 비공개키를 이용하여 복호화한다.  
  pre master secret을 이용하여 master secret을 생성하고 master secret을 이용하여 session key를 생성하여 서버와 클라이언트간에 대칭키 방식으로 데이터를 주고 받는다.  
  
5. Handshake 종료  
  
