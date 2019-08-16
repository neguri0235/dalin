r1 = zipWith (*)[1,2,3,4][5,6,7,8]

r2 = zipWith max [1,8,9,3][2,3,7,8]

r3 = zipWith (++) ["A","B","C"]["A","B","C"]

r4 = zipWith (*) (replicate 3 1) [1..]


-- zipWith : 인자가 3개인 함수
-- zipWith (+) : 인자가 2개인 함수, 인자는 리스트 2개
-- 인자로 전달된 2개의 리스트를 더하는 작업
r5 = zipWith (+) [1,2,3,4][5,6,7,8]

r6 = zipWith (zipWith (+)) [ [1,2],[3,4],[5,6]][[10,20],[30,40]]


myzipWith ::(a->b->c)->[a]->[b]->[c]

-- 입력 중 빈 리스트가 오면 무시
myzipWith _ [] _ = []

 -- 입력 중 빈 리스트가 오면 무시 
myzipWith _ _ [] = []

-- 입력 받을 때는 패턴 매칭을 써야 함
myzipWith f (x:xs) (y:ys) = f x y : myzipWith f xs ys

-- 함수를 입력 받아서 함수를 반환한다는 개념
myflip ::(a->b->c) -> (b->a->c)
myflip f = g
  where g x y = f y x

-- 이항인자, 값, 값
-- myflip (-) 5 3
-- 함수와 두개의 값을 입력 받는 다는 가정으로
myflip2 :: (a->b->c)->b->a->c
myflip2 f x y = f y x

r11 = map (+3) [1,2,3]
r12 = map ("Hi" ++ ) ["kim","Lee","Park"]
r13 = map fst [(1,2),(3,4),(5,6)]
r14 = map (replicate 3)[3..6]
r15 = map head [[1,2],[3,4],[5,6]]

-- map : 인자가 2개 (함수와 리스트)
-- map (*2) : 인자가 한개.리스트
--          : 인자로 전달된 리스트의 각 요소의 값을 2배로
r16 = map (map(*2)) [[1,2],[3,4],[5,6]]

r21 = filter ( <10 ) (filter even[1..20])

r22 = [ x | x <- [1..20], even x, x < 10]

r23 = filter (`elem`['a' ..'z']) "I am a boy"

-- r24 = filter (`mod` 3) [1..3]

r24 = filter (\x->if x `mod` 3 == 0 then True else False) [1..100]

myfilter ::(a->Bool) ->[a]->[a]
myfilter _ [] = []
myfilter p (x:xs)
 | p x = x : myfilter p xs
 | otherwise = myfilter p xs


r31 = foldl (+) 0 [1,2,3]  -- (((0+1) + 2 ) + 3)
r32 = foldr (+) 0 [1,2,3]  -- (1 + (2 + (3 + 0)))

r33 = foldl1 (+) [1,2,3] -- ((1+2)+3)
r34 = foldr1 (+) [1,2,3] -- (1+(2+3))


-- 1:[] => [1] => 2:[1] => [2,1] => [3,2,1]
r35 = foldl(\x y ->y:x)[][1,2,3] 