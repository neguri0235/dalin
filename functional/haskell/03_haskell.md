### Type 만들기

-- Meter 단위 값을 Yard 단위로 값을 변경 하는 함수


1. 기존 타입의 별칭 만들기

``` haskell
type Meter = Double
type Yard  = Double

convert::Meter  ->  Yard
convert m = m * 1.0936
-- 함수 원형에 대해 가독성이 좋아짐
*Main> :t convert
convert :: Meter -> Yard
```

2. 기존 타입을 이용해서 새로운 타입 만들기

`newtype`이란 키워드를 사용함.
``` haskell
newtype Meter = Meter Double
newtype Yard = Yard Double

foo::Meter->Int
foo m = 0

-- foo 함수 호출 시 
foo 3 -- 에러 발생

foo Meter 3 -- 생성자를 통해서 호출해야 하지만 에러

foo $ Meter 3 -- OK
*Main> foo $Meter 3
0
```
3. 사용자 타입을 인자로 받는 경우
``` haskell
-- Meter를 받아서 Double 값을 반환하는 함수
-- getValue (Meter 3)

getValue:: Meter->Double
getvalue (Meter m) = m
*Main> getValue $ Meter 3
3.0
```

### 타입 클래스의 인스턴스로 만들기

Interactive mode의 shell에서 보이려면 Show 타입 클래스의 인스턴스가 되어야 함. `deriving` 지시어를 사용

``` haskell
newtype Meter = Meter Double deriving Show
newtype Yard = Yard Double

*Main> Meter 4
Meter 4.0
*Main> Yard 3
<interactive>:106:1: error:
    ? No instance for (Show Yard) arising from a use of ‘print’
    ? In a stmt of an interactive GHCi command: print it
*Main>

```

`instance`지시어를 사용해 보면
``` haskell
newtype Meter = Meter Double deriving Show
newtype Yard = Yard Double

instance Show Yard where
 show (Yard y )  = show y ++ " yd"
*Main> Yard 3
3.0 yd
```


-- Meter를 Yard로 변경하는 함수
-- Meter를 Num 타입 클래스의 인스턴스로 .. 
``` haskell 
convert :: Meter -> Yard

-- convert m = m * 1.093613
convert (Meter m) = Yard (m * 1.093613)
*Main> convert (Meter 1)
1.093613 yd
```

### 완전히 새로운 타입 만들기

``` haskell
-- 점을 나타내는 Point 타입
newtype Point = Point Double Double
-- 실행하면 아래와 같이 생성하는 하나의 필드만 있어야 한다고 에러가 나옴
func_3_1.hs:38:17: error:
    ? The constructor of a newtype must have exactly one field
        but ‘Point’ has two
    ? In the definition of data constructor ‘Point’
      In the newtype declaration for ‘Point’
   |
38 | newtype Point = Point Double Double
```

`data`라는 키워드를 사용하면 됨
``` haskell
data Point = Point Double Double deriving (Show, Eq)
Point :: Double -> Double -> Point
*Main> Point 1 1
Point 1.0 1.0
*Main> (Point 1 1) == (Point 0 0)
False
```

여러개를 같이 만들 수도 있음
``` haskell
data Shape = Circle Double Double Double | Rectangle Double Double Double Double deriving Show

*Main> :t Circle
Circle :: Double -> Double -> Double -> Shape
*Main> :t Rectangle
Rectangle :: Double -> Double -> Double -> Double -> Shape
*Main> Circle 1 1 4
Circle 1.0 1.0 4.0
*Main> Re
Read       ReadS      Real       RealFloat  RealFrac   Rectangle
*Main> Rectangle 1 2 3 4
Rectangle 1.0 2.0 3.0 4.0
*Main>
```


### 레코드 구분

새로운 데이터 타입을 만드는 기술

``` haskell
-- People 타입 : 이름, 나이, 주소
data People = People String Int String deriving Show

getName :: People -> String
getName (People n _ _) = n 
getAge :: People ->Int
getAge (People _ a _ ) = a

-- 사용할 때는 
*Main> getName ( People "AA" 2 "seoul")
"AA"
*Main> getAge (People "AA" 3 "Busan")
3
```

각 필드에 이름을 부여하는 것을 `레코드 구문`이라고 함
``` haskell
-- 이렇게 만들면 getter를 자동으로 만들어줌
data People = People { name::String, 
                       age ::Int, 
                       addr::String } deriving Show
*Main> name (People "Kim" 2 "seould")
"Kim"
*Main> age (People "Kim" 2 "seould")
2                       
```

### 인자가 없는 값 생성

생성자에 인자가 없는 경우는?

``` haskell
-- 인자가 있는 생성자
data Shape = Circle Int Int Int | Rectangle Int Int Int Int

-- Bool 의 경우 인자가 없는 True 생성자와 False 생성자가 있음
-- data Bool = True | False
-- 1주일을 표현하고 싶다
data Week = Mon | Tue | Wed | Thu | Fri | Sat | Sun deriving (Show , Eq, Enum)
*Main> succ Mon
Tue
```

### 타입 생성자

* 타입 생성자:타입을 인자로 받아서 새로운 타입을 만드는 생성자
* 값 생성자  : 값을 인자로 받아서 해당 타입의 값을 만드는 생성자

``` haskell
--data Shape = Rectangle Int Int Int Int
-- Int 뿐만 아니라 임의의 타입도 처리할 수 있도록
data Shape a = Rectangle a a a a deriving Show
-- 면적을 구하는 함수
area :: Num a => Shape a -> a
area (Rectangle x1 y1 x2 y2 ) = (x2-x1)*(y2-y1)
*Main> area (Rectangle  1 1 10 10)
81
```

### Maybe

int 의 문제점 : 잘못된 값(값 없음)을 표현할 수 없다.
``` cpp
int foo() { return 실패;}

template<typename T> struct Maybe {
    bool b; // 유효성
    T value;
}
Maybe<int> m ; int 를 보관하고 값 없음을 나타냄
```

``` haskell
-- 값이 없으면 Nothing 그렇지 않으면 a
data Maybe a = Nothing | Just a

Prelude> :i Maybe
data Maybe a = Nothing | Just a         -- Defined in ‘GHC.Base’
instance Applicative Maybe -- Defined in ‘GHC.Base’
instance Eq a => Eq (Maybe a) -- Defined in ‘GHC.Base’
instance Functor Maybe -- Defined in ‘GHC.Base’
instance Monad Maybe -- Defined in ‘GHC.Base’
instance Semigroup a => Monoid (Maybe a) -- Defined in ‘GHC.Base’
instance Ord a => Ord (Maybe a) -- Defined in ‘GHC.Base’
instance Semigroup a => Semigroup (Maybe a)
  -- Defined in ‘GHC.Base’
instance Show a => Show (Maybe a) -- Defined in ‘GHC.Show’
instance Read a => Read (Maybe a) -- Defined in ‘GHC.Read’
instance Foldable Maybe -- Defined in ‘Data.Foldable’
instance Traversable Maybe -- Defined in ‘Data.Traversable’
Prelude>
```

예제를 보면 입력된 값이 5 이상이면 다음수를, 5 이하이면 실패를 반한

``` haskell
--data Maybe a = Nothing | Just a
{-
next ::Int->Int
next x
 | x > 5 = succ x
 | otherwise = ?
-}

next::Int->Maybe Int
next x
 | x > 5 = Just (succ x)
 | otherwise = Nothing;

-- Maybe Int 를 받아서 Int를 반환
getValue::Maybe Int->Int
getValue (Just m) = m
getValue Nothing = 0
*Main> getValue (Just 8)
8
*Main> getValue Nothing
0
```

### 재귀적인 데이터 구조
#### List 만들기

``` haskell
data List = Empty | Node Int List deriving Show
*Main> Empty
Empty
*Main> Node 10 Empty
Node 10 Empty
*Main> Node 20 (Node 10 Empty)
Node 20 (Node 10 Empty)
*Main> Node 30(Node 20 (Node 10 Empty))
Node 30 (Node 20 (Node 10 Empty))
data List a = Empty | Node a (List a)deriving Show
```

특수 문자로 생성자 만들기
``` haskell
-- Node => :+
-- Node 10 Empty => 10 :+ Empty
data List a = Empty | a:+(List a) deriving Show
*Main> 10 :+ Empty
10 :+ Empty
*Main> 20 :+ (10 :+ Empty)
20 :+ (10 :+ Empty)
```
다음 내용은 너무 어렵다