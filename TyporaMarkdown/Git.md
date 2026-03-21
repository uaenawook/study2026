# Git

## 安装

### git官网

https://git-scm.com/

### git下载

![image-20221202104010743](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221202104010743.png)

### git安装

如果安装小乌龟 （图形化界面），则默认安装在`C盘`

**一路`next`**

#### 小乌龟安装

下载地址：https://www.lanzouw.com/iLKNxwpby5c     密码：iluo12



##### 填写邮箱

![image-20221202104805091](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221202104805091.png)

![image-20221202105533485](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221202105533485.png)

一路next 就好了

## 使用

![image-20221202110258225](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221202110258225.png)

9

## 暂存区

#### 查看暂存区状态

```c
git status
```

#### 删除暂存区的文件

```c
git rm --cached test.txt
```

#### 提交暂存区

```c
git commit -m "日志" test.txt
```

![image-20221116160727206](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116160727206.png)

![image-20221116161400098](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116161400098.png)

## 版本控制

#### 查看版本信息

```c
git reflog	简略
git log		详细
```

![image-20221116161755393](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116161755393.png)

#### 版本穿梭

```c
git reset --hard 版本号
```

![image-20221116162551267](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116162551267.png)

#### 查看版本号所在文件

在隐藏目录的 `.git\refs\heads`

![image-20221116162804877](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116162804877.png)

## 分支控制

#### 查看分支

```c
git branch -v
```

![image-20221116164145631](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116164145631.png)

#### 添加分支

```c
git branch 分支名
```

![image-20221116164622473](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116164622473.png)

#### 切换分支

```c
git checkout hot-fix
```

![image-20221116164905733](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116164905733.png)

![image-20221116165422865](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116165422865.png)

#### 合并分支

```c
git merge 分支名
```

![image-20221116170334973](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116170334973.png)

#### 合并冲突

```c
git merge hot-fix
```

条件 代码在master分支修改 在hot-fix分支修改

**master**

```c
hello HH! 2
hello HH! 3
hello HH!
hello HH!
hello HH! master test
hello HH!
```

**hot-fix**

```c
hello HH! 2
hello HH! 3
hello HH!
hello HH!
hello HH!
hello HH! hot-fix text
```

**合并后提示：合并冲突**

```c
uaena@DESKTOP-OEIGGLC MINGW64 /e/Storeroom/Gitee/git-demo (master)
$ git merge hot-fix
Auto-merging test.txt
CONFLICT (content): Merge conflict in test.txt
Automatic merge failed; fix conflicts and then commit the result.

在text.txt中合并冲突
自动合并失败;修复冲突，然后提交结果
```

**此时文件内的显示**

![image-20221116172319048](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116172319048.png)

**手动合并，把没用的删除**

![image-20221116173230571](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116173230571.png)

**合并后 重新add**

**重新commit 但是不要写 文件名，因为会产生歧义**

![image-20221116173804816](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116173804816.png)

**==注意：合并只会修改当前分支，不会修改合并过来的分支==**

![image-20221116173601852](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20221116173601852.png)