{-
type Meter = Double
type Yard  = Double

convert::Meter  ->  Yard
convert m = m * 1.0936
-}
{-
newtype Meter = Meter Double
newtype Yard = Yard Double

foo::Meter->Int
foo m = 0


-- Meter를 받아서 Double 값을 반환하는 함수
-- getValue (Meter 3)

getValue:: Meter->Double
getValue (Meter m) = m
-}

newtype Meter = Meter Double deriving Show
newtype Yard = Yard Double

instance Show Yard where
 show (Yard y )  = show y ++ " yd"


-- Meter를 Yard로 변경하는 함수
-- Meter를 Num 타입 클래스의 인스턴스로 .. 
convert :: Meter -> Yard

-- convert m = m * 1.093613
convert (Meter m) = Yard (m * 1.093613)