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