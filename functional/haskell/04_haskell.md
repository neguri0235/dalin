### Module

관련된 함수와 타입을 묶어놓는, 라이브러리 로딩과 같은 기능

``` haskell
*Main> sort [1,2,3,4,5]

<interactive>:27:1: error:
    ? Variable not in scope: sort :: [Integer] -> t
    ? Perhaps you meant ‘sqrt’ (imported from Prelude)
*Main> import Data.List
*Main Data.List> sort [1,5,3,2,6,4,7]
[1,2,3,4,5,6,7]
*Main Data.List> nub [1,5,3,2,6,4,5,7,1,4]
[1,5,3,2,6,4,7]
```

각 자릿수의 합이 15가 되는 최소의 숫자
``` haskell
import Data.Char
import Data.List

-- digitToSum
digitToSum::Int->Int

-- 함수 합성을 써보자
-- show
-- 1423 => "1423
-- map digitToInt
-- [1 4 2 3]
-- 15 
digitToSum x = sum . map digitToInt . show

*Main Data.List Data.Char> digitToSum 1423
10

-- calcTo 15 : 자리수의 핪이 15가 되는 최초의 숫자
calcTo :: Int -> Maybe Int
calcTo n = (\x -> digitToSum x == n)[1..]
```

### Monad

``` haskell
f1 ::Int -> Maybe Int
f1 0 = Nothing
f1 n = Just (2*n)

f2 ::Int -> Maybe Int
f2 0 = Nothing
f2 n = Just (3*n)

-- f1 , f2 를 동시에 실행한다고 하면

f1nf2 :: Int -> Maybe Int

-- 실패 가능성이 있어서 아래처럼 쓸 수가 없음
--f1nf2 n = f2(f1 n)

-- 이렇게 만들 수도 있음
f1nf2 n = case f1 n of
    Nothing ->Nothing
    Just nn -> f2 nn

*Main> f1nf2 10
Just 60
*Main> f1nf2 0
Nothing
```

실패할 가능성이 있다는 표현에 대해 아래처럼 단순히 쓸 수 있음
``` haskell
f1nf2 n = do
    nn <- f1 n -- 실패할 수 있다는 표현
    f2 nn
```

``` haskell
-- f1 4 => [0,1,2,3]
f1 ::Int -> [Int]
f1 n = [0..n-1]


-- 인자로 전달된 요소의 +1, -1값을 구하고 싶다
f2::Int->[Int]
f2 n = [n+1, n-1]

-- 그럼 f1 의 리턴 값에 모두 f2를 적용하고 싶은 경우?
-- [0,1,2,3] => [1,-1, 2,0, 3,1,4,2]

f1nf2 :: Int->[Int]
f1nf2 n = concat (map f2 (f1 n))
*Main> f1nf2 4
[1,-1,2,0,3,1,4,2]
```

복잡해 보임. 
``` haskell
f1nf2 n = do
    nn <- f1 n  -- 복수의 요소를 고려한 연산
    f2 nn
```

결국 `모나드`는 문맥을 가지는 계산기, 미리 약속된 형태의 계산 방식
* Maybe Monad : 실패할 가능성이 있는
* List Monad : 복수의 요소를 의미