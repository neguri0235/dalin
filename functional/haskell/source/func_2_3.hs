-- 임의의 타입의 리스트를 입력 받아서 임의의 타입을 반환
myHead :: [a] -> a
myHead [] = error "myHead empty list"
myHead (x:xs) = x

addTwo :: Num a => [a] -> a
addTwo (x:y:xs) = (x+y)

addSpace :: [Char] -> [Char]
--addSpace (' ':xs) = ' ':xs
addSpace str@(' ':xs) = str  -- as 패턴
addSpace xs = ' ':xs

translate :: Int -> String
--{
translate 1 = "one"
translate 2 = "two"
translate 3 = "three"
translate 4 = "other"
--}

-- C 언어의 case 문 처럼
translate x = "result is " ++ case x of 1 -> "one"
                                        2 -> "two"
                                        3 -> "three"
                                        _ -> "other"
