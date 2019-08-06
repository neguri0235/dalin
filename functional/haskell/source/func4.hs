{--
foo::Int->Int->Int
-- 반드시 else가 있어야 함.
-- 명령형 언어의 if : statement
-- Haskell의 if : expression (반드시 값이 있어야 함)
foo x y = if x > y then x + y else x - y
--}

-- 임의의 타입으로 만들면 
-- Ord 와 Num 클래스 제약을 만족해야 함
foo::(Ord a,Num a) =>a->a->a

foo x y = if x > y then x + y else x - y
