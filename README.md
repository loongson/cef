# cef for loongarch64(交叉编译)

* cef社区项目地址 - https://bitbucket.org/chromiumembedded/cef

# 当前分支
* **6312**
-------
# cef 源码编译（交叉编译）
* **编译系统：debian 12**
* **编译平台：x86_64**
* **目标平台：loongarch64**

## 1.制作cef所需交叉编译工具链
* **编译器：[llvm-project](https://github.com/llvm/llvm-project.git)**
* **sysroot：[loongson](https://github.com/loongson)仓库的[build-tools](https://github.com/loongson/build-tools)中的CLFS（clfs-loongarch64-system-x.x-sysroot.squashfs）**
------
### 1.1.制作sysroot
```
mkdir -p /opt/loongarch64/sysroot
mount clfs-loongarch64-system-x.x-sysroot.squashfs /mnt
cp -raf /mnt /opt/loongarch64/sysroot/
umount /mnt
```
* **sysroot保留以下目录结构：**
```
.
|-- lib -> usr/lib
|-- lib64 -> usr/lib64
`-- usr
    |-- include
    |-- lib
    |-- lib64
    `-- share
        |
        `-- pkgconfig
```
### 1.2.编译llvm-project (clang version 19.0.0git (https://github.com/llvm/llvm-project.git 7c4c274643cedcf9671e1db65361231a7d9bee70))
```
git clone https://github.com/llvm/llvm-project.git
cd llvm-project
git checkout 7c4c274643cedcf9671e1db65361231a7d9bee70
cmake -S llvm -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_INSTALL_PREFIX=/opt/loongarch64/llvm-19
cd build
ninja && ninja install
```
* **继续在llvm-project目录下编译compiler-rt:**
```
mkdir build-compiler-rt
cd build-compiler-rt
cmake ../compiler-rt/ -G Ninja -DCMAKE_AR=/opt/loongarch64/llvm-19/bin/llvm-ar -DCMAKE_ASM_COMPILER_TARGET=loongarch64-unknown-linux-gnu -DCMAKE_ASM_FLAGS="-mcmodel=medium -mabi=lp64d --target=loongarch64-linux-gnu --sysroot=/opt/loongarch64/sysroot" -DCMAKE_C_COMPILER=/opt/loongarch64/llvm-19/bin/clang -DCMAKE_C_COMPILER_TARGET=loongarch64-unknown-linux-gnu -DCMAKE_C_FLAGS="-mcmodel=medium -mabi=lp64d --target=loongarch64-linux-gnu --sysroot=/opt/loongarch64/sysroot" -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" -DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=ON -DCMAKE_NM=/opt/loongarch64/llvm-19/bin/llvm-nm -DCMAKE_RANLIB=/opt/loongarch64/llvm-19/bin/llvm-ranlib -DCOMPILER_RT_BUILD_BUILTINS=ON  -DCOMPILER_RT_BUILD_LIBFUZZER=OFF -DCOMPILER_RT_BUILD_MEMPROF=OFF -DCOMPILER_RT_BUILD_PROFILE=ON -DCOMPILER_RT_BUILD_SANITIZERS=OFF -DCOMPILER_RT_BUILD_XRAY=OFF -DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON -DLLVM_CMAKE_DIR=/opt/loongarch64/llvm-19 -DCMAKE_INSTALL_PREFIX=/opt/loongarch64/llvm-19/lib/clang/19
rm ./* -rf
```
* **编译x64的compiler-rt:**
```
cmake ../compiler-rt/ -G Ninja -DCMAKE_AR=/opt/loongarch64/llvm-19/bin/llvm-ar -DCMAKE_ASM_COMPILER_TARGET=x86_64-unknown-linux-gnu -DCMAKE_ASM_FLAGS="" -DCMAKE_C_COMPILER=/opt/loongarch64/llvm-19/bin/clang -DCMAKE_C_COMPILER_TARGET=x86_64-unknown-linux-gnu -DCMAKE_C_FLAGS="" -DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=ON -DCMAKE_NM=/opt/loongarch64/llvm-19/bin/llvm-nm -DCMAKE_RANLIB=/opt/loongarch64/llvm-19/bin/llvm-ranlib -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" -DCOMPILER_RT_BUILD_BUILTINS=ON  -DCOMPILER_RT_BUILD_LIBFUZZER=OFF -DCOMPILER_RT_BUILD_MEMPROF=OFF -DCOMPILER_RT_BUILD_PROFILE=ON -DCOMPILER_RT_BUILD_SANITIZERS=OFF -DCOMPILER_RT_BUILD_XRAY=OFF -DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON -DLLVM_CMAKE_DIR=/opt/loongarch64/llvm-19 -DCMAKE_INSTALL_PREFIX=/opt/loongarch64/llvm-19/lib/clang/19
ninja && ninja install
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
python automate-git.py --url=https://github.com/loongson/cef.git --download-dir=/path/to/code --depot-tools-dir=/path/to/code/depot_tools --branch=6312 --no-build --no-distrib
```
## 3.编译cef
### 3.1.将depot_tools加入环境变量
```
export PATH=$PATH:/path/to/code/depot_tools
```
### 3.2.生成编译工程文件
```
cd /path/to/code/chromium/src/cef
GN_DEFINES='target_cpu="loong64" clang_use_chrome_plugins=false treat_warnings_as_errors=false dcheck_always_on=false use_gold=false use_system_libffi=true clang_base_path="/opt/loongarch64/llvm-19" target_sysroot="/opt/loongarch64/sysroot"' ./cef_create_projects.sh
```
* 也可以将CLFS解压到/path/to/code/chromium/src/build/linux/debian_bullseye_loong64-sysroot下，无需在GN_DEFINES中设置target_sysroot.
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
