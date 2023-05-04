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

#### 配置cmakelists.txt
![image](https://user-images.githubusercontent.com/73093214/236188657-c8d72a0c-2626-4a9b-af56-a865f10c5bb2.png)

target_link加上openvino,并将三个路径更换为自己电脑对应的路径

#### 使用须知
推理文件基于1\*64\*64\*1(NWHC)的数字识别网络所写，其它的网络比如四点模型需要自行更换input_shape、和最后的结果获取等内容
此外，数字识别的数字图片的获取和预处理也需要自行加上，再丢入infer()函数进行推理
![image](https://user-images.githubusercontent.com/73093214/236189990-6bd10ac0-3697-45be-9cf2-0fd752d6ceee.png)


