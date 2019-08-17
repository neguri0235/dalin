
-- People 타입 : 이름, 나이, 주소
{-
data People = People String Int String deriving Show

getName :: People -> String
getName (People n _ _) = n 

getAge :: People ->Int
getAge (People _ a _ ) = a
-}

-- 각 필드에 이름을 부여하는 것
-- 이렇게 만들면 getter를 자동으로 만들어줌
data People = People { name::String, 
                       age ::Int, 
                       addr::String } deriving Show
{-

data Shape = Circle Int Int Int | Rectangle Int Int Int Int

-- Bool 의 경우 인자가 없는 True 생성자와 False 생성자가 있음
-- data Bool = True | False


-- 1주일을 표현하고 싶다
data Week = Mon | Tue | Wed | Thu | Fri | Sat | Sun deriving (Show , Eq, Enum)
-}


--data Shape = Rectangle Int Int Int Int
-- Int 뿐만 아니라 임의의 타입도 처리할 수 있도록
data Shape a = Rectangle a a a a deriving Show

-- 면적을 구하는 함수
area :: Num a => Shape a -> a
area (Rectangle x1 y1 x2 y2 ) = (x2-x1)*(y2-y1)

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


--data List = Empty | Node Int List deriving Show

--data List a = Empty | Node a (List a)deriving Show

-- 특수 문자로 생성자 만들기
-- Node => :+
-- Node 10 Empty => 10 :+ Empty
data List a = Empty | a:+(List a) deriving Show
