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
