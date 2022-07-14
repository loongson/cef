# cef for loongarch64(交叉编译)

* cef社区项目地址 - https://bitbucket.org/chromiumembedded/cef

# 目前支持分支
* **4844**
-------
# cef 源码编译（交叉编译）
* **编译平台：x86_64**
* **目标平台：loongarch64**

## 1.制作cef所需交叉编译工具链
* **编译器：[loongson](https://github.com/loongson)仓库的[binutils-gdb](https://github.com/loongson/binutils-gdb)和[llvm-project](https://github.com/loongson/llvm-project)**
* **sysroot：[loongson](https://github.com/loongson)仓库的[build-tools](https://github.com/loongson/build-tools)中的CLFS（loongarch64-clfs-system-x.x.tar.bz2）**
------
### 1.1.编译llvm-project
```
git clone https://github.com/loongson/llvm-project.git
cd llvm-project
cmake -S llvm -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang" -DCMAKE_INSTALL_PREFIX=/opt/loongarch64/toolchain -DLLVM_DEFAULT_TARGET_TRIPLE="x86_64-linux-gnu;loongarch64-linux-gnu"
cd build
ninja && ninja install
```
### 1.2.编译binutils-gdb
```
git clone https://github.com/loongson/binutils-gdb.git
cd binutils-gdb
mkdir build
cd build
../configure --prefix=/opt/loongarch64/toolchain --target=x86_64-linux-gnu --disable-nls --enable-shared --enable-64-bit-bfd --disable-werror
make && make install

rm ./* -rf
../configure --prefix=/opt/loongarch64/toolchain --target=loongarch64-linux-gnu --with-lib-path=/usr/lib64:/lib64:/usr/lib:/lib --disable-nls --enable-shared --enable-64-bit-bfd --disable-werror
make && make install
```
### 1.3.制作sysroot
```
mkdir -p /opt/loongarch64/sysroot
tar xvf loongarch64-clfs-system-x.x.tar.bz2 -C /opt/loongarch64/sysroot
```
### 1.4.将交叉编译工具链加入环境变量
```
export PATH=$PATH:/opt/loongarch64/toolchain/bin
```
## 2.代码拉取
* **代码目录结构：**
```
.
└── code
    ├── automate
    ├── cef
    ├── chromium
    └── depot_tools
```
* 在automate目录中下载代码拉取脚本[automate-git.py](https://bitbucket.org/chromiumembedded/cef/raw/master/tools/automate/automate-git.py)
```
automate/
└── automate-git.py
```
* 获取源码及依赖(在automate目录下执行)
```
python automate-git.py --url=https://github.com/loongson/cef.git --download-dir=/path/to/code --depot-tools-dir=/path/to/code/depot_tools --branch=4844 --no-build --no-distrib
```
## 3.编译cef
### 3.1.将depot_tools加入环境变量
```
export PATH=$PATH:/path/to/code/depot_tools
```
### 3.2.生成编译工程文件
```
cd /path/to/code/chromium/src/cef
GN_DEFINES='target_cpu="loong64" clang_use_chrome_plugins=false enable_swiftshader=false angle_enable_swiftshader=false enable_swiftshader_vulkan=false treat_warnings_as_errors=false dcheck_always_on=false use_gold=false use_lld=false clang_base_path="/opt/loongarch64/toolchain" target_sysroot="/opt/loongarch64/sysroot"' ./cef_create_projects.sh
```
* 也可以将CLFS解压到/path/to/code/chromium/src/build/linux/debian_sid_loong64-sysroot下，无需在GN_DEFINES中设置target_sysroot.
### 3.3.执行编译
```
cd /path/to/code/chromium/src
ninja -C out/Release cef chrome_sandbox
ninja -C out/Debug cef chrome_sandbox
```
### 3.4.cef打包
```
cd /path/to/code/chromium/cef
python tools/make_distrib.py --ninja-build --loong64-build --output-dir /path/to/
```
