
### 데이터 타입

``` haskell
> :t False
False :: Bool
> :t 3
3 :: Num p=p
```

타입을 볼때 좀 복잡한데, 타입 클래스의 개념 때문에 복잡해 보임

### 연산자
``` haskell
Prelude> 3 + 4
7
Prelude> 3+4*2
11
Prelude> 5+ -3

<interactive>:16:1: error:
    Precedence parsing error
        cannot mix ‘+’ [infixl 6] and prefix `-' [infixl 6] in the same infix expression
Prelude> 5+ (-3)
2
Prelude> 3 == 3
True
Prelude> 3 /= 3
False
```
음수를 나타날 때는 괄호로 써야 하고, Not 이 !로 쓰는 것이 아니라 `/=`로 써야 함.

### 함수를 사용하자 

Haskell에서는 인자를 전달할 때 괄호가 아닌 공백을 사용하고, 함수를 호출 한다는 표현대신 함수를 적용한다고 표현.
``` haskell
Prelude> succ 5
6
Prelude> succ 10
11
Prelude> succ 3*2
8
Prelude> succ (3*2)
7
Prelude> max 10 20
20
Prelude> mod 10 3
1
Prelude> 10 `mod` 3  -- 중위 함수를 사용 할 수 있는데, 이런 경우 가독성이 좋음
1

Prelude> (+) 3  4    -- 연산자도 결국 함수 이기 때문에, ( ) 로 묶어 전위 함수로 만듬
7
```

### 함수를 만들자

규칙
* 함수의 이름은 소문자로 시작
* 타입의 이름은 대문자로 시작

#### 인자가 1개인 함수

`returnMe`란 함수를 만들어 보면.
1. 함수 타입 선언
    > returnMe :: Int ->Int   # Int를 입력 받고 Int를 반환
2. 함수의 구현
    > `=` 로 구현부를 표현. x 를 입력 받고 반환값에 return을 사용할 필요 없음
    > returnMe x = x


#### 인자가 2 개인 함수

> 예를 들어 두개의 인수를 입력 받고, 두번째 인자를 반환한다고 하면  
>> returnMe2 :: Int->Int->Int   # 함수 선언  
  returnMe2 x y = y    # 함수 구현


### 일반화 함수

``` haskell
returnMe ::Int->Int
returnMe  x = x

-- Hashell 에서는 함수 오버로딩이 지원하지 않음.

returnMe ::Double->Double
returnme x = x
```

결국 Template, Generic 을 사용해야 함.  
대문자는 데이터 타입을 의미 하므로 임의의 타입은 소문자로 작성. 그리고 아래 예제에서 a는 `type parameter` 라고 부름  

``` haskell 
returnMe :: a->a
returnMe x = x
```

### 타입과 타입 클래스

int 를 입력 받고 다음 숫자를 리턴.  

``` haskell
returnNext :: Int->Int
returnNext x = x+1
```
그런데 임의의 타입을 지원하고 싶으면?   
아마도 이렇게 하겠지만 실행하면 에러가 발생한다. 

``` haskell
returnNext :: a->a
returnNext x = x+1
```

왜냐면 a 가 문자열이나 Bool 이면 +, - 가 아니기 때문에 이렇게 쓸 수 없음.   

#### 타입 클래스
**NUM** : Word, Int, Integet, Float, Double은 +,- 등의 연산을 지원하는 공통적인 특정이 있는데, `Int 타입은 Num 타입 클래스의 인스턴스이다` 표현한다.

**ENUM** : Bool 이나 Char 은 이전과 다음을 구할 수 있는데, 다음(next,succeed)을 계산 할 수 있는 데이터 타입은 모두 `ENUM` 타입 클래스에 속한다. String을 제외하고 모두 포함된다고 보면 됨.


``` haskell

-- returnNext는 임의의 타입을 받지만 a 는 Num type class 란 의미로 함수 선언 
returnNext :: Num a=> a->a
returnNext x = x + 1
```
