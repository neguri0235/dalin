
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


#### 클래스 제약
`:i`를 이용해서 타입 클래스를 조사 할 수 있음

``` haskell
Prelude> :i Num
class Num a where
  (+) :: a -> a -> a
  (-) :: a -> a -> a
  (*) :: a -> a -> a
  negate :: a -> a
  abs :: a -> a
  signum :: a -> a
  fromInteger :: Integer -> a
  {-# MINIMAL (+), (*), abs, signum, fromInteger, (negate | (-)) #-}
        -- Defined in ‘GHC.Num’
instance Num Word -- Defined in ‘GHC.Num’
instance Num Integer -- Defined in ‘GHC.Num’
instance Num Int -- Defined in ‘GHC.Num’
instance Num Float -- Defined in ‘GHC.Float’
instance Num Double -- Defined in ‘GHC.Float’
```

### 타입 클래스 종류
* Num : 숫자 타입의 공통된 동작
* Integral : 정수 타입들의 공통된 동작
* Floating
* Eq
* Ord  : 크기(>,<,>=,<=)
* Show : 값이 문자로 표현
* Read : 문자열을 이용해서 값으로 변환 'succ (read "1"::Int)'
* Enum

``` haskell

foo::Int->Int->Int
-- 반드시 else가 있어야 함.
-- 명령형 언어의 if : statement
-- Haskell의 if : expression (반드시 값이 있어야 함)
foo x y = if x > y then x + y else x - y

-- 임의의 타입으로 만들면 
-- Ord 와 Num 클래스 제약을 만족해야 함
foo::(Ord a, Num a) =>a->a->a

foo x y = if x > y then x + y else x - y
```

### 다형성 상수

3의 타입은? 확인해 보면 아래 처럼 조금 복잡하게 나옴.

``` haskell
*Main> :t 3
3 :: Num p => p
```
  
아래의 경우 `f2 3` 으로 하는 경우 에러가 발생하지 않고 3.0으로 리턴됨  
그럼 다시 위에서 `3::Num p=>p`라고 나온 것은 3은 임의의 타입(타입 이름이 소문자 이므로)인데, 타입클래스 Num의 인스턴스이다(Int,Double,Float중 하나)라는 의미.
``` haskell
f1::Int->Int
f1 x = x

f2::Double->Double
f2 x=x
```

정확한 타입을 지정하려면
``` haskell
*Main> :t 3::Int
3::Int :: Int
-- 정확히 Int 라고 나오고
-- f2에 3을 Int라고 타입을 정해서 보내면 컴파일 에러가 발생함
*Main> f2 3::Int

<interactive>:32:1: error:
    ? Couldn't match expected type ‘Int’ with actual type ‘Double’
    ? In the expression: f2 3 :: Int
      In an equation for ‘it’: it = f2 3 :: Int

```

#### 변수 만들기

``` haskell
-- 인자가 1개인 함수
one::Int->Int
one x = x

-- 인자가 없는 함수
-- 결국 변수 선언 하는 것 같은데..
-- 변수(상수)에 값을 부여하는 것을 binding이라고 부름.
zero ::Int
zero = 1
-- 값을 binding하면 변경할 수 없음
--zero = 2
```
