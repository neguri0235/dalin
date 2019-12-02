## DHCP

1. PC 수가 많거나 PC의 이동등이 있을 때 ip 주소를 동적으로 할당함
2. 약자는 Dynamic Host Configuration Protocol 임
3. 네트워크에 사용되는 주소를 DHCP 서버에서 관리를 하게 됨. 
4. 결국 리소스를 효율적으로 관리하고 IP 충돌도 막을 수 있음
​

반대로 DHCP 서버가 다운되면 아무것도 할 수 없음.

DHCP 서버에서 IP 할당은 주소를 임대해 주는 개념인데, 영구적으로 사용할 수 있도록 해주는 것은 아니고 일정 기간 사용할 수 있도록 IP Lease Time을 설정하게 된다. 그리고 단말 입장에서 IP를 계속 사용하려면 IP Address Renewal을 DHCP 서버에 요청해야 함.

그리고 더이상 사용하지 않을 때는 IP Address Release를 하게 되는데 언제인지는 모르겠음


절차는 다음과 같다
1. DHCP Discover
client에서 server를 찾는 과정인데, 동일 subnet 상에 broadcasting 해서 찾게 되고 Dest MAC = FF:FF:FF:FF:FF:FF 를 사용하게 됨. 
그리고 이때 전달하는 메시지에는 client의 MAC 을 포함하게 됨
2. DHCP Offer
서버에서 단말에게 IP 주소를 넣어서 보내게 되는 과정.
offer message에 Flag가 있어서 1 이면 broadcast로 0이면 unicast로 보내게 됨
3. DHCP Request 
Offer 받은 IP 주소에 대해서 사용할 수 있도록 해달라고 요청하는 과정
4. DHCP Ack
client에서 요청한 IP 주소를 사요할 수 있도록 ack를 주고 IP Lease time도 같이 전달 함.