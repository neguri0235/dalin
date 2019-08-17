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
digitToSum  = sum . map digitToInt . show

-- calcTo 15 : 자리수의 핪이 15가 되는 최초의 숫자
calcTo :: Int -> Maybe Int
calcTo n = (\x -> digitToSum x == n)[1..]