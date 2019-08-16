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


-- newtype Point = Point Double Double
data Point = Point Double Double deriving (Show, Eq)

data Shape = Circle Double Double Double | Rectangle Double Double Double Double deriving Show

-- 면적을 구하는 함수

-- area (Circle (Point 1 1 ) 5)
-- area (Rectange(Point 1 1) (Point 10 10))

area::Shape->Double
area (Circle _ _ r) = 3.14 * r ^ 2
area (Rectangle (Point x1 y1) (Point x2 y2)) =  (x2 -x1 )*( y2-y1)