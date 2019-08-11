
grade :: Int -> Char  -- 선언

--{ 패턴 매칭을 사용하면
grade 90 = 'A'
grade 60 = 'F'
--}

grade score    -- 구현
 | score < 60 = 'F'
 | score < 90 = 'A'
 | otherwise = 'B' 


grade2 :: Double->Double->Char

grade2 score1 score2
 | score  < minScore = 'F'
 | score  < highScore = 'A'
 | otherwise = 'B'
 where score = (score1 + score2)/2
       minScore = 60
       highScore = 90