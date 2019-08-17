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
{-
-- 이렇게 만들 수도 있음
f1nf2 n = case f1 n of
    Nothing ->Nothing
    Just nn -> f2 nn
-}

f1nf2 n = do
    nn <- f1 n
    f2 nn

