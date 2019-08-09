--{
addPair :: Num a => (a,a) ->(a,a) ->(a,a)
addPair (x1,y1)(x2,y2) = (x1 + x2, y1 + y2)

--}

first:: (a,b,c) -> a
first (x,_,_) = x

second:: (a,b,c) -> b
second (_,y,_) = y

third:: (a,b,c) -> c
third (_,_,z) = z