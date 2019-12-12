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