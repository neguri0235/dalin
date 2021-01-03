통계

'''

> y <- sleep$extra[sleep$group==1]
> y
 [1]  0.7 -1.6 -0.2 -1.2 -0.1  3.4  3.7  0.8  0.0  2.0
> summary(y)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
 -1.600  -0.175   0.350   0.750   1.700   3.700 
> sd(y)
[1] 1.78901

> t.test(y)

	One Sample t-test

data:  y
t = 1.3257, df = 9, p-value = 0.2176
alternative hypothesis: true mean is not equal to 0
95 percent confidence interval:
 -0.5297804  2.0297804
sample estimates:
mean of x 
     0.75 

> t.test(y, alternative="greater")

	One Sample t-test

data:  y
t = 1.3257, df = 9, p-value = 0.1088
alternative hypothesis: true mean is greater than 0
95 percent confidence interval:
 -0.2870553        Inf
sample estimates:
mean of x 
     0.75 
'''

R 에서 기본으로 제공하는 데이터를 사용하여 연습해 보면, 수면 시간 증가는   
0.75시간이고 표준 편차는 1.8 시간이다. 그런데 이 정보를 가지고 어떤 의미 있는 설명(narrative)를 할수 있을 까?  
t = 1.3257 : 데이터로 부터 계산산 t-통계량  
df = 9 (degree of freedom) 자유도를 나타내며 공식은 df = n -1 
p-value - 0.1088 . 자유도 df = 9인 t 분포가 관측된 t 값보다 클 확률  

통계학은 알려지지 않은 참값이 있음을 가정한다. 알려지지 않은 참 값을 모수(population parameter)라고 표현한다.  여기서 알려지지 않은 참 값이란 '수면제를 
먹었을때 증가한 평균 수면시간'을 의미한다. 그런데 모수의 값은 불완전한 이 세상의 데이터로서는 완전히 알아낼수 없다.  

통계의 추정은 불완전한, 잡음이 섞여 있는 데이터로 부터 숨겨진 진실, 즉 모수의 값을 찾애내는 것이다.
