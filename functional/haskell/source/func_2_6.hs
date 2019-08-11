
-- 특정 함수를 2번 실행하는 함수
-- 1번째 인자 : 함수(인자가 1개)
-- 2번째 인자 : 임의의 타입의 값
applyTwice ::(a->a)->a->a
applyTwice f x = f (f x)

``` haskell
*Main> applyTwice succc 5

<interactive>:86:12: error:
    ? Variable not in scope: succc :: a -> a
    ? Perhaps you meant ‘succ’ (imported from Prelude)
*Main> applyTwice succ 5
7
```


