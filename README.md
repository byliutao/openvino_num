#### 配置openvino环境

```
wget https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB
sudo apt-key add GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB
sudo apt-get install gnupg
echo "deb https://apt.repos.intel.com/openvino/2022 focal main" | sudo tee /etc/apt/sources.list.d/intel-openvino-2022.list
sudo apt update
apt-cache search openvino
sudo apt install openvino
```
#### 激活nuc上的gpu
```
mkdir neo
cd neo
wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.13463.18/intel-igc-core_1.0.13463.18_amd64.deb
wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.13463.18/intel-igc-opencl_1.0.13463.18_amd64.deb
wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-level-zero-gpu-dbgsym_1.3.25812.14_amd64.ddeb
wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-level-zero-gpu_1.3.25812.14_amd64.deb
wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-opencl-icd-dbgsym_23.09.25812.14_amd64.ddeb
wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-opencl-icd_23.09.25812.14_amd64.deb
wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/libigdgmm12_22.3.0_amd64.deb
wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/ww09.sum
sha256sum -c ww09.sum
sudo dpkg -i *.deb
```

#### 配置cmakelists.txt
![image](https://user-images.githubusercontent.com/73093214/236188657-c8d72a0c-2626-4a9b-af56-a865f10c5bb2.png)
![image](https://user-images.githubusercontent.com/73093214/236194104-b56de9cd-39f1-4384-9a59-2a35b188e302.png)

target_link加上openvino,并将三个路径更换为自己电脑对应的路径(前面一张图是我笔记本的位置，后一张是我测试的nuc的位置)

#### 使用须知
推理文件基于1\*64\*64\*1(NWHC)的数字识别网络所写，其它的网络比如四点模型需要自行更换input_shape、和最后的结果获取等内容
![image](https://user-images.githubusercontent.com/73093214/236189990-6bd10ac0-3697-45be-9cf2-0fd752d6ceee.png)

此外，数字识别的数字图片的获取和预处理也需要自行加上，再丢入infer()函数进行推理
默认使用的是CPU，如果要更换成GPU，将“CPU”改成“GPU”即可



