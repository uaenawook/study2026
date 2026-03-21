# 二叉树进阶

## 二叉搜索树

### 概念

左子树都小于跟，右子树大于根，子树同样满足上述条件。

![image-20220812011747276](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220812011747276.png)

![image-20220812012326665](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20220812012326665.png)

此时这种情况就需要AVLTree、RBTree

### 搜索次数 

最多查找高度次 O(N)

| 1000个数 | 10次 |
| -------- | ---- |
| 100w个数 | 20次 |
| 10亿数   | 30次 |
| 20亿数   | 31次 |

### 排序

中序遍历就是排序
