### 기본 명령어
* git log --name-only # 이름만 보임
* git log -p           # 좀더 자세한 정보가 보임
* git diff             # commit 간의 차이점을 보여줌
* git log --parents    # 해당 커밋의 부모 커밋을 보여줌

### 기본 개념
git 은 commit 마다 snapshot을 저장함.
 다시 말해서 파일이 변경되면 그 파일 자체를 저장함.
변경되지 않은 파일은 원본 파일의 링크만 저장함

git 은 text 기반이라서 각각의 snapshot에서는 압축해서 저장함. 문제는 큰 binary 파일을 저장할때.
그래서 LFS(large file system)같은 것이 나옴

### Branch
독립적인 개발 공간, 브랜치를 이용하면 병렬적으로 개발 가능  
브랜치는 커밋을 가리키는 포인터, 커밋이 생성되면 자동으로 업데이트  
브랜치를 만드는 멋은 새로운 포인터를 만드는 과정(속도가 빠름)

* git branch
* git log --decorate
  master branch가 어떤 커밋을 가르키는지 .
* git branch ABC
  ABC 란 branch를 만듬
* git checkout ABC
  ABC 란 branch로 이동. 여기서 git log --decorate로 어떤 커밋을 가르키는지 확인 가능


### fetch
meta data를 업데이트를 하는 것인데, 항상 fetch를 사용해서 최신 정보로 업데이트해야함
git fetch origin master
git log origin/master


### tag
* git tag REL_01
* git tag -l
* git tag REL_02 commit # 특정 commit id 기준으로 tag를 만들 수 있음


### git state 
1. working directory
2. staging area
3. database area


* git add -A
 workding directory에 있는 수정한 모든 파일을 staging
* git add -u 
  신규 파일 제외
* git add *
  숨김 파일 제외
* git add .
  삭제한 파일 제외

* git diff --cached
staging에 어떤 수정 사항이 있는지 확인 가능

* git remote -v 
내가 어디서 소스를 clone 했는지 알 수 있음


* git push origin HEAD:refs/for/master


* git clone
fetch + checkout
fetch는 meta 정보만 있고 실제 파일은 없는 것임. 그래서 소스 받으면 처음엔 meta 만 받고 다음에 checkout 하는 것임

* git commit --amend

* git log --decorate --topo-order
  커밋이 생성된 순서가 아니라 반영된 순서로 보여줌
  
  
origin 은 단지 alias 임. 그렇지 않으면 전체 주소를 다 적어야 함.
``` bash
~/practice$ git remote -v
(base) D:\dojo\github\ml>git remote -v
origin  https://github.com/neguri/ml.git (fetch)
origin  https://github.com/neguri/ml.git (push)
```  

* git reset --hard <commit>
  origin/master 와 같이 하면 최신 소스와 맞춰짐. git pull 이 최신이 아님.
  하지만 reset 하게 되면 git history가 없어지므로 git revert를 사용하는 것이 좋음
  
 
다른 사람의 commit에 대해 dependecny가 있는 경우 git pull 로 한 다음에 올릴 수 있음
git cherry-pick 도 가능하지만. 이렇게 하면 commit id가 하나더 생성되고, 다른 사람의 commit의 patchset 이 변경됨