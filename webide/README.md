# webide
基于开源cloud9实现的IDE，本地路径： /Users/liangshanguang/Program/Web/webide/c9sdk

## 启用命令

```bash
docker run --security-opt seccomp=unconfined -it -d -p 9527:80 -v /root/l00379880/webide/workspace:/workspace/ waterknife/webide
```

## 下面是参考的资料

### cloud9相关的repo
+ 源码： https://github.com/c9/core
+ 容器： https://github.com/kdelfour/cloud9-docker
+ dockerhub: https://hub.docker.com/r/kdelfour/cloud9-docker

### docker部署cloud9
在线IDE https://www.jianshu.com/p/bcd3e476f129


### 源码部署cloud9
+ https://blog.csdn.net/ccaoee/article/details/55224884
+ 可能遇到amd-loader找不到的问题，见 https://github.com/c9/core/issues/432

## 后面的目标
+ 解决容器版本C++代码无法在线调试的问题(需要在容器内安装gdbserver)，这个需要较深的docker基础，需要好好补补，然后把cloud9-docker的dockerfile完善一下
+ 网站样式进行个性化定制
+ 引入鉴权模块
+ 代码提示尽量完善些
+ 把cloud9的terminal模块单独提取出来到webssh(因为它竟然可以缓存ssh会话session，再次打开terminal内容竟然不丢失，真是牛逼.唯一的缺点是中文会乱码--最新版的c9/core支持中文显示了，用最新的再做一次镜像)

