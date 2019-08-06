-- 인자가 1개인 함수
one::Int->Int
one x = x

-- 인자가 없는 함수
-- 결국 변수 선언 하는 것 같은데..
-- 변수(상수)에 값을 부여하는 것을 binding이라고 부름.
zero ::Int
zero = 1
-- 값을 binding하면 변경할 수 없음
--zero = 2