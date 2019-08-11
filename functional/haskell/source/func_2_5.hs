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

-- 인자로 전달된 값을 그대로 반환하는 함수
foo::Int->Int
foo x = x

-- 함수를 반환하는 함수

goo::Int->Int->Int
goo x = foo


add::Int->Int->Int
add x y = x + y

add3 :: Int->Int->Int->Int
add3 x y z = x + y + z


-- 정수 2개를 더하는 함수
add2  = add3 0

-- km를 m 로 변경
kmToMeter ::Int->Int
kmToMeter km = km*1000

kmToMeter2 = (*1000)

hoo = (+5)