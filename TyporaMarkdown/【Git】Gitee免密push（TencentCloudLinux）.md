![image-20230503010614245](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230503010614245.png)

## 前提：

我用的是腾讯云的Centos(Linux)服务器
我创建好了仓库
我配置过git 可以正常用密码push
以上自行解决
我们直接配置公钥解决免密push

## 1.在服务器上创建公钥
在用户根目录创建 公钥 邮箱写自己的 随意写 我写的是gitee绑定的邮箱
```
ssh-keygen -t ed25519 -C "820649664@qq.com"
```
回车三次形成密钥
## 2.查看.ssh
.ssh在 你的仓库文件同目录下
例如我的本地文件夹是GiteeLinux，.ssh跟GieeLinux同目录是隐藏文件
```
ll .ssh
```
![image-20230503010654810](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230503010654810.png)
id_ed25519是私钥
id_ed25519.pub是公钥

## 3.查看公钥
```
cat id_ed25519.pub
```
复制ssh-ed25519 ....820649664@qq.com的密钥
## 4.去gitee中添加密钥
将复制的公钥 去【设置】>【SSH公钥】>【添加】
![image-20230503010813322](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230503010813322.png)

## 5.回终端确定
在终端执行以下命令
```
ssh -T git@gitee.com
```
回复yes
![image-20230503010942877](https://picgo-1311604203.cos.ap-beijing.myqcloud.com/imageimage-20230503010942877.png)


如果成功则出现以下文字
> Warning: Permanently added 'gitee.com,212.64.63.215' (ECDSA) to the list of known hosts.
> Hi Meaning! You've successfully authenticated, but GITEE.COM does not provide shell access.

## 6.恭喜你可以免密push了