검색


SELECT * FROM sample25 WHERE text LIKE '%SQL%";
SELECT * FROM sample25 WHERE text LIKE 'SQL%"; // -> '전방일치'라고 부름
SELECT * FROM sample25 WHERE text LIKE '%SQL"; // -> '후방일치'라고 부름


%를 검색하고자 할 때, \ 를 사용, 좀더 복잡한 것을 검색하고자 할때는 정규표현식 사용을 권장

SELECT * FROM sample25 WHERE text LIKE '%\%%';


정렬


SELECT * FROM sample31 ORDER BY age;   // age로 정렬
SELECT * FROM sample31 ORDER BY age DESC; // 내림 차순 정렬
SELECT * FROM sample31 ORDER BY age ASC;  // 오름 차순 정렬


복수열 정렬 할때



SELECT * FROM sample32 ORDER BY a; // a 로만 정렬
SELECT * FROM sample32 ORDER BY a , b // a 로 정렬 후 b 로도 정렬




SELECT * FROM sample32 ORDER BY a ASC , b DESC; // a는 오름 차순으로, b는 내림 차순으로 정렬


database에 NULL 이 있으면 가장 작은 값으로 처리되서 , DESC로 정렬하면 가장 끝에, ASC로 정렬하면 가장 처음으로 들어 감.

결과 제한 하기
LIMIT 이란게 있는데 SQL 표준은 아니고, MySQL 하고 PostgreSQL에서 사용할 수 있음

SELECT * FROM sample33 LIMIT 3;


정렬하고 출력의 개수를 제한 할 수 도 있음

SELECT * FROM sample33 ORDER BY no DESC LIMIT 3;
SELECT * FROM sample33 LIMIT 3 OFFSET 3;


수치연산


이런 데이터가 있을 때, price x quantity 를 계산한 결과가 필요한 경우

mysql> select * from sample34;
+------+-------+----------+
| no | price | quantity |
+------+-------+----------+
| 1 | 100 | 10 |
| 2 | 230 | 24 |
| 3 | 1980 | 1 |
+------+-------+----------+
3 rows in set (0.00 sec)



SELECT *, price * quantity FROM sample34;
mysql> 
+------+-------+----------+------------------+
| no | price | quantity | price * quantity |
+------+-------+----------+------------------+
| 1 | 100 | 10 | 1000 |
| 2 | 230 | 24 | 5520 |
| 3 | 1980 | 1 | 1980 |
+------+-------+----------+------------------+



AS를 붙여서 별명을 만들 수도 있음

SELECT *, price * quantity AS amount FROM sample34;
mysql> select *, price * quantity AS amount from sample34;
+------+-------+----------+--------+
| no | price | quantity | amount |
+------+-------+----------+--------+
| 1 | 100 | 10 | 1000 |
| 2 | 230 | 24 | 5520 |
| 3 | 1980 | 1 | 1980 |
+------+-------+----------+--------+



결과 계산한 이후에 WHERE 사용하기

SELECT *, price * quantity AS amount FROM sample34 WHERE price * quantity >= 2000;

+------+-------+----------+--------+
| no | price | quantity | amount |
+------+-------+----------+--------+
| 2 | 230 | 24 | 5520 |
+------+-------+----------+--------+
1 row in set (0.00 sec)



정렬도 할 수 있다

mysql> SELECT *, price * quantity AS amount FROM sample34 ORDER BY price*quantity DESC;

+------+-------+----------+--------+
| no | price | quantity | amount |
+------+-------+----------+--------+
| 2 | 230 | 24 | 5520 |
| 3 | 1980 | 1 | 1980 |
| 1 | 100 | 10 | 1000 |
+------+-------+----------+--------+
3 rows in set (0.00 sec)



Alias를 이용해서 정렬도 가능

mysql> SELECT *, price * quantity AS amount FROM sample34 ORDER BY amount DESC;


+------+-------+----------+--------+
| no | price | quantity | amount |
+------+-------+----------+--------+
| 2 | 230 | 24 | 5520 |
| 3 | 1980 | 1 | 1980 |
| 1 | 100 | 10 | 1000 |
+------+-------+----------+--------+
3 rows in set (0.00 sec)



반올림하기 (ROUND 함수를 사용하면됨)

mysql> SELECT amount, ROUND(amount) FROM sample341;

+---------+---------------+
| amount | ROUND(amount) |
+---------+---------------+
| 5961.60 | 5962 |
| 2138.40 | 2138 |
| 1080.00 | 1080 |
+---------+---------------+
3 rows in set (0.00 sec)



mysql> SELECT *, ROUND(amount) FROM sample341;
+---------+---------------+
| amount | ROUND(amount) |
+---------+---------------+
| 5961.60 | 5962 |
| 2138.40 | 2138 |
| 1080.00 | 1080 |
+---------+---------------+
3 rows in set (0.00 sec)



mysql> SELECT ROUND(amount) FROM sample341;
+---------------+
| ROUND(amount) |
+---------------+
| 5962 |
| 2138 |
| 1080 |
+---------------+
3 rows in set (0.00 sec)



소수점 아래 몇자리까지 사용할 것인지 결정

mysql> SELECT amount, ROUND(amount, 1) FROM sample341;
+---------+------------------+
| amount | ROUND(amount, 1) |
+---------+------------------+
| 5961.60 | 5961.6 |
| 2138.40 | 2138.4 |
| 1080.00 | 1080.0 |
+---------+------------------+
3 rows in set (0.00 sec)



10자리 크기로 반올림 할때는 - 를 붙여서 사용

mysql> SELECT amount, ROUND(amount, -2) FROM sample341;
+---------+-------------------+
| amount | ROUND(amount, -2) |
+---------+-------------------+
| 5961.60 | 6000 |
| 2138.40 | 2100 |
| 1080.00 | 1100 |
+---------+-------------------+
3 rows in set (0.00 sec)



문자열 연산


mysql> SELECT * FROM sample35;
+------+-------+----------+------+
| no | price | quantity | unit |
+------+-------+----------+------+
| 1 | 100 | 10 | 개 |
| 2 | 230 | 24 | 통 |
| 3 | 1980 | 1 | 장 |
+------+-------+----------+------+
3 rows in set (0.00 sec)



10, 24, 1은 수치형인데, unit의 문자열과 결합이 가능함. 

mysql> SELECT CONCAT(quantity, unit) FROM sample35;
+------------------------+
| CONCAT(quantity, unit) |
+------------------------+
| 10개 |
| 24통 |
| 1장 |
+------------------------+
3 rows in set (0.00 sec)



그 외에 , SUBSTRING, TRIM, CHARACTER_LENGTH 함수같은 것이 있음



날짜 연산
함수만 실행힐 수도 있는데, SELECT 뒤에 함수를 적어주면 됨, current_timestamp 도 함수인데, 인수를 전달할 필요가 없어서 괄호를 사용하지 않음.

mysql> SELECT CURRENT_TIMESTAMP;

+---------------------+
| current_timestamp |
+---------------------+
| 2020-03-11 08:41:58 |
+---------------------+
1 row in set (0.00 sec)



며칠 후 계산

mysql> SELECT CURRENT_DATE + INTERVAL 1 DAY;

+-------------------------------+
| CURRENT_DATE + INTERVAL 1 DAY |
+-------------------------------+
| 2020-03-12 |
+-------------------------------+
1 row in set (0.00 sec)



며칠 후 계산. 

mysql> SELECT CURRENT_DATE + INTERVAL 2 DAY;
+-------------------------------+
| CURRENT_DATE + INTERVAL 2 DAY |
+-------------------------------+
| 2020-03-13 |
+-------------------------------+
1 row in set (0.00 sec)

mysql>



날짜간 뺄셈. 특정일 사이 며칠이 흘렀는지 확인



mysql> SELECT DATEDIFF('2020-03-11', '2020-02-04');
+--------------------------------------+]
| DATEDIFF('2020-03-11', '2020-02-04') |
+--------------------------------------+
| 36 |
+--------------------------------------+
1 row in set (0.00 sec)

mysql>



CASE 문으로 데이터 변환하기


sample37을 보면 NULL이란 값이 들어 있는데, NULL을 0으로 변환하고자 함



mysql> SELECT * FROM sample37;

+------+
| a |
+------+
| 1 |
| 2 |
| NULL |
+------+
3 rows in set (0.01 sec)

CASE WHEN # IS @ THEN ^ ELSE & END 로 묶어주고, conv 라는 열을 만드는데, alias를 conv라고 이름 지음

mysql> SELECT a, CASE WHEN a IS NULL THEN 0 ELSE a END AS conv FROM sample37;

+------+------+
| a | conv |
+------+------+
| 1 | 1 |
| 2 | 2 |
| NULL | 0 |
+------+------+
3 rows in set (0.00 sec)



단순히 NULL을 0으로 바꾸는 목적이라면 COALACE를 사용할 수도 있다

mysql> SELECT a, COALESCE (a, 0) FROM sample37;

+------+-----------------+
| a | COALESCE (a, 0) |
+------+-----------------+
| 1 | 1 |
| 2 | 2 |
| NULL | 0 |
+------+-----------------+
3 rows in set (0.00 sec)



CASE, WHEN을 다중으로 사용하여 인코딩과 디코딩을 할 수 있음

mysql> SELECT a AS "코드",
-> CASE
-> WHEN a = 1 THEN '남자'
-> WHEN a = 2 THEN '여자'
-> ELSE '미지정'
-> END AS "성별" FROM sample37;

+--------+-----------+
| 코드 | 성별 |
+--------+-----------+
| 1 | 남자 |
| 2 | 여자 |
| NULL | 미지정 |
+--------+-----------+
3 rows in set (0.00 sec)



case뒤에 비교할 대상을 직접 넣을 수도 있음.

mysql> SELECT a AS "코드",
-> CASE a
-> WHEN 1 THEN '남자'
-> WHEN 2 THEN '여자'
-> ELSE '미지정'
-> END AS "성별" FROM sample37;

+--------+-----------+
| 코드 | 성별 |
+--------+-----------+
| 1 | 남자 |
| 2 | 여자 |
| NULL | 미지정 |
+--------+-----------+
3 rows in set (0.00 sec)

mysql>



행 추가하기 - INSERT


mysql> SELECT * FROM sample41;
Empty set (0.00 sec)

mysql> desc sample41;
+-------+-------------+------+-----+---------+-------+
| Field | Type | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| no | int(11) | NO | | NULL | |
| a | varchar(30) | YES | | NULL | |
| b | date | YES | | NULL | |
+-------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)



새로운 행을 추가함.

mysql> INSERT INTO sample41 VALUES(1,'ABC','2014-01-25');



Query OK, 1 row affected (0.01 sec)



추가한 다음에 결과를 보면 다음과 같음. 

mysql> SELECT * FROM sample41;

+----+------+------------+
| no | a | b |
+----+------+------------+
| 1 | ABC | 2014-01-25 |
+----+------+------------+
1 row in set (0.00 sec)



한행을 추가할때, 전체를 넣지 않고 특정 열만 선택해서 넣을 수도 있음

mysql> INSERT INTO sample41(a,no) VALUES('XYZ',2);


결과를 보면 b 열은 NULL로 들어가 있음


Query OK, 1 row affected (0.01 sec)

mysql> SELECT * FROM sample41;
+----+------+------------+
| no | a | b |
+----+------+------------+
| 1 | ABC | 2014-01-25 |
| 2 | XYZ | NULL |
+----+------+------------+
2 rows in set (0.00 sec)



모든 열을 NULL로 채우고 싶은 경우, 

mysql> INSERT INTO sample41(no, a, b) VALUES(NULL, NULL, NULL);


그런데 이렇게 하면 에러가 발생한다. 


ERROR 1048 (23000): Column 'no' cannot be null

description을 보면 속성에 NOT NULL로 되어 있다. 그래서 NULL이 입력이 안된다. 

mysql> desc sample41;
+-------+-------------+------+-----+---------+-------+
| Field | Type | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| no | int(11) | NO | | NULL | |
| a | varchar(30) | YES | | NULL | |
| b | date | YES | | NULL | |
+-------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)

mysql>



Default 값이 정의 되어 있는 경우, 



description을 보면, d 열이 0 으로 설정되어 있음. 

mysql> DESC sample411;
+-------+---------+------+-----+---------+-------+
| Field | Type | Null | Key | Default | Extra |
+-------+---------+------+-----+---------+-------+
| no | int(11) | NO | | NULL | |
| d | int(11) | YES | | 0 | |
+-------+---------+------+-----+---------+-------+
2 rows in set (0.00 sec)



그래서 명시적으로 d 열에 DEFAULT 를 넣어 주면, default로 설정된 0 이 들어가 있음을 확인할 수 있음. 

mysql> INSERT INTO sample411(no, d) VALUES(2, DEFAULT);

Query OK, 1 row affected (0.01 sec)

mysql> SELECT * FROM sample411;
+----+------+
| no | d |
+----+------+
| 1 | 1 |
| 2 | 0 |
+----+------+
2 rows in set (0.00 sec)



위는 명시적으로 DEFAULT를 넣은 것이고, 암묵적으로 넣을 수도 있음.

DEFAULT 라고 넣어주지 않았음에도, DEFAULT값이 들어가 있음. 

mysql> INSERT INTO sample411(no) VALUES(3);

Query OK, 1 row affected (0.00 sec)

mysql> SELECT * FROM sample411;
+----+------+
| no | d |
+----+------+
| 1 | 1 |
| 2 | 0 |
| 3 | 0 |
+----+------+
3 rows in set (0.00 sec)



삭제하기


mysql> SELECT * FROM sample41;
+----+------+------------+
| no | a | b |
+----+------+------------+
| 1 | ABC | 2014-01-25 |
| 2 | XYZ | NULL |
| 3 | XAR | NULL |
+----+------+------------+
3 rows in set (0.00 sec)



mysql> DELETE FROM sample41 WHERE no = 3;
Query OK, 1 row affected (0.00 sec)



DELETE FROM을 사용해서 삭제함. 



mysql> SELECT * FROM sample41;
+----+------+------------+
| no | a | b |
+----+------+------------+
| 1 | ABC | 2014-01-25 |
| 2 | XYZ | NULL |
+----+------+------------+
2 rows in set (0.00 sec)



데이터 갱신하기 - UPDATE


no =2 의 값을 보면 날짜가 NULL로 되어 있음. 



mysql> SELECT * FROM sample41 order by no;
+----+------+------------+
| no | a | b |
+----+------+------------+
| 1 | ABC | 2014-01-25 |
| 2 | XYZ | NULL |
+----+------+------------+
2 rows in set (0.00 sec)



no=2 에 대해서 날짜를 입력하면,

mysql> UPDATE sample41 SET b = '2014-09-04' WHERE no=2;

Query OK, 1 row affected (0.01 sec)
Rows matched: 1 Changed: 1 Warnings: 0

아래처럼 날짜기 입력된 것을 확인할 \

mysql> SELECT * FROM sample41 order by no;
+----+------+------------+
| no | a | b |
+----+------+------------+
| 1 | ABC | 2014-01-25 |
| 2 | XYZ | 2014-09-04 |
+----+------+------------+
2 rows in set (0.01 sec)

mysql>





복수열도 갱신할 수 있다.  (하나의 행에 대해서 여러 값을 변경하는 것)



행 개수 구하기 - COUNT


출력되는 결과의 개수를 구할 때

mysql> SELECT * FROM sample51;

Current database: sample

+------+------+----------+
| no | name | quantity |
+------+------+----------+
| 1 | A | 1 |
| 2 | A | 2 |
| 3 | B | 10 |
| 4 | C | 3 |
| 5 | NULL | NULL |
+------+------+----------+
5 rows in set (0.01 sec)

mysql> SELECT COUNT(*) FROM sample51;
+----------+
| COUNT(*) |
+----------+
| 5 |
+----------+
1 row in set (0.00 sec)



WHERE를 같이 쓸 수 있음



mysql> SELECT COUNT(*) FROM sample51 WHERE name='A';
+----------+
| COUNT(*) |
+----------+
| 2 |
+----------+
1 row in set (0.00 sec)



NULL은 집계에서 제외됨

mysql> SELECT COUNT(no), COUNT(name) FROM sample51;

+-----------+-------------+
| COUNT(no) | COUNT(name) |
+-----------+-------------+
| 5 | 4 |
+-----------+-------------+
1 row in set (0.00 sec)



중복 제거 할때

name의 전체를 출력하면 다음과 같음. 

mysql> SELECT ALL name FROM sample51;

+------+
Collaboration Center| name |
+------+
| A |
| A |
| B |
| C |
| NULL |
+------+
5 rows in set (0.00 sec)



그런데 중복을 제거하고 출력하려면, DISTINCT를 넣으면 됨

mysql> SELECT DISTINCT name FROM sample51;

+------+
| name |
+------+
| A |
| B |
| C |
| NULL |
+------+
4 rows in set (0.00 sec)



mysql> SELECT COUNT(ALL name), COUNT(DISTINCT name) FROM sample51;

+-----------------+----------------------+
| COUNT(ALL name) | COUNT(DISTINCT name) |
+-----------------+----------------------+
| 4 | 3 |
+-----------------+----------------------+
1 row in set (0.00 sec)

SUM, MIN/MAX, AVG
사용법은 간담함



mysql> SELECT SUM(quantity) FROM sample51;

+---------------+
| SUM(quantity) |
+---------------+
| 16 |
+---------------+
1 row in set (0.00 sec)

mysql> SELECT AVG(quantity) FROM sample51;

+---------------+
| AVG(quantity) |
+---------------+
| 4.0000 |
+---------------+
1 row in set (0.00 sec)



mysql> SELECT MIN(quantity) FROM sample51;
+---------------+
| MIN(quantity) |
+---------------+
| 1 |
+---------------+
1 row in set (0.00 sec)



mysql> SELECT MAX(quantity) FROM sample51;
+---------------+
| MAX(quantity) |
+---------------+
| 10 |
+---------------+
1 row in set (0.00 sec)



그룹화 - GROUP BY


name 열을 그룹화해 계산하기



mysql> SELECT name, COUNT(name), SUM(quantity) FROM sample51 GROUP BY name;


먼저 GROUP BY를 통해서 이름별로 A, B, C, NULL로 나뉘고,  이름별로 count를 하고 , sum을 처리함

+------+-------------+---------------+
| name | COUNT(name) | SUM(quantity) |
+------+-------------+---------------+
| NULL | 0 | NULL |
| A | 2 | 3 |
| B | 1 | 10 |
| C | 1 | 3 |
+------+-------------+---------------+
4 rows in set (0.00 sec)



WHERE 에서는 집계 함수를 사용할 수 없음

mysql> SELECT name, COUNT(name) FROM sample51 GROUP BY name;

+------+-------------+
| name | COUNT(name) |
+------+-------------+
| NULL | 0 |
| A | 2 |
| B | 1 |
| C | 1 |
+------+-------------+
4 rows in set (0.00 sec)



mysql> SELECT name, COUNT(name) FROM sample51 GROUP by name HAVING COUNT(name) = 1;

+------+-------------+
| name | COUNT(name) |
+------+-------------+
| B | 1 |
| C | 1 |
+------+-------------+
2 rows in set (0.00 sec)



결과값의 정렬

mysql> SELECT name, COUNT(name), SUM(quantity) FROM sample51 GROUP BY name ORDER BY SUM(quantity) DESC;
+------+-------------+---------------+
| name | COUNT(name) | SUM(quantity) |
+------+-------------+---------------+
| B | 1 | 10 |
| C | 1 | 3 |
| A | 2 | 3 |
| NULL | 0 | NULL |
+------+-------------+---------------+
4 rows in set (0.01 sec)



서브쿼리


DELETE의 WHERE 구에서 서브쿼리 사용하기



mysql> SELECT * FROM sample54;

+------+------+
| no | a |
+------+------+
| 1 | 100 |
| 2 | 900 |
| 3 | 20 |
| 4 | 80 |
+------+------+
4 rows in set (0.00 sec)



아래 명령이 동작해야 할 것 같지만 MySQL에서는 동작하지 않는다. 

mysql> DELETE FROM sample54 WHERE a = (SELECT MIN(a) FROM sample54);

ERROR 1093 (HY000): You can't specify target table 'sample54' for update in FROM clause



하나의 행이 반환되지만, 열리 복수인 패턴

> SELECT MIN(a), MAX(no) FROM sample54;

+--------+---------+
| MIN(a) | MAX(no) |
+--------+---------+
| 20 | 4 |
+--------+---------+
1 row in set (0.00 sec)



mysql> SELECT
-> (SELECT COUNT(*) FROM sample51) AS sq1,
-> (SELECT COUNT(*) FROM sample54) AS sq2;

+------+------+
| sq1 | sq2 |
+------+------+
| 5 | 4 |
+------+------+
1 row in set (0.00 sec)



insert 명령과 서브 쿼리를 같이 쓸 수 있음

mysql> SELECT * FROM sample541;
Empty set (0.00 sec)



mysql> INSERT INTO sample541 VALUES (
-> (SELECT COUNT(*) FROM sample51),
-> (SELECT COUNT(*) FROM sample54)
-> );

Query OK, 1 row affected (0.00 sec)

mysql> SELECT * FROM sample541;

+------+------+
| a | b |
+------+------+
| 5 | 4 |
+------+------+
1 row in set (0.00 sec)



상관 서브쿼리
mysql> SELECT * FROM sample551;
+------+------+
| no | a |
+------+------+
| 1 | NULL |
| 2 | NULL |
| 3 | NULL |
| 4 | NULL |
| 5 | NULL |
+------+------+
5 rows in set (0.00 sec)



mysql> SELECT * FROM sample552;
+------+
| no2 |
+------+
| 3 |
| 5 |
+------+
2 rows in set (0.00 sec)



EXISTS를 사용하기 - 데이터가 존재하는지 , 아닌지를 판별하기 위한 조건을 위해 EXISTS 술어를 사용한다.

mysql> UPDATE sample551 SET a = '있음' WHERE
-> EXISTS(SELECT * FROM sample552 WHERE no2 = no);
Query OK, 2 rows affected (0.00 sec)
Rows matched: 2 Changed: 2 Warnings: 0



mysql> mysql> SELECT * FROM sample551;
+------+--------+
| no | a |
+------+--------+
| 1 | NULL |
| 2 | NULL |
| 3 | 있음 |
| 4 | NULL |
| 5 | 있음 |
+------+--------+
5 rows in set (0.00 sec)



NOT EXISTS 도 사용 가능

mysql> UPDATE sample551 SET a = '없음' WHERE
-> NOT EXISTS (SELECT * FROM sample552 WHERE no2=no);

Query OK, 3 rows affected (0.00 sec)
Rows matched: 3 Changed: 3 Warnings: 0

mysql> SELECT * FROM sample551;
+------+--------+
| no | a |
+------+--------+
| 1 | 없음 |
| 2 | 없음 |
| 3 | 있음 |
| 4 | 없음 |
| 5 | 있음 |
+------+--------+
5 rows in set (0.00 sec)
