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

#### 가드 (Guard)

점수에 따라서 등급을 반환하는 함수를 만들어 보자  
패턴 매칭이 아닌, 조건에 따른 함수를 별도로 제공하는 `Guard`를 사용하면,

``` haskell
grade :: Int -> Char  -- 선언

--{ 패턴 매칭을 사용하면
grade 90 = 'A'
grade 60 = 'F'
--}

grade score    -- 구현
 | score < 60 = 'F'
 | score < 90 = 'A'
 | otherwise = 'B' 
 ```

 #### where

 두개의 입력을 받아서 평군을 구해고 등급을 반환해 보면 , 이렇게 만들 것임. 그런데 중복이 있음.(score1+score2)
 ``` haskell
 grade2 :: Double->Double->Char
grade2 score1 score2
 | (score1 + score2) /2 < 60 = 'F'
 | (score1 + score2) /2 < 90 = 'A'
 | otherwise = 'B'
```

중복이 있거나 반복되는 표현식에 대해 하나의 변수에 담아서 사용  
``` haskell
grade2 :: Double->Double->Char
grade2 score1 score2
 | score  < minScore = 'F'
 | score  < highScore = 'A'
 | otherwise = 'B'
 where score = (score1 + score2)/2
       minScore = 60
       highScore = 90
```

#### 재귀 호출

팩토리얼을 구할 때 패턴 매칭을 사용해 보면
``` haskell
factorial :: Int -> Int
factorial 1 = 1
factorial n = n * factorial (n -1)
```

유용한 함수를 어떻게 구현 할 수 있는지 
``` haskell
factorial :: Int -> Int
factorial 1 = 1
factorial n = n * factorial (n -1)

-- repeat
myrepeat :: a->[a]  -- 정수 뿐만 아니라 임의의 타임
myrepeat x = x : myrepeat x

-- reverse
myreverse :: [a]->[a]
myreverse [] = []  -- 재귀의 종료 조건이 위에 있어야 함
myreverse (x:xs) = myreverse xs ++ [x]

-- replicate
myreplicate :: Int->a->[a]
myreplicate n _  -- 종료조건인데, n 이 0보다 작을 경우
 | n <= 0 = []
myreplicate n x = x : myreplicate (n-1) x

-- zip : zip [1,2,3] [10,20,30] => [ (1,10), (2,20), (3,30)]
-- 패턴 매칭과 재귀 호출을 같이 이용해야 함.
myzip :: [a]->[b]->[(a,b)]
myzip [] _ = []
myzip _ [] = []
myzip (x:xs) (y:ys) = (x,y):myzip xs ys


-- take : take 3 [1,2,3,4,5] => [1,2,3]
mytake :: Int->[a]->[a]
--mytake 0 _ = []
mytake n _
 | n <= 0 = []
mytake _ [] = []
mytake n (x:xs) = x : mytake (n-1) xs
```

### 커리(curry) 함수 

함수는 왼쪽에서 오른쪽으로 결합된다.

``` haskell
*Main> succ 9
10
*Main> succ max 5 4

<interactive>:51:1: error:
    ? Non type-variable argument in the constraint: Enum (a -> a -> a)
      (Use FlexibleContexts to permit this)
    ? When checking the inferred type
        it :: forall a. (Enum (a -> a -> a), Ord a, Num a) => a
*Main> succ (max 5 4)
6
```

함수를 반환하는 함수를 만들어 보면

``` haskell
-- 인자로 전달된 값을 그대로 반환하는 함수
foo::Int->Int
foo x = x

-- 함수를 반환하는 함수
goo::Int->(Int->Int)
-- 그런데 goo 를 아래처럼 선언해도 동작 잘함
-- goo::Int->Int-Int
goo x = foo
```

`Int->(Int->Int)`와 `Int->Int->Int`는 같은 표현임.

__Haskell 에서 모든 함수는 인자가 한 개다__  
인자가 2개 처럼 보이는 함수는 모두 인자를 한개 가지고 함수(인자가 한 개인)를 반환하는 함수이다.

``` haskell
add::Int->Int->Int
add x y = x + y

add3 :: Int->Int->Int->Int
add3 x y z = x + y + z

-- 인자의 개수만큼 입력 받을 때 까지 함수를 계속 반환함
*Main> ((add3 10)20)30
60
```

#### 인자를 고정한 함수 만들기

``` haskell
-- 정수 2개를 더하는 함수
add2  = add3 0

-- km를 m 로 변경
kmToMeter ::Int->Int
kmToMeter km = km*1000
kmToMeter2 = (*1000)
```

연산자의 인자를 부분적으로 적용해서 사용하는 것을 `Section`이라고 부름


### 고차(Higher-order) 함수

함수를 인자로 전달 받거나, 함수를 반환하는 함수

-- 특정 함수를 2번 실행하는 함수
-- 1번째 인자 : 함수(인자가 1개)
-- 2번째 인자 : 임의의 타입의 값
applyTwice ::(a->a)->a->a
applyTwice f x = f (f x)

``` haskell
*Main> applyTwice succc 5

<interactive>:86:12: error:
    ? Variable not in scope: succc :: a -> a
    ? Perhaps you meant ‘succ’ (imported from Prelude)
*Main> applyTwice succ 5
7
```

applyTwice에 함수를 전달하는 3가지 방법
1. 인자가 한개인 함수 전달
2. 인자가 N 개인 함수의 인자를 N-1개만 적용하여 전달
3. 람다 표현식을 만드는 방법

``` haskell
*Main> applyTwice (+3) 5
11
*Main> applyTwice (*2) 5
20
*Main> applyTwice (\x->x*2)5
20
*Main> applyTwice (\x y->x*y)5
20
*Main> applyTwice ((\x y->x*y) 2) 5
20
*Main>
```


### zipWith

`zipWith` 함수는   
입력: 이항함수, 리스트, 리스트  
출력: 리스트

``` haskell
Prelude> :t zipWith
zipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
Prelude> zipWith (+) [1,2,3][4,5,6]
[5,7,9]
```

좀더 심화한 예제
``` haskell

r1 = zipWith (*)[1,2,3,4][5,6,7,8]

r2 = zipWith max [1,8,9,3][2,3,7,8]

r3 = zipWith (++) ["A","B","C"]["A","B","C"]

r4 = zipWith (*) (replicate 3 1) [1..]


-- zipWith : 인자가 3개인 함수
-- zipWith (+) : 인자가 2개인 함수, 인자는 리스트 2개
-- 인자로 전달된 2개의 리스트를 더하는 작업
r5 = zipWith (+) [1,2,3,4][5,6,7,8]

r6 = zipWith (zipWith (+)) [ [1,2],[3,4],[5,6]][[10,20],[30,40]]

Prelude> :l func_2_7.hs
[1 of 1] Compiling Main             ( func_2_7.hs, interpreted )
Ok, one module loaded.
*Main> r1
[5,12,21,32]
*Main> r2
[2,8,9,8]
*Main> r3
["AA","BB","CC"]
*Main> r3
["AA","BB","CC"]
*Main> r4
[1,2,3]
*Main> r5
[6,8,10,12]
*Main> r6
[[11,22],[33,44]]
```

zipWith를 구현해 보면

``` haskell
myzipWith ::(a->b->c)->[a]->[b]->[c]
-- 입력 중 빈 리스트가 오면 무시
myzipWith _ [] _ = []
 -- 입력 중 빈 리스트가 오면 무시 
myzipWith _ _ [] = []
-- 입력 받을 때는 패턴 매칭을 써야 함
myzipWith f (x:xs) (y:ys) = f x y : myzipWith f xs ys
```

### flip

이항 함수의 인자의 순서를 바꾸어서 새로운 함수를 반환

``` haskell
*Main> :t flip
flip :: (a -> b -> c) -> b -> a -> c
*Main> (-) 5 3
2
*Main> flip (-) 5 3
-2
*Main> zip [1,2,3][10,20,30]
[(1,10),(2,20),(3,30)]
*Main> flip zip [1,2,3][10,20,30]
[(10,1),(20,2),(30,3)]
```

flip을 만들어 보면
``` haskell

-- 함수를 입력 받아서 함수를 반환한다는 개념
myflip ::(a->b->c) -> (b->a->c)
myflip f = g
  where g x y = f y x

-- 이항인자, 값, 값
-- myflip (-) 5 3
-- 함수와 두개의 값을 입력 받는 다는 가정으로
myflip2 :: (a->b->c)->b->a->c
myflip2 f x y = f y x
```
이렇게 `g x y = f y x` 로 새로운 함수를 만들어서 구현할 수 있음, 아니면 함수와 두개의 인자를 받는다는

### map
``` haskell
*Main> :t map
map :: (a -> b) -> [a] -> [b]
*Main>
*Main> map (+3) [1,2,3]
[4,5,6]


r11 = map (+3) [1,2,3]
r12 = map ("Hi" ++ ) ["kim","Lee","Park"]
r13 = map fst [(1,2),(3,4),(5,6)]
r14 = map (replicate 3)[3..6]
r15 = map head [[1,2],[3,4],[5,6]]

-- map : 인자가 2개 (함수와 리스트)
-- map (*2) : 인자가 한개.리스트
--          : 인자로 전달된 리스트의 각 요소의 값을 2배로
r16 = map (map(*2)) [[1,2],[3,4],[5,6]]

*Main> r11
[4,5,6]
*Main> r12
["Hikim","HiLee","HiPark"]
*Main> r14
[[3,3,3],[4,4,4],[5,5,5],[6,6,6]]
*Main> r13
[1,3,5]
*Main> r15
[1,3,5]
*Main> r16
[[2,4],[6,8],[10,12]]
*Main>
```

### Filter

리스트의 요소 중 조건자(predicator)를 만족하는 요소만을 가진 새로운 리스트를 반환

``` haskell
*Main> :t filter
filter :: (a -> Bool) -> [a] -> [a]
*Main> filter even [1..10]
[2,4,6,8,10]
```

``` haskel

r21 = filter ( <10 ) (filter even[1..20])

r22 = [ x | x <- [1..20], even x, x < 10]

r23 = filter (`elem`['a' ..'z']) "I am a boy"

-- r24 = filter (`mod` 3) [1..3]

r24 = filter (\x->if x `mod` 3 == 0 then True else False) [1..100]

*Main> r21
[2,4,6,8]
*Main> r22
[2,4,6,8]
*Main> r23
"amaboy"
*Main> r24
[3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81,8
4,87,90,93,96,99]
```

직업 만들어 보면
``` haskell

myfilter ::(a->Bool) ->[a]->[a]
myfilter _ [] = []
myfilter p (x:xs)
 | p x = x : myfilter p xs
 | otherwise = myfilter p xs
```


### Fold
리스트의 모든 요소에 순서대로 이항 함수를 적용
``` haskell
foldl :: Foldable t => (b -> a -> b) -> b -> t a -> b
r31 = foldl (+) 0 [1,2,3]  -- (((0+1) + 2 ) + 3)
r32 = foldr (+) 0 [1,2,3]  -- (1 + (2 + (3 + 0)))

r33 = foldl1 (+) [1,2,3] -- ((1+2)+3)
r34 = foldr1 (+) [1,2,3] -- (1+(2+3))
-- 1:[] => [1] => 2:[1] => [2,1] => [3,2,1]
r35 = foldl(\x y ->y:x)[][1,2,3] 
*Main> r31
6
*Main> r32
6
*Main> r33
6
*Main> r34
6
*Main> r35
[3,2,1]
```


### 함수 적용 연산자 '$'

함수에 인자를 적용하는 방법  
공백 : 우선 순위가 높음
$ : 우선 순위가 낮음
``` haskell
*Main> succ$1
2
*Main> succ max 5 3

<interactive>:70:1: error:
    ? Non type-variable argument in the constraint: Enum (a -> a -> a)
      (Use FlexibleContexts to permit this)
    ? When checking the inferred type
        it :: forall a. (Enum (a -> a -> a), Ord a, Num a) => a
*Main> succ$max 5 3
6
*Main> succ(max 5 3)
6
```
### 함수 합성
함수 결과 값을 다른 함수의 입력으로 바로 전달
``` haskell
*Main> negate $succ 4
-5
*Main> negate (succ 3)
-4

-- a 가 입력되어 b가 반환되고 b가 입력되어 c가 리턴되는 함수
*Main> :t (.)
(.) :: (b -> c) -> (a -> b) -> a -> c
*Main> (negate . succ ) 3
-4
*Main> ( (min 5) . negate .succ)3
-4
```

리스트에 있는 모든 요소를 음수로 변경 후,리스트의 합을 구하고 싶다
``` haskell
-- [1,-2,-3,4,-5]
--r1 = map negate [1,-2,-3,4,-5]
r2 = map (negate .abs) [1,-2,-3,4,-5]
r3 = sum $ map (negate .abs ) [1,-2,-3,4,-5]
*Main> r2
[-1,-2,-3,-4,-5]
*Main> r3
-15
```
