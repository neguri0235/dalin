### arguments

#### 기본 사용법

```
import argparse
parser = argparse.ArgumentParser()
parser.parse_args()
```

아무런 동작도 없는 코드인데, `-h`와 `--help` 옵션은 기본으로 제공함


``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("echo")
args = parser.parse_args()
print(args.echo)
```

실행하면 echo 라는 parameter는 필요한 것으로 오는데 'args.echo` 처럼 변수가 지정된 것임  
그리고 그 변수에 전달한 param 이 들어 가는 것임
``` bash
>python arg.py -h
usage: arg.py [-h] echo

positional arguments:
  echo

optional arguments:
  -h, --help  show this help message and exit
 ```
 

  
아래와 같은 코드가 있다면, 결과는 sqaure 를 return 할 것으로 예상 하지만,  
 ``` python
 import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", help="display a square of a given number")
args = parser.parse_args()
print(args.square**2)
```  

실행해 보면 타입이 맞지 않는다고 나옴. 그래서 입력 받는 타입을 지정할 수가 있는데,,
``` bash
>python arg.py 2
Traceback (most recent call last):
  File "arg.py", line 13, in <module>
    print(args.square**2)
TypeError: unsupported operand type(s) for ** or pow(): 'str' and 'int'
```

아래처럼 타입을 명시적으로 지정해 주면 됨. 참고로 `help` 에 문자열을 넣으면 `-h`에 대해서 출력됨
``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", help="display a square of a given number", type=int)
args = parser.parse_args()
print(args.square**2)
```

#### 옵션의	예 

`--` 를 통해서 옵션을 추가할 수 있음. `-`도 가능하지만 `-` 와 `--`를 혼용할 수는 없음

``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--verbosity", help="increase output verbosity")
args = parser.parse_args()
if args.verbosity:
    print("verbosity turned on")
```

그래서 `--`와 `-`를 같이 사용하고 싶다면
`parser.add_argument("-v", "--verbose", ...)` 처럼 인자를 추가해야 함

`--verbose`를 통해 True, False 를 기본으로 설정하게 됨.`store_true`나 `store_false`는 예약어라서 변경하게 되면 에러 발생  

```  python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--verbose", help="increase output verbosity",
                    action="store_true")
args = parser.parse_args()
if args.verbose:
    print("verbosity turned on")
```


#### 위치 및 옵션 인자 결합

드디어 일반적으로 볼수 있는 옵션의 인자를 보게 됨.  
``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", type=int,
                    help="display a square of a given number")
parser.add_argument("-v", "--verbose", action="store_true",
                    help="increase output verbosity")
args = parser.parse_args()
answer = args.square**2
if args.verbose:
    print("the square of {} equals {}".format(args.square, answer))
else:
    print(answer)
```

실행해 보면 전달되는 argument의 순서는 중요치 않음
``` bash
>python arg.py 10 -v
the square of 10 equals 100

>python arg.py 10
100

>python arg.py  -v 10
the square of 10 equals 100
```

하는김에 true, false가 아닌 옵션으로 출력을 더 제어해 보면
``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", type=int,
                    help="display a square of a given number")
parser.add_argument("-v", "--verbosity", type=int,
                    help="increase output verbosity")
args = parser.parse_args()
answer = args.square**2
if args.verbosity == 2:
    print("the square of {} equals {}".format(args.square, answer))
elif args.verbosity == 1:
    print("{}^2 == {}".format(args.square, answer))
else:
    print(answer)
```

`-v` 옵션뒤에 입력 받는 값을 통해서 동작의 옵션을 변경함
``` bash
> python arg.py  10
100

> python arg.py  10 -v 1
10^2 == 100

> python arg.py  10 -v 2
the square of 10 equals 100

> python arg.py  10 -v 0
100
```

하지만 `-v 0` 입력 받는 것은 기대했던 동작이 아니니, 입력을 제한 할 수도 있다.
``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", type=int,
                    help="display a square of a given number")
parser.add_argument("-v", "--verbosity", type=int, choices=[0, 1, 2],
                    help="increase output verbosity")
args = parser.parse_args()
answer = args.square**2
if args.verbosity == 2:
    print("the square of {} equals {}".format(args.square, answer))
elif args.verbosity == 1:
    print("{}^2 == {}".format(args.square, answer))
else:
    print(answer)
```
도움말을 한번 보면
``` bash
>python arg.py  -h
usage: arg.py [-h] [-v {0,1,2}] square

positional arguments:
  square                display a square of a given number

optional arguments:
  -h, --help            show this help message and exit
  -v {0,1,2}, --verbosity {0,1,2}
                        increase output verbosity
```

그래서 지원하지 않는 입력을 추가하면 에러가 발생함
``` bash
>python arg.py  10 -v 4
usage: arg.py [-h] [-v {0,1,2}] square
arg.py: error: argument -v/--verbosity: invalid choice: 4 (choose from 0, 1, 2)
```

옵션의 개수를 통해 동작을 구분하는 것도 있음. 
``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", type=int,
                    help="display the square of a given number")
parser.add_argument("-v", "--verbosity", action="count",
                    help="increase output verbosity")
args = parser.parse_args()
answer = args.square**2
if args.verbosity == 2:
    print("the square of {} equals {}".format(args.square, answer))
elif args.verbosity == 1:
    print("{}^2 == {}".format(args.square, answer))
else:
    print(answer)
```
그런데 이걸 어디다 쓰지?

``` bash
> python arg.py  10 -v
10^2 == 100

> python arg.py  10 -v -v
the square of 10 equals 100

> python arg.py  10 -vv
the square of 10 equals 100
```


위 예제에서 `if args.verbosity >= 2:` 를 입력하면 2개 이상의 값도 입력 받을 수 있음. 그런데 이걸 어디다 쓰는지..

#### 조금 더 발전 시키기

argument 를 여러개 받을 수 있다면,
```
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("x", type=int, help="the base")
parser.add_argument("y", type=int, help="the exponent")
parser.add_argument("-v", "--verbosity", action="count", default=0)
args = parser.parse_args()
answer = args.x**args.y
if args.verbosity >= 2:
    print("{} to the power {} equals {}".format(args.x, args.y, answer))
elif args.verbosity >= 1:
    print("{}^{} == {}".format(args.x, args.y, answer))
else:
    print(answer)
```	
#### 조금 더 발전 시키기

argument 를 여러개 받을 수 있다면,
``` python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("x", type=int, help="the base")
parser.add_argument("y", type=int, help="the exponent")
parser.add_argument("-v", "--verbosity", action="count", default=0)
args = parser.parse_args()
answer = args.x**args.y
if args.verbosity >= 2:
    print("{} to the power {} equals {}".format(args.x, args.y, answer))
elif args.verbosity >= 1:
    print("{}^{} == {}".format(args.x, args.y, answer))
else:
    print(answer)
```	

``` bash
> python arg.py  2 3 -v
2^3 == 8
```

#### 충돌하는 옵션 

`add_mutually_exclusive_group` 를 통해서 동시에 옵션이 입력되면 에러가 발생

``` python

import argparse

parser = argparse.ArgumentParser()
group = parser.add_mutually_exclusive_group()
group.add_argument("-v", "--verbose", action="store_true")
group.add_argument("-q", "--quiet", action="store_true")
parser.add_argument("x", type=int, help="the base")
parser.add_argument("y", type=int, help="the exponent")
args = parser.parse_args()
answer = args.x**args.y

if args.quiet:
    print(answer)
elif args.verbose:
    print("{} to the power {} equals {}".format(args.x, args.y, answer))
else:
    print("{}^{} == {}".format(args.x, args.y, answer))
```

`ArgumentParser` 에 description을 추가하여 도움말에 같이 표시 할 수도 있음
```
import argparse
parser = argparse.ArgumentParser(description="calculate X to the power of Y")
group = parser.add_mutually_exclusive_group()
group.add_argument("-v", "--verbose", action="store_true")
group.add_argument("-q", "--quiet", action="store_true")
parser.add_argument("x", type=int, help="the base")
parser.add_argument("y", type=int, help="the exponent")
args = parser.parse_args()
answer = args.x**args.y

if args.quiet:
    print(answer)
elif args.verbose:
    print("{} to the power {} equals {}".format(args.x, args.y, answer))
else:
    print("{}^{} == {}".format(args.x, args.y, answer))
```