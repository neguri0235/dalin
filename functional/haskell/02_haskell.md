### 패턴 매칭

아래 함수는 인자가 어떤 숫자가 들어오든 'sorry'를 반환한다.

``` haskell
translate :: Int -> String -- [Char]
translate x = "sorry"
```

그래서 이렇게 만들면 인자를 보고서 반환 값이 달라진다.
함수의 패턴을 보고 구현부를 따로 만드는 것을 `패턴 매칭`이라고 부름
``` haskell
translate :: Int -> String -- [Char]
translate 1 = "one"
translate 2 = "two"
translate 3 = "three"
translate x = "sorry"
-- translste _ = "sorry"  처럼 할 수 도 있음
```

패턴 매칭은 위에서 부터 순서대로 실행하고, 마지막에 placehold 같은게 없으면 매칭되지 않는 입력이 올 경우 오류가 발생함.

#### tuple 패턴 매칭

addPair 함수를 만들고 실행해 보면.
``` haskell
addPair :: (Int,Int) ->(Int,Int) ->(Int,Int)
addPair p1 p2 = (fst p1 + fst p2, snd p1 + snd p2)

*Main> addPair (1,1) (2,5)
(3,6)
```

addPair를 패턴 매칭으로 만들어 보면, fst 와 snd 의 사용 없이 곧다로 tuple에 접근할 수 있음
``` haskell
addPair :: (Int,Int) ->(Int,Int) ->(Int,Int)
addPair (x1,y1)(x2,y2) = (x1 + x2, y1 + y2)
```

Int type 외에 다른 타입도 사용하고 싶으면 
``` haskell
addPair :: Num a => (a,a) ->(a,a) ->(a,a)
addPair (x1,y1)(x2,y2) = (x1 + x2, y1 + y2)
```

인자가 세개인 tuple에서 각 요소를 꺼내는 함수를 패턴 매칭을 사용하면,

``` haskell
first:: (a,b,c) -> a
first (x,_,_) = x

second:: (a,b,c) -> b
second (_,y,_) = y

third:: (a,b,c) -> c
third (_,_,z) = z
```

#### list 패턴 매칭
임의의 타입의 리스트를 입력 받아서 임의의 타입을 반환

``` haskell
myHead :: [a] -> a
myHead [] = error "myHead empty list"
```
만약 빈 리스트가 들어올 경우, 에러를 보여 줄 수 있도록 처리  
`myHead xs=` 로 받게되면, `xs`에서 가장 첫번째 원소와 나머지 원소를 분리해야 하는데 구현이 쉽지 않음 

``` haskell
myHead :: [a] -> a
myHead [] = error "myHead empty list"
myHead (x:xs) = x
```
cons를 사용해서(괄호를 붙여 줘야함) 첫번째와 그 외의 것을 구분함.

head 는 만들었으니, list의 처음 두개를 만들면 더하는 함수를 만들면, 
``` haskell
addTwo :: Num a => [a] -> a
addTwo (x:[]) = error "one element list"
addTwo (x:y:xs) = (x+y)
```

문자열의 첫번째 요소가 공백이면 바로 리턴하고 , 아니면 공백을 추가하여 리턴하는 함수는 ?
``` haskell
addSpace :: [Char] -> [Char]
--addSpace (' ':xs) = ' ':xs
addSpace str@(' ':xs) = str  -- as 패턴
addSpace xs = ' ':xs
```
패턴 매칭을 사용하면 함수의 입력이 분리된 형태로 받게 되는데, 분리된 형태가 아닌 원래의 패턴으로 받고자 할때 'as패턴`을 사용하게 된다.

#### case 표현식

``` haskell

translate :: Int -> String

translate 1 = "one"
translate 2 = "two"
translate 3 = "three"
translate 4 = "other"

-- C 언어의 case 문 처럼
translate x = case x of 1 -> "one"
                        2 -> "two"
                        3 -> "three"
                        _ -> "other"

```
그리고 이렇게 중간에 문자열을 넣을 수도 있음
``` haskell
translate x = "result is " ++ case x of 1 -> "one"
                                        2 -> "two"
                                        3 -> "three"
                                        _ -> "other"
```